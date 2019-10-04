//code from beam_actor.cal, instance beamer_1
#include <stdint.h>
#include <string.h>
#include "beamer_1.h"
#include "common.h"

//InputPorts
uint64_t* beamer_1_ch0_buffer SECTION(".core6.data");
uint64_t* beamer_1_ch1_buffer SECTION(".core6.data");
int* beamer_1_ch0_ready SECTION(".core6.data");
int* beamer_1_ch0_valid SECTION(".core6.data");
int* beamer_1_ch1_ready SECTION(".core6.data");
int* beamer_1_ch1_valid SECTION(".core6.data");

//OutputPorts
uint64_t* beamer_1_ch12_buffer SECTION(".core6.data");
uint64_t* beamer_1_ch13_buffer SECTION(".core6.data");
int* beamer_1_ch12_ready SECTION(".core6.data");
int* beamer_1_ch12_valid SECTION(".core6.data");
int* beamer_1_ch13_ready SECTION(".core6.data");
int* beamer_1_ch13_valid SECTION(".core6.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t beamer_1_complex_p0_pos SECTION(".core6.data");
int64_t beamer_1_complex_p0_val SECTION(".core6.data");
int64_t beamer_1_complex_p1_pos SECTION(".core6.data");
int64_t beamer_1_complex_p1_val SECTION(".core6.data");
int64_t beamer_1_complex_p2_pos SECTION(".core6.data");
int64_t beamer_1_complex_p2_val SECTION(".core6.data");
int64_t beamer_1_complex_p3_pos SECTION(".core6.data");
int64_t beamer_1_complex_p3_val SECTION(".core6.data");
int64_t beamer_1_complex_p01 SECTION(".core6.data");
int64_t beamer_1_complex_p12 SECTION(".core6.data");
int64_t beamer_1_complex_p23 SECTION(".core6.data");
int64_t beamer_1_complex_p02 SECTION(".core6.data");
int64_t beamer_1_complex_p13 SECTION(".core6.data");
int64_t beamer_1_complex_input1_p_pos SECTION(".core6.data");
int64_t beamer_1_complex_input1_p_val SECTION(".core6.data");
int64_t beamer_1_complex_input2_p_pos SECTION(".core6.data");
int64_t beamer_1_complex_input2_p_val SECTION(".core6.data");
int64_t beamer_1_complex_output_p SECTION(".core6.data");
int32_t beamer_1_input_state SECTION(".core6.data");
int32_t beamer_1_beam1_i SECTION(".core6.data") = 0;
int32_t beamer_1_beam1_counter SECTION(".core6.data") = 0;
int32_t beamer_1_beam2_i SECTION(".core6.data") = 0;
int32_t beamer_1_beam2_counter SECTION(".core6.data") = 0;
int32_t beamer_1_ba_result_index SECTION(".core6.data") = 0;
int32_t beamer_1_bb_result_index SECTION(".core6.data") = 0;
int32_t beamer_1_inputData_index SECTION(".core6.data") = 0;
int64_t beamer_1_complex_ra[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core6.data");

int64_t beamer_1_complex_rb[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core6.data");

int64_t beamer_1_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core6.data");

int64_t beamer_1_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core6.data");

int32_t beamer_1_beamer_1_State SECTION(".core6.data");
#define FSM_beamer_1_state1 (0) 
#define FSM_beamer_1_state2 (1) 
#define FSM_beamer_1_state12 (2) 
#define FSM_beamer_1_state13 (3) 
#define FSM_beamer_1_state14 (4) 
#define FSM_beamer_1_state15 (5) 
#define FSM_beamer_1_state3 (6) 
#define FSM_beamer_1_state16 (7) 
#define FSM_beamer_1_state17 (8) 
#define FSM_beamer_1_state18 (9) 
#define FSM_beamer_1_state19 (10) 
#define FSM_beamer_1_state11 (11) 
#define FSM_beamer_1_state20 (12) 
int32_t beamer_1_beamer_1_IntCheckOutput SECTION(".core6.data") = -1;

static inline void beamer_1_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_1_complex_rb[i][0] = 1;
		beamer_1_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_1_inputData_index = (beamer_1_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_1_read_ra_val ( ) {
	int32_t i;
	int64_t ra_val [18];
	for(int beamer_1_read_ra_val_i = 0; beamer_1_read_ra_val_i < 18; beamer_1_read_ra_val_i++){
		ra_val[beamer_1_read_ra_val_i] = beamer_1_ch0_buffer[beamer_1_read_ra_val_i]; //read input 
	}
	*beamer_1_ch0_ready = 1; // channel ready to receive new data
	*beamer_1_ch0_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_1_complex_ra[i][1] = ra_val[i];
		i = (i + 1);

	}

	beamer_1_beam1_i = 0;

	beamer_1_beam2_i = 0;

}
static inline void beamer_1_read_rb_val ( ) {
	int32_t i;
	int64_t rb_val [18];
	for(int beamer_1_read_rb_val_i = 0; beamer_1_read_rb_val_i < 18; beamer_1_read_rb_val_i++){
		rb_val[beamer_1_read_rb_val_i] = beamer_1_ch1_buffer[beamer_1_read_rb_val_i]; //read input 
	}
	*beamer_1_ch1_ready = 1; // channel ready to receive new data
	*beamer_1_ch1_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_1_complex_rb[i][1] = rb_val[i];
		i = (i + 1);

	}

}
static inline void beamer_1_beam_int_loop_1 ( ) {
	
	beamer_1_complex_p0_pos = beamer_1_complex_ra[beamer_1_beam1_i + beamer_1_beam1_counter + 0][0];

	beamer_1_complex_p1_pos = beamer_1_complex_ra[beamer_1_beam1_i + beamer_1_beam1_counter + 3][0];

	beamer_1_complex_p2_pos = beamer_1_complex_ra[beamer_1_beam1_i + beamer_1_beam1_counter + 6][0];

	beamer_1_complex_p3_pos = beamer_1_complex_ra[beamer_1_beam1_i + beamer_1_beam1_counter + 9][0];

	beamer_1_input_state = 1;

	beamer_1_beam1_counter = (beamer_1_beam1_counter + 3);

	if ((beamer_1_beam1_counter == 9)){ 
		beamer_1_beam1_counter = 0;

		beamer_1_beam1_i = (beamer_1_beam1_i + 1);

	}

}
static inline void beamer_1_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_1_beam_int_loop_2 ( ) {
	
	beamer_1_complex_p0_pos = beamer_1_complex_rb[beamer_1_beam2_i + beamer_1_beam2_counter + 0][0];

	beamer_1_complex_p1_pos = beamer_1_complex_rb[beamer_1_beam2_i + beamer_1_beam2_counter + 3][0];

	beamer_1_complex_p2_pos = beamer_1_complex_rb[beamer_1_beam2_i + beamer_1_beam2_counter + 6][0];

	beamer_1_complex_p3_pos = beamer_1_complex_rb[beamer_1_beam2_i + beamer_1_beam2_counter + 9][0];

	beamer_1_input_state = 1;

	beamer_1_beam2_counter = (beamer_1_beam2_counter + 3);

	if ((beamer_1_beam2_counter == 9)){ 
		beamer_1_beam2_counter = 0;

		beamer_1_beam2_i = (beamer_1_beam2_i + 1);

	}

}
static inline void beamer_1_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_1_store_ba_results ( ) {
	
	beamer_1_complex_ba[beamer_1_ba_result_index][1] = beamer_1_complex_output_p;
	beamer_1_ba_result_index = (beamer_1_ba_result_index + 3);

	if ((beamer_1_ba_result_index == 9)){ 
		beamer_1_ba_result_index = 1;

	}

	if ((beamer_1_ba_result_index == 10)){ 
		beamer_1_ba_result_index = 2;

	}

	if ((beamer_1_ba_result_index == 11)){ 
		beamer_1_ba_result_index = 0;

	}

}
static inline void beamer_1_store_bb_results ( ) {
	
	beamer_1_complex_bb[beamer_1_bb_result_index][1] = beamer_1_complex_output_p;
	beamer_1_bb_result_index = (beamer_1_bb_result_index + 3);

	if ((beamer_1_bb_result_index == 9)){ 
		beamer_1_bb_result_index = 1;

	}

	if ((beamer_1_bb_result_index == 10)){ 
		beamer_1_bb_result_index = 2;

	}

	if ((beamer_1_bb_result_index == 11)){ 
		beamer_1_bb_result_index = 0;

	}

}
static inline void beamer_1_correlation ( ) {
	int32_t i;
	int64_t localba [9];
	int64_t localbb [9];
	
	i = 0;

	while (( i < 9 )) {
		localba[i] = beamer_1_complex_ba[i][1];
		localbb[i] = beamer_1_complex_bb[i][1];
		i = (i + 1);

	}

	for(int beamer_1_correlation_i = 0; beamer_1_correlation_i < 9; beamer_1_correlation_i++){
		beamer_1_ch12_buffer[beamer_1_correlation_i] = localba[beamer_1_correlation_i]; //write output 
	}
	*beamer_1_ch12_ready = 0; //channel NOT ready to receive new data
	*beamer_1_ch12_valid = 1; //(because) channel has new data 
	
	for(int beamer_1_correlation_i = 0; beamer_1_correlation_i < 9; beamer_1_correlation_i++){
		beamer_1_ch13_buffer[beamer_1_correlation_i] = localbb[beamer_1_correlation_i]; //write output 
	}
	*beamer_1_ch13_ready = 0; //channel NOT ready to receive new data
	*beamer_1_ch13_valid = 1; //(because) channel has new data 
	
}
static inline void beamer_1_set_cubic_inputs ( ) {
	
	if ((beamer_1_input_state == 1)){ 
		beamer_1_complex_input1_p_pos = beamer_1_complex_p0_pos;

		beamer_1_complex_input1_p_val = beamer_1_complex_p0_val;

		beamer_1_complex_input2_p_pos = beamer_1_complex_p1_pos;

		beamer_1_complex_input2_p_val = beamer_1_complex_p1_val;

		beamer_1_input_state = 2;

	}
	else {
		if ((beamer_1_input_state == 2)){ 
			beamer_1_complex_p01 = beamer_1_complex_output_p;

			beamer_1_complex_input1_p_pos = beamer_1_complex_p1_pos;

			beamer_1_complex_input1_p_val = beamer_1_complex_p1_val;

			beamer_1_complex_input2_p_pos = beamer_1_complex_p2_pos;

			beamer_1_complex_input2_p_val = beamer_1_complex_p2_val;

			beamer_1_input_state = 3;

		}
		else {
			if ((beamer_1_input_state == 3)){ 
				beamer_1_complex_p12 = beamer_1_complex_output_p;

				beamer_1_complex_input1_p_pos = beamer_1_complex_p2_pos;

				beamer_1_complex_input1_p_val = beamer_1_complex_p2_val;

				beamer_1_complex_input2_p_pos = beamer_1_complex_p3_pos;

				beamer_1_complex_input2_p_val = beamer_1_complex_p3_val;

				beamer_1_input_state = 4;

			}
			else {
				if ((beamer_1_input_state == 4)){ 
					beamer_1_complex_p23 = beamer_1_complex_output_p;

					beamer_1_complex_input1_p_pos = beamer_1_complex_p0_pos;

					beamer_1_complex_input1_p_val = beamer_1_complex_p01;

					beamer_1_complex_input2_p_pos = beamer_1_complex_p3_pos;

					beamer_1_complex_input2_p_val = beamer_1_complex_p12;

					beamer_1_input_state = 5;

				}
				else {
					if ((beamer_1_input_state == 5)){ 
						beamer_1_complex_p02 = beamer_1_complex_output_p;

						beamer_1_complex_input1_p_pos = beamer_1_complex_p1_pos;

						beamer_1_complex_input1_p_val = beamer_1_complex_p12;

						beamer_1_complex_input2_p_pos = beamer_1_complex_p3_pos;

						beamer_1_complex_input2_p_val = beamer_1_complex_p23;

						beamer_1_input_state = 6;

					}
					else {
						if ((beamer_1_input_state == 6)){ 
							beamer_1_complex_p13 = beamer_1_complex_output_p;

							beamer_1_complex_input1_p_pos = beamer_1_complex_p0_pos;

							beamer_1_complex_input1_p_val = beamer_1_complex_p02;

							beamer_1_complex_input2_p_pos = beamer_1_complex_p3_pos;

							beamer_1_complex_input2_p_val = beamer_1_complex_p13;

							beamer_1_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_1_set_cubic_inputs_done ( ) {
	
}
static inline void beamer_1___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_1_complex_input1_p_pos, beamer_1_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_1_complex_input2_p_pos, beamer_1_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_1_complex_output_p = outputReg;
}
static inline void beamer_1_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_1_complex_ba[i][0] = beamer_1_complex_ra[i][0];
		beamer_1_complex_bb[i][0] = beamer_1_complex_rb[i][0];
		i = (i + 1);

	}

}
int int_state_vars_beamer_1 = 1;
void initStateVarsbeamer_1() {
beamer_1_beamer_1_State = FSM_beamer_1_state1;

}

int beamer_1(void)
{
  
	//InputPorts
 	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[ch0_size];
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[ch1_size];
	beamer_1_ch0_buffer =  ch0_buffer; 
	beamer_1_ch0_ready = &ch0_ready; 
	beamer_1_ch0_valid = &ch0_valid; 
	beamer_1_ch1_buffer =  ch1_buffer; 
	beamer_1_ch1_ready = &ch1_ready; 
	beamer_1_ch1_valid = &ch1_valid; 

	//OutputPorts
	extern int ch12_ready; 
	extern int ch12_valid; 
	extern uint64_t ch12_buffer[ch12_size];
	extern int ch13_ready; 
	extern int ch13_valid; 
	extern uint64_t ch13_buffer[ch13_size];
	beamer_1_ch12_buffer = ch12_buffer; 
	beamer_1_ch12_ready = &ch12_ready; 
	beamer_1_ch12_valid = &ch12_valid; 
	beamer_1_ch13_buffer = ch13_buffer; 
	beamer_1_ch13_ready = &ch13_ready; 
	beamer_1_ch13_valid = &ch13_valid; 
    
	if(int_state_vars_beamer_1 == 1){
		int_state_vars_beamer_1 = 0;
		initStateVarsbeamer_1();
	}
if ((beamer_1_beamer_1_IntCheckOutput == -1)){ 
	
beamer_1Schedule:

	
 switch (beamer_1_beamer_1_State) {
   case FSM_beamer_1_state1:
     		if (( beamer_1_inputData_index < NOF_PIXELS )){ 
			beamer_1_set_ra_rb_pos();
			beamer_1_beamer_1_State = FSM_beamer_1_state2;

			goto beamer_1Schedule;
		}

		     break;

   case FSM_beamer_1_state2:
     		if (*beamer_1_ch0_valid == 1){ 
							beamer_1_read_ra_val();
				beamer_1_beamer_1_State = FSM_beamer_1_state12;

				goto beamer_1Schedule;

		}

		     break;

   case FSM_beamer_1_state12:
     		if (( beamer_1_beam1_i < 3 )){ 
			beamer_1_beam_int_loop_1();
			beamer_1_beamer_1_State = FSM_beamer_1_state13;

			goto beamer_1Schedule;
		}

					beamer_1_beam_int_loop_1_done();
			beamer_1_beamer_1_State = FSM_beamer_1_state3;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state13:
     		if ((beamer_1_input_state != 0)){ 
			beamer_1_set_cubic_inputs();
			beamer_1_beamer_1_State = FSM_beamer_1_state15;

			goto beamer_1Schedule;
		}

					beamer_1_set_cubic_inputs_done();
			beamer_1_beamer_1_State = FSM_beamer_1_state14;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state14:
     					beamer_1_store_ba_results();
			beamer_1_beamer_1_State = FSM_beamer_1_state12;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state15:
     					beamer_1___acc__cubic();
			beamer_1_beamer_1_State = FSM_beamer_1_state13;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state3:
     		if (*beamer_1_ch1_valid == 1){ 
							beamer_1_read_rb_val();
				beamer_1_beamer_1_State = FSM_beamer_1_state16;

				goto beamer_1Schedule;

		}

		     break;

   case FSM_beamer_1_state16:
     		if (( beamer_1_beam2_i < 3 )){ 
			beamer_1_beam_int_loop_2();
			beamer_1_beamer_1_State = FSM_beamer_1_state17;

			goto beamer_1Schedule;
		}

					beamer_1_beam_int_loop_2_done();
			beamer_1_beamer_1_State = FSM_beamer_1_state11;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state17:
     		if ((beamer_1_input_state != 0)){ 
			beamer_1_set_cubic_inputs();
			beamer_1_beamer_1_State = FSM_beamer_1_state19;

			goto beamer_1Schedule;
		}

					beamer_1_set_cubic_inputs_done();
			beamer_1_beamer_1_State = FSM_beamer_1_state18;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state18:
     					beamer_1_store_bb_results();
			beamer_1_beamer_1_State = FSM_beamer_1_state16;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state19:
     					beamer_1___acc__cubic();
			beamer_1_beamer_1_State = FSM_beamer_1_state17;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state11:
     					beamer_1_set_ba_bb_pos();
			beamer_1_beamer_1_State = FSM_beamer_1_state20;

			goto beamer_1Schedule;

		     break;

   case FSM_beamer_1_state20:
     					
beamer_1_Action_0:

			if ((*beamer_1_ch12_ready == 1 && *beamer_1_ch13_ready == 1)){ 
				beamer_1_correlation();
				beamer_1_beamer_1_State = FSM_beamer_1_state1;

				goto beamer_1Schedule;
			}
			else {
				beamer_1_beamer_1_IntCheckOutput = 0;

				return(0);
			}


		     break;

}

	beamer_1_beamer_1_IntCheckOutput = -1;

}
else {
	
 switch (beamer_1_beamer_1_IntCheckOutput) {
   case 0:
     		beamer_1_beamer_1_IntCheckOutput = -1;

		goto beamer_1_Action_0;
}

}
goto beamer_1Schedule;
}
