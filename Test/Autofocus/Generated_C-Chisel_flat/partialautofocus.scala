package partialautofocus

import fpDivision._ 
import chisel3._
import chisel3.util._ 

class cubic() extends Module {
	val io = IO(new Bundle{
		val p0_pos_real_in = Input(UInt(width = 32.W))
		val p0_pos_imag_in = Input(UInt(width = 32.W))
		val p1_pos_real_in = Input(UInt(width = 32.W))
		val p1_pos_imag_in = Input(UInt(width = 32.W))
		val p2_pos_real_in = Input(UInt(width = 32.W))
		val p2_pos_imag_in = Input(UInt(width = 32.W))
		val p3_pos_real_in = Input(UInt(width = 32.W))
		val p3_pos_imag_in = Input(UInt(width = 32.W))
		val p0_val_real_in = Input(UInt(width = 32.W))
		val p0_val_imag_in = Input(UInt(width = 32.W))
		val p1_val_real_in = Input(UInt(width = 32.W))
		val p1_val_imag_in = Input(UInt(width = 32.W))
		val p2_val_real_in = Input(UInt(width = 32.W))
		val p2_val_imag_in = Input(UInt(width = 32.W))
		val p3_val_real_in = Input(UInt(width = 32.W))
		val p3_val_imag_in = Input(UInt(width = 32.W))
		val p03_real_out = Output(UInt(width = 32.W))
		val p03_imag_out = Output(UInt(width = 32.W))
	})



	//Define all versions of the variables
	val d1_imag_v1 = Wire(UInt(width = 32.W))
	val p01_real_v1 = Wire(UInt(width = 32.W))
	val tmp3_real_v6 = Wire(UInt(width = 32.W))
	val tmp3_real_v5 = Wire(UInt(width = 32.W))
	val tmp3_real_v4 = Wire(UInt(width = 32.W))
	val tmp3_real_v3 = Wire(UInt(width = 32.W))
	val tmp3_real_v2 = Wire(UInt(width = 32.W))
	val tmp3_real_v1 = Wire(UInt(width = 32.W))
	val p02_imag_v1 = Wire(UInt(width = 32.W))
	val denom_v6 = Wire(UInt(width = 32.W))
	val denom_v5 = Wire(UInt(width = 32.W))
	val denom_v4 = Wire(UInt(width = 32.W))
	val denom_v3 = Wire(UInt(width = 32.W))
	val denom_v2 = Wire(UInt(width = 32.W))
	val denom_v1 = Wire(UInt(width = 32.W))
	val d0_imag_v1 = Wire(UInt(width = 32.W))
	val p23_real_v1 = Wire(UInt(width = 32.W))
	val tmp0_imag_v6 = Wire(UInt(width = 32.W))
	val tmp0_imag_v5 = Wire(UInt(width = 32.W))
	val tmp0_imag_v4 = Wire(UInt(width = 32.W))
	val tmp0_imag_v3 = Wire(UInt(width = 32.W))
	val tmp0_imag_v2 = Wire(UInt(width = 32.W))
	val tmp0_imag_v1 = Wire(UInt(width = 32.W))
	val tmp3_imag_v6 = Wire(UInt(width = 32.W))
	val tmp3_imag_v5 = Wire(UInt(width = 32.W))
	val tmp3_imag_v4 = Wire(UInt(width = 32.W))
	val tmp3_imag_v3 = Wire(UInt(width = 32.W))
	val tmp3_imag_v2 = Wire(UInt(width = 32.W))
	val tmp3_imag_v1 = Wire(UInt(width = 32.W))
	val p13_real_v1 = Wire(UInt(width = 32.W))
	val x_int_real_v1 = Wire(UInt(width = 32.W))
	val d1_real_v1 = Wire(UInt(width = 32.W))
	val d2_imag_v1 = Wire(UInt(width = 32.W))
	val p03_imag_v1 = Wire(UInt(width = 32.W))
	val p02_real_v1 = Wire(UInt(width = 32.W))
	val tmp2_real_v6 = Wire(UInt(width = 32.W))
	val tmp2_real_v5 = Wire(UInt(width = 32.W))
	val tmp2_real_v4 = Wire(UInt(width = 32.W))
	val tmp2_real_v3 = Wire(UInt(width = 32.W))
	val tmp2_real_v2 = Wire(UInt(width = 32.W))
	val tmp2_real_v1 = Wire(UInt(width = 32.W))
	val tmp00_v42 = Wire(UInt(width = 32.W))
	val tmp00_v41 = Wire(UInt(width = 32.W))
	val tmp00_v40 = Wire(UInt(width = 32.W))
	val tmp00_v39 = Wire(UInt(width = 32.W))
	val tmp00_v38 = Wire(UInt(width = 32.W))
	val tmp00_v37 = Wire(UInt(width = 32.W))
	val tmp00_v36 = Wire(UInt(width = 32.W))
	val tmp00_v35 = Wire(UInt(width = 32.W))
	val tmp00_v34 = Wire(UInt(width = 32.W))
	val tmp00_v33 = Wire(UInt(width = 32.W))
	val tmp00_v32 = Wire(UInt(width = 32.W))
	val tmp00_v31 = Wire(UInt(width = 32.W))
	val tmp00_v30 = Wire(UInt(width = 32.W))
	val tmp00_v29 = Wire(UInt(width = 32.W))
	val tmp00_v28 = Wire(UInt(width = 32.W))
	val tmp00_v27 = Wire(UInt(width = 32.W))
	val tmp00_v26 = Wire(UInt(width = 32.W))
	val tmp00_v25 = Wire(UInt(width = 32.W))
	val tmp00_v24 = Wire(UInt(width = 32.W))
	val tmp00_v23 = Wire(UInt(width = 32.W))
	val tmp00_v22 = Wire(UInt(width = 32.W))
	val tmp00_v21 = Wire(UInt(width = 32.W))
	val tmp00_v20 = Wire(UInt(width = 32.W))
	val tmp00_v19 = Wire(UInt(width = 32.W))
	val tmp00_v18 = Wire(UInt(width = 32.W))
	val tmp00_v17 = Wire(UInt(width = 32.W))
	val tmp00_v16 = Wire(UInt(width = 32.W))
	val tmp00_v15 = Wire(UInt(width = 32.W))
	val tmp00_v14 = Wire(UInt(width = 32.W))
	val tmp00_v13 = Wire(UInt(width = 32.W))
	val tmp00_v12 = Wire(UInt(width = 32.W))
	val tmp00_v11 = Wire(UInt(width = 32.W))
	val tmp00_v10 = Wire(UInt(width = 32.W))
	val tmp00_v9 = Wire(UInt(width = 32.W))
	val tmp00_v8 = Wire(UInt(width = 32.W))
	val tmp00_v7 = Wire(UInt(width = 32.W))
	val tmp00_v6 = Wire(UInt(width = 32.W))
	val tmp00_v5 = Wire(UInt(width = 32.W))
	val tmp00_v4 = Wire(UInt(width = 32.W))
	val tmp00_v3 = Wire(UInt(width = 32.W))
	val tmp00_v2 = Wire(UInt(width = 32.W))
	val tmp00_v1 = Wire(UInt(width = 32.W))
	val tmp1_imag_v6 = Wire(UInt(width = 32.W))
	val tmp1_imag_v5 = Wire(UInt(width = 32.W))
	val tmp1_imag_v4 = Wire(UInt(width = 32.W))
	val tmp1_imag_v3 = Wire(UInt(width = 32.W))
	val tmp1_imag_v2 = Wire(UInt(width = 32.W))
	val tmp1_imag_v1 = Wire(UInt(width = 32.W))
	val tmp02_v18 = Wire(UInt(width = 32.W))
	val tmp02_v17 = Wire(UInt(width = 32.W))
	val tmp02_v16 = Wire(UInt(width = 32.W))
	val tmp02_v15 = Wire(UInt(width = 32.W))
	val tmp02_v14 = Wire(UInt(width = 32.W))
	val tmp02_v13 = Wire(UInt(width = 32.W))
	val tmp02_v12 = Wire(UInt(width = 32.W))
	val tmp02_v11 = Wire(UInt(width = 32.W))
	val tmp02_v10 = Wire(UInt(width = 32.W))
	val tmp02_v9 = Wire(UInt(width = 32.W))
	val tmp02_v8 = Wire(UInt(width = 32.W))
	val tmp02_v7 = Wire(UInt(width = 32.W))
	val tmp02_v6 = Wire(UInt(width = 32.W))
	val tmp02_v5 = Wire(UInt(width = 32.W))
	val tmp02_v4 = Wire(UInt(width = 32.W))
	val tmp02_v3 = Wire(UInt(width = 32.W))
	val tmp02_v2 = Wire(UInt(width = 32.W))
	val tmp02_v1 = Wire(UInt(width = 32.W))
	val tmp01_v42 = Wire(UInt(width = 32.W))
	val tmp01_v41 = Wire(UInt(width = 32.W))
	val tmp01_v40 = Wire(UInt(width = 32.W))
	val tmp01_v39 = Wire(UInt(width = 32.W))
	val tmp01_v38 = Wire(UInt(width = 32.W))
	val tmp01_v37 = Wire(UInt(width = 32.W))
	val tmp01_v36 = Wire(UInt(width = 32.W))
	val tmp01_v35 = Wire(UInt(width = 32.W))
	val tmp01_v34 = Wire(UInt(width = 32.W))
	val tmp01_v33 = Wire(UInt(width = 32.W))
	val tmp01_v32 = Wire(UInt(width = 32.W))
	val tmp01_v31 = Wire(UInt(width = 32.W))
	val tmp01_v30 = Wire(UInt(width = 32.W))
	val tmp01_v29 = Wire(UInt(width = 32.W))
	val tmp01_v28 = Wire(UInt(width = 32.W))
	val tmp01_v27 = Wire(UInt(width = 32.W))
	val tmp01_v26 = Wire(UInt(width = 32.W))
	val tmp01_v25 = Wire(UInt(width = 32.W))
	val tmp01_v24 = Wire(UInt(width = 32.W))
	val tmp01_v23 = Wire(UInt(width = 32.W))
	val tmp01_v22 = Wire(UInt(width = 32.W))
	val tmp01_v21 = Wire(UInt(width = 32.W))
	val tmp01_v20 = Wire(UInt(width = 32.W))
	val tmp01_v19 = Wire(UInt(width = 32.W))
	val tmp01_v18 = Wire(UInt(width = 32.W))
	val tmp01_v17 = Wire(UInt(width = 32.W))
	val tmp01_v16 = Wire(UInt(width = 32.W))
	val tmp01_v15 = Wire(UInt(width = 32.W))
	val tmp01_v14 = Wire(UInt(width = 32.W))
	val tmp01_v13 = Wire(UInt(width = 32.W))
	val tmp01_v12 = Wire(UInt(width = 32.W))
	val tmp01_v11 = Wire(UInt(width = 32.W))
	val tmp01_v10 = Wire(UInt(width = 32.W))
	val tmp01_v9 = Wire(UInt(width = 32.W))
	val tmp01_v8 = Wire(UInt(width = 32.W))
	val tmp01_v7 = Wire(UInt(width = 32.W))
	val tmp01_v6 = Wire(UInt(width = 32.W))
	val tmp01_v5 = Wire(UInt(width = 32.W))
	val tmp01_v4 = Wire(UInt(width = 32.W))
	val tmp01_v3 = Wire(UInt(width = 32.W))
	val tmp01_v2 = Wire(UInt(width = 32.W))
	val tmp01_v1 = Wire(UInt(width = 32.W))
	val p03_real_v1 = Wire(UInt(width = 32.W))
	val tmp0_real_v6 = Wire(UInt(width = 32.W))
	val tmp0_real_v5 = Wire(UInt(width = 32.W))
	val tmp0_real_v4 = Wire(UInt(width = 32.W))
	val tmp0_real_v3 = Wire(UInt(width = 32.W))
	val tmp0_real_v2 = Wire(UInt(width = 32.W))
	val tmp0_real_v1 = Wire(UInt(width = 32.W))
	val tmp2_imag_v6 = Wire(UInt(width = 32.W))
	val tmp2_imag_v5 = Wire(UInt(width = 32.W))
	val tmp2_imag_v4 = Wire(UInt(width = 32.W))
	val tmp2_imag_v3 = Wire(UInt(width = 32.W))
	val tmp2_imag_v2 = Wire(UInt(width = 32.W))
	val tmp2_imag_v1 = Wire(UInt(width = 32.W))
	val d3_imag_v1 = Wire(UInt(width = 32.W))
	val p12_real_v1 = Wire(UInt(width = 32.W))
	val d2_real_v1 = Wire(UInt(width = 32.W))
	val p13_imag_v1 = Wire(UInt(width = 32.W))
	val p01_imag_v1 = Wire(UInt(width = 32.W))
	val d3_real_v1 = Wire(UInt(width = 32.W))
	val tmp1_real_v6 = Wire(UInt(width = 32.W))
	val tmp1_real_v5 = Wire(UInt(width = 32.W))
	val tmp1_real_v4 = Wire(UInt(width = 32.W))
	val tmp1_real_v3 = Wire(UInt(width = 32.W))
	val tmp1_real_v2 = Wire(UInt(width = 32.W))
	val tmp1_real_v1 = Wire(UInt(width = 32.W))
	val p12_imag_v1 = Wire(UInt(width = 32.W))
	val d0_real_v1 = Wire(UInt(width = 32.W))
	val p23_imag_v1 = Wire(UInt(width = 32.W))
	val x_int_imag_v1 = Wire(UInt(width = 32.W))
	//Define the temp values for the outputs
	val p03_real_v0 = Wire(UInt(width = 32.W))
	val p03_imag_v0 = Wire(UInt(width = 32.W))

	//Read the inputs
	val p0_pos_real_v0 = io.p0_pos_real_in
	val p0_pos_imag_v0 = io.p0_pos_imag_in
	val p1_pos_real_v0 = io.p1_pos_real_in
	val p1_pos_imag_v0 = io.p1_pos_imag_in
	val p2_pos_real_v0 = io.p2_pos_real_in
	val p2_pos_imag_v0 = io.p2_pos_imag_in
	val p3_pos_real_v0 = io.p3_pos_real_in
	val p3_pos_imag_v0 = io.p3_pos_imag_in
	val p0_val_real_v0 = io.p0_val_real_in
	val p0_val_imag_v0 = io.p0_val_imag_in
	val p1_val_real_v0 = io.p1_val_real_in
	val p1_val_imag_v0 = io.p1_val_imag_in
	val p2_val_real_v0 = io.p2_val_real_in
	val p2_val_imag_v0 = io.p2_val_imag_in
	val p3_val_real_v0 = io.p3_val_real_in
	val p3_val_imag_v0 = io.p3_val_imag_in
	val tmp0_real_v0 = Wire(UInt(width = 32.W))
	val tmp0_imag_v0 = Wire(UInt(width = 32.W))
	val tmp00_v0 = Wire(UInt(width = 32.W))
	val tmp01_v0 = Wire(UInt(width = 32.W))
	val tmp02_v0 = Wire(UInt(width = 32.W))
	val tmp1_real_v0 = Wire(UInt(width = 32.W))
	val tmp1_imag_v0 = Wire(UInt(width = 32.W))
	val tmp2_real_v0 = Wire(UInt(width = 32.W))
	val tmp2_imag_v0 = Wire(UInt(width = 32.W))
	val tmp3_real_v0 = Wire(UInt(width = 32.W))
	val tmp3_imag_v0 = Wire(UInt(width = 32.W))
	val d0_real_v0 = Wire(UInt(width = 32.W))
	val d0_imag_v0 = Wire(UInt(width = 32.W))
	val d1_real_v0 = Wire(UInt(width = 32.W))
	val d1_imag_v0 = Wire(UInt(width = 32.W))
	val d2_real_v0 = Wire(UInt(width = 32.W))
	val d2_imag_v0 = Wire(UInt(width = 32.W))
	val d3_real_v0 = Wire(UInt(width = 32.W))
	val d3_imag_v0 = Wire(UInt(width = 32.W))
	val p01_real_v0 = Wire(UInt(width = 32.W))
	val p01_imag_v0 = Wire(UInt(width = 32.W))
	val p12_real_v0 = Wire(UInt(width = 32.W))
	val p12_imag_v0 = Wire(UInt(width = 32.W))
	val p23_real_v0 = Wire(UInt(width = 32.W))
	val p23_imag_v0 = Wire(UInt(width = 32.W))
	val p02_real_v0 = Wire(UInt(width = 32.W))
	val p02_imag_v0 = Wire(UInt(width = 32.W))
	val p13_real_v0 = Wire(UInt(width = 32.W))
	val p13_imag_v0 = Wire(UInt(width = 32.W))
	val x_int_real_v0 = Wire(UInt(width = 32.W))
	val x_int_imag_v0 = Wire(UInt(width = 32.W))
	val denom_v0 = Wire(UInt(width = 32.W))

	x_int_real_v1 := "b00111111100000000000000000000000".U
	x_int_imag_v1 := "b00111111100000000000000000000000".U
	val FP_sub0 = Module(new FPAdd(32))
	d0_real_v1 := FP_sub0.io.out
	FP_sub0.io.in1 := x_int_real_v1
	FP_sub0.io.in2 := "b10000000000000000000000000000000".U ^ p0_pos_real_v0
	val FP_sub1 = Module(new FPAdd(32))
	d0_imag_v1 := FP_sub1.io.out
	FP_sub1.io.in1 := x_int_imag_v1
	FP_sub1.io.in2 := "b10000000000000000000000000000000".U ^ p0_pos_imag_v0
	val FP_sub2 = Module(new FPAdd(32))
	d1_real_v1 := FP_sub2.io.out
	FP_sub2.io.in1 := x_int_real_v1
	FP_sub2.io.in2 := "b10000000000000000000000000000000".U ^ p1_pos_real_v0
	val FP_sub3 = Module(new FPAdd(32))
	d1_imag_v1 := FP_sub3.io.out
	FP_sub3.io.in1 := x_int_imag_v1
	FP_sub3.io.in2 := "b10000000000000000000000000000000".U ^ p1_pos_imag_v0
	val FP_sub4 = Module(new FPAdd(32))
	d2_real_v1 := FP_sub4.io.out
	FP_sub4.io.in1 := x_int_real_v1
	FP_sub4.io.in2 := "b10000000000000000000000000000000".U ^ p2_pos_real_v0
	val FP_sub5 = Module(new FPAdd(32))
	d2_imag_v1 := FP_sub5.io.out
	FP_sub5.io.in1 := x_int_imag_v1
	FP_sub5.io.in2 := "b10000000000000000000000000000000".U ^ p2_pos_imag_v0
	val FP_sub6 = Module(new FPAdd(32))
	d3_real_v1 := FP_sub6.io.out
	FP_sub6.io.in1 := x_int_real_v1
	FP_sub6.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_real_v0
	val FP_sub7 = Module(new FPAdd(32))
	d3_imag_v1 := FP_sub7.io.out
	FP_sub7.io.in1 := x_int_imag_v1
	FP_sub7.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_imag_v0
	val FP_mul0 = Module(new FPMult(32))
	tmp00_v1 := FP_mul0.io.out
	FP_mul0.io.in1 := p0_pos_real_v0
	FP_mul0.io.in2 := d1_real_v1

	val FP_mul1 = Module(new FPMult(32))
	tmp01_v1 := FP_mul1.io.out
	FP_mul1.io.in1 := p0_val_imag_v0
	FP_mul1.io.in2 := d1_imag_v1

	val FP_sub8 = Module(new FPAdd(32))
	tmp0_real_v1 := FP_sub8.io.out
	FP_sub8.io.in1 := tmp00_v1
	FP_sub8.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v1
	val FP_mul2 = Module(new FPMult(32))
	tmp00_v2 := FP_mul2.io.out
	FP_mul2.io.in1 := p0_val_real_v0
	FP_mul2.io.in2 := d1_imag_v1

	val FP_mul3 = Module(new FPMult(32))
	tmp01_v2 := FP_mul3.io.out
	FP_mul3.io.in1 := p0_val_imag_v0
	FP_mul3.io.in2 := d1_real_v1

	val FP_add0 = Module(new FPAdd(32))
	tmp0_imag_v1 := FP_add0.io.out
	FP_add0.io.in1 := tmp00_v2
	FP_add0.io.in2 := tmp01_v2

	val FP_mul4 = Module(new FPMult(32))
	tmp00_v3 := FP_mul4.io.out
	FP_mul4.io.in1 := p1_pos_real_v0
	FP_mul4.io.in2 := d0_real_v1

	val FP_mul5 = Module(new FPMult(32))
	tmp01_v3 := FP_mul5.io.out
	FP_mul5.io.in1 := p1_val_imag_v0
	FP_mul5.io.in2 := d0_imag_v1

	val FP_sub9 = Module(new FPAdd(32))
	tmp1_real_v1 := FP_sub9.io.out
	FP_sub9.io.in1 := tmp00_v3
	FP_sub9.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v3
	val FP_mul6 = Module(new FPMult(32))
	tmp00_v4 := FP_mul6.io.out
	FP_mul6.io.in1 := p1_val_real_v0
	FP_mul6.io.in2 := d0_imag_v1

	val FP_mul7 = Module(new FPMult(32))
	tmp01_v4 := FP_mul7.io.out
	FP_mul7.io.in1 := p1_val_imag_v0
	FP_mul7.io.in2 := d0_real_v1

	val FP_add1 = Module(new FPAdd(32))
	tmp1_imag_v1 := FP_add1.io.out
	FP_add1.io.in1 := tmp00_v4
	FP_add1.io.in2 := tmp01_v4

	val FP_sub10 = Module(new FPAdd(32))
	tmp2_real_v1 := FP_sub10.io.out
	FP_sub10.io.in1 := tmp0_real_v1
	FP_sub10.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_real_v1
	val FP_sub11 = Module(new FPAdd(32))
	tmp2_imag_v1 := FP_sub11.io.out
	FP_sub11.io.in1 := tmp0_imag_v1
	FP_sub11.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_imag_v1
	val FP_sub12 = Module(new FPAdd(32))
	tmp3_real_v1 := FP_sub12.io.out
	FP_sub12.io.in1 := p0_pos_real_v0
	FP_sub12.io.in2 := "b10000000000000000000000000000000".U ^ p1_pos_real_v0
	val FP_sub13 = Module(new FPAdd(32))
	tmp3_imag_v1 := FP_sub13.io.out
	FP_sub13.io.in1 := p0_pos_imag_v0
	FP_sub13.io.in2 := "b10000000000000000000000000000000".U ^ p1_pos_imag_v0
	val FP_mul8 = Module(new FPMult(32))
	tmp00_v5 := FP_mul8.io.out
	FP_mul8.io.in1 := tmp3_real_v1
	FP_mul8.io.in2 := tmp3_real_v1

	val FP_mul9 = Module(new FPMult(32))
	tmp01_v5 := FP_mul9.io.out
	FP_mul9.io.in1 := tmp3_imag_v1
	FP_mul9.io.in2 := tmp3_imag_v1

	val FP_add2 = Module(new FPAdd(32))
	tmp02_v1 := FP_add2.io.out
	FP_add2.io.in1 := tmp00_v5
	FP_add2.io.in2 := tmp01_v5

	val FP_add3 = Module(new FPAdd(32))
	denom_v1 := FP_add3.io.out
	FP_add3.io.in1 := tmp02_v1
	FP_add3.io.in2 := "b00011110011000101010110001110000".U

	val FP_mul10 = Module(new FPMult(32))
	tmp00_v6 := FP_mul10.io.out
	FP_mul10.io.in1 := tmp2_real_v1
	FP_mul10.io.in2 := tmp3_real_v1

	val FP_mul11 = Module(new FPMult(32))
	tmp01_v6 := FP_mul11.io.out
	FP_mul11.io.in1 := tmp2_imag_v1
	FP_mul11.io.in2 := tmp3_imag_v1

	val FP_add4 = Module(new FPAdd(32))
	tmp02_v2 := FP_add4.io.out
	FP_add4.io.in1 := tmp00_v6
	FP_add4.io.in2 := tmp01_v6

	val FP_div0 = Module(new FPDiv(32))
	p01_real_v1 := FP_div0.io.out
	FP_div0.io.in1 := tmp02_v2
	FP_div0.io.in2 := denom_v1

	val FP_mul12 = Module(new FPMult(32))
	tmp00_v7 := FP_mul12.io.out
	FP_mul12.io.in1 := tmp2_imag_v1
	FP_mul12.io.in2 := tmp3_real_v1

	val FP_mul13 = Module(new FPMult(32))
	tmp01_v7 := FP_mul13.io.out
	FP_mul13.io.in1 := tmp2_real_v1
	FP_mul13.io.in2 := tmp3_imag_v1

	val FP_sub14 = Module(new FPAdd(32))
	tmp02_v3 := FP_sub14.io.out
	FP_sub14.io.in1 := tmp00_v7
	FP_sub14.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v7
	val FP_div1 = Module(new FPDiv(32))
	p01_imag_v1 := FP_div1.io.out
	FP_div1.io.in1 := tmp02_v3
	FP_div1.io.in2 := denom_v1

	val FP_mul14 = Module(new FPMult(32))
	tmp00_v8 := FP_mul14.io.out
	FP_mul14.io.in1 := p1_val_real_v0
	FP_mul14.io.in2 := d2_real_v1

	val FP_mul15 = Module(new FPMult(32))
	tmp01_v8 := FP_mul15.io.out
	FP_mul15.io.in1 := p1_val_imag_v0
	FP_mul15.io.in2 := d2_imag_v1

	val FP_sub15 = Module(new FPAdd(32))
	tmp0_real_v2 := FP_sub15.io.out
	FP_sub15.io.in1 := tmp00_v8
	FP_sub15.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v8
	val FP_mul16 = Module(new FPMult(32))
	tmp00_v9 := FP_mul16.io.out
	FP_mul16.io.in1 := p1_val_real_v0
	FP_mul16.io.in2 := d2_imag_v1

	val FP_mul17 = Module(new FPMult(32))
	tmp01_v9 := FP_mul17.io.out
	FP_mul17.io.in1 := p1_val_imag_v0
	FP_mul17.io.in2 := d2_real_v1

	val FP_add5 = Module(new FPAdd(32))
	tmp0_imag_v2 := FP_add5.io.out
	FP_add5.io.in1 := tmp00_v9
	FP_add5.io.in2 := tmp01_v9

	val FP_mul18 = Module(new FPMult(32))
	tmp00_v10 := FP_mul18.io.out
	FP_mul18.io.in1 := p2_val_real_v0
	FP_mul18.io.in2 := d1_real_v1

	val FP_mul19 = Module(new FPMult(32))
	tmp01_v10 := FP_mul19.io.out
	FP_mul19.io.in1 := p2_val_imag_v0
	FP_mul19.io.in2 := d1_imag_v1

	val FP_sub16 = Module(new FPAdd(32))
	tmp1_real_v2 := FP_sub16.io.out
	FP_sub16.io.in1 := tmp00_v10
	FP_sub16.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v10
	val FP_mul20 = Module(new FPMult(32))
	tmp00_v11 := FP_mul20.io.out
	FP_mul20.io.in1 := p2_val_real_v0
	FP_mul20.io.in2 := d1_imag_v1

	val FP_mul21 = Module(new FPMult(32))
	tmp01_v11 := FP_mul21.io.out
	FP_mul21.io.in1 := p2_val_imag_v0
	FP_mul21.io.in2 := d1_real_v1

	val FP_add6 = Module(new FPAdd(32))
	tmp1_imag_v2 := FP_add6.io.out
	FP_add6.io.in1 := tmp00_v11
	FP_add6.io.in2 := tmp01_v11

	val FP_sub17 = Module(new FPAdd(32))
	tmp2_real_v2 := FP_sub17.io.out
	FP_sub17.io.in1 := tmp0_real_v2
	FP_sub17.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_real_v2
	val FP_sub18 = Module(new FPAdd(32))
	tmp2_imag_v2 := FP_sub18.io.out
	FP_sub18.io.in1 := tmp0_imag_v2
	FP_sub18.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_imag_v2
	val FP_sub19 = Module(new FPAdd(32))
	tmp3_real_v2 := FP_sub19.io.out
	FP_sub19.io.in1 := p1_pos_real_v0
	FP_sub19.io.in2 := "b10000000000000000000000000000000".U ^ p2_pos_real_v0
	val FP_sub20 = Module(new FPAdd(32))
	tmp3_imag_v2 := FP_sub20.io.out
	FP_sub20.io.in1 := p1_pos_imag_v0
	FP_sub20.io.in2 := "b10000000000000000000000000000000".U ^ p2_pos_imag_v0
	val FP_mul22 = Module(new FPMult(32))
	tmp00_v12 := FP_mul22.io.out
	FP_mul22.io.in1 := tmp3_real_v2
	FP_mul22.io.in2 := tmp3_real_v2

	val FP_mul23 = Module(new FPMult(32))
	tmp01_v12 := FP_mul23.io.out
	FP_mul23.io.in1 := tmp3_imag_v2
	FP_mul23.io.in2 := tmp3_imag_v2

	val FP_add7 = Module(new FPAdd(32))
	tmp02_v4 := FP_add7.io.out
	FP_add7.io.in1 := tmp00_v12
	FP_add7.io.in2 := tmp01_v12

	val FP_add8 = Module(new FPAdd(32))
	denom_v2 := FP_add8.io.out
	FP_add8.io.in1 := tmp02_v4
	FP_add8.io.in2 := "b00011110011000101010110001110000".U

	val FP_mul24 = Module(new FPMult(32))
	tmp00_v13 := FP_mul24.io.out
	FP_mul24.io.in1 := tmp2_real_v2
	FP_mul24.io.in2 := tmp3_real_v2

	val FP_mul25 = Module(new FPMult(32))
	tmp01_v13 := FP_mul25.io.out
	FP_mul25.io.in1 := tmp2_imag_v2
	FP_mul25.io.in2 := tmp3_imag_v2

	val FP_add9 = Module(new FPAdd(32))
	tmp02_v5 := FP_add9.io.out
	FP_add9.io.in1 := tmp00_v13
	FP_add9.io.in2 := tmp01_v13

	val FP_div2 = Module(new FPDiv(32))
	p12_real_v1 := FP_div2.io.out
	FP_div2.io.in1 := tmp02_v5
	FP_div2.io.in2 := denom_v2

	val FP_mul26 = Module(new FPMult(32))
	tmp00_v14 := FP_mul26.io.out
	FP_mul26.io.in1 := tmp2_imag_v2
	FP_mul26.io.in2 := tmp3_real_v2

	val FP_mul27 = Module(new FPMult(32))
	tmp01_v14 := FP_mul27.io.out
	FP_mul27.io.in1 := tmp2_real_v2
	FP_mul27.io.in2 := tmp3_imag_v2

	val FP_sub21 = Module(new FPAdd(32))
	tmp02_v6 := FP_sub21.io.out
	FP_sub21.io.in1 := tmp00_v14
	FP_sub21.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v14
	val FP_div3 = Module(new FPDiv(32))
	p12_imag_v1 := FP_div3.io.out
	FP_div3.io.in1 := tmp02_v6
	FP_div3.io.in2 := denom_v2

	val FP_mul28 = Module(new FPMult(32))
	tmp00_v15 := FP_mul28.io.out
	FP_mul28.io.in1 := p2_val_real_v0
	FP_mul28.io.in2 := d3_real_v1

	val FP_mul29 = Module(new FPMult(32))
	tmp01_v15 := FP_mul29.io.out
	FP_mul29.io.in1 := p2_val_imag_v0
	FP_mul29.io.in2 := d3_imag_v1

	val FP_sub22 = Module(new FPAdd(32))
	tmp0_real_v3 := FP_sub22.io.out
	FP_sub22.io.in1 := tmp00_v15
	FP_sub22.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v15
	val FP_mul30 = Module(new FPMult(32))
	tmp00_v16 := FP_mul30.io.out
	FP_mul30.io.in1 := p2_val_real_v0
	FP_mul30.io.in2 := d3_imag_v1

	val FP_mul31 = Module(new FPMult(32))
	tmp01_v16 := FP_mul31.io.out
	FP_mul31.io.in1 := p2_val_imag_v0
	FP_mul31.io.in2 := d3_real_v1

	val FP_add10 = Module(new FPAdd(32))
	tmp0_imag_v3 := FP_add10.io.out
	FP_add10.io.in1 := tmp00_v16
	FP_add10.io.in2 := tmp01_v16

	val FP_mul32 = Module(new FPMult(32))
	tmp00_v17 := FP_mul32.io.out
	FP_mul32.io.in1 := p3_val_real_v0
	FP_mul32.io.in2 := d2_real_v1

	val FP_mul33 = Module(new FPMult(32))
	tmp01_v17 := FP_mul33.io.out
	FP_mul33.io.in1 := p3_val_imag_v0
	FP_mul33.io.in2 := d2_imag_v1

	val FP_sub23 = Module(new FPAdd(32))
	tmp1_real_v3 := FP_sub23.io.out
	FP_sub23.io.in1 := tmp00_v17
	FP_sub23.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v17
	val FP_mul34 = Module(new FPMult(32))
	tmp00_v18 := FP_mul34.io.out
	FP_mul34.io.in1 := p3_val_real_v0
	FP_mul34.io.in2 := d2_imag_v1

	val FP_mul35 = Module(new FPMult(32))
	tmp01_v18 := FP_mul35.io.out
	FP_mul35.io.in1 := p3_val_imag_v0
	FP_mul35.io.in2 := d2_real_v1

	val FP_add11 = Module(new FPAdd(32))
	tmp1_imag_v3 := FP_add11.io.out
	FP_add11.io.in1 := tmp00_v18
	FP_add11.io.in2 := tmp01_v18

	val FP_sub24 = Module(new FPAdd(32))
	tmp2_real_v3 := FP_sub24.io.out
	FP_sub24.io.in1 := tmp0_real_v3
	FP_sub24.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_real_v3
	val FP_sub25 = Module(new FPAdd(32))
	tmp2_imag_v3 := FP_sub25.io.out
	FP_sub25.io.in1 := tmp0_imag_v3
	FP_sub25.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_imag_v3
	val FP_sub26 = Module(new FPAdd(32))
	tmp3_real_v3 := FP_sub26.io.out
	FP_sub26.io.in1 := p2_pos_real_v0
	FP_sub26.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_real_v0
	val FP_sub27 = Module(new FPAdd(32))
	tmp3_imag_v3 := FP_sub27.io.out
	FP_sub27.io.in1 := p2_pos_imag_v0
	FP_sub27.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_imag_v0
	val FP_mul36 = Module(new FPMult(32))
	tmp00_v19 := FP_mul36.io.out
	FP_mul36.io.in1 := tmp3_real_v3
	FP_mul36.io.in2 := tmp3_real_v3

	val FP_mul37 = Module(new FPMult(32))
	tmp01_v19 := FP_mul37.io.out
	FP_mul37.io.in1 := tmp3_imag_v3
	FP_mul37.io.in2 := tmp3_imag_v3

	val FP_add12 = Module(new FPAdd(32))
	tmp02_v7 := FP_add12.io.out
	FP_add12.io.in1 := tmp00_v19
	FP_add12.io.in2 := tmp01_v19

	val FP_add13 = Module(new FPAdd(32))
	denom_v3 := FP_add13.io.out
	FP_add13.io.in1 := tmp02_v7
	FP_add13.io.in2 := "b00011110011000101010110001110000".U

	val FP_mul38 = Module(new FPMult(32))
	tmp00_v20 := FP_mul38.io.out
	FP_mul38.io.in1 := tmp2_real_v3
	FP_mul38.io.in2 := tmp3_real_v3

	val FP_mul39 = Module(new FPMult(32))
	tmp01_v20 := FP_mul39.io.out
	FP_mul39.io.in1 := tmp2_imag_v3
	FP_mul39.io.in2 := tmp3_imag_v3

	val FP_add14 = Module(new FPAdd(32))
	tmp02_v8 := FP_add14.io.out
	FP_add14.io.in1 := tmp00_v20
	FP_add14.io.in2 := tmp01_v20

	val FP_div4 = Module(new FPDiv(32))
	p23_real_v1 := FP_div4.io.out
	FP_div4.io.in1 := tmp02_v8
	FP_div4.io.in2 := denom_v3

	val FP_mul40 = Module(new FPMult(32))
	tmp00_v21 := FP_mul40.io.out
	FP_mul40.io.in1 := tmp2_imag_v3
	FP_mul40.io.in2 := tmp3_real_v3

	val FP_mul41 = Module(new FPMult(32))
	tmp01_v21 := FP_mul41.io.out
	FP_mul41.io.in1 := tmp2_real_v3
	FP_mul41.io.in2 := tmp3_imag_v3

	val FP_sub28 = Module(new FPAdd(32))
	tmp02_v9 := FP_sub28.io.out
	FP_sub28.io.in1 := tmp00_v21
	FP_sub28.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v21
	val FP_div5 = Module(new FPDiv(32))
	p23_imag_v1 := FP_div5.io.out
	FP_div5.io.in1 := tmp02_v9
	FP_div5.io.in2 := denom_v3

	val FP_mul42 = Module(new FPMult(32))
	tmp00_v22 := FP_mul42.io.out
	FP_mul42.io.in1 := p01_real_v1
	FP_mul42.io.in2 := d2_real_v1

	val FP_mul43 = Module(new FPMult(32))
	tmp01_v22 := FP_mul43.io.out
	FP_mul43.io.in1 := p01_imag_v1
	FP_mul43.io.in2 := d2_imag_v1

	val FP_sub29 = Module(new FPAdd(32))
	tmp0_real_v4 := FP_sub29.io.out
	FP_sub29.io.in1 := tmp00_v22
	FP_sub29.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v22
	val FP_mul44 = Module(new FPMult(32))
	tmp00_v23 := FP_mul44.io.out
	FP_mul44.io.in1 := p01_real_v1
	FP_mul44.io.in2 := d2_imag_v1

	val FP_mul45 = Module(new FPMult(32))
	tmp01_v23 := FP_mul45.io.out
	FP_mul45.io.in1 := p01_imag_v1
	FP_mul45.io.in2 := d2_real_v1

	val FP_add15 = Module(new FPAdd(32))
	tmp0_imag_v4 := FP_add15.io.out
	FP_add15.io.in1 := tmp00_v23
	FP_add15.io.in2 := tmp01_v23

	val FP_mul46 = Module(new FPMult(32))
	tmp00_v24 := FP_mul46.io.out
	FP_mul46.io.in1 := p12_real_v1
	FP_mul46.io.in2 := d0_real_v1

	val FP_mul47 = Module(new FPMult(32))
	tmp01_v24 := FP_mul47.io.out
	FP_mul47.io.in1 := p12_imag_v1
	FP_mul47.io.in2 := d0_imag_v1

	val FP_sub30 = Module(new FPAdd(32))
	tmp1_real_v4 := FP_sub30.io.out
	FP_sub30.io.in1 := tmp00_v24
	FP_sub30.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v24
	val FP_mul48 = Module(new FPMult(32))
	tmp00_v25 := FP_mul48.io.out
	FP_mul48.io.in1 := p12_real_v1
	FP_mul48.io.in2 := d0_imag_v1

	val FP_mul49 = Module(new FPMult(32))
	tmp01_v25 := FP_mul49.io.out
	FP_mul49.io.in1 := p12_imag_v1
	FP_mul49.io.in2 := d0_real_v1

	val FP_add16 = Module(new FPAdd(32))
	tmp1_imag_v4 := FP_add16.io.out
	FP_add16.io.in1 := tmp00_v25
	FP_add16.io.in2 := tmp01_v25

	val FP_sub31 = Module(new FPAdd(32))
	tmp2_real_v4 := FP_sub31.io.out
	FP_sub31.io.in1 := tmp0_real_v4
	FP_sub31.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_real_v4
	val FP_sub32 = Module(new FPAdd(32))
	tmp2_imag_v4 := FP_sub32.io.out
	FP_sub32.io.in1 := tmp0_imag_v4
	FP_sub32.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_imag_v4
	val FP_sub33 = Module(new FPAdd(32))
	tmp3_real_v4 := FP_sub33.io.out
	FP_sub33.io.in1 := p0_pos_real_v0
	FP_sub33.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_real_v0
	val FP_sub34 = Module(new FPAdd(32))
	tmp3_imag_v4 := FP_sub34.io.out
	FP_sub34.io.in1 := p0_pos_imag_v0
	FP_sub34.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_imag_v0
	val FP_mul50 = Module(new FPMult(32))
	tmp00_v26 := FP_mul50.io.out
	FP_mul50.io.in1 := tmp3_real_v4
	FP_mul50.io.in2 := tmp3_real_v4

	val FP_mul51 = Module(new FPMult(32))
	tmp01_v26 := FP_mul51.io.out
	FP_mul51.io.in1 := tmp3_imag_v4
	FP_mul51.io.in2 := tmp3_imag_v4

	val FP_add17 = Module(new FPAdd(32))
	tmp02_v10 := FP_add17.io.out
	FP_add17.io.in1 := tmp00_v26
	FP_add17.io.in2 := tmp01_v26

	val FP_add18 = Module(new FPAdd(32))
	denom_v4 := FP_add18.io.out
	FP_add18.io.in1 := tmp02_v10
	FP_add18.io.in2 := "b00011110011000101010110001110000".U

	val FP_mul52 = Module(new FPMult(32))
	tmp00_v27 := FP_mul52.io.out
	FP_mul52.io.in1 := tmp2_real_v4
	FP_mul52.io.in2 := tmp3_real_v4

	val FP_mul53 = Module(new FPMult(32))
	tmp01_v27 := FP_mul53.io.out
	FP_mul53.io.in1 := tmp2_imag_v4
	FP_mul53.io.in2 := tmp3_imag_v4

	val FP_add19 = Module(new FPAdd(32))
	tmp02_v11 := FP_add19.io.out
	FP_add19.io.in1 := tmp00_v27
	FP_add19.io.in2 := tmp01_v27

	val FP_div6 = Module(new FPDiv(32))
	p02_real_v1 := FP_div6.io.out
	FP_div6.io.in1 := tmp02_v11
	FP_div6.io.in2 := denom_v4

	val FP_mul54 = Module(new FPMult(32))
	tmp00_v28 := FP_mul54.io.out
	FP_mul54.io.in1 := tmp2_imag_v4
	FP_mul54.io.in2 := tmp3_real_v4

	val FP_mul55 = Module(new FPMult(32))
	tmp01_v28 := FP_mul55.io.out
	FP_mul55.io.in1 := tmp2_real_v4
	FP_mul55.io.in2 := tmp3_imag_v4

	val FP_sub35 = Module(new FPAdd(32))
	tmp02_v12 := FP_sub35.io.out
	FP_sub35.io.in1 := tmp00_v28
	FP_sub35.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v28
	val FP_div7 = Module(new FPDiv(32))
	p02_imag_v1 := FP_div7.io.out
	FP_div7.io.in1 := tmp02_v12
	FP_div7.io.in2 := denom_v4

	val FP_mul56 = Module(new FPMult(32))
	tmp00_v29 := FP_mul56.io.out
	FP_mul56.io.in1 := p12_real_v1
	FP_mul56.io.in2 := d3_real_v1

	val FP_mul57 = Module(new FPMult(32))
	tmp01_v29 := FP_mul57.io.out
	FP_mul57.io.in1 := p12_imag_v1
	FP_mul57.io.in2 := d3_imag_v1

	val FP_sub36 = Module(new FPAdd(32))
	tmp0_real_v5 := FP_sub36.io.out
	FP_sub36.io.in1 := tmp00_v29
	FP_sub36.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v29
	val FP_mul58 = Module(new FPMult(32))
	tmp00_v30 := FP_mul58.io.out
	FP_mul58.io.in1 := p12_real_v1
	FP_mul58.io.in2 := d3_imag_v1

	val FP_mul59 = Module(new FPMult(32))
	tmp01_v30 := FP_mul59.io.out
	FP_mul59.io.in1 := p12_imag_v1
	FP_mul59.io.in2 := d3_real_v1

	val FP_add20 = Module(new FPAdd(32))
	tmp0_imag_v5 := FP_add20.io.out
	FP_add20.io.in1 := tmp00_v30
	FP_add20.io.in2 := tmp01_v30

	val FP_mul60 = Module(new FPMult(32))
	tmp00_v31 := FP_mul60.io.out
	FP_mul60.io.in1 := p23_real_v1
	FP_mul60.io.in2 := d1_real_v1

	val FP_mul61 = Module(new FPMult(32))
	tmp01_v31 := FP_mul61.io.out
	FP_mul61.io.in1 := p23_imag_v1
	FP_mul61.io.in2 := d1_imag_v1

	val FP_sub37 = Module(new FPAdd(32))
	tmp1_real_v5 := FP_sub37.io.out
	FP_sub37.io.in1 := tmp00_v31
	FP_sub37.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v31
	val FP_mul62 = Module(new FPMult(32))
	tmp00_v32 := FP_mul62.io.out
	FP_mul62.io.in1 := p23_real_v1
	FP_mul62.io.in2 := d1_imag_v1

	val FP_mul63 = Module(new FPMult(32))
	tmp01_v32 := FP_mul63.io.out
	FP_mul63.io.in1 := p23_imag_v1
	FP_mul63.io.in2 := d1_real_v1

	val FP_add21 = Module(new FPAdd(32))
	tmp1_imag_v5 := FP_add21.io.out
	FP_add21.io.in1 := tmp00_v32
	FP_add21.io.in2 := tmp01_v32

	val FP_sub38 = Module(new FPAdd(32))
	tmp2_real_v5 := FP_sub38.io.out
	FP_sub38.io.in1 := tmp0_real_v5
	FP_sub38.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_real_v5
	val FP_sub39 = Module(new FPAdd(32))
	tmp2_imag_v5 := FP_sub39.io.out
	FP_sub39.io.in1 := tmp0_imag_v5
	FP_sub39.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_imag_v5
	val FP_sub40 = Module(new FPAdd(32))
	tmp3_real_v5 := FP_sub40.io.out
	FP_sub40.io.in1 := p1_pos_real_v0
	FP_sub40.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_real_v0
	val FP_sub41 = Module(new FPAdd(32))
	tmp3_imag_v5 := FP_sub41.io.out
	FP_sub41.io.in1 := p1_pos_imag_v0
	FP_sub41.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_imag_v0
	val FP_mul64 = Module(new FPMult(32))
	tmp00_v33 := FP_mul64.io.out
	FP_mul64.io.in1 := tmp3_real_v5
	FP_mul64.io.in2 := tmp3_real_v5

	val FP_mul65 = Module(new FPMult(32))
	tmp01_v33 := FP_mul65.io.out
	FP_mul65.io.in1 := tmp3_imag_v5
	FP_mul65.io.in2 := tmp3_imag_v5

	val FP_add22 = Module(new FPAdd(32))
	tmp02_v13 := FP_add22.io.out
	FP_add22.io.in1 := tmp00_v33
	FP_add22.io.in2 := tmp01_v33

	val FP_add23 = Module(new FPAdd(32))
	denom_v5 := FP_add23.io.out
	FP_add23.io.in1 := tmp02_v13
	FP_add23.io.in2 := "b00011110011000101010110001110000".U

	val FP_mul66 = Module(new FPMult(32))
	tmp00_v34 := FP_mul66.io.out
	FP_mul66.io.in1 := tmp2_real_v5
	FP_mul66.io.in2 := tmp3_real_v5

	val FP_mul67 = Module(new FPMult(32))
	tmp01_v34 := FP_mul67.io.out
	FP_mul67.io.in1 := tmp2_imag_v5
	FP_mul67.io.in2 := tmp3_imag_v5

	val FP_add24 = Module(new FPAdd(32))
	tmp02_v14 := FP_add24.io.out
	FP_add24.io.in1 := tmp00_v34
	FP_add24.io.in2 := tmp01_v34

	val FP_div8 = Module(new FPDiv(32))
	p13_real_v1 := FP_div8.io.out
	FP_div8.io.in1 := tmp02_v14
	FP_div8.io.in2 := denom_v5

	val FP_mul68 = Module(new FPMult(32))
	tmp00_v35 := FP_mul68.io.out
	FP_mul68.io.in1 := tmp2_imag_v5
	FP_mul68.io.in2 := tmp3_real_v5

	val FP_mul69 = Module(new FPMult(32))
	tmp01_v35 := FP_mul69.io.out
	FP_mul69.io.in1 := tmp2_real_v5
	FP_mul69.io.in2 := tmp3_imag_v5

	val FP_sub42 = Module(new FPAdd(32))
	tmp02_v15 := FP_sub42.io.out
	FP_sub42.io.in1 := tmp00_v35
	FP_sub42.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v35
	val FP_div9 = Module(new FPDiv(32))
	p13_imag_v1 := FP_div9.io.out
	FP_div9.io.in1 := tmp02_v15
	FP_div9.io.in2 := denom_v5

	val FP_mul70 = Module(new FPMult(32))
	tmp00_v36 := FP_mul70.io.out
	FP_mul70.io.in1 := p02_real_v1
	FP_mul70.io.in2 := d3_real_v1

	val FP_mul71 = Module(new FPMult(32))
	tmp01_v36 := FP_mul71.io.out
	FP_mul71.io.in1 := p02_imag_v1
	FP_mul71.io.in2 := d3_imag_v1

	val FP_sub43 = Module(new FPAdd(32))
	tmp0_real_v6 := FP_sub43.io.out
	FP_sub43.io.in1 := tmp00_v36
	FP_sub43.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v36
	val FP_mul72 = Module(new FPMult(32))
	tmp00_v37 := FP_mul72.io.out
	FP_mul72.io.in1 := p02_real_v1
	FP_mul72.io.in2 := d3_imag_v1

	val FP_mul73 = Module(new FPMult(32))
	tmp01_v37 := FP_mul73.io.out
	FP_mul73.io.in1 := p02_imag_v1
	FP_mul73.io.in2 := d3_real_v1

	val FP_add25 = Module(new FPAdd(32))
	tmp0_imag_v6 := FP_add25.io.out
	FP_add25.io.in1 := tmp00_v37
	FP_add25.io.in2 := tmp01_v37

	val FP_mul74 = Module(new FPMult(32))
	tmp00_v38 := FP_mul74.io.out
	FP_mul74.io.in1 := p13_real_v1
	FP_mul74.io.in2 := d0_real_v1

	val FP_mul75 = Module(new FPMult(32))
	tmp01_v38 := FP_mul75.io.out
	FP_mul75.io.in1 := p13_imag_v1
	FP_mul75.io.in2 := d0_imag_v1

	val FP_sub44 = Module(new FPAdd(32))
	tmp1_real_v6 := FP_sub44.io.out
	FP_sub44.io.in1 := tmp00_v38
	FP_sub44.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v38
	val FP_mul76 = Module(new FPMult(32))
	tmp00_v39 := FP_mul76.io.out
	FP_mul76.io.in1 := p13_real_v1
	FP_mul76.io.in2 := d0_imag_v1

	val FP_mul77 = Module(new FPMult(32))
	tmp01_v39 := FP_mul77.io.out
	FP_mul77.io.in1 := p13_imag_v1
	FP_mul77.io.in2 := d0_real_v1

	val FP_add26 = Module(new FPAdd(32))
	tmp1_imag_v6 := FP_add26.io.out
	FP_add26.io.in1 := tmp00_v39
	FP_add26.io.in2 := tmp01_v39

	val FP_sub45 = Module(new FPAdd(32))
	tmp2_real_v6 := FP_sub45.io.out
	FP_sub45.io.in1 := tmp0_real_v6
	FP_sub45.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_real_v6
	val FP_sub46 = Module(new FPAdd(32))
	tmp2_imag_v6 := FP_sub46.io.out
	FP_sub46.io.in1 := tmp0_imag_v6
	FP_sub46.io.in2 := "b10000000000000000000000000000000".U ^ tmp1_imag_v6
	val FP_sub47 = Module(new FPAdd(32))
	tmp3_real_v6 := FP_sub47.io.out
	FP_sub47.io.in1 := p0_pos_real_v0
	FP_sub47.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_real_v0
	val FP_sub48 = Module(new FPAdd(32))
	tmp3_imag_v6 := FP_sub48.io.out
	FP_sub48.io.in1 := p0_pos_imag_v0
	FP_sub48.io.in2 := "b10000000000000000000000000000000".U ^ p3_pos_imag_v0
	val FP_mul78 = Module(new FPMult(32))
	tmp00_v40 := FP_mul78.io.out
	FP_mul78.io.in1 := tmp3_real_v6
	FP_mul78.io.in2 := tmp3_real_v6

	val FP_mul79 = Module(new FPMult(32))
	tmp01_v40 := FP_mul79.io.out
	FP_mul79.io.in1 := tmp3_imag_v6
	FP_mul79.io.in2 := tmp3_imag_v6

	val FP_add27 = Module(new FPAdd(32))
	tmp02_v16 := FP_add27.io.out
	FP_add27.io.in1 := tmp00_v40
	FP_add27.io.in2 := tmp01_v40

	val FP_add28 = Module(new FPAdd(32))
	denom_v6 := FP_add28.io.out
	FP_add28.io.in1 := tmp02_v16
	FP_add28.io.in2 := "b00011110011000101010110001110000".U

	val FP_mul80 = Module(new FPMult(32))
	tmp00_v41 := FP_mul80.io.out
	FP_mul80.io.in1 := tmp2_real_v6
	FP_mul80.io.in2 := tmp3_real_v6

	val FP_mul81 = Module(new FPMult(32))
	tmp01_v41 := FP_mul81.io.out
	FP_mul81.io.in1 := tmp2_imag_v6
	FP_mul81.io.in2 := tmp3_imag_v6

	val FP_add29 = Module(new FPAdd(32))
	tmp02_v17 := FP_add29.io.out
	FP_add29.io.in1 := tmp00_v41
	FP_add29.io.in2 := tmp01_v41

	val FP_div10 = Module(new FPDiv(32))
	p03_real_v1 := FP_div10.io.out
	FP_div10.io.in1 := tmp02_v17
	FP_div10.io.in2 := denom_v6

	val FP_mul82 = Module(new FPMult(32))
	tmp00_v42 := FP_mul82.io.out
	FP_mul82.io.in1 := tmp2_imag_v6
	FP_mul82.io.in2 := tmp3_real_v6

	val FP_mul83 = Module(new FPMult(32))
	tmp01_v42 := FP_mul83.io.out
	FP_mul83.io.in1 := tmp2_real_v6
	FP_mul83.io.in2 := tmp3_imag_v6

	val FP_sub49 = Module(new FPAdd(32))
	tmp02_v18 := FP_sub49.io.out
	FP_sub49.io.in1 := tmp00_v42
	FP_sub49.io.in2 := "b10000000000000000000000000000000".U ^ tmp01_v42
	val FP_div11 = Module(new FPDiv(32))
	p03_imag_v1 := FP_div11.io.out
	FP_div11.io.in1 := tmp02_v18
	FP_div11.io.in2 := denom_v6


	//Write the outputs
	io.p03_real_out := p03_real_v1
	io.p03_imag_out := p03_imag_v1
}
