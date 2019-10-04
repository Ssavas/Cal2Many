//code from beam_actor.cal, instance beamer_2
#include <stdint.h>
#include <string.h>
#include "beamer_2.h"
#include "common.h"

//InputPorts
uint64_t* beamer_2_ch2_buffer SECTION(".core7.data");
uint64_t* beamer_2_ch3_buffer SECTION(".core7.data");
int* beamer_2_ch2_ready SECTION(".core7.data");
int* beamer_2_ch2_valid SECTION(".core7.data");
int* beamer_2_ch3_ready SECTION(".core7.data");
int* beamer_2_ch3_valid SECTION(".core7.data");

//OutputPorts
uint64_t* beamer_2_ch14_buffer SECTION(".core7.data");
uint64_t* beamer_2_ch15_buffer SECTION(".core7.data");
int* beamer_2_ch14_ready SECTION(".core7.data");
int* beamer_2_ch14_valid SECTION(".core7.data");
int* beamer_2_ch15_ready SECTION(".core7.data");
int* beamer_2_ch15_valid SECTION(".core7.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t beamer_2_complex_p0_pos SECTION(".core7.data");
int64_t beamer_2_complex_p0_val SECTION(".core7.data");
int64_t beamer_2_complex_p1_pos SECTION(".core7.data");
int64_t beamer_2_complex_p1_val SECTION(".core7.data");
int64_t beamer_2_complex_p2_pos SECTION(".core7.data");
int64_t beamer_2_complex_p2_val SECTION(".core7.data");
int64_t beamer_2_complex_p3_pos SECTION(".core7.data");
int64_t beamer_2_complex_p3_val SECTION(".core7.data");
int64_t beamer_2_complex_p01 SECTION(".core7.data");
int64_t beamer_2_complex_p12 SECTION(".core7.data");
int64_t beamer_2_complex_p23 SECTION(".core7.data");
int64_t beamer_2_complex_p02 SECTION(".core7.data");
int64_t beamer_2_complex_p13 SECTION(".core7.data");
int64_t beamer_2_complex_input1_p_pos SECTION(".core7.data");
int64_t beamer_2_complex_input1_p_val SECTION(".core7.data");
int64_t beamer_2_complex_input2_p_pos SECTION(".core7.data");
int64_t beamer_2_complex_input2_p_val SECTION(".core7.data");
int64_t beamer_2_complex_output_p SECTION(".core7.data");
int32_t beamer_2_input_state SECTION(".core7.data");
int32_t beamer_2_beam1_i SECTION(".core7.data") = 0;
int32_t beamer_2_beam1_counter SECTION(".core7.data") = 0;
int32_t beamer_2_beam2_i SECTION(".core7.data") = 0;
int32_t beamer_2_beam2_counter SECTION(".core7.data") = 0;
int32_t beamer_2_ba_result_index SECTION(".core7.data") = 0;
int32_t beamer_2_bb_result_index SECTION(".core7.data") = 0;
int32_t beamer_2_inputData_index SECTION(".core7.data") = 0;
int64_t beamer_2_complex_ra[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core7.data");

int64_t beamer_2_complex_rb[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core7.data");

int64_t beamer_2_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core7.data");

int64_t beamer_2_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core7.data");

int32_t beamer_2_beamer_2_State SECTION(".core7.data");
#define FSM_beamer_2_state1 (0) 
#define FSM_beamer_2_state2 (1) 
#define FSM_beamer_2_state12 (2) 
#define FSM_beamer_2_state13 (3) 
#define FSM_beamer_2_state14 (4) 
#define FSM_beamer_2_state15 (5) 
#define FSM_beamer_2_state3 (6) 
#define FSM_beamer_2_state16 (7) 
#define FSM_beamer_2_state17 (8) 
#define FSM_beamer_2_state18 (9) 
#define FSM_beamer_2_state19 (10) 
#define FSM_beamer_2_state11 (11) 
#define FSM_beamer_2_state20 (12) 
int32_t beamer_2_beamer_2_IntCheckOutput SECTION(".core7.data") = -1;

static inline void beamer_2_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_2_complex_rb[i][0] = 1;
		beamer_2_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_2_inputData_index = (beamer_2_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_2_read_ra_val ( ) {
	int32_t i;
	int64_t ra_val [18];
	for(int beamer_2_read_ra_val_i = 0; beamer_2_read_ra_val_i < 18; beamer_2_read_ra_val_i++){
		ra_val[beamer_2_read_ra_val_i] = beamer_2_ch2_buffer[beamer_2_read_ra_val_i]; //read input 
	}
	*beamer_2_ch2_ready = 1; // channel ready to receive new data
	*beamer_2_ch2_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_2_complex_ra[i][1] = ra_val[i];
		i = (i + 1);

	}

	beamer_2_beam1_i = 0;

	beamer_2_beam2_i = 0;

}
static inline void beamer_2_read_rb_val ( ) {
	int32_t i;
	int64_t rb_val [18];
	for(int beamer_2_read_rb_val_i = 0; beamer_2_read_rb_val_i < 18; beamer_2_read_rb_val_i++){
		rb_val[beamer_2_read_rb_val_i] = beamer_2_ch3_buffer[beamer_2_read_rb_val_i]; //read input 
	}
	*beamer_2_ch3_ready = 1; // channel ready to receive new data
	*beamer_2_ch3_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_2_complex_rb[i][1] = rb_val[i];
		i = (i + 1);

	}

}
static inline void beamer_2_beam_int_loop_1 ( ) {
	
	beamer_2_complex_p0_pos = beamer_2_complex_ra[beamer_2_beam1_i + beamer_2_beam1_counter + 0][0];

	beamer_2_complex_p1_pos = beamer_2_complex_ra[beamer_2_beam1_i + beamer_2_beam1_counter + 3][0];

	beamer_2_complex_p2_pos = beamer_2_complex_ra[beamer_2_beam1_i + beamer_2_beam1_counter + 6][0];

	beamer_2_complex_p3_pos = beamer_2_complex_ra[beamer_2_beam1_i + beamer_2_beam1_counter + 9][0];

	beamer_2_input_state = 1;

	beamer_2_beam1_counter = (beamer_2_beam1_counter + 3);

	if ((beamer_2_beam1_counter == 9)){ 
		beamer_2_beam1_counter = 0;

		beamer_2_beam1_i = (beamer_2_beam1_i + 1);

	}

}
static inline void beamer_2_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_2_beam_int_loop_2 ( ) {
	
	beamer_2_complex_p0_pos = beamer_2_complex_rb[beamer_2_beam2_i + beamer_2_beam2_counter + 0][0];

	beamer_2_complex_p1_pos = beamer_2_complex_rb[beamer_2_beam2_i + beamer_2_beam2_counter + 3][0];

	beamer_2_complex_p2_pos = beamer_2_complex_rb[beamer_2_beam2_i + beamer_2_beam2_counter + 6][0];

	beamer_2_complex_p3_pos = beamer_2_complex_rb[beamer_2_beam2_i + beamer_2_beam2_counter + 9][0];

	beamer_2_input_state = 1;

	beamer_2_beam2_counter = (beamer_2_beam2_counter + 3);

	if ((beamer_2_beam2_counter == 9)){ 
		beamer_2_beam2_counter = 0;

		beamer_2_beam2_i = (beamer_2_beam2_i + 1);

	}

}
static inline void beamer_2_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_2_store_ba_results ( ) {
	
	beamer_2_complex_ba[beamer_2_ba_result_index][1] = beamer_2_complex_output_p;
	beamer_2_ba_result_index = (beamer_2_ba_result_index + 3);

	if ((beamer_2_ba_result_index == 9)){ 
		beamer_2_ba_result_index = 1;

	}

	if ((beamer_2_ba_result_index == 10)){ 
		beamer_2_ba_result_index = 2;

	}

	if ((beamer_2_ba_result_index == 11)){ 
		beamer_2_ba_result_index = 0;

	}

}
static inline void beamer_2_store_bb_results ( ) {
	
	beamer_2_complex_bb[beamer_2_bb_result_index][1] = beamer_2_complex_output_p;
	beamer_2_bb_result_index = (beamer_2_bb_result_index + 3);

	if ((beamer_2_bb_result_index == 9)){ 
		beamer_2_bb_result_index = 1;

	}

	if ((beamer_2_bb_result_index == 10)){ 
		beamer_2_bb_result_index = 2;

	}

	if ((beamer_2_bb_result_index == 11)){ 
		beamer_2_bb_result_index = 0;

	}

}
static inline void beamer_2_correlation ( ) {
	int32_t i;
	int64_t localba [9];
	int64_t localbb [9];
	
	i = 0;

	while (( i < 9 )) {
		localba[i] = beamer_2_complex_ba[i][1];
		localbb[i] = beamer_2_complex_bb[i][1];
		i = (i + 1);

	}

	for(int beamer_2_correlation_i = 0; beamer_2_correlation_i < 9; beamer_2_correlation_i++){
		beamer_2_ch14_buffer[beamer_2_correlation_i] = localba[beamer_2_correlation_i]; //write output 
	}
	*beamer_2_ch14_ready = 0; //channel NOT ready to receive new data
	*beamer_2_ch14_valid = 1; //(because) channel has new data 
	
	for(int beamer_2_correlation_i = 0; beamer_2_correlation_i < 9; beamer_2_correlation_i++){
		beamer_2_ch15_buffer[beamer_2_correlation_i] = localbb[beamer_2_correlation_i]; //write output 
	}
	*beamer_2_ch15_ready = 0; //channel NOT ready to receive new data
	*beamer_2_ch15_valid = 1; //(because) channel has new data 
	
}
static inline void beamer_2_set_cubic_inputs ( ) {
	
	if ((beamer_2_input_state == 1)){ 
		beamer_2_complex_input1_p_pos = beamer_2_complex_p0_pos;

		beamer_2_complex_input1_p_val = beamer_2_complex_p0_val;

		beamer_2_complex_input2_p_pos = beamer_2_complex_p1_pos;

		beamer_2_complex_input2_p_val = beamer_2_complex_p1_val;

		beamer_2_input_state = 2;

	}
	else {
		if ((beamer_2_input_state == 2)){ 
			beamer_2_complex_p01 = beamer_2_complex_output_p;

			beamer_2_complex_input1_p_pos = beamer_2_complex_p1_pos;

			beamer_2_complex_input1_p_val = beamer_2_complex_p1_val;

			beamer_2_complex_input2_p_pos = beamer_2_complex_p2_pos;

			beamer_2_complex_input2_p_val = beamer_2_complex_p2_val;

			beamer_2_input_state = 3;

		}
		else {
			if ((beamer_2_input_state == 3)){ 
				beamer_2_complex_p12 = beamer_2_complex_output_p;

				beamer_2_complex_input1_p_pos = beamer_2_complex_p2_pos;

				beamer_2_complex_input1_p_val = beamer_2_complex_p2_val;

				beamer_2_complex_input2_p_pos = beamer_2_complex_p3_pos;

				beamer_2_complex_input2_p_val = beamer_2_complex_p3_val;

				beamer_2_input_state = 4;

			}
			else {
				if ((beamer_2_input_state == 4)){ 
					beamer_2_complex_p23 = beamer_2_complex_output_p;

					beamer_2_complex_input1_p_pos = beamer_2_complex_p0_pos;

					beamer_2_complex_input1_p_val = beamer_2_complex_p01;

					beamer_2_complex_input2_p_pos = beamer_2_complex_p3_pos;

					beamer_2_complex_input2_p_val = beamer_2_complex_p12;

					beamer_2_input_state = 5;

				}
				else {
					if ((beamer_2_input_state == 5)){ 
						beamer_2_complex_p02 = beamer_2_complex_output_p;

						beamer_2_complex_input1_p_pos = beamer_2_complex_p1_pos;

						beamer_2_complex_input1_p_val = beamer_2_complex_p12;

						beamer_2_complex_input2_p_pos = beamer_2_complex_p3_pos;

						beamer_2_complex_input2_p_val = beamer_2_complex_p23;

						beamer_2_input_state = 6;

					}
					else {
						if ((beamer_2_input_state == 6)){ 
							beamer_2_complex_p13 = beamer_2_complex_output_p;

							beamer_2_complex_input1_p_pos = beamer_2_complex_p0_pos;

							beamer_2_complex_input1_p_val = beamer_2_complex_p02;

							beamer_2_complex_input2_p_pos = beamer_2_complex_p3_pos;

							beamer_2_complex_input2_p_val = beamer_2_complex_p13;

							beamer_2_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_2_set_cubic_inputs_done ( ) {
	
}
static inline void beamer_2___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_2_complex_input1_p_pos, beamer_2_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_2_complex_input2_p_pos, beamer_2_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_2_complex_output_p = outputReg;
}
static inline void beamer_2_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_2_complex_ba[i][0] = beamer_2_complex_ra[i][0];
		beamer_2_complex_bb[i][0] = beamer_2_complex_rb[i][0];
		i = (i + 1);

	}

}
int int_state_vars_beamer_2 = 1;
void initStateVarsbeamer_2() {
beamer_2_beamer_2_State = FSM_beamer_2_state1;

}

int beamer_2(void)
{
  
	//InputPorts
 	extern int ch2_ready; 
	extern int ch2_valid; 
	extern uint64_t ch2_buffer[ch2_size];
	extern int ch3_ready; 
	extern int ch3_valid; 
	extern uint64_t ch3_buffer[ch3_size];
	beamer_2_ch2_buffer =  ch2_buffer; 
	beamer_2_ch2_ready = &ch2_ready; 
	beamer_2_ch2_valid = &ch2_valid; 
	beamer_2_ch3_buffer =  ch3_buffer; 
	beamer_2_ch3_ready = &ch3_ready; 
	beamer_2_ch3_valid = &ch3_valid; 

	//OutputPorts
	extern int ch14_ready; 
	extern int ch14_valid; 
	extern uint64_t ch14_buffer[ch14_size];
	extern int ch15_ready; 
	extern int ch15_valid; 
	extern uint64_t ch15_buffer[ch15_size];
	beamer_2_ch14_buffer = ch14_buffer; 
	beamer_2_ch14_ready = &ch14_ready; 
	beamer_2_ch14_valid = &ch14_valid; 
	beamer_2_ch15_buffer = ch15_buffer; 
	beamer_2_ch15_ready = &ch15_ready; 
	beamer_2_ch15_valid = &ch15_valid; 
    
	if(int_state_vars_beamer_2 == 1){
		int_state_vars_beamer_2 = 0;
		initStateVarsbeamer_2();
	}
if ((beamer_2_beamer_2_IntCheckOutput == -1)){ 
	
beamer_2Schedule:

	
 switch (beamer_2_beamer_2_State) {
   case FSM_beamer_2_state1:
     		if (( beamer_2_inputData_index < NOF_PIXELS )){ 
			beamer_2_set_ra_rb_pos();
			beamer_2_beamer_2_State = FSM_beamer_2_state2;

			goto beamer_2Schedule;
		}

		     break;

   case FSM_beamer_2_state2:
     		if (*beamer_2_ch2_valid == 1){ 
							beamer_2_read_ra_val();
				beamer_2_beamer_2_State = FSM_beamer_2_state12;

				goto beamer_2Schedule;

		}

		     break;

   case FSM_beamer_2_state12:
     		if (( beamer_2_beam1_i < 3 )){ 
			beamer_2_beam_int_loop_1();
			beamer_2_beamer_2_State = FSM_beamer_2_state13;

			goto beamer_2Schedule;
		}

					beamer_2_beam_int_loop_1_done();
			beamer_2_beamer_2_State = FSM_beamer_2_state3;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state13:
     		if ((beamer_2_input_state != 0)){ 
			beamer_2_set_cubic_inputs();
			beamer_2_beamer_2_State = FSM_beamer_2_state15;

			goto beamer_2Schedule;
		}

					beamer_2_set_cubic_inputs_done();
			beamer_2_beamer_2_State = FSM_beamer_2_state14;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state14:
     					beamer_2_store_ba_results();
			beamer_2_beamer_2_State = FSM_beamer_2_state12;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state15:
     					beamer_2___acc__cubic();
			beamer_2_beamer_2_State = FSM_beamer_2_state13;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state3:
     		if (*beamer_2_ch3_valid == 1){ 
							beamer_2_read_rb_val();
				beamer_2_beamer_2_State = FSM_beamer_2_state16;

				goto beamer_2Schedule;

		}

		     break;

   case FSM_beamer_2_state16:
     		if (( beamer_2_beam2_i < 3 )){ 
			beamer_2_beam_int_loop_2();
			beamer_2_beamer_2_State = FSM_beamer_2_state17;

			goto beamer_2Schedule;
		}

					beamer_2_beam_int_loop_2_done();
			beamer_2_beamer_2_State = FSM_beamer_2_state11;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state17:
     		if ((beamer_2_input_state != 0)){ 
			beamer_2_set_cubic_inputs();
			beamer_2_beamer_2_State = FSM_beamer_2_state19;

			goto beamer_2Schedule;
		}

					beamer_2_set_cubic_inputs_done();
			beamer_2_beamer_2_State = FSM_beamer_2_state18;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state18:
     					beamer_2_store_bb_results();
			beamer_2_beamer_2_State = FSM_beamer_2_state16;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state19:
     					beamer_2___acc__cubic();
			beamer_2_beamer_2_State = FSM_beamer_2_state17;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state11:
     					beamer_2_set_ba_bb_pos();
			beamer_2_beamer_2_State = FSM_beamer_2_state20;

			goto beamer_2Schedule;

		     break;

   case FSM_beamer_2_state20:
     					
beamer_2_Action_0:

			if ((*beamer_2_ch14_ready == 1 && *beamer_2_ch15_ready == 1)){ 
				beamer_2_correlation();
				beamer_2_beamer_2_State = FSM_beamer_2_state1;

				goto beamer_2Schedule;
			}
			else {
				beamer_2_beamer_2_IntCheckOutput = 0;

				return(0);
			}


		     break;

}

	beamer_2_beamer_2_IntCheckOutput = -1;

}
else {
	
 switch (beamer_2_beamer_2_IntCheckOutput) {
   case 0:
     		beamer_2_beamer_2_IntCheckOutput = -1;

		goto beamer_2_Action_0;
}

}
goto beamer_2Schedule;
}
