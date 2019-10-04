package partialbeamer_2

import ComplexArithmetics._
import fpDivision._ 
import chisel3._
import chisel3.util._ 

class cubic() extends Module {
	val io = IO(new Bundle{
		val beamer_2_complex_input1_p_pos_in = Input(UInt(width = 64.W))
		val beamer_2_complex_input1_p_val_in = Input(UInt(width = 64.W))
		val beamer_2_complex_input2_p_pos_in = Input(UInt(width = 64.W))
		val beamer_2_complex_input2_p_val_in = Input(UInt(width = 64.W))
		val beamer_2_complex_output_p_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val complex_d1_v1 = Wire(UInt(width = 64.W))
	val complex_d0_v1 = Wire(UInt(width = 64.W))
	val complex_tmp1_v1 = Wire(UInt(width = 64.W))
	val complex_tmp0_v1 = Wire(UInt(width = 64.W))
	val complex_tmp3_v3 = Wire(UInt(width = 64.W))
	val complex_tmp3_v2 = Wire(UInt(width = 64.W))
	val complex_tmp3_v1 = Wire(UInt(width = 64.W))
	val complex_tmp2_v1 = Wire(UInt(width = 64.W))
	val x_int_v1 = Wire(UInt(width = 32.W))

	//Read the inputs
	val beamer_2_complex_input1_p_pos_v0 = io.beamer_2_complex_input1_p_pos_in
	val beamer_2_complex_input1_p_val_v0 = io.beamer_2_complex_input1_p_val_in
	val beamer_2_complex_input2_p_pos_v0 = io.beamer_2_complex_input2_p_pos_in
	val beamer_2_complex_input2_p_val_v0 = io.beamer_2_complex_input2_p_val_in

	
	x_int_v1 := 1.U	// x_int_v1 total delay: 0

	val C_sub0 = Module(new ComplexSub())
	complex_d0_v1 := C_sub0.io.out
	C_sub0.io.in1 := x_int_v1
	C_sub0.io.in2 := complex_input1_p_pos
	// complex_d0_v1 total delay: 3

	val C_sub1 = Module(new ComplexSub())
	complex_d1_v1 := C_sub1.io.out
	C_sub1.io.in1 := x_int_v1
	C_sub1.io.in2 := complex_input2_p_pos
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
	C_sub3.io.in1 := complex_input1_p_pos
	C_sub3.io.in2 := complex_input2_p_pos
	// complex_tmp3_v1 total delay: 3
	when ( complex_tmp3_v1 === 0.U ){
		complex_tmp3_v2 := 1.U		// complex_tmp3_v2 total delay: 0
	}

	//Phi functions (Muxes) go in here
	complex_tmp3_v3 := Mux(complex_tmp3_v3 === 0.U, complex_tmp3_v2, complex_tmp3_v1)

	val C_div0 = Module(new ComplexDiv())
	complex_output_p := C_div0.io.out
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
	// complex_output_p_vnull total delay: 19

	//Write the outputs
	// beamer_2_complex_output_p_v0 total delay : 0
	io.beamer_2_complex_output_p_out := beamer_2_complex_output_p_v0
	io.valid := io.en
}
