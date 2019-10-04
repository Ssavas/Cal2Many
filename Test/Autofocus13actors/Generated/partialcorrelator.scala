package partialcorrelator

import fpDivision._ 
import chisel3._
import chisel3.util._ 

class correlation() extends Module {
	val io = IO(new Bundle{
		val correlator_total_sum_in = Input(UInt(width = 32.W))
		val correlator_correlation_input1_in = Input(UInt(width = 64.W))
		val correlator_correlation_input2_in = Input(UInt(width = 64.W))
		val correlator_total_sum_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val tmp5_v1 = Wire(UInt(width = 32.W))
	val tmp3_v1 = Wire(UInt(width = 32.W))
	val tmp4_v1 = Wire(UInt(width = 32.W))
	val tmp1_v1 = Wire(UInt(width = 32.W))
	val tmp2_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def NOF_PIXELS_KERNEL : Int = 36
	def NOF_PIXELS : Int = 216

	//Read the inputs
	val correlator_total_sum_v0 = io.correlator_total_sum_in
	val correlator_correlation_input1_v0 = io.correlator_correlation_input1_in
	val correlator_correlation_input2_v0 = io.correlator_correlation_input2_in

	
	val c_mag0 = Module(new C_mag())
	c_mag0.io.in := correlation_input1
	val C_mag_ret_v0 = c_mag0.io.out
	tmp1_v1 := C_mag_ret	// tmp1_v1 total delay: 0
	
	val c_mag1 = Module(new C_mag())
	c_mag1.io.in := correlation_input2
	val C_mag_ret_v1 = c_mag1.io.out
	tmp2_v1 := C_mag_ret	// tmp2_v1 total delay: 0

	val FP_mul0 = Module(new FPMult(32))
	tmp3_v1 := FP_mul0.io.out
	FP_mul0.io.in1 := tmp1_v1
	FP_mul0.io.in2 := tmp1_v1
	// tmp3_v1 total delay: 2

	val FP_mul1 = Module(new FPMult(32))
	tmp4_v1 := FP_mul1.io.out
	FP_mul1.io.in1 := tmp2_v1
	FP_mul1.io.in2 := tmp2_v1
	// tmp4_v1 total delay: 2

	val FP_mul2 = Module(new FPMult(32))
	tmp5_v1 := FP_mul2.io.out
	FP_mul2.io.in1 := tmp3_v1
	FP_mul2.io.in2 := tmp4_v1
	// tmp5_v1 total delay: 4

	val FP_add0 = Module(new FPAdd(32))
	total_sum := FP_add0.io.out
	val total_sum_vnull_Reg0 = RegNext(total_sum_vnull, 0.U)
	val total_sum_vnull_Reg1 = RegNext(total_sum_vnull_Reg0, 0.U)
	val total_sum_vnull_Reg2 = RegNext(total_sum_vnull_Reg1, 0.U)
	val total_sum_vnull_Reg3 = RegNext(total_sum_vnull_Reg2, 0.U)
	FP_add0.io.in1 := total_sum_vnull_Reg3
	FP_add0.io.in2 := tmp5_v1
	// total_sum_vnull total delay: 7

	//Write the outputs
	// correlator_total_sum_v0 total delay : 0
	io.correlator_total_sum_out := correlator_total_sum_v0
	io.valid := io.en
}
