
/** 

*/

network Test () ==> :

entities
	splitter = splitter();
	convR = conv();
	convG = conv();
	convB = conv();
	combiner = combiner();
		
structure
	splitter.R --> convR.ImageIn;
	splitter.G --> convG.ImageIn;
	splitter.B --> convB.ImageIn;
	convR.ResultOut --> combiner.R_in;
	convG.ResultOut --> combiner.G_in;
	convB.ResultOut --> combiner.B_in;
end


