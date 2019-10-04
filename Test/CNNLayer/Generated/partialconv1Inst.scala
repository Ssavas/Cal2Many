package partialconv1Inst

import FPDivisionPipelined._ 
import chisel3._
import chisel3.util._ 

class applyFilter() extends Module {
	val io = IO(new Bundle{
		val conv1Inst_filterCounter_in = Input(UInt(width = 32.W))
		val conv1Inst_patch_in = Input(UInt(width = 32.W))
		val conv1Inst_applyResult_out = Output(UInt(width = 32.W))
		val en = Input(Bool())
		val valid = Output(Bool())
	})

	//Define all versions of the variables
	val conv1Inst_applyResult_v1 = Wire(UInt(width = 32.W))

	//Define the constants
	def filterRowSize : Int = 7
	def filterColSize : Int = 7
	def rowPadding : Int = 6
	def colPadding : Int = 6
	def inputRowSize : Int = 230
	def inputColSize : Int = 230
	def stride : Int = 2
	def numberOfFilters : Int = 64
	def numberOfInputChannels : Int = 3

	//Define the arrays as memory
	val filters = Vec(numberOfFilters, Vec(filterRowSize, Vec(filterColSize, UInt(32.W))))
	//Read the inputs
	val conv1Inst_filterCounter_v0 = io.conv1Inst_filterCounter_in
	val conv1Inst_patch_v0 = io.conv1Inst_patch_in

	
	val conv70 = Module(new convolution7())
	conv70.io.filterIndex := conv1Inst_filterCounter_v0
	conv70.io.patchData := conv1Inst_patch_v0
	conv70.io.readInput := io.readInput
	conv70.io.en := io.en

	val conv7_ret_v0 = conv70.io.out
	conv1Inst_applyResult_v1 := conv7_ret_v0	// conv1Inst_applyResult_v1 total delay: 17

	//Write the outputs
	// conv1Inst_applyResult_v1 total delay : 17
	io.conv1Inst_applyResult_out := conv1Inst_applyResult_v1
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
