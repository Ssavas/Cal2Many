package partialconvB

import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class applyFilter() extends Module {
	val io = IO(new Bundle{
		val convB_filterCounter_in = Input(UInt(width = 32.W))
		val convB_inputColCounter_in = Input(UInt(width = 32.W))
		val convB_inputRowCounter_in = Input(UInt(width = 32.W))
		val convB_inputImage_in = Input(UInt(width = 32.W))
		val readInput = Input(Bool())
		val convB_result_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val convB_result_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def filterRowSize : Int = 7
	def filterColSize : Int = 7
	def numberOfFilters : Int = 64
	def stride : Int = 2
	def inputColSize : Int = 230
	def inputRowSize : Int = 230

	//Read the inputs
	val convB_filterCounter_v0 = io.convB_filterCounter_in
	val convB_inputColCounter_v0 = io.convB_inputColCounter_in
	val convB_inputRowCounter_v0 = io.convB_inputRowCounter_in
	val convB_inputImage_v0 = io.convB_inputImage_in

	
	val conv70 = Module(new convolution7())
	conv70.io.filterIndex := convB_filterCounter_v0
	conv70.io.patchData := convB_inputImage_v0
	conv70.io.readInput := io.readInput
	conv70.io.en := io.en

	val conv7_ret_v0 = conv70.io.out
	convB_result_v1 := conv7_ret	// convB_result_v1 total delay: 0
	

	//Write the outputs
	// convB_result_v1 total delay : 0
	io.convB_result_out := convB_result_v1
	io.valid := io.en
}
