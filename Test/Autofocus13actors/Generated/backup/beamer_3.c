//code from beam_actor.cal, instance beamer_3
#include <stdint.h>
#include <string.h>
#include "beamer_3.h"
#include "common.h"

//InputPorts
uint64_t* beamer_3_ch4_buffer SECTION(".core8.data");
uint64_t* beamer_3_ch5_buffer SECTION(".core8.data");
int* beamer_3_ch4_ready SECTION(".core8.data");
int* beamer_3_ch4_valid SECTION(".core8.data");
int* beamer_3_ch5_ready SECTION(".core8.data");
int* beamer_3_ch5_valid SECTION(".core8.data");

//OutputPorts
uint64_t* beamer_3_ch16_buffer SECTION(".core8.data");
uint64_t* beamer_3_ch17_buffer SECTION(".core8.data");
int* beamer_3_ch16_ready SECTION(".core8.data");
int* beamer_3_ch16_valid SECTION(".core8.data");
int* beamer_3_ch17_ready SECTION(".core8.data");
int* beamer_3_ch17_valid SECTION(".core8.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t beamer_3_complex_p0_pos SECTION(".core8.data");
int64_t beamer_3_complex_p0_val SECTION(".core8.data");
int64_t beamer_3_complex_p1_pos SECTION(".core8.data");
int64_t beamer_3_complex_p1_val SECTION(".core8.data");
int64_t beamer_3_complex_p2_pos SECTION(".core8.data");
int64_t beamer_3_complex_p2_val SECTION(".core8.data");
int64_t beamer_3_complex_p3_pos SECTION(".core8.data");
int64_t beamer_3_complex_p3_val SECTION(".core8.data");
int64_t beamer_3_complex_p01 SECTION(".core8.data");
int64_t beamer_3_complex_p12 SECTION(".core8.data");
int64_t beamer_3_complex_p23 SECTION(".core8.data");
int64_t beamer_3_complex_p02 SECTION(".core8.data");
int64_t beamer_3_complex_p13 SECTION(".core8.data");
int64_t beamer_3_complex_input1_p_pos SECTION(".core8.data");
int64_t beamer_3_complex_input1_p_val SECTION(".core8.data");
int64_t beamer_3_complex_input2_p_pos SECTION(".core8.data");
int64_t beamer_3_complex_input2_p_val SECTION(".core8.data");
int64_t beamer_3_complex_output_p SECTION(".core8.data");
int32_t beamer_3_input_state SECTION(".core8.data");
int32_t beamer_3_beam1_i SECTION(".core8.data") = 0;
int32_t beamer_3_beam1_counter SECTION(".core8.data") = 0;
int32_t beamer_3_beam2_i SECTION(".core8.data") = 0;
int32_t beamer_3_beam2_counter SECTION(".core8.data") = 0;
int32_t beamer_3_ba_result_index SECTION(".core8.data") = 0;
int32_t beamer_3_bb_result_index SECTION(".core8.data") = 0;
int32_t beamer_3_inputData_index SECTION(".core8.data") = 0;
int64_t beamer_3_complex_ra[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core8.data");

int64_t beamer_3_complex_rb[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core8.data");

int64_t beamer_3_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core8.data");

int64_t beamer_3_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core8.data");

int32_t beamer_3_beamer_3_State SECTION(".core8.data");
#define FSM_beamer_3_state1 (0) 
#define FSM_beamer_3_state2 (1) 
#define FSM_beamer_3_state12 (2) 
#define FSM_beamer_3_state13 (3) 
#define FSM_beamer_3_state14 (4) 
#define FSM_beamer_3_state15 (5) 
#define FSM_beamer_3_state3 (6) 
#define FSM_beamer_3_state16 (7) 
#define FSM_beamer_3_state17 (8) 
#define FSM_beamer_3_state18 (9) 
#define FSM_beamer_3_state19 (10) 
#define FSM_beamer_3_state11 (11) 
#define FSM_beamer_3_state20 (12) 
int32_t beamer_3_beamer_3_IntCheckOutput SECTION(".core8.data") = -1;

static inline void beamer_3_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_3_complex_rb[i][0] = 1;
		beamer_3_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_3_inputData_index = (beamer_3_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_3_read_ra_val ( ) {
	int32_t i;
	int64_t ra_val [18];
	for(int beamer_3_read_ra_val_i = 0; beamer_3_read_ra_val_i < 18; beamer_3_read_ra_val_i++){
		ra_val[beamer_3_read_ra_val_i] = beamer_3_ch4_buffer[beamer_3_read_ra_val_i]; //read input 
	}
	*beamer_3_ch4_ready = 1; // channel ready to receive new data
	*beamer_3_ch4_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_3_complex_ra[i][1] = ra_val[i];
		i = (i + 1);

	}

	beamer_3_beam1_i = 0;

	beamer_3_beam2_i = 0;

}
static inline void beamer_3_read_rb_val ( ) {
	int32_t i;
	int64_t rb_val [18];
	for(int beamer_3_read_rb_val_i = 0; beamer_3_read_rb_val_i < 18; beamer_3_read_rb_val_i++){
		rb_val[beamer_3_read_rb_val_i] = beamer_3_ch5_buffer[beamer_3_read_rb_val_i]; //read input 
	}
	*beamer_3_ch5_ready = 1; // channel ready to receive new data
	*beamer_3_ch5_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_3_complex_rb[i][1] = rb_val[i];
		i = (i + 1);

	}

}
static inline void beamer_3_beam_int_loop_1 ( ) {
	
	beamer_3_complex_p0_pos = beamer_3_complex_ra[beamer_3_beam1_i + beamer_3_beam1_counter + 0][0];

	beamer_3_complex_p1_pos = beamer_3_complex_ra[beamer_3_beam1_i + beamer_3_beam1_counter + 3][0];

	beamer_3_complex_p2_pos = beamer_3_complex_ra[beamer_3_beam1_i + beamer_3_beam1_counter + 6][0];

	beamer_3_complex_p3_pos = beamer_3_complex_ra[beamer_3_beam1_i + beamer_3_beam1_counter + 9][0];

	beamer_3_input_state = 1;

	beamer_3_beam1_counter = (beamer_3_beam1_counter + 3);

	if ((beamer_3_beam1_counter == 9)){ 
		beamer_3_beam1_counter = 0;

		beamer_3_beam1_i = (beamer_3_beam1_i + 1);

	}

}
static inline void beamer_3_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_3_beam_int_loop_2 ( ) {
	
	beamer_3_complex_p0_pos = beamer_3_complex_rb[beamer_3_beam2_i + beamer_3_beam2_counter + 0][0];

	beamer_3_complex_p1_pos = beamer_3_complex_rb[beamer_3_beam2_i + beamer_3_beam2_counter + 3][0];

	beamer_3_complex_p2_pos = beamer_3_complex_rb[beamer_3_beam2_i + beamer_3_beam2_counter + 6][0];

	beamer_3_complex_p3_pos = beamer_3_complex_rb[beamer_3_beam2_i + beamer_3_beam2_counter + 9][0];

	beamer_3_input_state = 1;

	beamer_3_beam2_counter = (beamer_3_beam2_counter + 3);

	if ((beamer_3_beam2_counter == 9)){ 
		beamer_3_beam2_counter = 0;

		beamer_3_beam2_i = (beamer_3_beam2_i + 1);

	}

}
static inline void beamer_3_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_3_store_ba_results ( ) {
	
	beamer_3_complex_ba[beamer_3_ba_result_index][1] = beamer_3_complex_output_p;
	beamer_3_ba_result_index = (beamer_3_ba_result_index + 3);

	if ((beamer_3_ba_result_index == 9)){ 
		beamer_3_ba_result_index = 1;

	}

	if ((beamer_3_ba_result_index == 10)){ 
		beamer_3_ba_result_index = 2;

	}

	if ((beamer_3_ba_result_index == 11)){ 
		beamer_3_ba_result_index = 0;

	}

}
static inline void beamer_3_store_bb_results ( ) {
	
	beamer_3_complex_bb[beamer_3_bb_result_index][1] = beamer_3_complex_output_p;
	beamer_3_bb_result_index = (beamer_3_bb_result_index + 3);

	if ((beamer_3_bb_result_index == 9)){ 
		beamer_3_bb_result_index = 1;

	}

	if ((beamer_3_bb_result_index == 10)){ 
		beamer_3_bb_result_index = 2;

	}

	if ((beamer_3_bb_result_index == 11)){ 
		beamer_3_bb_result_index = 0;

	}

}
static inline void beamer_3_correlation ( ) {
	int32_t i;
	int64_t localba [9];
	int64_t localbb [9];
	
	i = 0;

	while (( i < 9 )) {
		localba[i] = beamer_3_complex_ba[i][1];
		localbb[i] = beamer_3_complex_bb[i][1];
		i = (i + 1);

	}

	for(int beamer_3_correlation_i = 0; beamer_3_correlation_i < 9; beamer_3_correlation_i++){
		beamer_3_ch16_buffer[beamer_3_correlation_i] = localba[beamer_3_correlation_i]; //write output 
	}
	*beamer_3_ch16_ready = 0; //channel NOT ready to receive new data
	*beamer_3_ch16_valid = 1; //(because) channel has new data 
	
	for(int beamer_3_correlation_i = 0; beamer_3_correlation_i < 9; beamer_3_correlation_i++){
		beamer_3_ch17_buffer[beamer_3_correlation_i] = localbb[beamer_3_correlation_i]; //write output 
	}
	*beamer_3_ch17_ready = 0; //channel NOT ready to receive new data
	*beamer_3_ch17_valid = 1; //(because) channel has new data 
	
}
static inline void beamer_3_set_cubic_inputs ( ) {
	
	if ((beamer_3_input_state == 1)){ 
		beamer_3_complex_input1_p_pos = beamer_3_complex_p0_pos;

		beamer_3_complex_input1_p_val = beamer_3_complex_p0_val;

		beamer_3_complex_input2_p_pos = beamer_3_complex_p1_pos;

		beamer_3_complex_input2_p_val = beamer_3_complex_p1_val;

		beamer_3_input_state = 2;

	}
	else {
		if ((beamer_3_input_state == 2)){ 
			beamer_3_complex_p01 = beamer_3_complex_output_p;

			beamer_3_complex_input1_p_pos = beamer_3_complex_p1_pos;

			beamer_3_complex_input1_p_val = beamer_3_complex_p1_val;

			beamer_3_complex_input2_p_pos = beamer_3_complex_p2_pos;

			beamer_3_complex_input2_p_val = beamer_3_complex_p2_val;

			beamer_3_input_state = 3;

		}
		else {
			if ((beamer_3_input_state == 3)){ 
				beamer_3_complex_p12 = beamer_3_complex_output_p;

				beamer_3_complex_input1_p_pos = beamer_3_complex_p2_pos;

				beamer_3_complex_input1_p_val = beamer_3_complex_p2_val;

				beamer_3_complex_input2_p_pos = beamer_3_complex_p3_pos;

				beamer_3_complex_input2_p_val = beamer_3_complex_p3_val;

				beamer_3_input_state = 4;

			}
			else {
				if ((beamer_3_input_state == 4)){ 
					beamer_3_complex_p23 = beamer_3_complex_output_p;

					beamer_3_complex_input1_p_pos = beamer_3_complex_p0_pos;

					beamer_3_complex_input1_p_val = beamer_3_complex_p01;

					beamer_3_complex_input2_p_pos = beamer_3_complex_p3_pos;

					beamer_3_complex_input2_p_val = beamer_3_complex_p12;

					beamer_3_input_state = 5;

				}
				else {
					if ((beamer_3_input_state == 5)){ 
						beamer_3_complex_p02 = beamer_3_complex_output_p;

						beamer_3_complex_input1_p_pos = beamer_3_complex_p1_pos;

						beamer_3_complex_input1_p_val = beamer_3_complex_p12;

						beamer_3_complex_input2_p_pos = beamer_3_complex_p3_pos;

						beamer_3_complex_input2_p_val = beamer_3_complex_p23;

						beamer_3_input_state = 6;

					}
					else {
						if ((beamer_3_input_state == 6)){ 
							beamer_3_complex_p13 = beamer_3_complex_output_p;

							beamer_3_complex_input1_p_pos = beamer_3_complex_p0_pos;

							beamer_3_complex_input1_p_val = beamer_3_complex_p02;

							beamer_3_complex_input2_p_pos = beamer_3_complex_p3_pos;

							beamer_3_complex_input2_p_val = beamer_3_complex_p13;

							beamer_3_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_3_set_cubic_inputs_done ( ) {
	
}
static inline void beamer_3___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_3_complex_input1_p_pos, beamer_3_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_3_complex_input2_p_pos, beamer_3_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_3_complex_output_p = outputReg;
}
static inline void beamer_3_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_3_complex_ba[i][0] = beamer_3_complex_ra[i][0];
		beamer_3_complex_bb[i][0] = beamer_3_complex_rb[i][0];
		i = (i + 1);

	}

}
int int_state_vars_beamer_3 = 1;
void initStateVarsbeamer_3() {
beamer_3_beamer_3_State = FSM_beamer_3_state1;

}

int beamer_3(void)
{
  
	//InputPorts
 	extern int ch4_ready; 
	extern int ch4_valid; 
	extern uint64_t ch4_buffer[ch4_size];
	extern int ch5_ready; 
	extern int ch5_valid; 
	extern uint64_t ch5_buffer[ch5_size];
	beamer_3_ch4_buffer =  ch4_buffer; 
	beamer_3_ch4_ready = &ch4_ready; 
	beamer_3_ch4_valid = &ch4_valid; 
	beamer_3_ch5_buffer =  ch5_buffer; 
	beamer_3_ch5_ready = &ch5_ready; 
	beamer_3_ch5_valid = &ch5_valid; 

	//OutputPorts
	extern int ch16_ready; 
	extern int ch16_valid; 
	extern uint64_t ch16_buffer[ch16_size];
	extern int ch17_ready; 
	extern int ch17_valid; 
	extern uint64_t ch17_buffer[ch17_size];
	beamer_3_ch16_buffer = ch16_buffer; 
	beamer_3_ch16_ready = &ch16_ready; 
	beamer_3_ch16_valid = &ch16_valid; 
	beamer_3_ch17_buffer = ch17_buffer; 
	beamer_3_ch17_ready = &ch17_ready; 
	beamer_3_ch17_valid = &ch17_valid; 
    
	if(int_state_vars_beamer_3 == 1){
		int_state_vars_beamer_3 = 0;
		initStateVarsbeamer_3();
	}
if ((beamer_3_beamer_3_IntCheckOutput == -1)){ 
	
beamer_3Schedule:

	
 switch (beamer_3_beamer_3_State) {
   case FSM_beamer_3_state1:
     		if (( beamer_3_inputData_index < NOF_PIXELS )){ 
			beamer_3_set_ra_rb_pos();
			beamer_3_beamer_3_State = FSM_beamer_3_state2;

			goto beamer_3Schedule;
		}

		     break;

   case FSM_beamer_3_state2:
     		if (*beamer_3_ch4_valid == 1){ 
							beamer_3_read_ra_val();
				beamer_3_beamer_3_State = FSM_beamer_3_state12;

				goto beamer_3Schedule;

		}

		     break;

   case FSM_beamer_3_state12:
     		if (( beamer_3_beam1_i < 3 )){ 
			beamer_3_beam_int_loop_1();
			beamer_3_beamer_3_State = FSM_beamer_3_state13;

			goto beamer_3Schedule;
		}

					beamer_3_beam_int_loop_1_done();
			beamer_3_beamer_3_State = FSM_beamer_3_state3;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state13:
     		if ((beamer_3_input_state != 0)){ 
			beamer_3_set_cubic_inputs();
			beamer_3_beamer_3_State = FSM_beamer_3_state15;

			goto beamer_3Schedule;
		}

					beamer_3_set_cubic_inputs_done();
			beamer_3_beamer_3_State = FSM_beamer_3_state14;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state14:
     					beamer_3_store_ba_results();
			beamer_3_beamer_3_State = FSM_beamer_3_state12;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state15:
     					beamer_3___acc__cubic();
			beamer_3_beamer_3_State = FSM_beamer_3_state13;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state3:
     		if (*beamer_3_ch5_valid == 1){ 
							beamer_3_read_rb_val();
				beamer_3_beamer_3_State = FSM_beamer_3_state16;

				goto beamer_3Schedule;

		}

		     break;

   case FSM_beamer_3_state16:
     		if (( beamer_3_beam2_i < 3 )){ 
			beamer_3_beam_int_loop_2();
			beamer_3_beamer_3_State = FSM_beamer_3_state17;

			goto beamer_3Schedule;
		}

					beamer_3_beam_int_loop_2_done();
			beamer_3_beamer_3_State = FSM_beamer_3_state11;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state17:
     		if ((beamer_3_input_state != 0)){ 
			beamer_3_set_cubic_inputs();
			beamer_3_beamer_3_State = FSM_beamer_3_state19;

			goto beamer_3Schedule;
		}

					beamer_3_set_cubic_inputs_done();
			beamer_3_beamer_3_State = FSM_beamer_3_state18;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state18:
     					beamer_3_store_bb_results();
			beamer_3_beamer_3_State = FSM_beamer_3_state16;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state19:
     					beamer_3___acc__cubic();
			beamer_3_beamer_3_State = FSM_beamer_3_state17;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state11:
     					beamer_3_set_ba_bb_pos();
			beamer_3_beamer_3_State = FSM_beamer_3_state20;

			goto beamer_3Schedule;

		     break;

   case FSM_beamer_3_state20:
     					
beamer_3_Action_0:

			if ((*beamer_3_ch16_ready == 1 && *beamer_3_ch17_ready == 1)){ 
				beamer_3_correlation();
				beamer_3_beamer_3_State = FSM_beamer_3_state1;

				goto beamer_3Schedule;
			}
			else {
				beamer_3_beamer_3_IntCheckOutput = 0;

				return(0);
			}


		     break;

}

	beamer_3_beamer_3_IntCheckOutput = -1;

}
else {
	
 switch (beamer_3_beamer_3_IntCheckOutput) {
   case 0:
     		beamer_3_beamer_3_IntCheckOutput = -1;

		goto beamer_3_Action_0;
}

}
goto beamer_3Schedule;
}
