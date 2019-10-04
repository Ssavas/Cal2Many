package partialconvG

import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class applyFilter() extends Module {
	val io = IO(new Bundle{
		val convG_filterCounter_in = Input(UInt(width = 32.W))
		val convG_inputColCounter_in = Input(UInt(width = 32.W))
		val convG_inputRowCounter_in = Input(UInt(width = 32.W))
		val convG_inputImage_in = Input(UInt(width = 32.W))
		val readInput = Input(Bool())
		val convG_result_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val convG_result_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def filterRowSize : Int = 7
	def filterColSize : Int = 7
	def numberOfFilters : Int = 64
	def stride : Int = 2
	def inputColSize : Int = 230
	def inputRowSize : Int = 230

	//Read the inputs
	val convG_filterCounter_v0 = io.convG_filterCounter_in
	val convG_inputColCounter_v0 = io.convG_inputColCounter_in
	val convG_inputRowCounter_v0 = io.convG_inputRowCounter_in
	val convG_inputImage_v0 = io.convG_inputImage_in

	
	val conv70 = Module(new convolution7())
	conv70.io.filterIndex := convG_filterCounter_v0
	conv70.io.patchData := convG_inputImage_v0
	conv70.io.readInput := io.readInput
	conv70.io.en := io.en

	val conv7_ret_v0 = conv70.io.out
	convG_result_v1 := conv7_ret	// convG_result_v1 total delay: 0
	

	//Write the outputs
	// convG_result_v1 total delay : 0
	io.convG_result_out := convG_result_v1
	io.valid := io.en
}
