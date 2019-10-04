package partialconvG

import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class applyFilter() extends Module {
	val io = IO(new Bundle{
		val convG_filterCounter_in = Input(UInt(width = 32.W))
		val convG_inputImage_in = Input(UInt(width = 32.W))
		val readInput = Input(Bool())
		val convG_applyResult_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val convG_applyResult_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def filterRowSize : Int = 7
	def filterColSize : Int = 7
	def numberOfFilters : Int = 64
	def stride : Int = 2
	def inputColSize : Int = 230
	def inputRowSize : Int = 230

	//Read the inputs
	val convG_filterCounter_v0 = io.convG_filterCounter_in
	val convG_inputImage_v0 = io.convG_inputImage_in

	
	val conv70 = Module(new convolution7())
	conv70.io.filterIndex := convG_filterCounter_v0
	conv70.io.patchData := convG_inputImage_v0
	conv70.io.readInput := io.readInput
	conv70.io.en := io.en

	val conv7_ret_v0 = conv70.io.out
	convG_applyResult_v1 := conv7_ret_v0	// convG_applyResult_v1 total delay: 17
	

	//Write the outputs
	// convG_applyResult_v1 total delay : 17
	io.convG_applyResult_out := convG_applyResult_v1
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
	io.valid := validReg16
}
