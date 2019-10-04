/**
	This file is a copy of PrintCalEpiphany.java. 
	It supports the commlib that is developed in july 2017. 
	The file is created by Süleyman Savas.

	This backend generates a hybrid of C and Chisel. The actions starting
	with __acc__ will be generated as accelerators.
**/
package hh.backend.c;

import hh.AST.syntaxtree.*;
import hh.common.translator.VisitorActor;
import hh.common.translator.VisitorExp;
import hh.common.translator.VisitorStm;
import hh.common.translator.VisitorType;
import hh.simplenet.*;

import java.io.PrintWriter;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;




public class PrettyPrintChisel implements 
VisitorActor<Object,Object>, VisitorType<Object,Object>, VisitorStm<Object,Object>, VisitorExp<Object,Object>
{

	private String indent 		= "";
	
	private String comint 		= "";
	private boolean duplicatVar, oldval, isGlobal;
	private boolean bAddtimer			= false;
	public ExpList globExp				= new ExpList();
	public IdentifierList globId		= new IdentifierList(); 
	public HashSet<String> hsInclude	= new HashSet<String>();
	public String cCode 				= "";
	public String chiselCode 			= "";
	public String sActionInsOuts		= "";
	public String sActionInsOutsInts	= "";
	public String sInclude				= "";
	public String instName				= "";
	public String typeName				= "";
	public ArrayList<Channel> cInput 	= new ArrayList<Channel>();
	public ArrayList<Channel> cOutput 	= new ArrayList<Channel>();

	public HashMap<String, ArrayList<String>> inputCons;
	public HashMap<String, ArrayList<String>> outputCons;
	public boolean printPort;
	public int tmpInt = 0;
	
	private HashMap<String, String> outputVarDeclType    = new HashMap<String, String>();	// The list to hold the variable declaration type of the output (type options: simple and complex) <id, type>
	private HashMap<String, String> arrayAndIndexWritten = new HashMap<String, String>(); // The list of arrays and indices (index calculations should be done outside the accelerator)
	private HashMap<String, String> arrayAndIndexRead    = new HashMap<String, String>();
	private ArrayList<String> arrayIndices               = new ArrayList<String>();
	private ArrayList<String> variablesRead              = new ArrayList<String>();		// The list of variables which are read in an action
	private ArrayList<String> variablesWritten           = new ArrayList<String>();		// The list of variables which are modified in an action
	private ArrayList<String> moduleInputs               = new ArrayList<String>();
	private ArrayList<String> inputs32Bits               = new ArrayList<String>();
	private ArrayList<String> inputs64Bits               = new ArrayList<String>();
	private ArrayList<String> moduleOutputs              = new ArrayList<String>();
	private ArrayList<String> actionGlobalVars           = new ArrayList<String>();		// The list of variables which are global in an action
	private HashMap<String, Integer> varVersions         = new HashMap<String, Integer>();	// variable versions for SSA
	private ArrayList<String> phiVariables               = new ArrayList<String>();
	private HashMap<String, Integer> globalDelays        = new HashMap<String, Integer>();	// This hashmap will keep the cycle delay for each variable that is output of a component with pipeline stages
//String format is: n.i.s + "_v" + varVersions.get(n.i.s)
	
	private int localDelay;																// This integer is used for calculating the total delay of an output (localDelay = delay of the operation)
	// cycle delays for each component (these numbers are library dependent)
	private int complexMulDelay  = 4;
	private int complexAddDelay  = 3;
	private int complexDivDelay  = 9;
	private int complexSubDelay  = 3;
	//private int complexSqrtDelay = 9; //mult + add + sqrt (should be 10?)
	private int complexCMagDelay = 9;
	private int floatMulDelay  = 2;
	private int floatAddDelay  = 3;
	private int floatDivDelay  = 5;
	private int floatSubDelay  = 3;
	private int floatSqrtDelay = 5;
	
	private ArrayList<Integer> moduleInputsSizes = new ArrayList<Integer>();
	private ArrayList<Integer> moduleOutputsSizes = new ArrayList<Integer>();
	
	public NetworkMap networkMap 	  = null;
	public SEQ_Actor actorInProcess   = null;
	public ActionDecl actionInProcess = null;
	private String chiselIndent       = "";
	private boolean checkchannel 	  = true;
	private boolean printChisel 	  = false;
	private int divCounter 			  = 0;
	private int subCounter 			  = 0;	// Float subtracter counter
	private int addCounter 			  = 0;
	private int mulCounter 			  = 0;
	private int sqrtCounter			  = 0;
	private int C_magCounter          = 0;
	private int C_divCounter 	      = 0;
	private int C_subCounter 		  = 0;	// Complex subtracter counter
	private int C_addCounter 		  = 0;
	private int C_mulCounter 		  = 0;
	private boolean isAssignLeft      = false;
	private boolean isFirstIteration  = false;
	private boolean newBlock          = false;
	
	// Complex variables support
	private boolean complexMulFlag = false;
	private boolean complexDivFlag = false;
	private boolean complexAddFlag = false;
	private boolean complexSubFlag = false;
	
	public static int actorNumber = -1;
	
	public PrettyPrintChisel(NetworkMap networkMap){
		
		this.networkMap = networkMap;
	}
	// MainClass m;
	// ClassDeclList cl;
	public Object visit(SEQ_Actor n, Object env) {
		// Reset the complex operation flags for each actor
		complexMulFlag = false;
		complexDivFlag = false;
		complexAddFlag = false;
		complexSubFlag = false;
		
		actorNumber++;
		actorInProcess = n;
		instName = n.i.s;
		typeName = n.it.s;
		System.out.println("Actor name " + instName);
		inputCons = n.inputConnections;
		outputCons = n.outputConnections;		
		int j;
		ArrayList<String> multiConne = new ArrayList<String>();
		
		// Input port declarations
		if(n.input != null)
			if(n.input.size() > 0){
				cCode = cCode +("//InputPorts\n");

				for( j = 0; j < n.input.size() - 1; j++ ){
					multiConne.clear();
					multiConne.addAll((ArrayList<String>) n.input.get(j).accept(this,env));
					for(String s:multiConne)
						//cCode = cCode + s + ", ";
						if(actorNumber > 0)
							cCode = cCode + "uint64_t " + instName + "_" + s + " SECTION(\".core" + actorNumber + ".data\"" + ");\n";	// TODO the type should be dynamic
						else
							cCode = cCode + "uint64_t " + instName + "_" + s + ";\n";
				}
				multiConne.clear();
				multiConne.addAll((ArrayList<String>) n.input.get(j).accept(this,env));
				for( j = 0; j < multiConne.size() - 1; j++ )
					//cCode = cCode + multiConne.get(j)+ ", ";
					if(actorNumber > 0)
						cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j)+ " SECTION(\".core" + actorNumber + ".data\"" + ");\n";	// TODO the type should be dynamic
					else
						cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j)+  ";\n";
				
				//cCode = cCode  + multiConne.get(j)+";";
				if(actorNumber > 0)
					cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j) + " SECTION(\".core" + actorNumber + ".data\"" + ");\n";	// TODO the type should be dynamic
				else
					cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j) + ";\n";

			}
		
		// Output port declarations
		if(n.output != null)
			if(n.output.size() > 0){

				cCode = cCode +("\n//OutputPorts\n");

				for( j = 0; j < n.output.size() - 1; j++){
					multiConne.clear();
					multiConne.addAll((ArrayList<String>) n.output.get(j).accept(this,env));
					for(String s:multiConne)
						//cCode = cCode +  s+ ", ";
						if(actorNumber > 0)
							cCode = cCode + "uint64_t " + instName + "_" + s + " SECTION(\".core" + actorNumber + ".data\"" + ");\n";
						else
							cCode = cCode + "uint64_t " + instName + "_" + s + ";\n";
				}
				multiConne.clear();
				multiConne.addAll((ArrayList<String>) n.output.get(j).accept(this,env));
				for( j=0;j<multiConne.size()-1;j++)
					//cCode = cCode +  multiConne.get(j)+ ", ";
					if(actorNumber > 0)
						cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j) + " SECTION(\".core" + actorNumber + ".data\"" + ");\n";
					else
						cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j) + ";\n";
				//cCode = cCode + multiConne.get(j)+";";
				if(actorNumber > 0)
					cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j) + " SECTION(\".core" + actorNumber + ".data\"" + ");\n";
				else
					cCode = cCode + "uint64_t " + instName + "_" + multiConne.get(j) + ";\n";
			}
		
		cCode = cCode +"\n";// extern int "+n.i.s +"_State;\n";
		isGlobal = true;
		for(VarDecl vr : n.vl){
			comint = "";
			//			cCode = cCode +;
			vr.accept(this, "static ");
			cCode = cCode +("\n");
		}
		
		if(bAddtimer)
			cCode = cCode +("\nint core_counter = 0;");
		isGlobal = false;

		if(n.pros != null)
			for(ProcedureDecl pro : n.pros){
				cCode = cCode + "static ";
				
				if(pro.t != null)
					pro.t.accept(this, env);
				else 
					cCode = cCode + ("void");
				
				cCode = cCode + (" ");
				pro.i.accept(this, env);
				cCode = cCode +(" (");
				
				if(pro.fl != null)
					for ( int i = 0; i < pro.fl.size(); i++ ) {
						pro.fl.get(i).accept(this,env);
						if (i+1 < pro.fl.size()) { cCode = cCode +(", "); }
					}
				
				cCode = cCode +(");\n");
			}

		// Function declarations
		if(n.funs !=null)
			for(FunctionDecl fun : n.funs){
				cCode = cCode +"static ";
				
				if(fun.t != null)
					fun.t.accept(this,env);
				else 
					cCode = cCode + ("int");
				
				cCode = cCode + (" ");
				fun.i.accept(this,env);
				cCode = cCode + (" (");
				
				if(fun.fl != null)
					for ( int i = 0; i < fun.fl.size(); i++ ) {
						fun.fl.get(i).accept(this,env);
						if (i+1 < fun.fl.size()) { cCode = cCode +(", "); }
					}
				
				cCode = cCode +(");\n");
			}


		//	cCode = cCode + "static int (*next_state) (void) = " +typeName + "_State0;\n ";
		/*for(PortHH po:n.output)
			cCode = cCode + "extern FILE *"+ typeName+"_"+ po.i.s +";\n";*/
		//	cCode = cCode + "extern FILE *"+ typeName+";\n";
		Integer actionNo = 0;
		for(ActionDecl ac: n.acs)
			ac.accept(this, actionNo++);

		if(n.funs != null)
			for(FunctionDecl fun : n.funs)
				fun.accept(this, env);
		
		if(n.pros != null)
			for(ProcedureDecl pro : n.pros)
				pro.accept(this, env);
		
		if(n.grs != null)
			for(GuardDecl gr : n.grs)
				gr.accept(this, env);


		if(globId.size() != 0){

			cCode = cCode + "\nint int_state_vars_"+n.i.s+" = 1;\nvoid initStateVars"+n.i.s+"() {\n";
			
			for( j = 0; j < globId.size(); j++){
				if(globExp.get(j) instanceof ListComprehension){
					//	ListComprehension gex =(ListComprehension)globExp.get(j);
					//	PrintListComp(globId.get(j),gex,env);
					//					globId.get(j).accept(this, env);
					//					cCode = cCode +" = ";

					globExp.get(j).accept(this,globId.get(j).s);
					//	cCode = cCode +  "\n DisplayListComprehension \n";
					comint="";


					//					DisplayListComprehension((ListComprehension)globExp.get(j),(Object)globId.get(j).s);


				}
				else {
					globId.get(j).accept(this, env);
					cCode = cCode +(" = ");
					globExp.get(j).accept(this, env);
					cCode = cCode +(";\n");
				}

			}
			//			for(int im=0; im<globVal.size();im++){
			//				globVal.
			//			}


			cCode = cCode +("\n"+"}\n");

		}

		n.actionScheduler.accept(this, env);
		String timerDone = "if(core_counter >= myNum){\n"
				+ "#if COMP_TIME_ONLY\n"
				+ "	shm.comp_timer[core_id] = timerValue;\n"
				+ "#else\n"
				+ "	shm.comp_timer[core_id] = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);\n"
				+ "#endif\n"
				+ "	shm.done[core_id] = 1;\n}\n";		

		if(bAddtimer){
			int i = cCode.lastIndexOf("goto");
			String sStart = cCode.substring(0, i);
			String sEnd = cCode.substring(i);
			cCode = sStart + timerDone + sEnd;
		}

		/* 
		 * Addition by Süleyman
		 * Generate channel table for each core when the backend is PicoRV
		 */
		String chTable = networkMap.channelTablePerCore(n.i.s);
		//cCode = chTable + "\n" + "#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))\n\n" + cCode;
		/* End of addition */
		
		// Memory operations for complex functions (real and imaginary parts of the number are combined in a uint64_t)
		// the higher address holds real part whereas the lower address holds imaginary part
		String memoryOperationsPart1 = "\tuint64_t result;\n"
				+ "\tfloat in1_real, in1_imag, in2_real, in2_imag, result_real, result_imag;\n"
				+ "\tmemcpy(&in1_imag, &in1, 4);\n"
				+ "\tmemcpy(&in1_real, ((char*)&in1) + 4, 4);\n"
				+ "\tmemcpy(&in2_imag, &in2, 4);\n"
				+ "\tmemcpy(&in2_real, ((char*)&in2) + 4, 4);\n";
		
		String memoryOperationsPart2 = "\tmemcpy(&result, &result_imag, 4);\n"
				+ "\tmemcpy(((char*)&result) + 4, &result_real, 4);\n "
				+ "\treturn(result);\n"
				+ "}\n";
		
		if(complexSubFlag){
			String complexOperation = null;
			
			complexOperation = "uint64_t ComplexSub(uint64_t in1, uint64_t in2){\n"
					+ memoryOperationsPart1
					+ "\tresult_real = in1_real - in2_real;\n"
					+ "\tresult_imag = in1_imag - in2_imag;\n"
					+ memoryOperationsPart2;
			
			cCode = complexOperation + cCode;
		}
			
		if(complexAddFlag){
			String complexOperation = null;
			
			complexOperation = "uint64_t ComplexAdd(uint64_t in1, uint64_t in2){\n"
					+ memoryOperationsPart1
					+ "\tresult_real = in1_real + in2_real\n;"
					+ "\tresult_imag = in1_imag + in2_imag\n;"
					+ memoryOperationsPart2;
			
			cCode = complexOperation + cCode;
		}
			
		if(complexMulFlag){
			String complexOperation = null;
			
			complexOperation = "uint64_t ComplexMul(uint64_t in1, uint64_t in2){\n"
					+ memoryOperationsPart1  
					+ "\tresult_real = in1_real * in2_real - in1_imag * in2_imag;\n"
					+ "\tresult_imag = in1_real * in2_imag + in1_imag * in2_real;\n"
					+ memoryOperationsPart2;
			
			
			cCode = complexOperation + cCode;
		}
			
		if(complexDivFlag){
			String complexOperation = null;
			
			complexOperation = "uint64_t ComplexDiv(uint64_t in1, uint64_t in2){\n"
					+ memoryOperationsPart1
					+ "\tfloat denom = in2_real * in2_real + in2_imag + in2_imag + 1.2e-63;  /*to prevent division by zero*/ \n\n"
					+ "\tresult_real = (in1_real * in2_real + in1_imag * in2_imag) / denom;\n"
					+ "\tresult_imag = (in1_imag * in2_real - in1_real * in2_imag) / denom;\n"
					+ memoryOperationsPart2;
			
			cCode = complexOperation + cCode;
		}
		
		// Add the struct for Complex type if it is used.
		if(complexAddFlag || complexDivFlag || complexMulFlag || complexSubFlag){
			String complexStruct = null;
			
			complexStruct = "typedef struct{\n"
					+ "\tfloat real;\n"
					+ "\tfloat imag;\n"
					+ "}Complex;\n";
			//cCode = complexStruct + cCode;
			sInclude = sInclude + "#include <string.h>\n";
		}
			
		cCode = "//code from " + n.it.s + ".cal, instance " + n.i.s + "" +
				"\n#include <stdint.h>\n" +
				sInclude + "\n" + cCode;
		
		//		"/* shared memory overlay, and core indices */\n" +
		//		"volatile shm_t shm SECTION(\".shared_dram\");\n" +
		//		"char commlib_heap[HEAP_SZ_"+n.i.s +"];\n"+				
		//		cCode;
				
		ArrayList<String> multiLang = new ArrayList<String>();

		multiLang.add(cCode);
		multiLang.add(chiselCode);
	
		//return cCode;
		return multiLang;
	}


	private void DisplayListComprehension(ListComprehension n,	Object env) {
		String var=(String)env;
		ArrayList<String> vars= new ArrayList<String>();
		ArrayList<ListComprehension> cmps= new ArrayList<ListComprehension>();
		ExpList exEls= new ExpList();
		ListOfListCompGen gens = n.compGen;

		ExpList exs =n.eles;
		//	Exp exp=null;
		cmps.add(n);

		int exseles=exs.size();
		while(exseles>0){
			for(int iels=0; iels<exs.size();iels++){
				if(exs.get(iels) instanceof ListComprehension){
					ListComprehension lc =(ListComprehension)exs.get(iels);
					cmps.add(lc);
					exs=lc.eles;
					exseles=exs.size();
				}
				else{
					//					System.out.println(iels);				
					exEls.add(exs.get(iels));
					exseles--;
				}
			}

		}
		//TODO was only > 
		if(cmps.size()>0){
			for(int ic=cmps.size()-1;ic>=0;ic--)
			{
				ListComprehension lc=cmps.get(ic);
				if(lc.compGen !=null){
					for(int icg=0; icg <lc.compGen.size();icg++){
						if(lc.compGen.get(icg).colExp instanceof GenIntegers)
							vars.add((String)lc.compGen.get(icg).accept(this,env));
						else
							lc.compGen.get(icg).accept(this, env);
					}

				}
			}

			if(vars.size()>0){
				cCode = cCode +var;
				for(int is=vars.size()-1;is>=0;is--){
					String sIndex =vars.get(is);
					cCode = cCode +  "[" +sIndex +"]";
				}
				cCode = cCode + " = ";
				if(exEls.size()>0)
					exEls.get(0).accept(this, env);
				else
					cCode = cCode +"0";
				cCode = cCode +";";
			}
		}
		if(n.compGen!=null)
			if(n.compGen.size()>0){

			}
			else if(exEls.size()>0){
				for(int i=0; i<exEls.size();i++){
					cCode = cCode +"  "+var+"["+i+"] = ";
					exEls.get(i).accept(this,env);
					cCode = cCode +";\n";

				}
			}
	}

	// Type t;
	// Identifier i;

	private void PrintIntegrs(GenIntegers gI, ExpList fils, FormalList vars, Object env) {
		cCode = cCode +("int " + vars.get(0).i.s +", temp_" + vars.get(0).i.s + "=0;\nfor("+ vars.get(0).i.s +"=");
		gI.e1.accept(this, env);
		cCode = cCode +("; "+vars.get(0).i.s +" <=" );
		gI.e2.accept(this, env);
		cCode = cCode + "; " +vars.get(0).i.s +" ++){\n  "+ (String)env+ "[temp_" +vars.get(0).i.s + "] = ";
		vars.get(0).accept(this, env);

		cCode = cCode +"temp_" +vars.get(0).i.s + " ++;\n}\n  ";

	}
	
	public void PrintIntegrs(GenIntegers gI, Identifier id, String type, Object env){
		cCode = cCode +(type + id.s + ";\nfor("+ id.s +"=");
		gI.e1.accept(this, env);
		cCode = cCode +("; "+id.s +" <=" );
		gI.e2.accept(this, env);
		cCode = cCode +("; " +id.s +" ++){\n");

	}

	private String CheckChannel(String s){
		String ss = "";
		// TODO : send the channel/core number within HOST()
		ss = "\tif(!" + s + ") {\n\t\tHOST(" + networkMap.mapEntityPlace.get(instName) + ") = 0xDEADC0DE;\n\t\tasm volatile(\".byte 0x00, 0x00, 0x00, 0x00\");\n\t}\n";
		
		return ss;
	}
	// Type t;
	// Identifier i;
	// PortDeclList input, output;
	// VarDeclList vl;
	// StatementList sl,oStms;
	// Exp e;
	public Object visit(ActionDecl n, Object env) {

		this.actionInProcess = n;
		
		//Let's call the accelerator from the C code
		cCode = cCode + ("\nstatic inline void ");
		n.i.accept(this, env);
		cCode = cCode + " ( ) {\n";
				
		if(n.i.s.contains("__acc__")){
			printChisel = true;
			System.out.println("Found an action to be accelerated!\nCreating the chisel code...\n");
		}
		
		if(printChisel){
			
			// clean the variables if there was any other accelerated action
			moduleInputs.clear();
			moduleOutputs.clear();
			inputs32Bits.clear();
			inputs64Bits.clear();
			moduleInputsSizes.clear();
			moduleOutputsSizes.clear();
			
			// Get the types of the variables (options: simple, complex)
			for(int j = 0; j < actorInProcess.vl.size(); j++){
				VarDeclSimp varDeclSimp;
				VarDeclComp varDeclComp;
				if(actorInProcess.vl.get(j) instanceof VarDeclSimp){
					varDeclSimp = (VarDeclSimp) actorInProcess.vl.get(j);
					outputVarDeclType.put(varDeclSimp.i.s, "simple");
				}
				else{
					varDeclComp = (VarDeclComp) actorInProcess.vl.get(j);
					outputVarDeclType.put(varDeclComp.i.s, "complex");
				}
			}
			
			isFirstIteration = true;
			n.sl.accept(this, env);
			isFirstIteration = false;
			
			chiselIndent = chiselIndent + "\t";
			
			// Class decleration
			chiselCode = chiselCode + "\nclass "+ n.i.s.substring(instName.length() + 8) + "() extends Module {\n";			//print class declaration (skip "__acc__")
			
			// I/O definitions should be here however we first need to go through statements to figure out which global variables
			// are used. So that we can have them as inputs and outputs to the action module.
			
			// Variable declarations
			/* All variables are declared as Wires. The width is based on the type of variable
			 * Float variables have the width of 32 bits where as complex variables have the
			 * width of 64 bits */
			// TODO printing the variable declerations is disabled. Because the first versions of the variables are not used in the code.
			//chiselCode = chiselCode + "\n//Declare the first version of the variables\n";
			for ( int i = 0; i < n.vl.size(); i++ ) {				
				boolean tmp = false;
				int varSize = 0;
				
				if(n.vl.get(i) instanceof VarDeclSimp){
					String varDeclSimp = ((VarDeclSimp)n.vl.get(i)).i.s;
					// if the variable is a complex then the size is 64 otherwise 32
					if(varDeclSimp.startsWith("complex_"))
						varSize = 64;
					else
						varSize = 32;
					
					// if the variable is an index, let's take it out of the accelerator
					if(arrayIndices.contains(varDeclSimp)){
						printChisel = false;
						n.vl.get(i).accept(this, env);
						cCode = cCode + "\n\t";
						printChisel = true;
						tmp = true;
					}
					else{
						//chiselCode = chiselCode + "\tval ";
						//((VarDeclSimp)n.vl.get(i)).i.accept(this, env);
						actionGlobalVars.add(varDeclSimp);
						varVersions.putIfAbsent(varDeclSimp, 0);	// Set the versions of the action variables to zero
					}
				}
				else{
					String varDeclComp = ((VarDeclComp)n.vl.get(i)).i.s;
					
					if(varDeclComp.startsWith("complex_"))
						varSize = 64;
					else
						varSize = 32;
					
					//chiselCode = chiselCode + "\tval ";
					((VarDeclComp)n.vl.get(i)).i.accept(this, env);
					actionGlobalVars.add(varDeclComp);
					varVersions.putIfAbsent(varDeclComp, 0); // Set the versions of the action variables to zero
				}
				if(!tmp){
					//chiselCode = chiselCode + "_v0 = Wire(UInt(width = " + varSize + ".W))\n";
				}
			}
			
			// Let's add all the global actor variables to the action variable version list. The versions start from zero 
			for(int j = 0; j < actorInProcess.vl.size(); j++){
				VarDeclSimp varDeclSimp;
				VarDeclComp varDeclComp;
				if(actorInProcess.vl.get(j) instanceof VarDeclSimp){
					varDeclSimp = (VarDeclSimp) actorInProcess.vl.get(j);
					varVersions.putIfAbsent(varDeclSimp.i.s, 0);
					outputVarDeclType.put(varDeclSimp.i.s, "simple");
				}
				else{
					varDeclComp = (VarDeclComp) actorInProcess.vl.get(j);
					varVersions.putIfAbsent(varDeclComp.i.s, 0);
					outputVarDeclType.put(varDeclComp.i.s, "complex");
				}
			}
			// Let's add the input and output ports to the variable version list. The versions start from zero
			if(n.input != null){
				for(int j = 0; j < n.input.size(); j++ ){
					ArrayList<String> portName = (ArrayList<String>) n.input.get(j).accept(this, env);
					varVersions.putIfAbsent(portName.get(0), 0);
				}
			}
			if(n.output != null){
				for(int j = 0; j < n.output.size(); j++ ){
					ArrayList<String> portName = (ArrayList<String>) n.output.get(j).accept(this, env);
					varVersions.putIfAbsent(portName.get(0), 0);
				}
			}
			
			
			chiselCode =  chiselCode + "\n";
			// Generate statements
			n.sl.accept(this, env);
			
			// Print inputs/outputs
			String i_o = "";
			
			/* First we need to identify inputs and outputs by checking the ports and global variables */
			if(n.input != null){
				i_o = i_o + "\tval io = IO(new Bundle{\n";
				for(int j = 0; j < n.input.size(); j++ ){
					ArrayList<String> portName = (ArrayList<String>) n.input.get(j).accept(this, env);
					i_o = i_o + "\t\tval " + portName.get(0) + "_in = Input(UInt(width = 32.W))\n";		//by default the inputs are 32 bits
					moduleInputs.add(portName.get(0));
					moduleInputsSizes.add(32);		// By default, I/O ports of the actors are 32 bit wide
				}
			}

			// The global variables which are used by this action are inputs.
			// We will not include the variables generated by this framework by simply checking the name of the framework.
			for(int j = 0; j < actorInProcess.vl.size(); j++){

				VarDeclSimp varDeclSimp;
				VarDeclComp varDeclComp;
				boolean isVariableUsed = false;
				if(actorInProcess.vl.get(j) instanceof VarDeclSimp){
					varDeclSimp = (VarDeclSimp) actorInProcess.vl.get(j);
					
					// Check if the global variable is read in the action
					for(int i = 0; i < variablesRead.size(); i++)
						if(varDeclSimp.i.s.equals(variablesRead.get(i)))
							isVariableUsed = true;
					
					// Let's check the size of the variable (if it is integer (32) or complex (64))
					int varSize;
					if(varDeclSimp.t instanceof FloatType)
						varSize = ((FloatType)varDeclSimp.t).size;
					else if(varDeclSimp.t instanceof IntegerType)
						varSize = ((IntegerType) varDeclSimp.t).size;
					else
						varSize = 32; // fallback case
/*					
					if(varDeclSimp.i.s.startsWith("complex_"))
						varSize = 64;
					else
						varSize = 32;
*/				
					if(isVariableUsed && !varDeclSimp.i.s.startsWith(actorInProcess.i.s) && !varDeclSimp.i.s.endsWith("_ret")){
						i_o = i_o + "\t\tval " + varDeclSimp.i.s + "_in = Input(UInt(width = " + varSize + ".W))\n";
						moduleInputs.add(varDeclSimp.i.s);
						moduleInputsSizes.add(varSize);
					}
				}
				else{
					varDeclComp = (VarDeclComp) actorInProcess.vl.get(j);
					
					// Check if the global variable is read in the action
					for(int i = 0; i < variablesRead.size(); i++)
						if(varDeclComp.i.s.equals(variablesRead.get(i)))
							isVariableUsed = true;
					
					// Let's check the size of the variable (if it is integer (32) or complex (64))
					int varSize;
					if(varDeclComp.i.s.startsWith("complex_"))
						varSize = 64;
					else
						varSize = 32;
					
					if(isVariableUsed && !varDeclComp.i.s.startsWith(actorInProcess.i.s) && !varDeclComp.i.s.endsWith("_ret")){
						i_o = i_o + "\t\tval " + varDeclComp.i.s + "_in = Input(UInt(width = " + varSize + ".W))\n";
						moduleInputs.add(varDeclComp.i.s);
						moduleInputsSizes.add(varSize);
					}
				}
			}
			
			// If we don't modify a global variable, then we don't have to send it out. 
			// We save all the variable strings in a global arraylist<string> and at the end add the outputs.
			if(n.output != null){
				for(int j = 0; j < n.output.size(); j++ ){
					ArrayList<String> portName = (ArrayList<String>) n.output.get(j).accept(this, env);
					i_o = i_o + "\t\tval " + portName.get(0) + "_out = Output(UInt(width = 32.W))\n";
					moduleOutputs.add(portName.get(0));
					moduleOutputsSizes.add(32); 		// By default, size of the actors ports is 32 bits
				}
			}
			
			for(int j = 0; j < actorInProcess.vl.size(); j++){

				VarDeclSimp varDeclSimp;
				VarDeclComp varDeclComp;
				boolean isVariableUsed = false;
				
				if(actorInProcess.vl.get(j) instanceof VarDeclSimp){
					varDeclSimp = (VarDeclSimp) actorInProcess.vl.get(j);
					
					// Check if the global variable is read in the action
					for(int i = 0; i < variablesWritten.size(); i++)
						if(varDeclSimp.i.s.equals(variablesWritten.get(i)))
							isVariableUsed = true;
					
					// Let's check the size of the variable (if it is integer (32) or complex (64))
					int varSize;
					if(varDeclSimp.i.s.startsWith("complex_"))
						varSize = 64;
					else
						varSize = 32;
						
					if(isVariableUsed && !varDeclSimp.i.s.startsWith(actorInProcess.i.s) && !varDeclSimp.i.s.endsWith("_ret")){
						i_o = i_o + "\t\tval " + varDeclSimp.i.s + "_out = Output(UInt(width = " + varSize + ".W))\n";
						moduleOutputs.add(varDeclSimp.i.s);
						moduleOutputsSizes.add(varSize);
					}
				}
				else{
					varDeclComp = (VarDeclComp) actorInProcess.vl.get(j);
					
					// Check if the global variable is read in the action
					for(int i = 0; i < variablesWritten.size(); i++)
						if(varDeclComp.i.s.equals(variablesWritten.get(i)))
							isVariableUsed = true;
					
					// Let's check the size of the variable (if it is integer (32) or complex (64))
					int varSize;
					if(varDeclComp.i.s.startsWith("complex_"))
						varSize = 64;
					else
						varSize = 32;
					
					if(isVariableUsed && !varDeclComp.i.s.startsWith(actorInProcess.i.s) && !varDeclComp.i.s.endsWith("_ret")){
						i_o = i_o + "\t\tval " + varDeclComp.i.s + "_out = Output(UInt(width = " + varSize + ".W))\n";
						moduleOutputs.add(varDeclComp.i.s);
						moduleOutputsSizes.add(varSize);
					}
				}
			}
			
			// Add enable and valid signals
			i_o = i_o + "\t\tval en = Input(Bool())\n";
			i_o = i_o + "\t\tval valid = Output(Bool())\n";
			
			i_o = i_o + "\t})\n";
			
			//Define all versions of the variables
			i_o = i_o + "\n" + chiselIndent + "//Define all versions of the variables\n";
			for (Map.Entry<String, Integer> entry : varVersions.entrySet()) {
			    String key = entry.getKey();
			    int value = entry.getValue();
			    
			    int varSize = 0;
			    
			    if(key.startsWith("complex_"))
			    	varSize = 64;
			    else
			    	varSize = 32;
			    
			    if(value > 0){
			    	for (int i = value; i > 0; i--)
			    		i_o = i_o + chiselIndent + "val " + key + "_v" + i + " = Wire(UInt(width = " + varSize + ".W))\n";
			    }
			}
			
			// Define the temp values for the outputs
			//i_o = i_o + chiselIndent + "\n//Define the temp values for the outputs\n";
			for(int i = 0; i < moduleOutputs.size(); i++){
				if(!moduleInputs.contains(moduleOutputs.get(i))){
					//i_o = i_o + chiselIndent + "val " + moduleOutputs.get(i) + "_v0" + " = " + "Wire(UInt(width = " + moduleOutputsSizes.get(i) + ".W))\n";
					actionGlobalVars.add(moduleOutputs.get(i));
				}
			}
			
			i_o = i_o +  "\n" + chiselIndent + "//Read the inputs\n";
			// Connect to module inputs to some cables with the proper variable name
			for(int i = 0; i < moduleInputs.size(); i++){
				i_o = i_o + chiselIndent + "val " + moduleInputs.get(i) + "_v0" + " = io." + moduleInputs.get(i) + "_in\n";
			}
			
			chiselCode = chiselCode + "\n" + chiselIndent + "//Write the outputs\n";
			// Connect to module outputs to some cables with the proper variable name
			
			
			/** PIPELINING THE OUTPUT**/
			// Find the output with the longest delay (then we will delay the other outputs as much as needed)
			int longestOutputDelay = 0;
			for(int i = 0; i < moduleOutputs.size(); i++){
				int delayTmp = 0;
				String output = moduleOutputs.get(i) + "_v" + varVersions.get(moduleOutputs.get(i));
				if(globalDelays.containsKey(output))
					delayTmp = globalDelays.get(output);
				
				if(delayTmp > longestOutputDelay)
					longestOutputDelay = delayTmp;
				
				chiselCode = chiselCode + chiselIndent + "// " + output + " total delay : " + delayTmp + "\n";
			}
			
			
			
			// Delay all the outputs for the same amount of cycles
			for(int i = 0; i < moduleOutputs.size(); i++){
				int currentOutputDelay = 0;
				String output = moduleOutputs.get(i) + "_v" + varVersions.get(moduleOutputs.get(i));
				if(globalDelays.containsKey(output))
					currentOutputDelay = globalDelays.get(output);
				
				// Inserting delay registers to the output paths
				for(int j = 0; j < longestOutputDelay - currentOutputDelay; j++){
					if( j == 0){
						chiselCode = chiselCode + chiselIndent + "val " + output + "_Reg" + j + " = RegNext(" + output + ", 0.U)\n";
					}
					else{
						chiselCode = chiselCode + chiselIndent + "val " + output + "_Reg" + j + " = RegNext(" + output + "_Reg" + (j - 1) + ", 0.U)\n";
					}
				}
				
				if(longestOutputDelay - currentOutputDelay > 0)
					chiselCode = chiselCode + chiselIndent +  "io." + moduleOutputs.get(i) + "_out := " + output + "_Reg" + (longestOutputDelay - currentOutputDelay - 1) + "\n";
				else
					chiselCode = chiselCode + chiselIndent +  "io." + moduleOutputs.get(i) + "_out := " + output + "\n";
				
			}
			
			// Set the valid signal (it must be delayed as much as the longest output delay
			for(int i = 0; i < longestOutputDelay; i++){
				if(i == 0)
					chiselCode = chiselCode + chiselIndent + "val validReg" + i + " = RegNext(io.en, 0.U)\n";
				else
					chiselCode = chiselCode + chiselIndent + "val validReg" + i + " = RegNext(validReg" + (i - 1) + ", 0.U)\n";
			}
			
			if(longestOutputDelay > 0)
				chiselCode = chiselCode + chiselIndent +  "io.valid := validReg" + (longestOutputDelay - 1) + "\n";
			else
				chiselCode = chiselCode + chiselIndent +  "io.valid := io.en\n";
			
			/** END OF PIPELINING THE OUTPUT **/
/*
			for(int i = 0; i < moduleOutputs.size(); i++){
				chiselCode = chiselCode + chiselIndent +  "io." + moduleOutputs.get(i) + "_out := " + moduleOutputs.get(i) + "_v" + varVersions.get(moduleOutputs.get(i)) + "\n";
			}	
	*/		
			String classDefinition = "class "+ n.i.s.substring(instName.length() + 8)+ "() extends Module {\n";
			int indexOfClassDef = chiselCode.indexOf(classDefinition) + classDefinition.length();
			chiselCode = new StringBuilder(chiselCode).insert(indexOfClassDef, i_o).toString();	
			
			
			chiselCode =  chiselCode + "}";
			
			// Add the libraries
			// TODO  We should add conditions for importing the floating-point library (check the number of division, multiplier, adder, sub etc units) 
			chiselCode = "import fpDivision._ \nimport chisel3._\nimport chisel3.util._ \n" + chiselCode;			//print imports
			
			// Add the complex arithmetics if they are used
			if((C_subCounter + C_mulCounter + C_addCounter + C_divCounter) > 0)
				chiselCode = "import ComplexArithmetics._\n" + chiselCode;
						
			// Package name
			chiselCode = "package partial" + instName + "\n\n" + chiselCode;				//print package
			
						
			printChisel = false;
			variablesRead.clear();
			variablesWritten.clear();
			varVersions.clear();

			
			/* We can send max 4 floating point numbers at each instruction call.
			 * This includes combining two floating points in one 64-bit register.
			 * We will use the variables stored in the moduleInputs list.
			*/
			boolean evenInputs = false;
			boolean evenOutputs = false;

			/* Check the input sizes. If they are 64 the send them directly via custom instructions. 
			 * Otherwise (if they are smaller than 64 bits) there will be some memory operations to 
			 * send more then a single input in a custom instruction source register.
			 */
			
			boolean thereIs32BitsInput = false;
			boolean thereIs64BitsInput = false;
			
			for(int i = 0; i < moduleInputs.size(); i++){
				if(moduleInputsSizes.get(i) == 64)
					thereIs64BitsInput = true; 	// The inputs are 64 bits (perhaps complex numbers)
				
				if(moduleInputsSizes.get(i) == 32)	// We have both 64 bits and 32 bits inputs
					thereIs32BitsInput = true;
			}
			
			// Let's separate the inputs (this helps with having mixture of 32bits and 64 bits inputs)
			for(int i = 0; i < moduleInputs.size(); i++){
				if(moduleInputsSizes.get(i) == 32)
					inputs32Bits.add(moduleInputs.get(i));	
				else if(moduleInputsSizes.get(i) == 64)
					inputs64Bits.add(moduleInputs.get(i));
			}	
			
			ArrayList<String> tmp64Regs = new ArrayList<String>();
			/** EXECUTING THE CUSTOM INSTRUCTIONS **/ 
			cCode = cCode + "\n\t//Lets execute the custom instructions\n";
			
			/* The inputs seem to be 32 bits wide, let's copy them into 64 bits variables */
			if(thereIs32BitsInput) {	
				for(int i = 0; i < (inputs32Bits.size() + 1) / 2; i++){			// inputs32Bits replaced the moduleInputs
					cCode = cCode + "\tuint64_t acc_input" + i + ";\n";
					tmp64Regs.add("acc_input" + i);
				}
				
				cCode = cCode + "\n\t//Copy two floating point numbers into 64 bit registers \n";
				for(int i = 0; i < inputs32Bits.size(); i++){
					String indexTmp = "";
					// Check if the value is read from an array. If so, add the index.
					if(arrayAndIndexRead.containsKey(inputs32Bits.get(i)))
						indexTmp = "[" + arrayAndIndexRead.get(inputs32Bits.get(i)) + "]";
					
					// Let the copying begin
					if(inputs32Bits.size() % 2 == 0){
						if(i % 2 == 1)
							cCode = cCode + "\tmemcpy(&acc_input" + (i >> 1) + ", &" +  inputs32Bits.get(i) + indexTmp + ", 4);\n";
						else
							cCode = cCode + "\tmemcpy(((char*)&acc_input" + (i >> 1) + ") + 4, &" +  inputs32Bits.get(i) + indexTmp + ", 4);\n";
					}
					else {
						if(i == inputs32Bits.size() - 1){
							cCode = cCode + "\tmemcpy(((char*)&acc_input" + (i >> 1) + ") + 4, &" + inputs32Bits.get(i) + indexTmp + ", 4);\n";
						}
						else if(i % 2 == 1)
							cCode = cCode + "\tmemcpy(&acc_input" + (i >> 1) + ", &" +  inputs32Bits.get(i) + indexTmp + ", 4);\n";
						else
							cCode = cCode + "\tmemcpy(((char*)&acc_input" + (i >> 1) + ") + 4, &" +  inputs32Bits.get(i) + indexTmp + ", 4);\n";
					}
				}
							
			}
			
			// Are there any 64 bits input? If so, just send them via the custom instruction
			if(thereIs64BitsInput){
				cCode = cCode + "\tuint64_t outputReg;\n";
				
				int i;
				ArrayList<String> tmp64Bits = new ArrayList<String>();
				tmp64Bits = (ArrayList<String>) inputs64Bits.clone();
				
				// Here we determine what the inputs registers will hold
				for(i = 0; i < ((inputs64Bits.size() * 2 + inputs32Bits.size() + 3) / 4); i++){
					String [] inputName = {"", ""};
					
					for(int j = 0; j < 2; j++){
						if(!tmp64Bits.isEmpty()){ // The input is 64 bits						
							String indexTmp = "";
							// Check if the value is read from an array. If so, add the index.
							if(arrayAndIndexRead.containsKey(tmp64Bits.get(0)))
								indexTmp = "[" + arrayAndIndexRead.get(tmp64Bits.get(0)) + "]";
							
							inputName[j] = tmp64Bits.get(0);
							tmp64Bits.remove(inputName[j]);
							inputName[j] = inputName[j] + indexTmp;
						} else if(!tmp64Regs.isEmpty()){	// The input is 32 bits
							inputName[j] = tmp64Regs.get(0);
							tmp64Regs.remove(inputName[j]);						
						} else {							// No input left (this shouldn't be possible)
							inputName[j] = "0";
						}
					}
					
					// Lets print the custom instructions
					if((i + 1) < ((inputs64Bits.size() * 2 + inputs32Bits.size() + 3) / 4))
						cCode = cCode + "\tROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, " +  inputName[0] + ", " + 
							inputName[1] + ", FUNCT_IN" + (i + 1) +" );\n";
					else
						cCode  = cCode + "\tROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, " + inputName[0] + ", " + inputName[1] + ", FUNCT_FIRE );\n";
				}
/*				
				for(i = 0; i < (inputs64Bits.size() - 1) / 2; i++){		//inputs64Bits replaced the moduleInputs
					String indexTmp1 = "";
					String indexTmp2 = "";
					// Check if the value is read from an array. If so, add the index.
					if(arrayAndIndexRead.containsKey(inputs64Bits.get(i * 2)))
						indexTmp1 = "[" + arrayAndIndexRead.get(inputs64Bits.get(i * 2)) + "]";
					if(arrayAndIndexRead.containsKey(inputs64Bits.get(i * 2 + 1)))
						indexTmp2 = "[" + arrayAndIndexRead.get(inputs64Bits.get(i * 2 + 1)) + "]";
					
					cCode = cCode + "\tROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, " +  inputs64Bits.get(i * 2) + indexTmp1 + ", " + 
							inputs64Bits.get(i * 2 + 1) + indexTmp2 + ", FUNCT_IN" + (i + 1) +" );\n";
				}
				
				// Lets print the blocking custom instruction
				String indexTmp1 = "";
				
				// Check if the value is read from an array. If so, add the index.
				if(arrayAndIndexRead.containsKey(inputs64Bits.get(i * 2)))
					indexTmp1 = "[" + arrayAndIndexRead.get(inputs64Bits.get(i * 2)) + "]";
			
				cCode  = cCode + "\tROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, " + inputs64Bits.get(i * 2) + indexTmp1 + ", ";
				if(inputs64Bits.size() > i * 2 + 1){
					String indexTmp2 = "";
					if(arrayAndIndexRead.containsKey(inputs64Bits.get(i * 2 + 1)))
						indexTmp2 = "[" + arrayAndIndexRead.get(inputs64Bits.get(i * 2 + 1)) + "]";
					cCode = cCode + inputs64Bits.get(i * 2 + 1) + indexTmp2;
				}
				else
					cCode = cCode + "0";
				
				cCode = cCode + ", FUNCT_FIRE );\n";
*/				
				/** READING THE RESULTS OF THE ACCELERATOR (64 bits version)**/ 
				// Lets read the first result
				cCode = cCode + "\n\t//Lets read the results\n";
				if(arrayAndIndexWritten.containsKey(moduleOutputs.get(0))){
					cCode = cCode + "\t" + moduleOutputs.get(0) + "[" + arrayAndIndexWritten.get(moduleOutputs.get(0)) + "] = outputReg;\n";
				}
				else{
					cCode = cCode + "\t" + moduleOutputs.get(0) + " = outputReg;\n";
				}
				
				/* If we need to read more than 64 bits of result, we store the previous result and call the custom instruction as many times as needed */
				for(i = 1; i < moduleOutputs.size(); i++){
					cCode  = cCode + "\tROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, 0, 0, FUNCT_READ);\n"; 
					if(arrayAndIndexWritten.containsKey(moduleOutputs.get(i))){
						cCode = cCode + "\t" + moduleOutputs.get(0) + "[" + arrayAndIndexWritten.get(moduleOutputs.get(0)) + "] = outputReg;\n";
					}
					else{	
						cCode = cCode + "\t" + moduleOutputs.get(i) + " = outputReg;\n";
					}
				}
				
				/** READING THE RESULTS OF THE ACCELERATOR (32 bit version) this is a TODO (merge this with the 64 bit version)**/
	/*			
				outputRegCounter++; 	// The first outputReg is used by the firing instruction
				
				// Save the results in floating point variables
				cCode = cCode + "\n\t//Save the results (and read any extra result)\n";
				for(int i = 0; i < (moduleOutputs.size() + 1) / 2; i++){
					// If we need to read more than 64 bits of result, we store the previous result and call the custom instruction as many times as needed 
					if( i > 0 ){
						cCode  = cCode + "\n\tROCC_INSTRUCTION(XCUSTOM_ACC, outputReg" + outputRegCounter + ", 0, 0, FUNCT_READ);\n"; 
						outputRegCounter++;
					}
					cCode = cCode + "\tfloat results" + i + "[2];\n"; 
					cCode = cCode + "\tmemcpy(&results" + i + "[0], &outputReg" + i + ", 8);\n";
				}
				
				// Set the actual variables which were the outputs of the action
				cCode = cCode + "\n\t//Set the outputs\n";
				for(int i = 0; i < moduleOutputs.size(); i++){
					if(arrayAndIndexWritten.containsKey(moduleOutputs.get(i))){
						cCode = cCode + "\t" + moduleOutputs.get(i) + "[" + arrayAndIndexWritten.get(moduleOutputs.get(i)) + "] = results" + (i / 2) + "[" + i % 2 + "];\n";
					}
					else{	
						cCode = cCode + "\t" + moduleOutputs.get(i) + " = results" + (i / 2) + "[" + i % 2 + "];\n";
					}
				}
	*/
			}

			
			cCode = cCode + "}";
			
		}
		else{
			
			String old = indent;
			sActionInsOuts = ""+(Integer)env;
			/*
			cCode = cCode + ("\nstatic void ");
			//n.t.accept(this,env);
			cCode = cCode +" ";
			n.i.accept(this, env);
			cCode = cCode +" (";
	
			cCode = cCode +") { \n";
			*/
			//	cCode = cCode +"fprintf("+typeName+",\""+(Integer)env +"\");\n";
			indent = indent + "\t";
			duplicatVar = true;
	
			// Variable declarations
			for ( int i = 0; i < n.vl.size(); i++ ) {
	
				cCode = cCode + (indent);
				if(n.vl.get(i) instanceof VarDeclSimp){
					if(((VarDeclSimp)n.vl.get(i)).t != null)
						((VarDeclSimp)n.vl.get(i)).t.accept(this, env);
					else
						cCode = cCode +"int";
					
					cCode = cCode +" ";
					((VarDeclSimp)n.vl.get(i)).i.accept(this, env);
					cCode = cCode +";";
				}
				else{
					((VarDeclComp)n.vl.get(i)).t.accept(this, ((VarDeclComp)n.vl.get(i)).i.s);
					//	((VarDeclComp)n.vl.get(i)).i.accept(this, env);
					cCode = cCode +";";
				}
				cCode = cCode +("\n");
			}
	
			indent = old;
			n.sl.accept(this, env);
	
			//write on out put port
			duplicatVar = false;
	
			//	cCode = cCode +(indent + "return ");
			//	n.e.accept(this,env);
			
			sActionInsOuts = "\""+ sActionInsOuts + "\\n\""+ sActionInsOutsInts;
	
			//	cCode = cCode +"fprintf("+typeName+",\"\\n\");\n";
	
			cCode = cCode +("  }");
		}
		return null;
	}
	
	public Object visit(ActionScheduler n, Object env) {

		String timer1 ="", timer2 ="", com_init ="", timer3 ="";
		
		int j;
		cCode = cCode + "\nint main(void)\n{\n  ";

		/* Epiphany specific stuff */
		//cCode = cCode +  timer1;	
		//cCode = cCode + "\t/* initialization */\n\tplatform_init();";
		//cCode = cCode + "\n\tcomm_init("+ networkMap.commTableName + ", NUM_CHANNELS);\n";
		//cCode = cCode + "		"+ com_init+ "shm.init[core_id] = comm_init(shm.channels, commlib_heap, HEAP_SZ_"+instName +");\n   ";
		ArrayList<String> multiConne = new ArrayList<String>();
		
		int channelCounter = 0;	// This is used for indexing the channel table. It assumes that the input channels are above the output channels in the table.
		if(n.input != null)
			if(n.input.size() > 0){
				cCode = cCode +("\n\t//InputPorts\n ");
				
				for( j = 0; j < n.input.size(); j++){
					multiConne.clear();
					multiConne.addAll((ArrayList<String>) n.input.get(j).accept(this,env));
					for(String s : multiConne) {
						if(s.startsWith("ch")) {
							cCode = cCode + "\t"+  s + " = comm_get_rhandle(" + networkMap.commTableName + ", NUM_CHANNELS, " + channelCounter++  +");\n";
							if(checkchannel)
								cCode = cCode + CheckChannel(s);
						}
						else{
							//cCode = cCode + "\t"+  s + " = comm_get_rhandle(" + networkMap.commTableName + ", NUM_CHANNELS, " + "0);\n";
						}
						
					}
				}
				/*		multiConne.clear();
				multiConne.addAll((ArrayList<String>) n.input.get(j).accept(this,env));
				for( j=0;j<multiConne.size()-1;j++)
					cCode = cCode +multiConne.get(j)+ ", ";
				cCode = cCode + multiConne.get(j)+";";*/

			}
		if(n.output != null)
			if(n.output.size()>0){

				cCode = cCode +("\n\t//OutputPorts\n");

				for( j=0;j<n.output.size();j++){
					multiConne.clear();
					multiConne.addAll((ArrayList<String>) n.output.get(j).accept(this,env));
					
					for(String s:multiConne){
						if(s.startsWith("ch")){
							cCode = cCode + "\t" + s + " = comm_get_whandle("+ networkMap.commTableName + ", NUM_CHANNELS, "+ channelCounter++ +");\n";
							if(checkchannel)
								cCode = cCode + CheckChannel(s);
						}
						else{
						}
					}
				}
				
				/*multiConne.clear();
				multiConne.addAll((ArrayList<String>) n.output.get(j).accept(this,env));
				for( j=0;j<multiConne.size()-1;j++)
					cCode = cCode +multiConne.get(j)+ ", ";
				cCode = cCode + multiConne.get(j)+";";*/
			}	
		if(globId.size() != 0){			
			cCode = cCode + "    if(int_state_vars_"+instName+"==1){\n" +
					"        int_state_vars_"+instName+" = 0;\n" +
					"        initStateVars"+instName+"();\n\t}\n";
		}
		//		cCode = cCode +"" +
		//	//			"\nprintf(\"------.............  "+ instName+" ----------\\n\");\n"+
		//				"{\n";
		cCode = cCode + timer2;
		for(VarDecl v : n.vars){
			v.accept(this, env);
			cCode = cCode +"\n";
		}

		cCode = cCode + timer3;
		for(CStatement s : n.sl)
			s.accept(this, env);
		cCode = cCode + "\n}";
		return null;
	}

	// Exp e1,e2;
	public Object visit(And n, Object env) {
		
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this,env);
			}
			else {
				chiselCode = chiselCode +("( ");
				n.e1.accept(this, env);
				chiselCode = chiselCode +(" && ");
				n.e2.accept(this,env);
				chiselCode = chiselCode +(" )");
			}
		}
		else{
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" && ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}
		
		return null;
	}

	// Identifier i;
	// Exp e1,e2;
	public Object visit(FieldAssign n, Object env) {

		n.i.accept(this,env);
		cCode = cCode +("[");
		n.e1.accept(this,env);
		cCode = cCode +("] = ");
		n.e2.accept(this,env);
		cCode = cCode +(";");

		return null;
	}



	// Identifier i;
	// Exp e;
	public Object visit(Assign n, Object env) {
		if(n.e instanceof ListComprehension){
			n.e.accept(this, n.i.s);
		}
		else{
			if(printChisel){
				if(!isFirstIteration){
					if(arrayIndices.contains(n.i.s)){	// If the assignment is to an index, we forward it to the C code
						printChisel = false;
						n.accept(this, env);
						printChisel = true;
					}
				}
				if(!arrayIndices.contains(n.i.s)){
					isAssignLeft = true;
					n.i.accept(this, env);
					isAssignLeft = false;
				}
				if(!isFirstIteration && !arrayIndices.contains(n.i.s))	{
					chiselCode = chiselCode + " := ";
				}
				if(!arrayIndices.contains(n.i.s)){
					localDelay = 0;
					n.e.accept(this, env);
					if(varVersions.containsKey(n.i.s))
						varVersions.replace(n.i.s, varVersions.get(n.i.s) + 1);
					
					// If the assignment is to a variable that is delayed, we need to set the delay of the new variable
					if(!isFirstIteration && n.e instanceof IdentifierExp){
						String var = ((IdentifierExp)n.e).s;
						if(varVersions.containsKey(var))
							var = var + "_v" + varVersions.get(var);

						if(globalDelays.containsKey(var))
							localDelay = globalDelays.get(var);
						
					}
					if(globalDelays.containsKey(n.i.s + "_v" + varVersions.get(n.i.s)))
						globalDelays.replace(n.i.s + "_v" + varVersions.get(n.i.s), localDelay);
					else
						globalDelays.put(n.i.s + "_v" + varVersions.get(n.i.s), localDelay);
					
					if(!isFirstIteration)
						chiselCode = chiselCode + chiselIndent + "// " + n.i.s + "_v" + varVersions.get(n.i.s) + " total delay: " + globalDelays.get(n.i.s + "_v" +  varVersions.get(n.i.s));
				}
				
			}
			else{
				n.i.accept(this, env);
				cCode = cCode +(" = ");
				n.e.accept(this, env);
				cCode = cCode +(";\n");
			}
		}
		return null;
	}

	// Exp e1,e2;
	public Object visit(BitAnd n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				chiselCode = chiselCode +("( ");
				n.e1.accept(this, env);
				chiselCode = chiselCode + " & ";
				n.e2.accept(this, env);
				chiselCode = chiselCode +(" )");
			}
			
		}
		else{
			cCode = cCode +("(");
			n.e1.accept(this, env);
			cCode = cCode +(" & ");
			n.e2.accept(this, env);
			cCode = cCode +(")");
		}
		return null;
	}


	// Exp e1,e2;
	public Object visit(BitNot n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e.accept(this, env);
			}
			else {
				chiselCode = chiselCode + (" ~ ");
				n.e.accept(this, env);
			}
		}
		else{
			cCode = cCode + ("( ~ ");
			n.e.accept(this, env);
			cCode = cCode + (")");
		}
		return null;
	}

	// Exp e1,e2;
	public Object visit(BitOr n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				chiselCode = chiselCode +("( ");
				n.e1.accept(this, env);
				chiselCode = chiselCode +(" | ");
				n.e2.accept(this, env);
				chiselCode = chiselCode +(" )");
			}
		}
		else{
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" | ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}

		return null;
	}

	@Override
	public Object visit(BitXOr n, Object env) {
		
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				chiselCode = chiselCode + "( ";
				n.e1.accept(this, env);
				chiselCode = chiselCode + " ^ ";
				n.e2.accept(this, env);
				chiselCode = chiselCode + ")";
			}
		}
		else{
			cCode = cCode + "(";
			n.e1.accept(this, env);
			cCode = cCode + "^";
			n.e2.accept(this, env);
			cCode = cCode + ")";
		}

		return null;
	}

	// StatementList sl;
	public Object visit(Block n, Object env) {

		if(printChisel){
			if(isFirstIteration){
				for ( int i = 0; i < n.sl.size(); i++ ) {
					n.sl.get(i).accept(this, env);
				}
			}
			else{
				for ( int i = 0; i < n.sl.size(); i++ ) {
					chiselCode = chiselCode + chiselIndent;
					n.sl.get(i).accept(this, env);
					chiselCode = chiselCode + ("\n");
				}
			}
		}
		else{
			
			String old = indent;
			indent = indent + "\t";
			for ( int i = 0; i < n.sl.size(); i++ ) {
				cCode = cCode + (indent);
				n.sl.get(i).accept(this, env);
				cCode = cCode +("\n");
			}
			indent = old;
		}
		
		return null;
	}

	public Object visit(BooleanType n, Object env) {
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + "val";	// I am not sure what to put here yet. TODO
		}
		else
			cCode = cCode +("int");
		return null;
	}

	public Object visit(BooleanLiteral n, Object env) {
		if(n.value){
			if(printChisel){
				if(!isFirstIteration)
					chiselCode = chiselCode + "Bool(true)";
			}
			else
				cCode = cCode + ( "true");
		}
		else{
			if(printChisel){
				if(!isFirstIteration)
					chiselCode = chiselCode + "Bool(false)";
			}
			else
				cCode = cCode + ( "false");
		}
		return null;}

	// Exp e;
	// identifier i;
	// ExpList el;
	public Object visit(Call n, Object env) {
		n.e.accept(this, env);
		cCode = cCode +(".");
		n.i.accept(this,env);
		cCode = cCode +("(");
		for ( int i = 0; i < n.el.size(); i++ ) {
			n.el.get(i).accept(this,env);
			if ( i+1 < n.el.size() ) { cCode = cCode +(", "); }
		}
		cCode = cCode +(")");
		return null;
	}


	// In chisel, consume is done by just assigning the input to a variable.
	public Object visit(ConsumeToken n, Object env){

		ArrayList<String> conns= new ArrayList<String>();

		for( Identifier i: n.ids){
			if(printChisel){
				if(isFirstIteration){
					i.accept(this, env);
					conns.addAll((ArrayList<String>)n.p.accept(this, env));
				}
				else{
					i.accept(this, env);
					chiselCode = chiselCode + " := ";
					conns.addAll((ArrayList<String>)n.p.accept(this, env));
					chiselCode = chiselCode + conns.get(0) + "_in";
				}
			}
			else{
				cCode = cCode +"comm_read(";
				conns.addAll((ArrayList<String>)n.p.accept(this,env));
				cCode = cCode + conns.get(0)+ ", &";
				i.accept(this, env);
				cCode = cCode + ", 4"; //#Ayas - modified to 4 by Süleyman
				//n.rep.accept(this, env);
				cCode = cCode + "); // read 4 bytes \n";
			}
		}

		return null;
	}

	// Exp e1,e2;
	/*
	 * 	//TODO we need to find out either to use integer or floating point operation
	 * Generate an fpDiv module for division if the operands are float
	 * The module must be instantiated before the assignment. Thats why we find the last newline which means the line above the assignment.
	 * We use the index of the last newline to insert the module instantiation.
	 */
	public Object visit(Divide n, Object env) {
		
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else{
				int indexOfLastNewline = 0;
				for (int pos = chiselCode.indexOf("\n"); pos != -1; pos = chiselCode.indexOf("\n", pos + 1)) {
					indexOfLastNewline = pos;
				}
				
				
				//if((n.e1 instanceof IdentifierExp) && (n.e2 instanceof IdentifierExp)){
				
				String input1 = "";
				String input2 = "";
				
				// Let's check if the n.e1 is a single variable or an array
				if(n.e1 instanceof IdentifierExp)
					input1 = ((IdentifierExp) n.e1).s;
				else if(n.e1 instanceof ExpIndexer)
					input1 = ((IdentifierExp) ((ExpIndexer) n.e1).structure).s;
				
				if(n.e2 instanceof IdentifierExp)
					input2 = ((IdentifierExp) n.e2).s;
				else if(n.e1 instanceof ExpIndexer)
					input2 = ((IdentifierExp) ((ExpIndexer) n.e2).structure).s;
				
				boolean complexArithmetics = false;
				
				// If complex
				if(input1.startsWith("complex_") || input2.startsWith("complex_"))
					complexArithmetics = true;
				else
					complexArithmetics = false;
				
					if(complexArithmetics)
						chiselCode = chiselCode + "C_div" + C_divCounter + ".io.out\n";
					else
						chiselCode = chiselCode + "FP_div" + divCounter + ".io.out\n";
					
					/** PIPELINING **/
					//String input1 = ((IdentifierExp) n.e1).s;
					//String input2 = ((IdentifierExp) n.e2).s;
					input1 = input1 + "_v" + varVersions.get(input1);
					input2 = input2 + "_v" + varVersions.get(input2);
					// Fix the input delays
					int input1Delay = 0;
					int input2Delay = 0;
					int newInputDelay = 0;
					
					// If there is no global delay for the inputs then they are the inputs to the accelerator
					if(globalDelays.containsKey(input1))
						input1Delay = globalDelays.get(input1);
					
					if(globalDelays.containsKey(input2))
						input2Delay = globalDelays.get(input2);
					
					if(input1Delay > input2Delay){
						for(int i = 0; i < input1Delay - input2Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + i + " = RegNext(" + input2 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + i + " = RegNext(" + input2 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input1Delay;
						
						// Check if the operation is on complex numbers
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val C_div" + C_divCounter + " = Module(new ComplexDiv())").toString();
							//chiselCode = chiselCode + "C_div" + C_divCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_div"+ C_divCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_div"+ C_divCounter + ".io.in2 := " + input2 + "_Reg" + (input1Delay - input2Delay - 1) ;		
							//n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val FP_div" + divCounter + " = Module(new FPDiv(32))").toString();
							chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in2 := " + input2 + "_Reg" + (input1Delay - input2Delay - 1) ;		
							chiselCode = chiselCode + "\n";
						}
						
					}
					else if(input2Delay > input1Delay){
						for(int i = 0; i < input2Delay - input1Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input2Delay;
						
						// Check if the operation is on complex numbers
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_div" + C_divCounter + " = Module(new ComplexDiv())").toString();
							//chiselCode = chiselCode + "C_div" + C_divCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_div"+ C_divCounter + ".io.in1 := " + input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_div"+ C_divCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_div" + divCounter + " = Module(new FPDiv(32))").toString();
							//chiselCode = chiselCode + "C_div" + C_divCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in1 := " + input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
					}
					else{
						
						// Check if the operation is on complex numbers
						if(complexArithmetics){
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_div" + C_divCounter + " = Module(new ComplexDiv())").toString();
							//chiselCode = chiselCode + "C_div" + C_divCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_div"+ C_divCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_div"+ C_divCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
							newInputDelay = input2Delay;
						}
						else
						{
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_div" + divCounter + " = Module(new FPDiv(32))").toString();
							//chiselCode = chiselCode + "C_div" + C_divCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
							newInputDelay = input2Delay;
						}
					}
					
					// Set the new delay
					if(complexArithmetics){
						localDelay = complexDivDelay + newInputDelay;
						C_divCounter++;
					}
					else{
						localDelay = floatDivDelay + newInputDelay;
						divCounter++;
					}
					
					/**  END OF PIPELINING **/
					
					
			/*	}
				else{ // If float
					chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val FP_div" + divCounter + " = Module(new FPDiv(32))").toString();
					chiselCode = chiselCode + "FP_div" + divCounter + ".io.out\n";
					chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in1 := ";
					n.e1.accept(this, env);
					chiselCode = chiselCode + "\n";
					chiselCode = chiselCode + chiselIndent + "FP_div"+ divCounter + ".io.in2 := ";		
					n.e2.accept(this, env);
					chiselCode = chiselCode + "\n";
					divCounter++;
				}*/
			}
			
		}
		else
		{
			// Check if the variables are complex (if so, call the complex operation)
			boolean variablesComplex = false;
			if(n.e1 instanceof IdentifierExp)
				if(((IdentifierExp)n.e1).s.startsWith("complex_"))
					variablesComplex = true;
			
			if(n.e2 instanceof IdentifierExp)
				if(((IdentifierExp)n.e2).s.startsWith("complex_"))
					variablesComplex = true;
			
			if(variablesComplex){
				
				cCode = cCode + "ComplexDiv(";
				n.e1.accept(this, env);
				cCode = cCode + ", ";
				n.e2.accept(this, env);
				cCode = cCode + ")";
				complexDivFlag = true;
			}
			else {
				cCode = cCode + ("(");
				n.e1.accept(this, env);
				cCode = cCode + (" / ");
				n.e2.accept(this, env);
				cCode = cCode + (")");
			}
		}
		return null;
	}

	public Object visit(DoubleLiteral n, Object env) {
		if(printChisel){
			if(!isFirstIteration){
				//chiselCode = chiselCode + "\"b" + Long.toBinaryString(Double.doubleToRawLongBits(n.d)) + "\".U";
				
				String tmp = "";
				if(n.d == 0.0)
					tmp = "0";
				else{
					tmp =  Long.toBinaryString(Float.floatToRawIntBits(((float)(n.d))));
				
					int tmp_length = tmp.length();
					for(int i = 0; i < 32 - tmp_length; i ++)
						tmp = "0" + tmp;
				}
				
				chiselCode = chiselCode + "\"b" + tmp + "\".U";
			}
		}
		else{
			cCode = cCode +(""+n.d);
		}
		
		return null;
	}
	
	@Override
	public Object visit(ElseIf n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e.accept(this, env);
				n.s1.accept(this, env);
				if(n.s2 != null){
					n.s2.accept(this, env);
				}
			}
			else{
				String oldChiselIndent = chiselIndent;
				chiselIndent = chiselIndent + "\t";
				chiselCode = chiselCode + ".elsewhen (";
				n.e.accept(this, env);
				chiselCode = chiselCode +"){\n";
				chiselCode = chiselCode + chiselIndent;
				n.s1.accept(this, env);
				chiselCode = chiselCode + "}\n";
				if(n.s2 != null){
					chiselCode = chiselCode + oldChiselIndent + ".otherwise{\n";
					chiselCode = chiselCode + chiselIndent;
					n.s2.accept(this, env);
					chiselCode = chiselCode + "\n";
				}
			}
		}
		else{
			String old = indent;
			indent = indent + "  ";
			cCode = cCode +("else if (");
			n.e.accept(this,env);
			cCode = cCode +(") {\n");
			cCode = cCode +(indent);
			n.s1.accept(this,env);
			cCode = cCode +("}\n");
			if(n.s2 !=null){
				cCode = cCode +(old + "else {\n");
				cCode = cCode +(indent);
				n.s2.accept(this,env);
				cCode = cCode +"\n}";
			}
			indent = old;
		}

		return null;}

	public Object visit(Entity n, Object env) {

		cCode= cCode +" // Params for actor ";		
		n.it.accept(this, env);

		cCode= cCode +" instance  ";	

		n.i.accept(this, env);	
		cCode= cCode +"\n int ";	
		n.i.accept(this, env);
		cCode= cCode +"_state=0;\n";
		for(VarDecl v : n.parms){
			v.accept(this, env);
		}
		return null;
	}

	public Object visit(EntityPort n, Object env) {
		//cCode = cCode +(n.t.s + "_");
		boolean isTopPort =false;
		if(n.i.s !=null)
			cCode = cCode +(n.i.s+"_"); 
		else{
			isTopPort=true;
			cCode= cCode +"top_";
		}

		cCode = cCode +(n.p.s);
		return isTopPort;
	}


	public Object visit(Equal n, Object env) {
		if(!printChisel)
			if(!isFirstIteration)
				cCode = cCode +("(");
		n.e1.accept(this,env);
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + " === ";
		}
		else
			cCode = cCode +(" == ");
		n.e2.accept(this,env);
		if(!printChisel)
			if(!isFirstIteration)
				cCode = cCode +(")");
		return null;
	}

	@Override
	public Object visit(ExpIndexer n, Object env) {
		//cCode = cCode +("[");

		n.structure.accept(this, env);
		
		if(printChisel){
			// Add the index and the array to the read index list
			if(n.structure instanceof IdentifierExp && n.location instanceof IdentifierExp)
				arrayAndIndexRead.putIfAbsent(((IdentifierExp)n.structure).s, ((IdentifierExp)n.location).s);
				
		}
		else
		//for(Exp ex: n.location)
		{
			cCode = cCode +("[");
			n.location.accept(this, env);
			cCode = cCode +("]");

		}

		return null;
	}

	// Type t;
	// Identifier i;
	public Object visit(Formal n, Object env) {

		if(n.t!=null)
			if(n.t instanceof ListType){
				n.t.accept(this,n.i.s);
				return "";
			}
			else if(n.t instanceof FloatType){
				n.t.accept(this,n.i.s);
			}
			else	
				cCode = cCode +(indent +"int");
		
		cCode = cCode +(" ");
		String s= (String)n.i.accept(this,env);
		return s;
	}

	public Object visit(FunctionCall n, Object env){
		if(printChisel){

		}
		else{
			int i;
			n.i.accept(this, env);
			cCode = cCode +("(");
			for(i = 0; i < n.exs.size(); i++){
				n.exs.get(i).accept(this,env);

				if(i < n.exs.size()-1)
					cCode = cCode +(", ");			

			}
			cCode = cCode +(")");
			printPort = false;	
		}
		
		return null;
	}

	// Chisel part is not completed. Inputs are named as in1, in2 .. they must be connected to proper argument names in order to avoid
	// troubles within the function while using the arguments.
	public Object visit(FunctionDecl n, Object env) {
		if(n.i.s.startsWith("Mop_") || n.i.s.startsWith("Vop_"))
			return null;
		
		if(printChisel){
			if(isFirstIteration){
				
			}
			else{
				chiselCode = chiselCode + "class ";
				n.i.accept(this, env);
				chiselCode = chiselCode + "( ) extends Module {\n";
				chiselCode = chiselCode + chiselIndent + "val io = IO(new Bundle {\n";
				if(n.fl != null){
					for ( int i = 0; i < n.fl.size(); i++ ) {
						chiselCode = chiselCode + chiselIndent +  "val in" + i + " = Input(UInt(32))\n";
					}
				}
				chiselCode = chiselCode + chiselIndent +  "val out = Output(UInt(32))\n";
				chiselCode = chiselCode + chiselIndent + "})\n";
			}
		}
		else {
			String old = indent;
			cCode = cCode + (indent + "static ");
			if(n.t!=null)
				n.t.accept(this,env);
			else 
				cCode = cCode +("int");
			cCode = cCode +(" ");
			n.i.accept(this,env);
			cCode = cCode +(" (");
			if(n.fl!=null)
				for ( int i = 0; i < n.fl.size(); i++ ) {
					n.fl.get(i).accept(this,env);
					if (i+1 < n.fl.size()) { cCode = cCode +(", "); }
				}
			cCode = cCode +(") { \n");
			indent = indent + "  ";
			if(n.vl!=null)
				for ( int i = 0; i < n.vl.size(); i++ ) {
					cCode = cCode +(indent);
					n.vl.get(i).accept(this,env);
					cCode = cCode +("\n");
				}		
	
	
			if(n.e instanceof ListComprehension){		
				n.e.accept(this,n.i.s+"_ARRAY");		
			}
			else{		
				cCode = cCode +(indent + "return ");
				n.e.accept(this,env);
			}
			indent = old;
			cCode = cCode +(";\n");
			cCode = cCode +("  }\n");
		}
		return null;
	}

	@Override
	public Object visit(GenIntegers n, Object env) {

		//TODO GENinteger
		//	    String s=(String)env;
		//		
		//		cCode = cCode +"for( " +s ;
		//		
		//		cCode = cCode +(" = ");
		//		n.e1.accept(this,env);
		//		cCode = cCode +("- 1; " + s +"<=");
		//		n.e2.accept(this,env);
		//		cCode = cCode +" - 1; "+ s+" ++)\n";



		FormalList genFrs= new FormalList();
		String var="";
		if(env instanceof FormalList){
			genFrs=(FormalList)env;
			if (genFrs.size()>0){
				for(Formal genFr: genFrs){
					cCode = cCode +("for(");
					genFr.accept(this, env);
					cCode = cCode +(" = (");
					n.e1.accept(this,env);
					//cCode = cCode +("; " + genFr.i.s +"<=");
					cCode = cCode +(" - 1); " + genFr.i.s +" < "); // Added -1 to the beginning because CAL array starts from 1 instead of 0, and removed equality - Suleyman
					n.e2.accept(this,env);
					cCode = cCode +"; "+ genFr.i.s+" ++)\n";
					var=genFr.i.s;
				}
			}
		}
		else if (env instanceof VarDeclList){
			VarDeclList varss = (VarDeclList)env;
			for(VarDecl vars: varss){
				if(vars instanceof VarDeclSimp)
					var = ((VarDeclSimp)vars).i.s;
				else
					var ="i_0";
				cCode = cCode +"\nfor( int " + var ;
				cCode = cCode +(" = (");
				n.e1.accept(this, env);
				//cCode = cCode +("; " + var +"<=");
				cCode = cCode +(" - 1); " + var +" < "); // Added -1 to the beginning because CAL array starts from 1 instead of 0, and removed equality - Suleyman 
				n.e2.accept(this, env);
				cCode = cCode +"; "+ var+" ++)\n";

			}
		}
		else{
			var ="i_0";
			cCode = cCode +"\nfor( int " +var ;
			cCode = cCode +(" = (");
			n.e1.accept(this,env);
			//cCode = cCode +("; " + var +"<=");
			cCode = cCode +(" - 1); " + var +" < "); // Added -1 to the beginning because CAL array starts from 1 instead of 0, and removed equality - Suleyman
			n.e2.accept(this,env);
			cCode = cCode +"; "+ var+" ++)\n";

		}


		return var;
	}

	@Override
	public Object visit(GoTo n, Object e) {
		cCode = cCode +("goto " +n.s+";");
		return null;
	}

	public Object visit(GreaterOrEqual n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				chiselCode = chiselCode + "( ";
				n.e1.accept(this, env);
				chiselCode = chiselCode + " >= ";
				n.e2.accept(this, env);
				chiselCode = chiselCode + " ) ";
			}
		}
		else{
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" >= ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}
		return null;
	}

	public Object visit(GreaterThan n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else{
				chiselCode = chiselCode + "( ";
				n.e1.accept(this, env);
				chiselCode = chiselCode + " > ";
				n.e2.accept(this, env);
				chiselCode = chiselCode + " )";
			}
		}
		else{
			cCode = cCode + ("(");
			n.e1.accept(this, env);
			cCode = cCode + (" > ");
			n.e2.accept(this, env);
			cCode = cCode + (")");
		}
		return null;
	}

	// Type t;
	// Identifier i;
	// FormalList fl;
	// VarDeclList vl;
	// StatementList sl;
	// Exp e;
	public Object visit(GuardDecl n, Object env) {
		if(printChisel){
			
		}
		else {
		String old = indent;
			cCode = cCode +(indent+"");
			if(n.t!=null)
				n.t.accept(this,env);
			else 
				cCode = cCode +("int");
			cCode = cCode +(" ");
			n.i.accept(this,env);
			cCode = cCode +(" () { \n");
			indent = indent + "  ";
			if(n.vl!=null)
				for ( int i = 0; i < n.vl.size(); i++ ) {
					cCode = cCode +(indent);
					n.vl.get(i).accept(this,env);
					cCode = cCode +("\n");
				}
	
			if(n.sl != null)
				for ( int i = 0; i < n.sl.size(); i++ ) {
					indent = old+"  ";
					cCode = cCode + (indent);
					n.sl.get(i).accept(this,env);
					if ( i < n.sl.size() ) { cCode = cCode +("\n"); }
				}
	
	
			cCode = cCode + (indent + "return ");
			if(n.i.s.endsWith("One_Guard"))
				System.out.print("one is hear");
			for(int i=0; i < n.es.size(); i++){
				if(n.es.get(i) !=null)
					n.es.get(i).accept(this,env);
				if(i < n.es.size()-1)
					cCode = cCode +(" && ");
				else
					cCode = cCode +(";");
	
			}
			indent = old;
			cCode = cCode +(" \n}\n");
		}
		return null;
	}

	// String s;
	public Object visit(Identifier n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				if(isAssignLeft){
					if(!variablesWritten.contains(n.s)){
						variablesWritten.add(n.s);
					}
				}
				else if(!variablesRead.contains(n.s))
					variablesRead.add(n.s);
			}
			else {
				chiselCode = chiselCode + (n.s.replace('.', '_'));
				
				if(isAssignLeft){
					if(varVersions.containsKey(n.s)){
						chiselCode = chiselCode + "_v" + (varVersions.get(n.s) + 1);
					}
					if(newBlock)
						phiVariables.add(n.s);
				}
				else{
					if(varVersions.containsKey(n.s)){
						chiselCode = chiselCode + "_v" + varVersions.get(n.s);
					}
				}
			}
		}
		else
			cCode = cCode +(n.s.replace('.','_')); 
		return n.s;
	}

	// String s;
	public Object visit(IdentifierExp n, Object env) {

		if(printChisel){
			if(isFirstIteration){
								
				if(!isAssignLeft && !variablesRead.contains(n.s)){
					variablesRead.add(n.s);
				}
				else if(isAssignLeft){
					if( !variablesWritten.contains(n.s)){
						variablesWritten.add(n.s);
					}
				}
			}
			else {
				if(n.s.startsWith("$old$"))
					if(oldval)
						chiselCode = chiselCode + ("old_"+n.s.substring(5));
					else
						chiselCode = chiselCode + (n.s.substring(5));
				else  		
					chiselCode = chiselCode + (n.s.replace('.','_'));
				
				if(isAssignLeft){
					if(varVersions.containsKey(n.s)){
						// use a new version (the version will be increased at the end of the assignment)
						chiselCode = chiselCode + "_v" + (varVersions.get(n.s) + 1);	
					}
					if(newBlock)
						phiVariables.add(n.s);
				}
				else{
					if(varVersions.containsKey(n.s)){
						chiselCode = chiselCode + "_v" + varVersions.get(n.s);
					}
				}
			}
		}
		else{
			if(n.s.startsWith("$old$"))
				if(oldval)
					cCode = cCode +("old_"+n.s.substring(5));
				else
					cCode = cCode +(n.s.substring(5));
			else  		
				cCode = cCode +(n.s.replace('.','_'));
		}
		return n.s;
	}

	// String s;
	public Object visit(IdentifierType n, Object env) {
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + n.s;
		}
		else
			cCode = cCode +(n.s);
		return n.s;
	}

	// Exp e;
	// Statement s1,s2;
	public Object visit(If n, Object env) {
		phiVariables.clear();
		newBlock = true;
		HashMap<String, Integer> varVersionsOld = new HashMap<String, Integer>();
		varVersionsOld.putAll(varVersions);
		
		String old = indent;
		indent = indent + "";
		String chiselIndentOld = chiselIndent;
		
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + "when ( ";
		}
		else
			cCode = cCode +("if (");
		
		n.e.accept(this, env);
		
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + " ){\n";
		}
		else{
			cCode = cCode + ("){ \n");
			//cCode = cCode + (indent);
		}
		
		chiselIndent = chiselIndent + "\t";
		n.s1.accept(this, env);
		chiselIndent = chiselIndentOld;
		
		ArrayList<String> phiFunctionsPart1 = new ArrayList<String>();
		ArrayList<String> phiFunctionsPart2 = new ArrayList<String>();
		
		if(printChisel){
			if(!isFirstIteration){
				chiselCode = chiselCode + chiselIndent + "}\n";
				
				if(n.s2 == null)
					chiselCode = chiselCode + "\n" + chiselIndent + "//Phi functions (Muxes) go in here\n";
				
				// Add the phi function here (as a mux)
				// which versions of the variables will we use?
				for(int i = 0; i < phiVariables.size(); i++){
					String currentVariable = phiVariables.get(i);
					
					phiFunctionsPart1.add(chiselIndent + currentVariable + "_v" + (varVersions.get(currentVariable) + 1) + " := Mux(");
					//n.e.accept(this, env);
					phiFunctionsPart2.add(", " + currentVariable + "_v" + varVersions.get(currentVariable) + ", " + currentVariable + "_v" + varVersionsOld.get(currentVariable) + ")\n");
				
					varVersions.replace(currentVariable, varVersions.get(currentVariable) + 1);
				}
			}
		}
		else
			cCode = cCode + old + ("}\n");
		
		if(n.s2 != null){
			phiVariables.clear();
			varVersionsOld.clear();
			newBlock = true;
			varVersionsOld.putAll(varVersions);
			
			if(printChisel){
				if(!isFirstIteration)
					chiselCode = chiselCode + chiselIndent + ".otherwise {\n";
			}
			else{
				cCode = cCode + old + "else {\n";
			}
			
			chiselIndent = chiselIndent + "\t";
			n.s2.accept(this, env);
			chiselIndent = chiselIndentOld;
			
			if(printChisel){
				if(!isFirstIteration){
					chiselCode = chiselCode + chiselIndent + "}\n";
					chiselCode = chiselCode + "\n" + chiselIndent + "//Phi functions (Muxes) go in here\n";
					
					// Add the phi function here (as a  mux)
					// which versions of the variables will we use?
					for(int i = 0; i < phiVariables.size(); i++){
						String currentVariable = phiVariables.get(i);
						
						// We need to delay the inputs of the muxes
						/** PIPELINING **/
						String input1 = currentVariable + "_v" + varVersions.get(currentVariable);
						String input2 = currentVariable + "_v" + varVersionsOld.get(currentVariable);
						
						// Fix the input delays
						int input1Delay = 0;
						int input2Delay = 0;
						int newInputDelay = 0;
						// If there is no global for the inputs then they are the inputs to the accelerator
						if(globalDelays.containsKey(input1))
							input1Delay = globalDelays.get(input1);
						
						if(globalDelays.containsKey(input2))
							input2Delay = globalDelays.get(input2);
						
						if(input1Delay > input2Delay){
							for(int j = 0; j < input1Delay - input2Delay; j++){
								// Add registers to close the delay gap between the inputs
								if( j == 0){
									chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + j + " = RegNext(" + input2 + ", 0.U)\n";
								}
								else{
									chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + j + " = RegNext(" + input2 + "_Reg" + (j - 1) + ", 0.U)\n";
								}
							}
							
							chiselCode = chiselCode + chiselIndent + currentVariable + "_v" + (varVersions.get(currentVariable) + 1) + " := Mux( !( ";
							n.e.accept(this, env);
							chiselCode = chiselCode + " ), " + currentVariable + "_v" + varVersions.get(currentVariable) + ", " + currentVariable + "_v" + varVersionsOld.get(currentVariable) + "_Reg" + 
							(input1Delay - input2Delay - 1) +")\n";
							
							newInputDelay = input1Delay;
						}
						else if(input2Delay > input1Delay){
							for(int j = 0; j < input2Delay - input1Delay; j++){
								// Add registers to close the delay gap between the inputs
								if( j == 0){
									chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + j + " = RegNext(" + input1 + ", 0.U)\n";
								}
								else{
									chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + j + " = RegNext(" + input1 + "_Reg" + (j - 1) + ", 0.U)\n";
								}
							}
							
							chiselCode = chiselCode + chiselIndent + currentVariable + "_v" + (varVersions.get(currentVariable) + 1) + " := Mux( !( ";
							n.e.accept(this, env);
							chiselCode = chiselCode + " ), " + currentVariable + "_v" + varVersions.get(currentVariable) + "_Reg" + 
									(input2Delay - input1Delay - 1) + ", " + currentVariable + "_v" + varVersionsOld.get(currentVariable) +")\n";
							
							newInputDelay = input2Delay;
						}
						
						/** END OF PIPELINE **/
						else{
							chiselCode = chiselCode + chiselIndent + currentVariable + "_v" + (varVersions.get(currentVariable) + 1) + " := Mux( !( ";
							n.e.accept(this, env);
							chiselCode = chiselCode + " ), " + currentVariable + "_v" + varVersions.get(currentVariable) + ", " + currentVariable + "_v" + varVersionsOld.get(currentVariable) + ")\n";
							newInputDelay = input2Delay;
						}
						
						chiselCode = chiselCode + chiselIndent + "// " + currentVariable + "_v" + (varVersions.get(currentVariable) + 1) + " total delay: " + newInputDelay + "\n";
						// Set the delay value of the new variable
						globalDelays.put(currentVariable + "_v" + (varVersions.get(currentVariable) + 1), newInputDelay);
						
						varVersions.replace(currentVariable, varVersions.get(currentVariable) + 1);
					}
				}
			}
			else {
				cCode = cCode + old + ("}\n");
			}
		}
		
		for(int i = 0; i < phiFunctionsPart1.size(); i++){
			chiselCode = chiselCode + phiFunctionsPart1.get(i);
			n.e.accept(this, env);
			chiselCode = chiselCode + phiFunctionsPart2.get(i);
		}
		
		phiVariables.clear();
		newBlock     = false;
		indent       = old;
		return null;
	}

	// Exp c,e1,e2;
	public Object visit(IfExp n, Object env){
		if(printChisel){
			if(isFirstIteration){
				n.c.accept(this, env);
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else{
				chiselCode = chiselCode + "Mux(";
				n.c.accept(this, env);
				chiselCode = chiselCode + ", ";
				n.e1.accept(this, env);
				chiselCode = chiselCode + ", ";
				n.e2.accept(this, env);
				chiselCode = chiselCode + ")";
			}
		}
		else{
			cCode = cCode +("(");
			n.c.accept(this,env);
			cCode = cCode +(" ? ");
			n.e1.accept(this,env);
			cCode = cCode +(" : ");
			if(n.e2!=null)
				n.e2.accept(this,env);
			else
				cCode = cCode + "0";
			cCode = cCode +(")");
		}
		
		return null;
	}

	// int i;
	public Object visit(IntegerLiteral n, Object env) {
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + n.i + ".U";
		}
		else
			cCode = cCode +(""+ n.i);
		
		return null;
	}


	public Object visit(IntegerType n, Object env) {

		String sSize;
		if(n.size<=8)
			sSize =  "8_t";

		else if(n.size<=16)
			sSize = "16_t";

		else if(n.size<=32)
			sSize =  "32_t";

		else //if(n.size<=64)
			sSize =  "64_t";

		/*if(isGlobal){
			if((n.size % 8)==0){
				cCode = cCode +"int" + sSize;
				return null;
			}
			else{
				cCode = cCode + "struct { int"+ sSize + " oddbit:"+n.size +";}";
				return (String)"oddbit";
			}
		}
		else*/
		//sSize = "";	// removed to enable 64_t
		cCode = cCode + "int" + sSize;
		return null;
	}

	@Override
	public Object visit(Lable n, Object e) {

		cCode = cCode +("\n"+n.s+":\n");
		return null;
	}

	// Exp e1,e2;
	public Object visit(LeftShift n, Object env) {
		
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else{
				chiselCode = chiselCode + "( ";
				n.e1.accept(this, env);
				chiselCode = chiselCode + " << ";
				n.e2.accept(this, env);
				chiselCode = chiselCode + " )";
			}
			
		}
		else{
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" << ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}
		return null;
	}

	public Object visit(LessOrEqual n, Object env) {

		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else{
				chiselCode = chiselCode + ("( ");
				n.e1.accept(this, env);
				chiselCode = chiselCode +(" <= ");
				n.e2.accept(this, env);
				chiselCode = chiselCode + (" )");
			}
		}
		else{
			cCode = cCode +("( ");
			n.e1.accept(this, env);
			cCode = cCode +(" <= ");
			n.e2.accept(this, env);
			cCode = cCode + (" )");
		}
		return null;
	}

	// Exp e1,e2;
	public Object visit(LessThan n, Object env) {
		
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				chiselCode = chiselCode + ("( ");
				n.e1.accept(this, env);
				chiselCode = chiselCode + (" < ");
				n.e2.accept(this, env);
				chiselCode = chiselCode + (" )");
			}
		}
		else{
			cCode = cCode + ("( ");
			n.e1.accept(this, env);
			cCode = cCode + (" < ");
			n.e2.accept(this, env);
			cCode = cCode + (" )");
		}
		return null;
	}

	@Override
	public Object visit(ListAssign n, Object env) {		
		//cCode = cCode + indent;
		isAssignLeft = true;
		n.i.accept(this, env);
		isAssignLeft = false;
		if(printChisel){
			if(!isFirstIteration)
				chiselCode = chiselCode + " := ";
			else{
				String tmp1 = "";
				if(((ExpIndexer) n.i).location instanceof IntegerLiteral){
					tmp1 = Integer.toString(((IntegerLiteral)((ExpIndexer) n.i).location).i);
				}
				else{
					tmp1 = ((IdentifierExp)((ExpIndexer) n.i).location).s;
				}
				
				String tmp2 = ((IdentifierExp)((ExpIndexer) n.i).structure).s;
				
				arrayAndIndexWritten.putIfAbsent(tmp2, tmp1);
				arrayIndices.add(tmp1);
			}
		}
		else
			cCode = cCode + " = ";
		
		if(n.i instanceof IdentifierExp)
			n.e.accept(this, ((IdentifierExp)n.i).s);
		else
			n.e.accept(this, env);
		
		if(printChisel){
			String tmp = ((IdentifierExp)((ExpIndexer) n.i).structure).s;
			if(varVersions.containsKey(tmp)){
				varVersions.replace(tmp, varVersions.get(tmp) + 1);
				if(!isFirstIteration && n.e instanceof IdentifierExp){
					String var = ((IdentifierExp)n.e).s + "_v" + varVersions.get(((IdentifierExp)n.e).s);
					if(globalDelays.containsKey(var))
						globalDelays.put(tmp + "_v" + varVersions.get(tmp), globalDelays.get(var));
				}	
			}
			
		}
		else{
			cCode = cCode + ";";   
			if(n.len != null)
				cCode = cCode + "// for loop;";
		}

		return null;
	}

	public Object visit(ListCompGen n, Object env){

		//		if(n.fils!=null)
		//			cCode = cCode +  "\n "+ comint +"//  ListCompGen colExp " + (n.colExp!=null) +" fils "+ n.fils.size()+"\n";
		//		else
		//			cCode = cCode +  "\n "+ comint +"//  ListCompGen colExp " + (n.colExp!=null) +"\n";
		//		comint = comint + "   ";
		//
		//		//cCode = cCode +("ListCompGenFiliter " + n.colExp.toString());
		//		//		if(n.vars!=null)
		//		//			for(Formal f: n.vars){			
		//		//				genFr= f;//
		//		//				//f.accept(this,env);
		//		//			}
		//		//	cCode = cCode +(" n.vars ListCompGenFiliter ");
		//		String var="";
		//		if(n.colExp!=null){
		//			cCode = cCode + "\n "+ comint +"//  n.colExp " + n.colExp.toString() +"\n";
		//			if(n.colExp instanceof GenIntegers){
		//				PrintIntegrs((GenIntegers)n.colExp,n.fils,n.vars,env);
		//				var=(String)n.colExp.accept(this,n.vars);
		//			}
		//			else
		//				n.colExp.accept(this, env);
		//			}
		//		else
		//		{
		//			if(n.fils != null)
		//			{
		//				cCode = cCode + "\n "+ comint +"// nn.fils ListCompGenFiliter "+n.fils.size()+"\n";			
		//				if(n.fils.size()>0)
		//					for(Exp ex: n.fils)
		//						ex.accept(this,n.vars);
		//				//		ExpList es=(ExpList)(env);
		//				//		if(es!=null)
		//				//		for(Exp e:es){
		//				//			e.accept(this, null);
		//				//		}
		//			}
		//			if(n.vars!=null){
		//				cCode = cCode + "\n "+ comint +"//n.vars \n";
		//				for(Formal f:n.vars)
		//
		//					f.accept(this, env);
		//				cCode = cCode + comint;
		//			}
		//		}
		//		//	cCode = cCode +(" \nn.fils ListCompGenFiliter");
		//
		//		cCode = cCode +"end--------\n n.colExp ListCompGenFiliter";
		//
		//
		//
		//


		String var="";
		if(n.colExp!=null)
			if(n.colExp instanceof GenIntegers)
				var=(String)n.colExp.accept(this,n.vars);
			else
				n.colExp.accept(this, env);
		//	cCode = cCode +("\n n.colExp ListCompGenFiliter");
		if(n.fils != null)
			for(Exp ex: n.fils)
				ex.accept(this,n.vars);



		return var;

	}




	public Object visit(ListComprehension n, Object env){
		//		cCode = cCode + "\n "+ comint +"// ListComprehension \n";
		//		comint = comint + "   ";
		//		String var=(String) env;
		//		String ss=instName;/* + " " +(String)env ;
		//
		//		//TODO LIST COMPH
		//		if((String)env !=null)
		//			System.out.print("\n"+ss)*/;
		//			if(n.eles!=null && n.compGen!=null){
		//				cCode = cCode +  "\n "+ comint +"//  Elements "+n.eles.size()+" " + (n.compGen.size())+"\n";
		//
		//
		//				for(int icg=0;icg<n.compGen.size();icg++){
		//					//					cCode = cCode +  var+"_cg_"+icg;
		//					//if(n.compGen.get(icg) instanceof GenInteger)
		//					cCode = cCode +"\n  copGen "+ n.compGen.get(icg);
		//							n.compGen.get(icg).accept(this,  var+"_cg_"+icg);
		//				}
		//
		//				for(Exp e: n.eles){
		//					if(! (e instanceof ListComprehension)){
		//
		//						cCode = cCode +"\n  ele  " +e.toString();
		//							e.accept(this, null);
		//
		//					}
		//
		//				}
		//			}
		//			else if(n.eles!=null)
		//				if(n.eles.size()>0){
		//					cCode = cCode +  "\n "+ comint +"//  Elements "+n.eles.size()+" " + (n.compGen!=null)+"\n";
		//					cCode = cCode + "int "+var+ "_temp"+" [] ={";
		//					for(int ie=0;ie<n.eles.size();ie++){
		//
		//						//if(! (n.eles.get(ie) instanceof ListComprehension))
		//						{
		//							n.eles.get(ie).accept(this, null);
		//							if(ie<n.eles.size()-1)
		//								cCode = cCode + ", ";
		//							else
		//								cCode = cCode +"};\n ";
		//						}
		//
		//					}
		//					cCode = cCode + "  assignarray("+var+", "+var+"_temp, "+n.eles.size()+");";
		//				}
		//
		//
		//			//		 if(var!=null)
		//			//	    	cCode = cCode + var + " = ";
		//
		//
		//			//			cCode = cCode +  "\n DisplayListComprehension \n";
		//			//
		//			//		
		DisplayListComprehension(n,env);

		return null;
	}
	public Object visit(ListType n, Object env) {


		List<Type> ts= new ArrayList<Type>();

		Type t=n;
		if(n.t!=null)
			if(n.t instanceof ListType){
				while(((ListType)t).t instanceof ListType){
					ts.add(t);
					t=((ListType)t).t;
				}
				ts.add(t);

				if(ts.size()>0){
					//ts.get(ts.size()-1).accept(this, env);
					((ListType)ts.get(ts.size()-1)).t.accept(this, env);
					cCode = cCode +" " +env;

					for(int it=0;it<ts.size();it++){
						if(ts.get(it) instanceof ListType){				
							cCode = cCode +"[";
							((ListType)ts.get(it)).len.accept(this, env);			
							cCode = cCode +("]");

						}
						else
							n.t.accept(this, env);

					}
				}
			}
			else {
				n.t.accept(this, env);

				cCode = cCode +" "+ env+" [";
				n.len.accept(this, env);
				cCode = cCode +("]");
				return null;
			}


		//cCode = cCode +("List\n");


		//		if(n.t instanceof ListType)


		/*	cCode = cCode +("List");
		if(n.mval != null){
			Map<String, Exp> mv = n.mval;
			for(Map.Entry<String, Exp> entry : mv.entrySet()){
				cCode = cCode +("("+entry.getKey() + "=");
				entry.getValue().accept(this,env);				
				cCode = cCode +(")");
			}
			}
		if(n.mtype != null){
			Map<String, Type> mt = n.mtype;
			for(Map.Entry<String, Type> entry : mt.entrySet()){
				cCode = cCode +("("+entry.getKey() + "=");
				entry.getValue().accept(this,env);				
				cCode = cCode +(")");
			}
			}*/
		return null;

	}


	// TODO we need to find out either to use integer or floating point operation
	// Exp e1,e2;
	public Object visit(Minus n, Object env) {
		
		if(printChisel){
			// First we need to find the type of the variables. If integer then simple minus. If float then fpAdd().
			
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else{
				// If integer
				/*
				chiselCode = chiselCode +("(");
				n.e1.accept(this, env);
				chiselCode = chiselCode +(" - ");
				n.e2.accept(this, env);
				chiselCode = chiselCode +(")");
				*/
				
				// if float or complex
				int indexOfLastNewline = 0;
				for (int pos = chiselCode.indexOf("\n"); pos != -1; pos = chiselCode.indexOf("\n", pos + 1)) {
					indexOfLastNewline = pos;
				}

				//if((n.e1 instanceof IdentifierExp) && (n.e2 instanceof IdentifierExp)){
				
				String input1 = "";
				String input2 = "";
				
				// Let's check if the n.e1 is a single variable or an array
				if(n.e1 instanceof IdentifierExp)
					input1 = ((IdentifierExp) n.e1).s;
				else if(n.e1 instanceof ExpIndexer)
					input1 = ((IdentifierExp) ((ExpIndexer) n.e1).structure).s;
				
				if(n.e2 instanceof IdentifierExp)
					input2 = ((IdentifierExp) n.e2).s;
				else if(n.e1 instanceof ExpIndexer)
					input2 = ((IdentifierExp) ((ExpIndexer) n.e2).structure).s;
				
				boolean complexArithmetics = false;
				
				// If complex
				if(input1.startsWith("complex_") || input2.startsWith("complex_"))
					complexArithmetics = true;
				else
					complexArithmetics = false;
					
					if(complexArithmetics)
						chiselCode = chiselCode + "C_sub" + C_subCounter + ".io.out\n";
					else
						chiselCode = chiselCode + "FP_sub" + subCounter + ".io.out\n";
					
					
					/** PIPELINING **/
					//String input1 = ((IdentifierExp) n.e1).s;
					//String input2 = ((IdentifierExp) n.e2).s;
					input1 = input1 + "_v" + varVersions.get(input1);
					input2 = input2 + "_v" + varVersions.get(input2);
					// Fix the input delays
					int input1Delay = 0;
					int input2Delay = 0;
					int newInputDelay = 0;
					
					// If there is no global for the inputs then they are the inputs to the accelerator
					if(globalDelays.containsKey(input1))
						input1Delay = globalDelays.get(input1);
					
					if(globalDelays.containsKey(input2))
						input2Delay = globalDelays.get(input2);
					
					if(input1Delay > input2Delay){
						for(int i = 0; i < input1Delay - input2Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + i + " = RegNext(" + input2 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + i + " = RegNext(" + input2 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input1Delay;
						
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_sub" + C_subCounter + " = Module(new ComplexSub())").toString();
							//chiselCode = chiselCode + "C_sub" + C_subCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_sub"+ C_subCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_sub"+ C_subCounter + ".io.in2 := " + input2 + "_Reg" + (input1Delay - input2Delay - 1);		
							//n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_sub" + subCounter + " = Module(new FPAdd(32))").toString();
							chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in2 := \"b10000000000000000000000000000000\".U ^ " + input2 + "_Reg" + (input1Delay - input2Delay - 1);		
							//n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
					}
					else if(input2Delay > input1Delay){
						for(int i = 0; i < input2Delay - input1Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input2Delay;
						
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_sub" + C_subCounter + " = Module(new ComplexSub())").toString();
							//chiselCode = chiselCode + "C_sub" + C_subCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_sub"+ C_subCounter + ".io.in1 := "+ input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_sub"+ C_subCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_sub" + subCounter + " = Module(new FPAdd(32))").toString();
							//chiselCode = chiselCode + "C_sub" + C_subCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in1 := "+ input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in2 := \"b10000000000000000000000000000000\".U ^ ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
							
					}
					else {
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_sub" + C_subCounter + " = Module(new ComplexSub())").toString();
							//chiselCode = chiselCode + "C_sub" + C_subCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_sub"+ C_subCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_sub"+ C_subCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
							newInputDelay = input2Delay;
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_sub" + subCounter + " = Module(new FPAdd(32))").toString();
							//chiselCode = chiselCode + "C_sub" + C_subCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in2 := \"b10000000000000000000000000000000\".U ^ ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
							newInputDelay = input2Delay;
						}
							
					}
					
					// Set the new delay
					if(complexArithmetics){
						localDelay = complexSubDelay + newInputDelay;
						C_subCounter++;
					}
					else{
						localDelay = floatSubDelay + newInputDelay;
						subCounter++;
					}
					
					/**  END OF PIPELINING **/
					
/*				}
				else{
					// if float
					chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val FP_sub" + subCounter + " = Module(new FPAdd(32))").toString();
					chiselCode = chiselCode + "FP_sub" + subCounter + ".io.out\n";
					chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in1 := ";
					n.e1.accept(this, env);
					chiselCode = chiselCode + "\n";
					chiselCode = chiselCode + chiselIndent + "FP_sub"+ subCounter + ".io.in2 := \"b10000000000000000000000000000000\".U ^ ";		
					n.e2.accept(this, env);
					//chiselCode = chiselCode + "\n";
					subCounter++;
				}*/
			}
		}
		else{
			// Check if the variables are complex (if so, call the complex operation)
			if(n.e1 instanceof IdentifierExp && ((IdentifierExp)n.e1).s.startsWith("complex_") ||
			n.e2 instanceof IdentifierExp && ((IdentifierExp)n.e1).s.startsWith("complex_")){
				
				cCode = cCode + "ComplexSub(";
				n.e1.accept(this, env);
				cCode = cCode + ", ";
				n.e2.accept(this, env);
				cCode = cCode + ")";
				
				complexSubFlag = true;
			}
			else {
				cCode = cCode +("(");
				n.e1.accept(this, env);
				cCode = cCode +(" - ");
				n.e2.accept(this, env);
				cCode = cCode +(")");
			}
		}
		
		return null;
	}


	public Object visit(Negate n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e.accept(this, env);
				n.e.accept(this, env);
			}
			else {
				chiselCode = chiselCode + "Cat(1 ^ ";
				n.e.accept(this, env);
				chiselCode = chiselCode + "(31), ";
				n.e.accept(this, env);
				chiselCode = chiselCode + "(30, 0))";
			}
		}
		else{
			cCode = cCode +("( - ");
			n.e.accept(this,env);
			cCode = cCode +(") ");
		}

		return null;
	}
	
	// Exp e;
	public Object visit(NewArray n, Object env) {
		cCode = cCode +("new int [");
		n.e.accept(this,env);
		cCode = cCode +("]");
		return null;
	}

	// Exp e;
	public Object visit(Not n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e.accept(this, env);
			}
			else {
				chiselCode = chiselCode + "!";
				n.e.accept(this, env);
			}
		}
		else{
			cCode = cCode +("(! ");
			n.e.accept(this,env);
			cCode = cCode +(")");
		}
		
		return null;
	}
	
	public Object visit(NotEqual n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				n.e1.accept(this, env);
				chiselCode = chiselCode + " != ";
				n.e2.accept(this, env);
			}
		}
		else {
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" != ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}
		
		return null;
	}
	
	// Exp e1,e2;
	public Object visit(Or n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				chiselCode = chiselCode + "( ";
				n.e1.accept(this, env);
				chiselCode = chiselCode + " ) || (";
				n.e2.accept(this, env);
				chiselCode = chiselCode + " )";
			}
		}
		else {
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" || ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}
		
		return null;
	}


	//TODO we need to find out either to use integer or floating point operation
	// Exp e1,e2;
	public Object visit(Plus n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				
				// if integer
				/*
				n.e1.accept(this, env);
				chiselCode = chiselCode + " + ";
				n.e2.accept(this, env);
				*/
				
				
				int indexOfLastNewline = 0;
				for (int pos = chiselCode.indexOf("\n"); pos != -1; pos = chiselCode.indexOf("\n", pos + 1)) {
					indexOfLastNewline = pos;
				}
				
				String input1 = "";
				String input2 = "";
				
				// Let's check if the n.e1 is a single variable or an array
				if(n.e1 instanceof IdentifierExp)
					input1 = ((IdentifierExp) n.e1).s;
				else if(n.e1 instanceof ExpIndexer)
					input1 = ((IdentifierExp) ((ExpIndexer) n.e1).structure).s;
				
				if(n.e2 instanceof IdentifierExp)
					input2 = ((IdentifierExp) n.e2).s;
				else if(n.e1 instanceof ExpIndexer)
					input2 = ((IdentifierExp) ((ExpIndexer) n.e2).structure).s;
				
				boolean complexArithmetics = false;
					
				// If complex
				if(input1.startsWith("complex_") || input2.startsWith("complex_"))
					complexArithmetics = true;
				else
					complexArithmetics = false;
					
					if(complexArithmetics)
						chiselCode = chiselCode + "C_add" + C_addCounter + ".io.out\n";
					else
						chiselCode = chiselCode + "FP_add" + addCounter + ".io.out\n";
					
					/** PIPELINING **/
					//input1 = ((IdentifierExp) n.e1).s;
					//input2 = ((IdentifierExp) n.e2).s;
					input1 = input1 + "_v" + varVersions.get(input1);
					input2 = input2 + "_v" + varVersions.get(input2);
					// Fix the input delays
					int input1Delay = 0;
					int input2Delay = 0;
					int newInputDelay = 0;
					
					// If there is no global for the inputs then they are the inputs to the accelerator
					if(globalDelays.containsKey(input1))
						input1Delay = globalDelays.get(input1);
					
					if(globalDelays.containsKey(input2))
						input2Delay = globalDelays.get(input2);
					
					if(input1Delay > input2Delay){
						for(int i = 0; i < input1Delay - input2Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + i + " = RegNext(" + input2 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input2 + "_Reg" + i + " = RegNext(" + input2 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input1Delay;
						
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_add" + C_addCounter + " = Module(new ComplexAdd())").toString();
							//chiselCode = chiselCode + "C_add" + C_addCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_add"+ C_addCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_add"+ C_addCounter + ".io.in2 := " + input2 + "_Reg" + (input1Delay - input2Delay - 1);		
							//n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_add" + addCounter + " = Module(new FPAdd(32))").toString();
							chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in2 := " + input2 + "_Reg" + (input1Delay - input2Delay - 1);		
							chiselCode = chiselCode + "\n";
						}
					}
					else if(input2Delay > input1Delay){
						for(int i = 0; i < input2Delay - input1Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input2Delay;
						
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_add" + C_addCounter + " = Module(new ComplexAdd())").toString();
							//chiselCode = chiselCode + "C_add" + C_addCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_add"+ C_addCounter + ".io.in1 := " + input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_add"+ C_addCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_add" + addCounter + " = Module(new FPAdd(32))").toString();
							chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in1 := " + input1 + "_Reg" + (input2Delay - input1Delay - 1);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
					}
					else{
						if(complexArithmetics){
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_add" + C_addCounter + " = Module(new ComplexAdd())").toString();
							//chiselCode = chiselCode + "C_add" + C_addCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_add"+ C_addCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_add"+ C_addCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_add" + addCounter + " = Module(new FPAdd32())").toString();
							chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						
						newInputDelay = input2Delay;
					}
					
					// Set the new delay
					if(complexArithmetics){
						localDelay = complexAddDelay + newInputDelay;
						C_addCounter++;
					}
					else{
						localDelay = floatAddDelay + newInputDelay;
						addCounter++;
					}
					/**  END OF PIPELINING **/
					
					
				//}
				//else { // if float
					/*chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val FP_add" + addCounter + " = Module(new FPAdd(32))").toString();
					chiselCode = chiselCode + "FP_add" + addCounter + ".io.out\n";
					chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in1 := ";
					n.e1.accept(this, env);
					chiselCode = chiselCode + "\n";
					chiselCode = chiselCode + chiselIndent + "FP_add"+ addCounter + ".io.in2 := ";		
					n.e2.accept(this, env);
					chiselCode = chiselCode + "\n";
					addCounter++;*/
				//}
			}
		}
		else{
			// Check if the variables are complex (if so, call the complex operation)
			if(n.e1 instanceof IdentifierExp && ((IdentifierExp)n.e1).s.startsWith("complex_") ||
			n.e2 instanceof IdentifierExp && ((IdentifierExp)n.e1).s.startsWith("complex_")){
				
				cCode = cCode + "ComplexAdd(";
				n.e1.accept(this, env);
				cCode = cCode + ", ";
				n.e2.accept(this, env);
				cCode = cCode + ")";
				complexAddFlag = true;
			}
			else {
				cCode = cCode + ( "(");
				n.e1.accept(this, env);
				cCode = cCode + (" + ");
				n.e2.accept(this, env);
				cCode = cCode + (")");
			}
		}
		
		return null;
	}


	public Object visit(PortHH n, Object env){

		ArrayList<String> portName= new ArrayList<String>();

		if(inputCons != null)
			if(inputCons.get(instName+"#"+ n.i.s) != null)
				portName.addAll(inputCons.get(instName+"#"+ n.i.s));
		if(outputCons != null && portName.size() == 0)
			if(outputCons.get(instName+"#"+ n.i.s) != null)
				portName.addAll(outputCons.get(instName+"#"+ n.i.s));
		if(portName.size() == 0)
			portName.add("  " + n.i.s);
		if(printPort)
			cCode = cCode + portName.get(0);
		return portName;
	}
	
	// Exp e;
	public Object visit(Print n, Object env) {
		if(printChisel){
			
		}
		else{
		
			if(! hsInclude.contains("stdio.h")){
				hsInclude.add("stdio.h");
				sInclude = sInclude + "#include <stdio.h>\n";
			}
			ExpList prExs = new ExpList();
			cCode = cCode + ("printf(\"");	
			String sPrint = "";
			for(int i = 0; i < n.es.size(); i++){
				if(n.es.get(i) instanceof StringLiteral)
					sPrint = sPrint + ((StringLiteral)n.es.get(i)).s;
				else{// if(n.es.get(i) instanceof IntegerLiteral){
					sPrint = sPrint + "%d";
					prExs.add(n.es.get(i));
				}
				//			else if(n.es.get(i) instanceof BoolLiteral){
				//				cCode=cCode + "%d";
				//				prExs.add(n.es.get(i));
				//			}
	
				if(i<n.es.size()-1)
					cCode = cCode + sPrint;
				else
					if(n.isln)
						cCode = cCode +sPrint+"\\n\"";
					else
						cCode = cCode +sPrint+"\"";			
			}
			for(Exp ex:prExs){
				cCode = cCode +",";
				ex.accept(this, env);
			}
			cCode = cCode +");";
		}

		return null;
	}
	
	public Object visit(ProcedureDecl n, Object env) {
		if(n.i.s.startsWith("acc__"))
			printChisel = true;
		
		if(printChisel){
			chiselCode = chiselCode + "\n\nclass ";
			n.i.accept(this, env);
			chiselCode = chiselCode + "( ) extends Module {\n";
			chiselCode = chiselCode + chiselIndent + "val io = IO(new Bundle {\n";
			if(n.fl != null){
				for ( int i = 0; i < n.fl.size(); i++ ) {
					chiselCode = chiselCode + chiselIndent +  "\tval in" + i + " = Input(UInt(32))\n";
				}
			}
			chiselCode = chiselCode + chiselIndent +  "\tval out = Output(UInt(32))\n";
			chiselCode = chiselCode + chiselIndent + "})\n\n";
			
			for ( int i = 0; i < n.fl.size(); i++ ) {
				chiselCode = chiselCode + chiselIndent + "val ";
				n.fl.get(i).accept(this, env);
				chiselCode = chiselCode + " = io.in" + i + "\n";
			}
	// TODO variable can be a complex, then the width should be 64.W		
			if(n.vl != null){
				for( int i = 0; i < n.vl.size(); i++ ){
					chiselCode = chiselCode + chiselIndent + "val ";
					n.vl.get(i).accept(this, env);
					chiselCode = chiselCode +  " = Wire(UInt(width = 32.W))\n";
				}
			}
		
			if(n.sl != null)
				n.sl.accept(this, env);
			
			chiselCode = chiselCode + "}";
			printChisel = false;
		}
		else {
			
			String old = indent;
			indent = "";
			cCode = cCode +"\nstatic ";
			if(n.t != null)
				n.t.accept(this,env);
			else 
				cCode = cCode +("void");
			cCode = cCode +(" ");
			n.i.accept(this,env);
			cCode = cCode +(" (");
			if(n.fl != null)
				for ( int i = 0; i < n.fl.size(); i++ ) {
					n.fl.get(i).accept(this,env);
					if (i+1 < n.fl.size()) { cCode = cCode +(", "); }
				}
			cCode = cCode +(") { \n");
			indent = indent + "";	
			//if(n.i.s.equals("idct1d"))
				//System.out.print(cCode);

			if(n.vl!=null)
				for ( int i = 0; i < n.vl.size(); i++ ) {
					cCode = cCode +(indent);
					n.vl.get(i).accept(this,env);
					cCode = cCode +("\n");
				}
			if(n.sl != null)
				n.sl.accept(this,env);
			if(n.e != null){
				cCode = cCode +("\n" + indent + "return ");		
				n.e.accept(this,env);
				indent = old;
				cCode = cCode +(";");
			}
			cCode = cCode +("\n }\n");
		}
		
		return null;
	}
	
	public Object visit(ReadToken n, Object env){
		ArrayList<String> conns = new ArrayList<String>();
		/*	if(n.rep instanceof IntegerLiteral)


			if(((IntegerLiteral)n.rep).i>1){
				cCode = cCode +"comm_peek(";
				conns.addAll((ArrayList<String>)n.p.accept(this,env));
				cCode = cCode +conns.get(0)+ ", "+ ((IntegerLiteral)n.rep).i +");\n";


				String index=n.p.i.s+"_ix";
				cCode = cCode + "\nfor(int "+index+" =0; " + index+ "<"+((IntegerLiteral)n.rep).i+"; " +index +"++)";
				n.ids.get(0).accept(this,env);
				cCode = cCode +"["+index+"] = ";
				cCode = cCode +("comm_peek(");
				conns.addAll((ArrayList<String>)n.p.accept(this,env));
				cCode = cCode +conns.get(0)+ ", 1);\n";
				return null;					
			}*/
		for(Identifier i: n.ids){
			cCode = cCode +"comm_peek(";
			conns.addAll((ArrayList<String>)n.p.accept(this,env));
			cCode = cCode + conns.get(0)+ ", &";
			i.accept(this,env);
			cCode = cCode + ", 1";//#Ayas
			//n.rep.accept(this, env);
			cCode = cCode  +");\n";

		}  
		
		return null;
	}
	// Exp e1,e2;
	public Object visit(RightShift n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				n.e1.accept(this, env);
				chiselCode = chiselCode + " >> ";
				n.e2.accept(this, env);
			}
			
		}
		else{
			cCode = cCode +("(");
			n.e1.accept(this,env);
			cCode = cCode +(" >> ");
			n.e2.accept(this,env);
			cCode = cCode +(")");
		}
		
		return null;
	}
	
	public Object visit(SendToken n, Object env){
		ArrayList<String> conns= new ArrayList<String>();
		conns.addAll((ArrayList<String>)n.p.accept(this, env));

		for(int i = 0; i < n.e.size(); i++) {
			if(conns.size() > 1){	
				String tmpvar = "tmpvar_" + (tmpInt++) + "_"+ n.p.i.s;
				if(n.e.get(i) instanceof IdentifierExp){
					tmpvar = ((IdentifierExp)n.e.get(i)).s;
				}
				else{				
					cCode = cCode + "int "+ tmpvar + " = ";						
					n.e.get(i).accept(this, env);
					cCode = cCode +";\n\t";
				}

				for(String conn: conns){
					cCode = cCode +"comm_write("; 
					cCode = cCode +conn+ ", &" + tmpvar;
					cCode = cCode +(", ");
					n.rep.accept(this, env);
					cCode = cCode +(");\n");
				}
			}
			else
			{
				String tmpvar="tmpvar_" + (tmpInt++) + "_"+ n.p.i.s;
				if(n.e.get(i) instanceof IdentifierExp){
					tmpvar = ((IdentifierExp)n.e.get(i)).s;
				}
				else
				
				{				
					cCode = cCode + "int "+ tmpvar + " = ";						
					n.e.get(i).accept(this, env);
					cCode = cCode +";\n\t";
				}


				cCode = cCode +"comm_write("; 
				cCode = cCode +conns.get(0)+ ", &"+ tmpvar;
				cCode = cCode +(", 4");//#Ayas - modified to 4 by Süleyman
				//n.rep.accept(this, env);
				cCode = cCode +("); // send 4 bytes \n");

			}
		}    


		return null;
	}

	public Object visit(SimpEntityExpr n, Object env) {
		n.i.accept(this, env);
		cCode = cCode +(" ( ");
		for(VarDecl vr : n.vl)
			vr.accept(this, env);
		cCode = cCode +(");\n");
		return null;
	}

	// For square root, there must be a variable called SquareRoot_ret
	// We don't know the return variable of a function in CAL. We used a global variable to return the result. 
	// However there can be several global variables being modified within the function. Then it wouldn't be possible to know
	// which global variable is the return value. Therefore we use a fixed variable name for the return value.
	// The variable name is the function name + "_ret".
	public Object visit(StatementCall n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				if (((IdentifierExp)n.i).s.equals("SquareRoot")){
					n.el.get(0).accept(this ,env);
				}
				else{
					for ( int i = 0; i < n.el.size(); i++ ) {
						n.i.accept(this, env);
						n.el.get(i).accept(this, env);
					}
				}
			}
			else {
				if (((IdentifierExp)n.i).s.equals("SquareRoot")){
					chiselCode = chiselCode + "\n" + chiselIndent + "val sqrt"+ sqrtCounter + " = Module(new FPSqrt())\n";
					chiselCode = chiselCode + chiselIndent + "sqrt" + sqrtCounter + ".io.in := ";
					n.el.get(0).accept(this ,env);
					chiselCode = chiselCode + "\n" + chiselIndent + "val SquareRoot_ret_v" + sqrtCounter + " = sqrt" + sqrtCounter + ".io.out";
					
					int localDelay = 0;
					String input = ((IdentifierExp) n.el.get(0)).s;
					if(varVersions.containsKey(input))
						input = input + "_v" + varVersions.get(input);
					if(globalDelays.containsKey(input))
						localDelay = globalDelays.get(input);
					// Add the delay of the input and sqrt together for the globaldelay
					globalDelays.put("SquareRoot_ret_v" + sqrtCounter, floatSqrtDelay + localDelay);
					
					sqrtCounter++;
					
				}
				else if(((IdentifierExp)n.i).s.equals("C_mag")){
					
					chiselCode = chiselCode + "\n" + chiselIndent + "val c_mag"+ C_magCounter + " = Module(new C_mag())\n";
					chiselCode = chiselCode + chiselIndent + "c_mag" + C_magCounter + ".io.in := ";
					n.el.get(0).accept(this ,env);
					chiselCode = chiselCode + "\n" + chiselIndent + "val C_mag_ret_v" + C_magCounter + " = c_mag" + C_magCounter + ".io.out";
					
					int localDelay = 0;
					String input = ((IdentifierExp) n.el.get(0)).s;
					if(varVersions.containsKey(input))
						input = input + "_v" + varVersions.get(input);
					if(globalDelays.containsKey(input))
						localDelay = globalDelays.get(input);
					// Add the delay of the input and sqrt together for the globaldelay
					globalDelays.put("C_mag_ret_v" + C_magCounter, complexCMagDelay + localDelay);
					
					C_magCounter++;
				}
				else{
					chiselCode = chiselCode + "\n" + chiselIndent + "val "+ ((IdentifierExp)n.i).s + "_inst = Module(new " + ((IdentifierExp)n.i).s + "())\n";
					for ( int i = 0; i < n.el.size(); i++ ) {
						chiselCode = chiselCode + "\n" + chiselIndent; //+ ((IdentifierExp)n.i).s + "_inst.in" + i + " := ";
						n.i.accept(this, env);
						chiselCode = chiselCode + "_inst.in" + i + " := ";

						n.el.get(i).accept(this, env);
					}
					chiselCode = chiselCode + "\n" + chiselIndent + ((IdentifierExp)n.i).s + "_ret_v0 := " + ((IdentifierExp)n.i).s + "_inst.out";
				}
			}
		}
		else {
			if (((IdentifierExp)n.i).s.equals("wait"))
				cCode = cCode + "return 0;";
			else{
				n.i.accept(this,env);
				cCode = cCode +("(");
				for ( int i = 0; i < n.el.size(); i++ ) {
					if(n.el.get(i) instanceof PortHH)
						break;
					n.el.get(i).accept(this,env);
					if ( i+1 < n.el.size() ) { cCode = cCode +", "; }
				}
				cCode = cCode +(");");
			}
		}
		
		return null;
	}

	public Object visit(StringLiteral n, Object env) {
		cCode = cCode +"\""+n.s+"\"";
		return null;
	}


	public Object visit(SwitchCase n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.exCase.accept(this, env);
				for(int i = 0; i < n.sts.size(); i++){
					n.cases.get(i).accept(this, env);
					n.sts.get(i).accept(this, env);
				}
			}
			else {
				chiselCode = chiselCode + "\n switch( ";
				n.exCase.accept(this, env);
				chiselCode = chiselCode + " ){\n";
				for(int i = 0; i < n.sts.size(); i++){
					chiselCode = chiselCode + "\tis(";
					n.cases.get(i).accept(this, env);
					chiselCode = chiselCode + "){";
					n.sts.get(i).accept(this, env);
					chiselCode = chiselCode + "\n\t}";
				}
				chiselCode = chiselCode + "}";
			}
		}
		else {
			cCode = cCode + "\n switch (";
			n.exCase.accept(this, env);
			cCode = cCode +") {\n";
			for(int i=0;i<n.sts.size();i++){
				cCode = cCode + "   case ";
				n.cases.get(i).accept(this, env);
				cCode = cCode +":\n     ";
				n.sts.get(i).accept(this, env);
				//cCode = cCode +"     break;\n";
			}
			cCode = cCode +"}\n";
		}
		

		return null;
	}


	//TODO we need to find out either to use integer or floating point operation
	// Exp e1,e2;
	public Object visit(Times n, Object env) {
		if(printChisel){
			if(isFirstIteration){
				n.e1.accept(this, env);
				n.e2.accept(this, env);
			}
			else {
				/* If integer 
				n.e1.accept(this, env);
				chiselCode = chiselCode + " * ";
				n.e2.accept(this, env);
				*/
				
				
				int indexOfLastNewline = 0;
				for (int pos = chiselCode.indexOf("\n"); pos != -1; pos = chiselCode.indexOf("\n", pos + 1)) {
					indexOfLastNewline = pos;
				}
				 
				//if((n.e1 instanceof IdentifierExp) && (n.e2 instanceof IdentifierExp)){
					
					String input1 = "";
					String input2 = "";
					
					// Let's check if the n.e1 is a single variable or an array
					if(n.e1 instanceof IdentifierExp)
						input1 = ((IdentifierExp) n.e1).s;
					else if(n.e1 instanceof ExpIndexer)
						input1 = ((IdentifierExp) ((ExpIndexer) n.e1).structure).s;
					
					if(n.e2 instanceof IdentifierExp)
						input2 = ((IdentifierExp) n.e2).s;
					else if(n.e1 instanceof ExpIndexer)
						input2 = ((IdentifierExp) ((ExpIndexer) n.e2).structure).s;
					
					boolean complexArithmetics = false;
					
					// If complex
					if(input1.startsWith("complex_") || input2.startsWith("complex_"))
						complexArithmetics = true;
					else
						complexArithmetics = false;
					
					if(complexArithmetics)
						chiselCode = chiselCode + "C_mul" + C_mulCounter + ".io.out\n";
					else
						chiselCode = chiselCode + "FP_mul" + mulCounter + ".io.out\n";
					
					/** PIPELINING **/
					//input1 = ((IdentifierExp) n.e1).s;
					//input2 = ((IdentifierExp) n.e2).s;
					input1 = input1 + "_v" + varVersions.get(input1);
					input2 = input2 + "_v" + varVersions.get(input2);
					// Fix the input delays
					int input1Delay = 0;
					int input2Delay = 0;
					int newInputDelay = 0;
					
					// If there is no global for the inputs then they are the inputs to the accelerator
					if(globalDelays.containsKey(input1))
						input1Delay = globalDelays.get(input1);
					
					if(globalDelays.containsKey(input2))
						input2Delay = globalDelays.get(input2);
					
					if(input1Delay > input2Delay){
						for(int i = 0; i < input1Delay - input2Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + "_Reg" + i + " = RegNext(" + input2 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + "_Reg" + i + " = RegNext(" + input2 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input1Delay;
						
						if(complexArithmetics){
							// Generate the operation component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val C_mul" + C_mulCounter + " = Module(new ComplexMul())").toString();
							//chiselCode = chiselCode + "C_mul" + C_mulCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_mul"+ C_mulCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_mul"+ C_mulCounter + ".io.in2 :=" + input2 + "_Reg" + (input1Delay - input2Delay - 1);		
							//n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the operation component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val FP_mul" + mulCounter + " = Module(new FPMult(32))").toString();
							chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in2 :=" + input2 + "_Reg" + (input1Delay - input2Delay - 1);		
							chiselCode = chiselCode + "\n";
						}
					}
					else if(input2Delay > input1Delay){
						for(int i = 0; i < input2Delay - input1Delay; i++){
							// Add registers to close the delay gap between the inputs
							if( i == 0){
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + ", 0.U)\n";
							}
							else{
								chiselCode = chiselCode + chiselIndent + "val " + input1 + "_Reg" + i + " = RegNext(" + input1 + "_Reg" + (i - 1) + ", 0.U)\n";
							}
						}
						// Set the new common delay for the inputs
						newInputDelay = input2Delay;
						
						if(complexArithmetics){
							// Generate the operation component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_mul" + C_mulCounter + " = Module(new ComplexMul())").toString();
							//chiselCode = chiselCode + "C_mul" + C_mulCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_mul"+ C_mulCounter + ".io.in1 := " + input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_mul"+ C_mulCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the operation component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_mul" + mulCounter + " = Module(new FPMult(32))").toString();
							//chiselCode = chiselCode + "C_mul" + C_mulCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in1 := " + input1 + "_Reg" + (input2Delay - input1Delay - 1);
							//n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
					}
					else{
						if(complexArithmetics){
							// Generate the operation component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val C_mul" + C_mulCounter + " = Module(new ComplexMul())").toString();
							//chiselCode = chiselCode + "C_mul" + C_mulCounter + ".io.out\n";
							chiselCode = chiselCode + chiselIndent + "C_mul"+ C_mulCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "C_mul"+ C_mulCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						else{
							// Generate the operation component
							chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n\n" + chiselIndent + "val FP_mul" + mulCounter + " = Module(new FPMult(32))").toString();
							chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in1 := ";
							n.e1.accept(this, env);
							chiselCode = chiselCode + "\n";
							chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in2 := ";		
							n.e2.accept(this, env);
							chiselCode = chiselCode + "\n";
						}
						
						newInputDelay = input2Delay;
					}
					
					// Set the new delay
					if(complexArithmetics){
						localDelay = complexMulDelay + newInputDelay;	
						C_mulCounter++;
					}
					else{
						localDelay = floatMulDelay + newInputDelay;	
						mulCounter++;
					}
						
					/**  END OF PIPELINING **/
					

/*				}
				else {// If float
						chiselCode = new StringBuilder(chiselCode).insert(indexOfLastNewline, "\n" + chiselIndent + "val FP_mul" + mulCounter + " = Module(new FPMult(32))").toString();
					chiselCode = chiselCode + "FP_mul" + mulCounter + ".io.out\n";
					chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in1 := ";
					n.e1.accept(this, env);
					chiselCode = chiselCode + "\n";
					chiselCode = chiselCode + chiselIndent + "FP_mul"+ mulCounter + ".io.in2 := ";		
					n.e2.accept(this, env);
					chiselCode = chiselCode + "\n";
					mulCounter++;
					localDelay = 2;
				}*/
			}
		}
		else{
			
			// Check if the variables are complex (if so, call the complex operation)
			if(n.e1 instanceof IdentifierExp && ((IdentifierExp)n.e1).s.startsWith("complex_") ||
			n.e2 instanceof IdentifierExp && ((IdentifierExp)n.e1).s.startsWith("complex_")){
				
				cCode = cCode + "ComplexMul(";
				n.e1.accept(this, env);
				cCode = cCode + ", ";
				n.e2.accept(this, env);
				cCode = cCode + ")";
				complexMulFlag = true;
			}
			else {
				cCode = cCode +("(");
				n.e1.accept(this,env);
				cCode = cCode +(" * ");
				n.e2.accept(this,env);
				cCode = cCode +(")");
			}
		}
		
		return null;
	}

	public Object visit(NullType n, Object env) {
		cCode = cCode +("void");

		return null;
	}

	private String getElemen(Exp e) {
		String sels="";
		if(e instanceof ListComprehension){
			if(((ListComprehension) e).compGen!=null)
				if(((ListComprehension) e).compGen.size()>0)
					return null;


			int elSize =((ListComprehension) e).eles.size();
			for(int iex=0;iex <elSize;iex++){
				String com = ", ";
				if(iex== elSize-1)
					com ="";
				Exp elm = ((ListComprehension) e).eles.get(iex);
				if(elm instanceof IntegerLiteral)
					sels += ((IntegerLiteral) elm).i + com;
				else if(elm instanceof DoubleLiteral)
					sels += ((DoubleLiteral) elm).d + com;
				else if(elm instanceof BooleanLiteral)
					sels += ((BooleanLiteral) elm).value + com;
				else if(elm instanceof Negate){
					if(((Negate) elm).e instanceof IntegerLiteral)
						sels += "(-"+((IntegerLiteral)((Negate) elm).e).i + ")" +com;
					else 
						return null;

				}
				else
					return null;

			}
			return sels;
		}

		return null;
	}

	public Object visit(VarDeclComp n, Object env) {
		String old = indent;
		indent = indent + "\t";
		
		if(env instanceof String)
			cCode = cCode + (String)env;
		
		if(n.t != null)
			n.t.accept(this,n.i.s);
		else
			cCode = cCode + (indent + "int");


		if(n.es.size() > 0){
			cCode = cCode + " = {";   
			if (!isGlobal)
				for(int i = 0; i < n.es.size() - 1; i++){
					n.es.get(i).accept(this, env);
					cCode = cCode + ",";    		   
				}
			n.es.get(n.es.size()-1).accept(this, env);
			cCode = cCode + "};";
			return null;

		}

		//	n.i.accept(this,env);

		if(n.e == null )
			cCode = cCode +(";\n");
		else {
			String sels =getElemen(n.e);
			if (!isGlobal){
				if(n.e instanceof ListComprehension || n.e instanceof ListConc){
					cCode = cCode + ";\n";
					n.e.accept(this,n.i.s);
				}
				else{
					cCode = cCode +" = ";
					n.e.accept(this,n.i.s);
					cCode = cCode +(";\n");
				}

			}
			else if(sels!=null)
				cCode = cCode +" =  {"+ sels+"};\n";
			else
			{
				cCode = cCode +(";\n");
				globId.add(n.i);
				globExp.add(n.e);
				//			n.e.accept(this,env);

			}
		}
		
		indent = old;
		return null;
	}

	public Object visit(VarDeclSimp n, Object env) {
		String old = indent;
		indent = indent + "\t";
		if(printChisel){
			if(isFirstIteration){
				n.i.accept(this, env);
				if(n.e != null && (n.e instanceof BooleanLiteral || n.e instanceof IntegerLiteral || !isGlobal) ){
					n.e.accept(this, env);
				}
			}
			else {
				
				chiselCode = chiselCode + "val ";
				n.i.accept(this, env);
				if(n.e != null && (n.e instanceof BooleanLiteral || n.e instanceof IntegerLiteral || !isGlobal) ){
					chiselCode = chiselCode + " = ";
					n.e.accept(this, env);
				}
				else {
					globId.add(n.i);
					globExp.add(n.e);
				}
			}
		}
		else {
				
			if(isGlobal &&  !n.isAssignable && n.e!=null){
				cCode = cCode + "#define "+n.i.s+" (";
				n.e.accept(this, env);
				cCode = cCode + ") ";
			} 
			else {

				// Check if the variable is of Complex type
				/*if(n.i.s.startsWith("complex_")){
					ComplexType t = new ComplexType();
					t.accept(this, env);
					n.i.accept(this, env);
					cCode = cCode + ";";
				}					
				else*/ {	
					if(env instanceof String)
						cCode = cCode + (String)env;
					String oddbit=null;
					if(n.t != null){
						if(n.t instanceof IntegerType)
							if(isGlobal)
								oddbit = (String) n.t.accept(this,env);
							else
								n.t.accept(this,env);
						else
							n.t.accept(this,env);
					}
		
					else if(n.e!=null){
						if (n.e instanceof BooleanLiteral)
							cCode = cCode +(indent + "int");
						//	cCode = cCode +(indent + "boolean");
						else if (n.e instanceof IntegerLiteral)
							cCode = cCode +(indent + "int"); 
						else
							cCode = cCode +(indent + "int"); 
					}
		
					else
						cCode =cCode + "int";
		
					if(oddbit!=null)
						if(oddbit.equals("oddbit")){
							cCode = cCode +" Str_"+ n.i.s + ";\n";
							cCode = cCode +"#define " + n.i.s +" Str_" + n.i.s + ".oddbit";
						}
						else { 
							cCode = cCode +" ";
							n.i.accept(this,env);
						}
					else { 
						cCode = cCode +" ";
						n.i.accept(this,env);
					}
		
					if(n.e == null ){
						if(oddbit==null)
							cCode = cCode +(";");
					}
					else if ((n.e instanceof BooleanLiteral || n.e instanceof IntegerLiteral || !isGlobal) && oddbit==null){
						cCode = cCode +(" = ");
						n.e.accept(this,env);
						cCode = cCode +(";");
					}
					else{
						if(oddbit==null)
							cCode = cCode +(";");
						globId.add(n.i);
						globExp.add(n.e);
						//		n.e.accept(this,env);
					}
				}
			}	
		}
		indent = old;
		return null;
	}



	// Exp e;
	// Statement s;
	public Object visit(While n, Object env) {
		String old = indent;
		indent = indent + "";
		cCode = cCode +("while (");
		n.e.accept(this,env);
		cCode = cCode +(") {\n");
		n.s.accept(this,env);
		cCode = cCode + "}\n";
		indent = old;
		return null;
	}


	@Override
	public Object visit(CharLiteral n, Object env) {
		cCode = cCode + n.c;
		return null;
	}


	@Override
	public Object visit(ListConc n, Object env) {

		cCode = cCode + "\n// ListConc \n";
		n.e1.accept(this, "temp");
		cCode = cCode + "\n// =  ListConc \n";

		n.e2.accept(this, env);

		return null;
	}


	@Override
	public Object visit(StringConc n, Object env) {
		return null;
	}


	@Override
	public Object visit(For n, Object env) {
		String old=indent;
		indent = indent + "";
		// TODO Auto-generated method stub
		cCode = cCode + "for(int "+n.i.s+" = ";
		n.init.accept(this, env);
		cCode = cCode +"; ";
		n.con.accept(this, env);
		cCode = cCode +"; "+n.i.s+ " = ";
		n.step.accept(this, env);
		cCode = cCode +"){\n";
		n.s.accept(this, env);
		cCode = cCode + "}\n";
		indent = old;
		return n;
	}


	@Override
	public Object visit(FloatType n, Object env) {
		cCode = cCode + "float";
		return null;
	}

	@Override
	public Object visit(ComplexType n, Object env) {
		cCode = cCode + "Complex ";
		return null;
	}
	
	@Override
	public Object visit(ForEach n, Object env) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(Break break1, Object env) {
		cCode = cCode +"     break;\n";
		return null;
	}


	@Override
	public Object visit(TestInputPort n, Object env) {
		List<String> conns= new ArrayList<>();
		conns.addAll((List<String>)n.p.accept(this,env));
		cCode = cCode +"(comm_level("+conns.get(0)+") >= 1";//#Ayas
		//n.available_tokens.accept(this, env);

		cCode = cCode+ ")";
		if(conns.size()>1){
			for(int i=1; i<conns.size();i++){
				cCode=cCode +" && \n\t(comm_level("+conns.get(i)+") >= ";
				n.available_tokens.accept(this, env);
				cCode = cCode + ")";
			}
		}

		return null;
	}


	@Override
	public Object visit(TestOutputPort n, Object env) {
		List<String> conns= new ArrayList<>();
		conns.addAll((List<String>)n.p.accept(this,env));
		cCode = cCode +"(comm_space("+conns.get(0)+ ") >= ";
		n.available_room.accept(this, env);
		cCode = cCode + ")";

		/*	if(conns.size()>3){
				for(int i=1; i<conns.size();i++){
					cCode=cCode +" && \n\t(NumberOfElement(&"+conns.get(0)+") == NumberOfElement(&"+conns.get(i)+"))";				
				}
			}


		else */if(conns.size()>1){
			for(int i=1; i<conns.size();i++){
				cCode=cCode +" && \n\tTestOutputPort("+conns.get(i)+" , ";
				n.available_room.accept(this, env);
				cCode = cCode + ")";
			}
		}

		return null;
	}


	@Override
	public Object visit(MultipleOps n, Object env) {

		int i = 0;
		
		if(printChisel){
			if(isFirstIteration){
				for(i = 0; i < n.Operations.size(); i++){
					n.Operands.get(i).accept(this, env);
				}
				n.Operands.get(i).accept(this, env);	
			}
			else {
				for(i = 0; i < n.Operations.size(); i++){
					n.Operands.get(i).accept(this, env);
					String op = n.Operations.get(i);
					if(op.length()<=2){
						if(op.equals("or"))
							chiselCode = chiselCode + " || ";
						else if(op.equals("="))
							chiselCode = chiselCode + " === ";
						else
							chiselCode = chiselCode + " " + n.Operations.get(i) + " ";
					}
					else{
						if(op.equals("and"))
							chiselCode = chiselCode + " && ";
						else if(op.equals("bitor"))
							chiselCode = chiselCode + " | ";
						else if(op.equals("bitand"))
							cCode = cCode + " & ";
						else
							System.out.print(op);
					}
				}
				n.Operands.get(i).accept(this, env);	
			}
		}
		else{
			for(; i < n.Operations.size(); i++){
				n.Operands.get(i).accept(this, env);
				String op=n.Operations.get(i);
				if(op.length()<=2){
					if(op.equals("or"))
						cCode = cCode + " " + "||"  + " ";
					else if(op.equals("="))
						cCode = cCode + " " + "=="  + " ";
					else
						cCode = cCode + " " + n.Operations.get(i) + " ";
				}
				else{
					if(op.equals("and"))
						cCode = cCode + " " + "&&"  + " ";
					else if(op.equals("bitor"))
						cCode = cCode + " " + "|"  + " ";
					else if(op.equals("bitand"))
						cCode = cCode + " " + "&"  + " ";
					else
						System.out.print(op);
				}
			}
			n.Operands.get(i).accept(this, env);
		}
		return null;
	}


	@Override
	public Object visit(ExpList n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}




	@Override
	public Object visit(ActionFiringCond n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(ActorFSM n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(VectorOps n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(MatrixOps n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(Profile_Actor n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(Profile_ActionDecl n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(Profile_ActionScheduler n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(Profile_FunctionDecl n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public Object visit(Profile_ProcedureDecl n, Object e) {
		// TODO Auto-generated method stub
		return null;
	}


}

