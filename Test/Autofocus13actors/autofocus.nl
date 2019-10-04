
/** 

*/

network Test () ==> :

entities
	ranger_1 = range_actor();
	ranger_2 = range_actor();
	ranger_3 = range_actor();
	ranger_4 = range_actor();
	ranger_5 = range_actor();
	ranger_6 = range_actor();
	beamer_1 = beam_actor();
	beamer_2 = beam_actor();
	beamer_3 = beam_actor();
	beamer_4 = beam_actor();
	beamer_5 = beam_actor();
	beamer_6 = beam_actor();
	correlator = correlation_actor();
		
structure
	ranger_1.RA --> beamer_1.RA;
	ranger_1.RB --> beamer_1.RB;
	ranger_2.RA --> beamer_2.RA;
	ranger_2.RB --> beamer_2.RB;
	ranger_3.RA --> beamer_3.RA;
	ranger_3.RB --> beamer_3.RB;
	ranger_4.RA --> beamer_4.RA;
	ranger_4.RB --> beamer_4.RB;
	ranger_5.RA --> beamer_5.RA;
	ranger_5.RB --> beamer_5.RB;
	ranger_6.RA --> beamer_6.RA;
	ranger_6.RB --> beamer_6.RB;
	
	beamer_1.BA --> correlator.BA1;
	beamer_1.BB --> correlator.BB1;
	beamer_2.BA --> correlator.BA2;
	beamer_2.BB --> correlator.BB2;
	beamer_3.BA --> correlator.BA3;
	beamer_3.BB --> correlator.BB3;
	beamer_4.BA --> correlator.BA4;
	beamer_4.BB --> correlator.BB4;
	beamer_5.BA --> correlator.BA5;
	beamer_5.BB --> correlator.BB5;
	beamer_6.BA --> correlator.BA6;
	beamer_6.BB --> correlator.BB6;
end


