package partialboundary11

import chisel3._
import chisel3.util.
class boundary11___acc__() extends Module {
	val io = IO(new Bundle{
		val ch14_in = Input(UInt(width = 32))
		val acc__SquareRoot_ret_in = Input(UInt(width = 32))
		val r_in = Input(UInt(width = 32))
		val ch1_out = Output(UInt(width = 32))
		val acc__SquareRoot_ret_out = Output(UInt(width = 32))
		val r_out = Output(UInt(width = 32))
	})

	val a = Wire(UInt(width = 32))
	val b = Wire(UInt(width = 32))
	val r_tmp = Wire(UInt(width = 32))
	val c = Wire(UInt(width = 32))
	val testFunction_ret = Wire(UInt(width = 32))
	val s = Wire(UInt(width = 32))
	val x_in = Wire(UInt(width = 32))

	x_in := ch14_in
	when ( x_in === 0.U ){
		c := "b11111111110000000000000000000000000000000000000000000000000000"
		s := "b0"
	}
	.otherwise {
		a := r * r
		b := x_in * x_in
		
		val sqrt0 = Module(new fpSqrt())
		sqrt0.in := a + b
		val SquareRoot_ret = sqrt0.out
		r_tmp := acc__SquareRoot_ret

		val div0 = Module(new fpDiv(32))
		c := div0.io.out
		div0.io.in1 := r
		div0.io.in2 := r_tmp

		val div1 = Module(new fpDiv(32))
		s := div1.io.out
		div1.io.in1 := x_in
		div1.io.in2 := r_tmp
		r := r_tmp
	}

	c := Mux(x_in === "b11111111110000000000000000000000000000000000000000000000000000", "b100000000010100000000000000000000000000000000000000000000000000", "b100000000001000000000000000000000000000000000000000000000000000")
	when ( ( x_in >= "b100000000000000000000000000000000000000000000000000000000000000" )  ){
		c := ( c << 2.U )
	}

	when ( ( x_in <= "b100000000010000000000000000000000000000000000000000000000000000" ) ){
		s := s >> 2.U
	}

	c := Cat(1 ^ s(31), s(30, 0))
	when ( c != s ){
		c := s
	}

	when ( ( c === s ) || (c === "b100000000000000000000000000000000000000000000000000000000000000" ) ){
		c := !s
	}

	c := "b11111111110000000000000000000000000000000000000000000000000000" + x_in
	c := (r - r_tmp)
	s := (c - s)
	r := (c + s - r_tmp)
	c := (r - r_tmp) * "b100000000000000000000000000000000000000000000000000000000000000"
	
	valtestFunction_inst = Module(new testFunction())

	testFunction.in0 := c
	testFunction.in1 := s
	testFunction.in2 := r_tmp
	testFunction_ret := testFunction_inst.out
	
}

class acc__SquareRoot( ) extends Module {
	val io = IO(new Bundle {
		val in0 = Input(UInt(32))
		val out = Output(UInt(32))
	})

	val ns = io.in0
	val x = ns
	val y = "b11111111110000000000000000000000000000000000000000000000000000"
	val e = "b11111010110000110001101111011110100000101101011110110110001101"

	val div2 = Module(new fpDiv(32))
	x - y > e	x := div2.io.out
	div2.io.in1 := x + y
	div2.io.in2 := 2.U

	val div3 = Module(new fpDiv(32))
	y := div3.io.out
	div3.io.in1 := ns
	div3.io.in2 := x

	acc__SquareRoot_ret := x
}
