package partialconvR

import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class applyFilter() extends Module {
	val io = IO(new Bundle{
		val convR_filterCounter_in = Input(UInt(width = 32.W))
		val convR_inputColCounter_in = Input(UInt(width = 32.W))
		val convR_inputRowCounter_in = Input(UInt(width = 32.W))
		val convR_inputImage_in = Input(UInt(width = 32.W))
		val readInput = Input(Bool())
		val convR_result_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val convR_result_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def filterRowSize : Int = 7
	def filterColSize : Int = 7
	def numberOfFilters : Int = 64
	def stride : Int = 2
	def inputColSize : Int = 230
	def inputRowSize : Int = 230

	//Read the inputs
	val convR_filterCounter_v0 = io.convR_filterCounter_in
	val convR_inputColCounter_v0 = io.convR_inputColCounter_in
	val convR_inputRowCounter_v0 = io.convR_inputRowCounter_in
	val convR_inputImage_v0 = io.convR_inputImage_in

	
	val conv70 = Module(new convolution7())
	conv70.io.filterIndex := convR_filterCounter_v0
	conv70.io.patchData := convR_inputImage_v0
	conv70.io.readInput := io.readInput
	conv70.io.en := io.en

	val conv7_ret_v0 = conv70.io.out
	convR_result_v1 := conv7_ret	// convR_result_v1 total delay: 0
	

	//Write the outputs
	// convR_result_v1 total delay : 0
	io.convR_result_out := convR_result_v1
	io.valid := io.en
}
