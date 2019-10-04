
/** 

*/

network Test () ==> :

entities
	ranger = range_actor();
	beamer = beam_actor();
		
structure
	ranger.RA --> beamer.RA;
	ranger.RB --> beamer.RB;	
end


