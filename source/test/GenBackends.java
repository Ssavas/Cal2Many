

import hh.AST.syntaxtree.*;
import hh.backend.c.*;
import hh.common.passes.ImperativePass;
import hh.common.translator.*;
import hh.simplenet.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

import javax.swing.JFrame;

import net.opendf.ir.cal.Actor;
import net.opendf.ir.common.PortDecl;
import net.opendf.ir.net.ast.EntityNameBinding;
import net.opendf.ir.net.ast.NetworkDefinition;
import net.opendf.parser.lth.CalParser;
import net.opendf.parser.lth.NlParser;
import net.opendf.transform.caltoam.ActorToActorMachine;

public class GenBackends {

	private static boolean testChisel = true;
	private static String sFolder;
	private static String sBackend = "";
	private static List<String> CalOuts = new ArrayList<String>();
	private static ArrayList<String> net_Files;
	private static ArrayList<String> cal_Files;
	private static ArrayList<FlatNetwork>  networks;
	public static String cCode = "";
	public static String chiselCode = "";
	public static HashSet<String> setActors= new HashSet<String>();
	/**/  
	public static void main(String[] args) throws Exception {

		if(args.length < 4){
			System.out.println("Please give four arguments:  Path to the CAL and NL files, top level NL file name, Output path, and Backend");
			//return;
		}
		if(testChisel){
			
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\CNN4actors\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\CNN4actors\\Generated\\";
			args[3] = "RocketChisel";
			
			/*
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus13actors\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus13actors\\Generated\\";
			args[3] = "RocketChisel";
			*/
		/*	
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus2actors\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus2actors\\Generated\\";
			args[3] = "RocketChisel";
			*/
		/*
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\singleQRD\\CAL_version\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\singleQRD\\Generated\\";
			args[3] = "Chisel";
			*/
		/*	
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus\\CAL_version\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus\\Generated_C-Chisel\\";
			args[3] = "Chisel";
			*/
			/*
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus\\CAL_version_flat\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus\\Generated_C-Chisel_flat\\";
			args[3] = "Chisel";
			*/
		}
		else{
			/*
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\BasicIDCT2D\\CAL_version\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\BasicIDCT2D\\Generated\\";
			args[3] = "PicoRV";
			*/
			/*
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus\\CAL_version\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Cal2Chisel\\Cal2Many\\Test\\Autofocus\\Generated_C\\";
			args[3] = "C";
			*/
			args[0] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Dana\\ZF_column\\"; 
			args[1] = "Test";
			args[2] = "C:\\Users\\slesav\\Box Sync\\PhD\\Projects\\Dana\\ZF_column\\Generated_C\\";
			args[3] = "Epiphany";
		}
		
		sFolder= args[2];// + "\\";
		sBackend = args[3];
		generateNetworkedCal(args);
	
	}

	private static void generateNetworkedCal(String [] args) throws FileNotFoundException{

		FlatNetwork fnet = generateNetwork(args);
		List <String> entiss = new ArrayList<String>();
		NetworkMap networkMap = null;
		
		// Addition by Süleyman
		if(sBackend.equals("PicoRV") || sBackend.equals("Chisel") || sBackend.equals("RocketChisel")){
			networkMap = new NetworkMap(fnet, 2);
		}
		// End of addition

		if ( fnet!=null && cal_Files.size()>0)
		{

			// Check the availability of CAL file for each entity in the flatten network

			for(Entity ens:fnet.entities)				
				if(!cal_Files.contains(ens.it.s)){
					System.err.println("Actor " + ens.it.s + " can not be found in " + args[0]);
					return;
				}
	
			
			// parse the CAL code
			for(Entity enst : fnet.entities)
			{
				String [] calarg = new String[3];
				calarg[0]=args[0];
				calarg[1]=enst.it.s;
				calarg[2]=enst.i.s;

				gnerateCalC(null, calarg, enst.parms, true, fnet.chs, networkMap);
	
				System.err.println("Code generation for "+ enst.it.s + " is completed.");
				//				gnerateCalC(calarg,print_am_pams(enst.parms),false,null);
				entiss.add(enst.i.s);
				//break;

			}
		}


		if(sBackend.equals("C")){

			cCode=(String)fnet.accept(new PrettyPrintNet(),null);
			cCode= "/*" + cCode + "*/\n\n"+(String)fnet.accept(new PrettyPrintNetC(),null);

			PrintWriter writerNL = new PrintWriter(sFolder + fnet.it.s + ".c");
			writerNL.println(cCode);					
			writerNL.close();
		}

		if(sBackend.equals("Epiphany")){
			NetworkMap map = new NetworkMap(fnet,2);
/*
			JFrame frame = new JFrame();
			frame.getContentPane().add(new Mapping(map.SIMmap,map.SIMchs));

			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setSize(1000,1000);
			frame.setVisible(true);
*/
			PrintWriter writerNL = new PrintWriter(sFolder + fnet.it.s + "Map.c");
			writerNL.println(map.toString());					
			writerNL.close();
		}
		if(sBackend.equals("PicoRV")){

		}
	}
	private static String print_am_pams(VarDeclList parms) {
		String s="";
		for(VarDecl vd:parms){
			if(vd instanceof VarDeclSimp){
				s=s+"\n#define " + ((VarDeclSimp)vd).i.s + " ";
				Exp ex = ((VarDeclSimp)vd).e;
				if(ex != null)
					s = s + (String)ex.accept(new PrintExp(),null);

			}
		}
		return s;
	}
	private static FlatNetwork generateNetwork(String [] args) throws FileNotFoundException{
		net_Files = new ArrayList<String>();
		cal_Files = new ArrayList<String>();
		networks = new ArrayList<FlatNetwork>();

		// store NL and CAL files
		getNetworkAndCalFiles(args[0]);
		// pares and tranlate NL files
		parseNetworkFiles(args[0]);

		// flatten the NL files and print the code
		FlatNetwork fnet = null;
		if(networks.size() > 0){
			fnet = FlatteningNet.Flatten(networks.toArray(new FlatNetwork[networks.size()]), net_Files.toArray(new String [net_Files.size()]), args[1]);

		}	
		return fnet;
	}

	private static void gnerateCalC(SEQ_Actor impPass, String [] args,VarDeclList parms, boolean ports, ChannelList chs, NetworkMap networkMap ) throws FileNotFoundException{


		String actorsH = "";
		if(impPass == null){
			File calFile = new File(args[0] + args[1] + ".cal" );
			System.out.println("Parse actor " + args[0] + args[1] + ".cal");
			CalParser parser = new CalParser();
			Actor a = parser.parse(calFile);
			if (!parser.parseProblems.isEmpty()) {
				for (String p : parser.parseProblems) {
					System.err.println(p);
					System.exit(0);
				}
				return;
			}


			System.out.println("Generate actor machine for " + a.getName());
			for(PortDecl op:a.getOutputPorts())
				CalOuts.add(a.getName()+"_" + op.getName());

			CalC_AST cast;		

			ActorToActorMachine trans = new ActorToActorMachine();
			net.opendf.ir.am.ActorMachine am = trans.translate(a);
			if(ports)
				cast = ActorTranslate.translate(a, parms,args[1],args[2],
						getPortConnections(args[2],a.getInputPorts(),false,chs),
						getPortConnections(args[2],a.getOutputPorts(),true,chs),
						sBackend);

			else
				cast = ActorTranslate.translate(a, parms,args[1],args[2],null,null, sBackend);

			impPass = (SEQ_Actor) cast.pm.accept(new ImperativePass(), sBackend);
		}
		else{
			HashMap<String, ArrayList<String>> inprts = new HashMap<String, ArrayList<String>>();
			HashMap<String, ArrayList<String>> outprts = new HashMap<String, ArrayList<String>>();

			for(PortHH apd:impPass.input)
				inprts.put(impPass.i.s+"#"+apd.i.s, getPortLink(impPass.i.s,apd.i.s,false,chs));
			for(PortHH apd:impPass.output)
				inprts.put(impPass.i.s+"#"+apd.i.s, getPortLink(impPass.i.s,apd.i.s,true,chs));
	
			impPass.inputConnections = inprts;
			impPass.outputConnections = outprts;

		}
			
		String ext = "";
		String ext2 = "";
		if(sBackend.equals("Epiphany")){
			cCode=(String) impPass.accept(new PrintCalEpiphany(), null);
			ext =".c";
		}
		else if(sBackend.equals("PicoRV")){
			cCode=(String) impPass.accept(new PrintCalEpiphany_S(networkMap), null);
			ext =".c";
		}
		else if(sBackend.equals("C")){
			cCode=(String) impPass.accept(new PrettyPrintCalC(), null);
			ext = ".c";
		}
		else if(sBackend.equals("EIT")){
			ext = ".scala";
			cCode=(String) impPass.accept(new PrettyPrintCalEIT(), null);
		}
		else if(sBackend.equals("Chisel")){
			ext = ".c";
			ext2 = ".scala";
			ArrayList<String> multiLang = new ArrayList<String>();
			multiLang = (ArrayList<String>) impPass.accept(new PrettyPrintChisel(networkMap), null);
			cCode = multiLang.get(0);
			chiselCode = multiLang.get(1);
		}
		else if(sBackend.equals("RocketChisel")){
			ext = ".c";
			ext2 = ".scala";
			ArrayList<String> multiLang = new ArrayList<String>();
			multiLang = (ArrayList<String>) impPass.accept(new RocketChiselHybrid(networkMap), null);
			cCode = multiLang.get(0);
			chiselCode = multiLang.get(1);
			actorsH = multiLang.get(2);
		}
		
		if(sBackend.equals("DAG")){

			System.out.println(sFolder + impPass.i.s +".s will be  generated!\n");

			System.out.println(sFolder + impPass.i.s +".s is  generated!\n");

		}
		else
		{
			if(sBackend.equals("Chisel") || sBackend.equals("RocketChisel")){
				actorsH = "#ifndef _ACTORS"+  args[2]+"\n#define _ACTORS"+  args[2]+"\n"+ print_am_pams(parms)
				        + "\n// Macro for placing the data on corresponding core's memory \n" +
						"#undef  SECTION \n"+
						"#define SECTION(x) __attribute__((section(x))) \n" +
						//"\nint "+  args[2]+"();\n"+
						"\n" + actorsH;
				actorsH = actorsH + "\n// Macros for inlinig code to call the accelerator \n" +
					"#define STR1(x) #x \n" +
					"#define STR(x) STR1(x) \n" +
					"#define EXTRACT(a, size, offset) (((~(~0 << size) << offset) & a) >> offset) \n" +
					
					"#define CUSTOMX_OPCODE(x) CUSTOM_ ## x \n" +
					"#define CUSTOM_0 0b0001011 \n" +
					"#define CUSTOM_1 0b0101011 \n" +
					"#define CUSTOM_2 0b1011011 \n" +
					"#define CUSTOM_3 0b1111011 \n" +
					
					"#define CUSTOMX(X, rd, rs1, rs2, funct)         \\\n" +
					  "\tCUSTOMX_OPCODE(X)                   |         \\\n" +
					  "\t(rd                   << (7))       |         \\\n" +
					  "\t(0x7                  << (7+5))     |         \\\n" +
					  "\t(rs1                  << (7+5+3))   |         \\\n" +
					  "\t(rs2                  << (7+5+3+5)) |         \\\n" +
					  "\t(EXTRACT(funct, 7, 0) << (7+5+3+5+5)) \n" +
					
					"\n// Standard macro that passes rd, rs1, and rs2 via registers \n" +
					"#define ROCC_INSTRUCTION(X, rd, rs1, rs2, funct)                \\\n" +
					  "\tROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct, 10, 11, 12) \n" +
					
					"\n// rd, rs1, and rs2 are data \n" +
					"// rd_n, rs_1, and rs2_n are the register numbers to use \n" +
					"#define ROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) { \\\n" +
					    "\tregister uint64_t rd_  asm (\"x\" # rd_n);                            \\\n" +
					    "\tregister uint64_t rs1_ asm (\"x\" # rs1_n) = (uint64_t) rs1;          \\\n" +
					    "\tregister uint64_t rs2_ asm (\"x\" # rs2_n) = (uint64_t) rs2;          \\\n" +
					    "\tasm volatile (                                                      \\\n" +
					        "\t\t\".word \" STR(CUSTOMX(X, rd_n, rs1_n, rs2_n, funct)) \"\\n\\t\"      \\\n" +
					        "\t\t: \"=r\" (rd_)                                                    \\\n" +
					        "\t\t: [_rs1] \"r\" (rs1_), [_rs2] \"r\" (rs2_));                        \\\n" +
					    "\trd = rd_;                                                           \\\n" +
					  "} \n" +
					
					"#define XCUSTOM_ACC	0 \n" +
					"#define FUNCT_FIRE	4 \n" +
					"#define FUNCT_IN1	1 \n" +
					"#define FUNCT_IN2	2 \n" +
					"#define FUNCT_IN3	3 \n" +
					"#define FUNCT_READ 5 \n" +
					
					"\n// Standard macro that passes rd, rs1, and rs2 via registers and expects does not block (while waiting for the result) \n" +
					"#define ROCC_INSTRUCTION_NO_BLOCK(X, rd, rs1, rs2, funct)                \\\n" +
					  "\tROCC_INSTRUCTION_NO_BLOCK_R_R_R(X, rd, rs1, rs2, funct, 10, 11, 12) \n" +
					"\n\t// rd, rs1, and rs2 are data \n" +
					"\t// rd_n, rs_1, and rs2_n are the register numbers to use \n" +
					"#define ROCC_INSTRUCTION_NO_BLOCK_R_R_R(X, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) { \\\n" +
					    "\tregister uint64_t rd_  asm (\"x\" # rd_n);                            \\\n" +
					    "\tregister uint64_t rs1_ asm (\"x\" # rs1_n) = (uint64_t) rs1;          \\\n" +
					    "\tregister uint64_t rs2_ asm (\"x\" # rs2_n) = (uint64_t) rs2;          \\\n" +
					    "\tasm volatile (                                                      \\\n" +
					        "\t\t\".word \" STR(CUSTOMX_NP(X, rd_n, rs1_n, rs2_n, funct)) \"\\n\\t\"   \\\n" +
					        "\t\t: \"=r\" (rd_)                                                    \\\n" +
					        "\t\t: [_rs1] \"r\" (rs1_), [_rs2] \"r\" (rs2_));                        \\\n" +
					    "\trd = rd_;                                                           \\\n" +
					  "} \n" +
					
					"\n// no requirement for return register \n" +
					"#define CUSTOMX_NP(X, rd, rs1, rs2, funct)         \\\n" +
					  "\tCUSTOMX_OPCODE(X)                   |         \\\n" +
					  "\t(rd                   << (7))       |         \\\n" +
					  "\t(0x3                  << (7+5))     |         \\\n" +
					  "\t(rs1                  << (7+5+3))   |         \\\n" +
					  "\t(rs2                  << (7+5+3+5)) |         \\\n" +
					  "\t(EXTRACT(funct, 7, 0) << (7+5+3+5+5)) \n" +


					"\n#define ROCC_CUBIC(rd, rs1, rs2, rs3, rs4, rs5, rs6, rs7, rs8)                \\\n" +
					  "\tROCC_CUBIC_R(rd, rs1, rs2, rs3, rs4, rs5, rs6, rs7, rs8, 4, 5, 6, 7, 8, 9, 10, 11, 12) \n" +

					"\n#define ROCC_CUBIC_R(rd, rs1, rs2, rs3, rs4, rs5, rs6, rs7, rs8, rd_n, rs1_n, rs2_n, rs3_n, rs4_n, rs5_n, rs6_n, rs7_n, rs8_n) { \\\n" +
					    "\tregister uint64_t rd_  asm (\"x\" # rd_n);                            	\\\n" +
					    "\tregister uint64_t rs1_ asm (\"x\" # rs1_n) = (uint64_t) rs1;          	\\\n" +
					    "\tregister uint64_t rs2_ asm (\"x\" # rs2_n) = (uint64_t) rs2;          	\\\n" +
					    "\tregister uint64_t rs3_ asm (\"x\" # rs3_n) = (uint64_t) rs3;          	\\\n" +
					    "\tregister uint64_t rs4_ asm (\"x\" # rs4_n) = (uint64_t) rs4;          	\\\n" +
					    "\tregister uint64_t rs5_ asm (\"x\" # rs5_n) = (uint64_t) rs5;          	\\\n" +
					    "\tregister uint64_t rs6_ asm (\"x\" # rs6_n) = (uint64_t) rs6;          	\\\n" +
					    "\tregister uint64_t rs7_ asm (\"x\" # rs7_n) = (uint64_t) rs7;          	\\\n" +
					    "\tregister uint64_t rs8_ asm (\"x\" # rs8_n) = (uint64_t) rs8;          	\\\n" +
					    "\tasm volatile (                                                     		\\\n" +
					        "\t\t\".word \" STR(CUSTOMX_NP(0, rd_n, rs1_n, rs2_n, FUNCT_IN1)) \"\\n\\t\"   \\\n" +
							"\t\t\".word \" STR(CUSTOMX_NP(0, rd_n, rs3_n, rs4_n, FUNCT_IN2)) \"\\n\\t\"   \\\n" +
							"\t\t\".word \" STR(CUSTOMX_NP(0, rd_n, rs5_n, rs6_n, FUNCT_IN3)) \"\\n\\t\"   \\\n" +
							"\t\t\".word \" STR(CUSTOMX(0, rd_n, rs7_n, rs8_n, FUNCT_FIRE)) \"\\n\\t\"     \\\n" +
					        "\t\t: \"=r\" (rd_)                                                    	\\\n" +
					        "\t\t: [_rs1] \"r\" (rs1_), [_rs2] \"r\" (rs2_), [_rs3] \"r\" (rs3_), 			\\\n" +
							"\t\t[_rs4] \"r\" (rs4_), [_rs5] \"r\" (rs5_), [_rs6] \"r\" (rs6_), [_rs7] 	\\\n" +
							"\t\t\"r\" (rs7_), [_rs8] \"r\" (rs8_)) ;   			                     	\\\n" +
					    "\trd = rd_;                                                           	\\\n" +
					  "}\n \n#endif";
					
			}
			else{
				actorsH="#ifndef _ACTORS"+  args[2]+"\n#define _ACTORS"+  args[2]+"\n"+ print_am_pams(parms) + "\nint  Scheduler_"+  args[2]+"();\n";
			}

			PrintWriter writerActorh = new PrintWriter(sFolder + args[2] + ".h");
			writerActorh.println(actorsH);					
			writerActorh.close();
			PrintWriter writerActor = new PrintWriter(sFolder +args[2] + ext);
			writerActor.println(cCode);					
			writerActor.close();
			if(chiselCode != ""){
				PrintWriter writeChisel = new PrintWriter(sFolder + "partial" + args[2] + ext2);
				writeChisel.println(chiselCode);
				writeChisel.close();
			}

		}
	}

	private static void parseNetworkFiles(String arg) {
		for(String netName:net_Files)
		{

			System.out.println("Parse network " + netName);
			NlParser nparser = new NlParser();
			NetworkDefinition network = nparser.parse(arg, netName+".nl");
			nparser.printParseProblems();
			if(nparser.parseProblems.isEmpty()){
				new EntityNameBinding(network);
				networks.add(TranslateNet.translate(network));

			}
		}
	}

	private static void getNetworkAndCalFiles(String arg) {
		File folder = new File(arg);
		File[] listOfFiles = folder.listFiles();
		for (int i = 0; i < listOfFiles.length; i++) {
			if (listOfFiles[i].isFile()) {
				String str = listOfFiles[i].getName();
				if(str.endsWith(".nl")){
					net_Files.add(str.substring(0, str.length()-3));
				}
				else if(listOfFiles[i].getName().endsWith(".cal"))
					cal_Files.add(str.substring(0, str.length()-4));
			}
		}
	}

	private static  HashMap<String, ArrayList<String>>  getPortConnections(String eName,List<PortDecl> ports,boolean lookInput,ChannelList chs){
		HashMap<String, ArrayList<String>> prts= new HashMap<String, ArrayList<String>>();

		for(PortDecl apd:ports)
			prts.put(eName+"#"+apd.getName(), getPortLink(eName,apd.getName(),lookInput,chs));
		//		for(PortDecl apd:ports)
		//			if(lookInput)
		//				prts.put(eName+"#"+apd.getName(), getPortLinkTrue(eName,apd.getName(),chs));
		//			else
		//				prts.put(eName+"#"+apd.getName(), getPortLinkFalse(eName,apd.getName(),chs));

		return prts;
	}



	private static ArrayList<String> getPortLink(String eName,String pName, boolean lookInInput, ChannelList chs) {
		ArrayList<String> ports = new ArrayList<String>();
		
		
		int chNo = 0;
		if(lookInInput)
			for(Channel c : chs){

				if(c.p1.i.s!=null){
					if(eName.equals(c.p1.i.s) && pName.equals(c.p1.p.s))
						if(c.p2.i.s != null && !c.p2.i.s.equals(""))
							ports.add("ch" + chNo);
						else
							ports.add("SharedMemWrite_"+c.p1.p.s);


					if(c.p2.i.s != null && !c.p2.i.s.equals(""))
						if(c.p1.i.s != null &&  !c.p1.i.s.equals(""))
							chNo++;			
				}
			}
		else
			for(Channel c:chs){

				if(c.p2.i.s!=null){
					if(eName.equals(c.p2.i.s) && pName.equals(c.p2.p.s))
						if(c.p1.i.s!=null &&  !c.p1.i.s.equals(""))
							ports.add("ch"+(chNo));

						else
							ports.add("SharedMemRead_"+c.p1.p.s);

					if(c.p2.i.s!=null && !c.p2.i.s.equals(""))
						if(c.p1.i.s!=null &&  !c.p1.i.s.equals(""))
							chNo++;
				}

			}



		System.err.println(" Port " + pName +" of entity "+ eName+ " is not connected!");
		return ports;
	}

	/*private static DeclVar varDecl(String name, Expression expr) {
		return new DeclVar(null, name, null, expr, false);
	}

	private static ExprList ExpListComprehension(ListComprehension ls) {
		return new ExprList(null,null);
	}
	private static ExprLiteral litReal(Double d) {
		return new ExprLiteral(ExprLiteral.litReal , Double.toString(d));
	}
	private static ExprLiteral litString(String s) {
		return new ExprLiteral(ExprLiteral.litString , s);
	}
	private static ExprLiteral litInteger(int i) {
		return new ExprLiteral(ExprLiteral.litInteger, Integer.toString(i));
	}
	private static ExprLiteral litBool(boolean b) {
		return b? new ExprLiteral(ExprLiteral.litTrue,"true"): new ExprLiteral(ExprLiteral.litFalse, "false");
	}
	 */
}
