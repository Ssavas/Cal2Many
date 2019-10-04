
/** 

*/

network Test () ==> :

entities
	convR = conv();
	convG = conv();
	convB = conv();
	combiner = combiner();
		
structure
	convR.ResultOut --> combiner.R_in;
	convG.ResultOut --> combiner.G_in;
	convB.ResultOut --> combiner.B_in;
end


