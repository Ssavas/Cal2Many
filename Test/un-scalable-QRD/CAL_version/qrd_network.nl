

network qrd () ==> :

entities
	boundary00 = boundary();
	boundary11 = boundary();
	boundary22 = boundary();
	boundary33 =  boundary();
	
	inner01 = inner();
	inner02 = inner();
	inner03 = inner();
	inner12 = inner();
	inner13 = inner();
	inner23 = inner();
	
	splitter = splitter();
	joiner = joiner();
	
structure
	//source.O --> splitter.input;
	//joiner.outut -->sink.I;
	
	boundary00.ch_out --> inner01.in1;
	boundary11.ch_out --> inner12.in1;
	boundary22.ch_out --> inner23.in1;
	boundary33.ch_out --> joiner.in4;
	
	//horizontal channels
	inner01.out1 --> inner02.in1;
	inner02.out1 --> inner03.in1;
	inner03.out1 --> joiner.in1;
	inner12.out1 --> inner13.in1;
	inner13.out1 --> joiner.in2;
	inner23.out1 --> joiner.in3;
	
	//vertical channels
	splitter.out1 --> boundary00.ch_in;
	splitter.out2 --> inner01.in2;
	splitter.out3 --> inner02.in2;
	splitter.out4 --> inner03.in2;
	inner01.out2 --> boundary11.ch_in;
	inner02.out2 --> inner12.in2;
	inner03.out2 --> inner13.in2;
	inner12.out2 --> boundary22.ch_in;
	inner13.out2 --> inner23.in2;
	inner23.out2 --> boundary33.ch_in;
	
	
end
	