package partialbeamer

import ComplexArithmetics._
import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 
package partialbeamer

import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class correlation() extends Module {
	val io = IO(new Bundle{
		val beamer_correlation_input1_in = Input(UInt(width = 64.W))
		val beamer_correlation_input2_in = Input(UInt(width = 64.W))
		val beamer_total_sum_in = Input(UInt(width = 32.W))
		val beamer_total_sum_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val tmp5_v1 = Wire(UInt(width = 32.W))
	val tmp3_v1 = Wire(UInt(width = 32.W))
	val tmp4_v1 = Wire(UInt(width = 32.W))
	val tmp1_v1 = Wire(UInt(width = 32.W))
	val tmp2_v1 = Wire(UInt(width = 32.W))
	val beamer_total_sum_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def NOF_PIXELS_KERNEL : Int = 36
	def NOF_PIXELS : Int = 216
	def RA_RB_SIZE : Int = NOF_PIXELS_KERNEL2

	//Read the inputs
	val beamer_correlation_input1_v0 = io.beamer_correlation_input1_in
	val beamer_correlation_input2_v0 = io.beamer_correlation_input2_in
	val beamer_total_sum_v0 = io.beamer_total_sum_in

	
	val c_mag0 = Module(new C_mag())
	c_mag0.io.in := beamer_correlation_input1_v0
	val C_mag_ret_v0 = c_mag0.io.out
	tmp1_v1 := C_mag_ret_v0	// tmp1_v1 total delay: 9
	
	val c_mag1 = Module(new C_mag())
	c_mag1.io.in := beamer_correlation_input2_v0
	val C_mag_ret_v1 = c_mag1.io.out
	tmp2_v1 := C_mag_ret_v0	// tmp2_v1 total delay: 9

	val FP_mul0 = Module(new FPMult(32))
	tmp3_v1 := FP_mul0.io.out
	FP_mul0.io.in1 := tmp1_v1
	FP_mul0.io.in2 := tmp1_v1
	// tmp3_v1 total delay: 11

	val FP_mul1 = Module(new FPMult(32))
	tmp4_v1 := FP_mul1.io.out
	FP_mul1.io.in1 := tmp2_v1
	FP_mul1.io.in2 := tmp2_v1
	// tmp4_v1 total delay: 11

	val FP_mul2 = Module(new FPMult(32))
	tmp5_v1 := FP_mul2.io.out
	FP_mul2.io.in1 := tmp3_v1
	FP_mul2.io.in2 := tmp4_v1
	// tmp5_v1 total delay: 13

	val FP_add0 = Module(new FPAdd(32))
	beamer_total_sum_v1 := FP_add0.io.out
	val total_sum_vnull_Reg0 = RegNext(total_sum_vnull, 0.U)
	val total_sum_vnull_Reg1 = RegNext(total_sum_vnull_Reg0, 0.U)
	val total_sum_vnull_Reg2 = RegNext(total_sum_vnull_Reg1, 0.U)
	val total_sum_vnull_Reg3 = RegNext(total_sum_vnull_Reg2, 0.U)
	val total_sum_vnull_Reg4 = RegNext(total_sum_vnull_Reg3, 0.U)
	val total_sum_vnull_Reg5 = RegNext(total_sum_vnull_Reg4, 0.U)
	val total_sum_vnull_Reg6 = RegNext(total_sum_vnull_Reg5, 0.U)
	val total_sum_vnull_Reg7 = RegNext(total_sum_vnull_Reg6, 0.U)
	val total_sum_vnull_Reg8 = RegNext(total_sum_vnull_Reg7, 0.U)
	val total_sum_vnull_Reg9 = RegNext(total_sum_vnull_Reg8, 0.U)
	val total_sum_vnull_Reg10 = RegNext(total_sum_vnull_Reg9, 0.U)
	val total_sum_vnull_Reg11 = RegNext(total_sum_vnull_Reg10, 0.U)
	val total_sum_vnull_Reg12 = RegNext(total_sum_vnull_Reg11, 0.U)
	FP_add0.io.in1 := total_sum_vnull_Reg12
	FP_add0.io.in2 := tmp5_v1
	// beamer_total_sum_v1 total delay: 16

	val FP_div0 = Module(new FPDiv(32))
FP_div0.io.out
	FP_div0.io.in1 := 
	FP_div0.io.in2 := 

	//Write the outputs
	// beamer_total_sum_v1 total delay : 16
	io.beamer_total_sum_out := beamer_total_sum_v1
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
	io.valid := validReg15
}
class cubic() extends Module {
	val io = IO(new Bundle{
		val beamer_complex_input1_p_pos_in = Input(UInt(width = 64.W))
		val beamer_complex_input1_p_val_in = Input(UInt(width = 64.W))
		val beamer_complex_input2_p_pos_in = Input(UInt(width = 64.W))
		val beamer_complex_input2_p_val_in = Input(UInt(width = 64.W))
		val beamer_complex_output_p_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

		//Define all versions of the variables
		val complex_d1_v1 = Wire(UInt(width = 64.W))
		val complex_d0_v1 = Wire(UInt(width = 64.W))
		val x_int_v1 = Wire(UInt(width = 32.W))
		val complex_tmp1_v1 = Wire(UInt(width = 64.W))
		val beamer_complex_output_p_v1 = Wire(UInt(width = 32.W))
		val complex_tmp0_v1 = Wire(UInt(width = 64.W))
		val complex_tmp3_v3 = Wire(UInt(width = 64.W))
		val complex_tmp3_v2 = Wire(UInt(width = 64.W))
		val complex_tmp3_v1 = Wire(UInt(width = 64.W))
		val complex_tmp2_v1 = Wire(UInt(width = 64.W))

		//Define the constants
		def NOF_PIXELS_KERNEL : Int = 36
		def NOF_PIXELS : Int = 216
		def RA_RB_SIZE : Int = NOF_PIXELS_KERNEL2

		//Read the inputs
		val beamer_complex_input1_p_pos_v0 = io.beamer_complex_input1_p_pos_in
		val beamer_complex_input1_p_val_v0 = io.beamer_complex_input1_p_val_in
		val beamer_complex_input2_p_pos_v0 = io.beamer_complex_input2_p_pos_in
		val beamer_complex_input2_p_val_v0 = io.beamer_complex_input2_p_val_in

		
		x_int_v1 := 1.U		// x_int_v1 total delay: 0

		val C_sub0 = Module(new ComplexSub())
		complex_d0_v1 := C_sub0.io.out
		C_sub0.io.in1 := x_int_v1
		C_sub0.io.in2 := beamer_complex_input1_p_pos_v0
		// complex_d0_v1 total delay: 3

		val C_sub1 = Module(new ComplexSub())
		complex_d1_v1 := C_sub1.io.out
		C_sub1.io.in1 := x_int_v1
		C_sub1.io.in2 := beamer_complex_input2_p_pos_v0
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
		C_sub3.io.in1 := beamer_complex_input1_p_pos_v0
		C_sub3.io.in2 := beamer_complex_input2_p_pos_v0
		// complex_tmp3_v1 total delay: 3
		when ( complex_tmp3_v1 === 0.U ){
			complex_tmp3_v2 := 1.U			// complex_tmp3_v2 total delay: 0
		}

		//Phi functions (Muxes) go in here
		complex_tmp3_v3 := Mux(complex_tmp3_v3 === 0.U, complex_tmp3_v2, complex_tmp3_v1)

		val C_div0 = Module(new ComplexDiv())
		beamer_complex_output_p_v1 := C_div0.io.out
		val complex_tmp3_v3_Reg0 = RegNext(complex_tmp3_v3, 0.U)
		val complex_tmp3_v3_Reg1 = RegNext(complex_tmp3_v3_Reg0, 0.U)
		val complex_tmp3_v3_Reg2 = RegNext(complex_tmp3_v3_Reg1, 0.U)
		val complex_tmp3_v3_Reg3 = RegNext(complex_tmp3_v3_Reg2, 0.U)
		val complex_tmp3_v3_Reg4 = RegNext(complex_tmp3_v3_Reg3, 0.U)
		val complex_tmp3_v3_Reg5 = RegNext(complex_tmp3_v3_Reg4, 0.U)
		val complex_tmp3_v3_Reg6 = RegNext(complex_tmp3_v3_Reg5, 0.U)
		val complex_tmp3_v3_Reg7 = RegNext(complex_tmp3_v3_Reg6, 0.U)
		val complex_tmp3_v3_Reg8 = RegNext(complex_tmp3_v3_Reg7, 0.U)
		val complex_tmp3_v3_Reg9 = RegNext(complex_tmp3_v3_Reg8, 0.U)
		C_div0.io.in1 := complex_tmp2_v1
		C_div0.io.in2 := complex_tmp3_v3_Reg9
		// beamer_complex_output_p_v1 total delay: 19

		val FP_div1 = Module(new FPDiv(32))
FP_div1.io.out
		FP_div1.io.in1 := 
		FP_div1.io.in2 := 

		//Write the outputs
		// beamer_complex_output_p_v1 total delay : 19
		io.beamer_complex_output_p_out := beamer_complex_output_p_v1
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
