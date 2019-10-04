package partialsingleQRD

import fpDivision._ 
import chisel3._
import chisel3.util._ 

class calculate_boundary_part2() extends Module {
	val io = IO(new Bundle{
		val ROW_SIZE_in = Input(UInt(width = 32.W))
		val r_in = Input(UInt(width = 32.W))
		val x_in_in = Input(UInt(width = 32.W))
		val row_counter_in = Input(UInt(width = 32.W))
		val col_counter_in = Input(UInt(width = 32.W))
		val r_out = Output(UInt(width = 32.W))
		val c_out = Output(UInt(width = 32.W))
		val s_out = Output(UInt(width = 32.W))
		val col_counter_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val a_v1 = Wire(UInt(width = 32.W))
	val b_v1 = Wire(UInt(width = 32.W))
	val c_v1 = Wire(UInt(width = 32.W))
	val sqrt_tmp_v1 = Wire(UInt(width = 32.W))
	val r_v1 = Wire(UInt(width = 32.W))
	val s_v1 = Wire(UInt(width = 32.W))
	val col_counter_v1 = Wire(UInt(width = 32.W))
	val r_tmp_v1 = Wire(UInt(width = 32.W))
	//Define the temp values for the outputs
	val c_v0 = Wire(UInt(width = 32.W))
	val s_v0 = Wire(UInt(width = 32.W))

	//Read the inputs
	val ROW_SIZE_v0 = io.ROW_SIZE_in
	val r_v0 = io.r_in
	val x_in_v0 = io.x_in_in
	val row_counter_v0 = io.row_counter_in
	val col_counter_v0 = io.col_counter_in
	val a_v0 = Wire(UInt(width = 32.W))
	val b_v0 = Wire(UInt(width = 32.W))
	val r_tmp_v0 = Wire(UInt(width = 32.W))
	val sqrt_tmp_v0 = Wire(UInt(width = 32.W))

	

	val FP_mul0 = Module(new FPMult(32))
	a_v1 := FP_mul0.io.out
	FP_mul0.io.in1 := r_v0
	FP_mul0.io.in2 := r_v0
	// a_v1 total delay: 0

	val FP_mul1 = Module(new FPMult(32))
	b_v1 := FP_mul1.io.out
	FP_mul1.io.in1 := x_in_v0
	FP_mul1.io.in2 := x_in_v0
	// b_v1 total delay: 0

	val FP_add0 = Module(new FPAdd32())
	sqrt_tmp_v1 := FP_add0.io.out
	FP_add0.io.in1 := a_v1
	FP_add0.io.in2 := b_v1
	// sqrt_tmp_v1 total delay: 4
	
	val sqrt0 = Module(new FPSqrt())
	sqrt0.io.in := sqrt_tmp_v1
	val SquareRoot_ret_v0 = sqrt0.io.out
	r_tmp_v1 := SquareRoot_ret_v0	// r_tmp_v1 total delay: 9

	val FP_div0 = Module(new FPDiv(32))
	c_v1 := FP_div0.io.out
	val r_v0_Reg0 = RegNext(r_v0, 0.U)
	val r_v0_Reg1 = RegNext(r_v0_Reg0, 0.U)
	val r_v0_Reg2 = RegNext(r_v0_Reg1, 0.U)
	val r_v0_Reg3 = RegNext(r_v0_Reg2, 0.U)
	val r_v0_Reg4 = RegNext(r_v0_Reg3, 0.U)
	val r_v0_Reg5 = RegNext(r_v0_Reg4, 0.U)
	val r_v0_Reg6 = RegNext(r_v0_Reg5, 0.U)
	val r_v0_Reg7 = RegNext(r_v0_Reg6, 0.U)
	val r_v0_Reg8 = RegNext(r_v0_Reg7, 0.U)
	FP_div0.io.in1 := r_v0_Reg8
	FP_div0.io.in2 := r_tmp_v1
	// c_v1 total delay: 14

	val FP_div1 = Module(new FPDiv(32))
	s_v1 := FP_div1.io.out
	val x_in_v0_Reg0 = RegNext(x_in_v0, 0.U)
	val x_in_v0_Reg1 = RegNext(x_in_v0_Reg0, 0.U)
	val x_in_v0_Reg2 = RegNext(x_in_v0_Reg1, 0.U)
	val x_in_v0_Reg3 = RegNext(x_in_v0_Reg2, 0.U)
	val x_in_v0_Reg4 = RegNext(x_in_v0_Reg3, 0.U)
	val x_in_v0_Reg5 = RegNext(x_in_v0_Reg4, 0.U)
	val x_in_v0_Reg6 = RegNext(x_in_v0_Reg5, 0.U)
	val x_in_v0_Reg7 = RegNext(x_in_v0_Reg6, 0.U)
	val x_in_v0_Reg8 = RegNext(x_in_v0_Reg7, 0.U)
	FP_div1.io.in1 := x_in_v0_Reg8
	FP_div1.io.in2 := r_tmp_v1
	// s_v1 total delay: 14
	r_v1 := r_tmp_v1

	val FP_add1 = Module(new FPAdd32())
	col_counter_v1 := FP_add1.io.out
	FP_add1.io.in1 := col_counter_v0
	FP_add1.io.in2 := 1.U
	// col_counter_v1 total delay: 4

	//Write the outputs
	// r_v1 total delay : 9
	// c_v1 total delay : 14
	// s_v1 total delay : 14
	// col_counter_v1 total delay : 4
	val r_v1_Reg0 = RegNext(r_v1, 0.U)
	val r_v1_Reg1 = RegNext(r_v1_Reg0, 0.U)
	val r_v1_Reg2 = RegNext(r_v1_Reg1, 0.U)
	val r_v1_Reg3 = RegNext(r_v1_Reg2, 0.U)
	val r_v1_Reg4 = RegNext(r_v1_Reg3, 0.U)
	io.r_out := r_v1_Reg4
	io.c_out := c_v1
	io.s_out := s_v1
	val col_counter_v1_Reg0 = RegNext(col_counter_v1, 0.U)
	val col_counter_v1_Reg1 = RegNext(col_counter_v1_Reg0, 0.U)
	val col_counter_v1_Reg2 = RegNext(col_counter_v1_Reg1, 0.U)
	val col_counter_v1_Reg3 = RegNext(col_counter_v1_Reg2, 0.U)
	val col_counter_v1_Reg4 = RegNext(col_counter_v1_Reg3, 0.U)
	val col_counter_v1_Reg5 = RegNext(col_counter_v1_Reg4, 0.U)
	val col_counter_v1_Reg6 = RegNext(col_counter_v1_Reg5, 0.U)
	val col_counter_v1_Reg7 = RegNext(col_counter_v1_Reg6, 0.U)
	val col_counter_v1_Reg8 = RegNext(col_counter_v1_Reg7, 0.U)
	val col_counter_v1_Reg9 = RegNext(col_counter_v1_Reg8, 0.U)
	io.col_counter_out := col_counter_v1_Reg9
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
	io.valid := validReg13
}
