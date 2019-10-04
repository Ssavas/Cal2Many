package partialranger

import ComplexArithmetics._
import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class cubic() extends Module {
	val io = IO(new Bundle{
		val ranger_complex_input1_p_pos_in = Input(UInt(width = 64.W))
		val ranger_complex_input1_p_val_in = Input(UInt(width = 64.W))
		val ranger_complex_input2_p_pos_in = Input(UInt(width = 64.W))
		val ranger_complex_input2_p_val_in = Input(UInt(width = 64.W))
		val ranger_complex_output_p_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val complex_d1_v1 = Wire(UInt(width = 64.W))
	val complex_d0_v1 = Wire(UInt(width = 64.W))
	val complex_tmp1_v1 = Wire(UInt(width = 64.W))
	val complex_tmp0_v1 = Wire(UInt(width = 64.W))
	val complex_tmp3_v1 = Wire(UInt(width = 64.W))
	val complex_tmp2_v1 = Wire(UInt(width = 64.W))
	val ranger_complex_output_p_v1 = Wire(UInt(width = 32.W))
	val x_int_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def NOF_PIXELS_KERNEL : Int = 36
	def NOF_PIXELS : Int = 216

	//Read the inputs
	val ranger_complex_input1_p_pos_v0 = io.ranger_complex_input1_p_pos_in
	val ranger_complex_input1_p_val_v0 = io.ranger_complex_input1_p_val_in
	val ranger_complex_input2_p_pos_v0 = io.ranger_complex_input2_p_pos_in
	val ranger_complex_input2_p_val_v0 = io.ranger_complex_input2_p_val_in

	
	x_int_v1 := 1.U	// x_int_v1 total delay: 0

	val C_sub0 = Module(new ComplexSub())
	complex_d0_v1 := C_sub0.io.out
	C_sub0.io.in1 := x_int_v1
	C_sub0.io.in2 := ranger_complex_input1_p_pos_v0
	// complex_d0_v1 total delay: 3

	val C_sub1 = Module(new ComplexSub())
	complex_d1_v1 := C_sub1.io.out
	C_sub1.io.in1 := x_int_v1
	C_sub1.io.in2 := ranger_complex_input2_p_pos_v0
	// complex_d1_v1 total delay: 3

	val C_mul0 = Module(new ComplexMul())
	complex_tmp0_v1 := C_mul0.io.out
	val complex_input1_p_val_vnull_Reg0 = RegNext(complex_input1_p_val_vnull, 0.U)
	val complex_input1_p_val_vnull_Reg1 = RegNext(complex_input1_p_val_vnull_Reg0, 0.U)
	val complex_input1_p_val_vnull_Reg2 = RegNext(complex_input1_p_val_vnull_Reg1, 0.U)
	C_mul0.io.in1 := complex_input1_p_val_vnull_Reg2
	C_mul0.io.in2 := complex_d1_v1
	// complex_tmp0_v1 total delay: 7

	val C_mul1 = Module(new ComplexMul())
	complex_tmp1_v1 := C_mul1.io.out
	val complex_input2_p_val_vnull_Reg0 = RegNext(complex_input2_p_val_vnull, 0.U)
	val complex_input2_p_val_vnull_Reg1 = RegNext(complex_input2_p_val_vnull_Reg0, 0.U)
	val complex_input2_p_val_vnull_Reg2 = RegNext(complex_input2_p_val_vnull_Reg1, 0.U)
	C_mul1.io.in1 := complex_input2_p_val_vnull_Reg2
	C_mul1.io.in2 := complex_d0_v1
	// complex_tmp1_v1 total delay: 7

	val C_sub2 = Module(new ComplexSub())
	complex_tmp2_v1 := C_sub2.io.out
	C_sub2.io.in1 := complex_tmp0_v1
	C_sub2.io.in2 := complex_tmp1_v1
	// complex_tmp2_v1 total delay: 10

	val C_sub3 = Module(new ComplexSub())
	complex_tmp3_v1 := C_sub3.io.out
	C_sub3.io.in1 := ranger_complex_input1_p_pos_v0
	C_sub3.io.in2 := ranger_complex_input2_p_pos_v0
	// complex_tmp3_v1 total delay: 3
	val C_div0 = Module(new ComplexDiv())
	ranger_complex_output_p_v1 := C_div0.io.out
	val complex_tmp3_v1_Reg0 = RegNext(complex_tmp3_v1, 0.U)
	val complex_tmp3_v1_Reg1 = RegNext(complex_tmp3_v1_Reg0, 0.U)
	val complex_tmp3_v1_Reg2 = RegNext(complex_tmp3_v1_Reg1, 0.U)
	val complex_tmp3_v1_Reg3 = RegNext(complex_tmp3_v1_Reg2, 0.U)
	val complex_tmp3_v1_Reg4 = RegNext(complex_tmp3_v1_Reg3, 0.U)
	val complex_tmp3_v1_Reg5 = RegNext(complex_tmp3_v1_Reg4, 0.U)
	val complex_tmp3_v1_Reg6 = RegNext(complex_tmp3_v1_Reg5, 0.U)
	C_div0.io.in1 := complex_tmp2_v1
	C_div0.io.in2 := complex_tmp3_v1_Reg6
	// ranger_complex_output_p_v1 total delay: 19

	//Write the outputs
	// ranger_complex_output_p_v1 total delay : 19
	io.ranger_complex_output_p_out := ranger_complex_output_p_v1
	val validReg0 = RegNext(io.en, 0.U)
	val validReg1 = RegNext(validReg0, 0.U)
	val validReg2 = RegNext(validReg1, 0.U)
	val validReg3 = RegNext(validReg2, 0.U)
	val validReg4 = RegNext(validReg3, 0.U)
	val validReg5 = RegNext(validReg4, 0.U)
	val validReg6 = RegNext(validReg5, 0.U)
	val validReg7 = RegNext(validReg6, 0.U)
	val validReg8 = RegNext(validReg7, 0.U)
	val validReg9 = RegNext(validReg8, 0.U)
	val validReg10 = RegNext(validReg9, 0.U)
	val validReg11 = RegNext(validReg10, 0.U)
	val validReg12 = RegNext(validReg11, 0.U)
	val validReg13 = RegNext(validReg12, 0.U)
	val validReg14 = RegNext(validReg13, 0.U)
	val validReg15 = RegNext(validReg14, 0.U)
	val validReg16 = RegNext(validReg15, 0.U)
	val validReg17 = RegNext(validReg16, 0.U)
	val validReg18 = RegNext(validReg17, 0.U)
	io.valid := validReg18
}
