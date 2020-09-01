Cal2Chisel code generator - Eclipse Java project
@Author: Süleyman Savas - Halmstad University

Last modification : 2019-08-18

jUnit4-12.jar file should be added to the path. 

Some notes on the code generation:
- The action to be accelerator must have a prefix of "__acc__".
- A functions return value must be stored in a variable starting with the name of the function and ending with "_ret".
- Every function must return a value.
- Only floating point division is supported. (Integer division is not supported but it shouldn't be very difficult to go from float to int.)
- We do not support integer multiplication. Only floating point is supported.
- All global variables are used as inputs to all actions which are accelerated.
- Loop unrolling is not implemented yet. Therefore loops are not supported.
- Procedures and functions need to be inlined.
- Global variables which are used as return values of procedure must end with "_ret". Other global variables cannot end with "_ret".
- For square root, the procedure must be called SquareRoot and there must be a variable called SquareRoot_ret.
- Global variables should not start with the actor name
- No support for arrays inside the accelerator
- Multiple Operations in the same statement is not supported.
- Library files should be imported with a heuristic algorithm. (Maybe change the library name to FPOperations)
- Custom instructions should have proper output registers and FUNCT_X macro.

- Support for complex numbers is added.
	+ The variable name should start with "complex_".
	+ The type that is used in CAL is ignored.
	+ Inputs to the accelerator can either have only complex or only float formats.
	+ Complex numbers are 64 bits wide in chisel.

- We keep versions for variables (similar to SSA). The list is called varVersions. All versions are defined at the beginning of the code.
- After each if statement (at the end of a branch) we add a mux as a phi function.
- We need to fix self assignments. - FIXED
- We should apply dead code elimination to remove potential redundant ports
- Array indices are moved out of the accelerator 
	+ Needs a check if the array index is computed by using any local variables
	+ I use 2 hashmaps to store which array is used with which index. If the array is an input or output the index will be used in the C code.

- Action decl visit function goes through the statement list twice. 
	+ First iteration is to gather information such as which variables are read, which are modified, how many versions we need.
	+ The second one prints the chisel + c code.

- I added
		val en = Input(Bool())
		val valid = Output(Bool())
into the io bundle of the generated modules.

- Support for pipelining
	+ Pipelining based on the arithmetic operation components is added.
	+ Whenever a binary operation component is used, both inputs are checked for how long they have been delayed. The one that is delayed fewer cycles gets delay to get synched with the other input.
	+ Outputs are synchronized as well.
	+ valid signal is delayed as much as needed.
	? Optimization idea: add a stage register after each arithmetic block

	Non-Chisel Notes:
- package keyword is not supported by the parser for some reason. This has nothing to do with Chisel back-end.	
- elsif statement is not supported by the parser
- uint is not supported in List definitions

++ Additions on 2018 August
+ Support for C_mag function (the block for C_mag is instantiated whenever C_mag is seen in the code (from Autofocus app))
+ Support for mixed sized inputs to the accelerators (inputs with different width [32 or 64bits] can be sent to the same accelerator)
+ Generation of more than one accelerator for the same actor.
+ Support for while loop in CAL. It converts to for loop in Chisel. The while expression must be starting from zero and increasing. 

** Notes for backend for rocket core
* Channels will be shared variables sent through function calls to the actors 
	* main function becomes the actor name with arguments such as channels as buffers, flags for each channel and channels sizes
* Since the actor files will be linked together, global variable names should differ from a file to another - Done
* 'Repeat' for reading/writing is only supported with an integer literal.


* TODO : if the input to the accelerator is an array, send the address of the array and the size. The accelerator should read it from the memory directly.
* TODO : support for while loops
* TODO : constants will not be inputs to the accelerator. They will be defined in the accelerator.
- Constants cannot have expressions. Right hand side must be literal.
- conv7 procedure is converted into a hardware block. First argument to the procedure should be the filterIndex and the second argument should be the input image with up to 3 dimensions.
- Array dimensions must be variables with no additional expression or integer literals.
- Actions should send an element at a time. Repeat feature is not available.

* TODO : If there are more than one accelerator in an actor, use different custom instruction macros in the c and header files.
* TODO : Channel buffer sizes are 1. Make this dynamic.
* TODO : If there is communication in the accelerated action, custom instruction calls must be placed before writing to the channels.
* TODO : Generate the main file for multithreaded rocket core execution.
	- syncVector array, fire variables, syncsum variable, syncCores function, channel flags and buffers, thread_entry function with calls to the proper functions to start execution in each core. Finally an empty main function.
