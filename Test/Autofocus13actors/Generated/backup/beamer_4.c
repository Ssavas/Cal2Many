//code from beam_actor.cal, instance beamer_4
#include <stdint.h>
#include <string.h>
#include "beamer_4.h"
#include "common.h"

//InputPorts
uint64_t* beamer_4_ch6_buffer SECTION(".core9.data");
uint64_t* beamer_4_ch7_buffer SECTION(".core9.data");
int* beamer_4_ch6_ready SECTION(".core9.data");
int* beamer_4_ch6_valid SECTION(".core9.data");
int* beamer_4_ch7_ready SECTION(".core9.data");
int* beamer_4_ch7_valid SECTION(".core9.data");

//OutputPorts
uint64_t* beamer_4_ch18_buffer SECTION(".core9.data");
uint64_t* beamer_4_ch19_buffer SECTION(".core9.data");
int* beamer_4_ch18_ready SECTION(".core9.data");
int* beamer_4_ch18_valid SECTION(".core9.data");
int* beamer_4_ch19_ready SECTION(".core9.data");
int* beamer_4_ch19_valid SECTION(".core9.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t beamer_4_complex_p0_pos SECTION(".core9.data");
int64_t beamer_4_complex_p0_val SECTION(".core9.data");
int64_t beamer_4_complex_p1_pos SECTION(".core9.data");
int64_t beamer_4_complex_p1_val SECTION(".core9.data");
int64_t beamer_4_complex_p2_pos SECTION(".core9.data");
int64_t beamer_4_complex_p2_val SECTION(".core9.data");
int64_t beamer_4_complex_p3_pos SECTION(".core9.data");
int64_t beamer_4_complex_p3_val SECTION(".core9.data");
int64_t beamer_4_complex_p01 SECTION(".core9.data");
int64_t beamer_4_complex_p12 SECTION(".core9.data");
int64_t beamer_4_complex_p23 SECTION(".core9.data");
int64_t beamer_4_complex_p02 SECTION(".core9.data");
int64_t beamer_4_complex_p13 SECTION(".core9.data");
int64_t beamer_4_complex_input1_p_pos SECTION(".core9.data");
int64_t beamer_4_complex_input1_p_val SECTION(".core9.data");
int64_t beamer_4_complex_input2_p_pos SECTION(".core9.data");
int64_t beamer_4_complex_input2_p_val SECTION(".core9.data");
int64_t beamer_4_complex_output_p SECTION(".core9.data");
int32_t beamer_4_input_state SECTION(".core9.data");
int32_t beamer_4_beam1_i SECTION(".core9.data") = 0;
int32_t beamer_4_beam1_counter SECTION(".core9.data") = 0;
int32_t beamer_4_beam2_i SECTION(".core9.data") = 0;
int32_t beamer_4_beam2_counter SECTION(".core9.data") = 0;
int32_t beamer_4_ba_result_index SECTION(".core9.data") = 0;
int32_t beamer_4_bb_result_index SECTION(".core9.data") = 0;
int32_t beamer_4_inputData_index SECTION(".core9.data") = 0;
int64_t beamer_4_complex_ra[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core9.data");

int64_t beamer_4_complex_rb[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core9.data");

int64_t beamer_4_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core9.data");

int64_t beamer_4_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core9.data");

int32_t beamer_4_beamer_4_State SECTION(".core9.data");
#define FSM_beamer_4_state1 (0) 
#define FSM_beamer_4_state2 (1) 
#define FSM_beamer_4_state12 (2) 
#define FSM_beamer_4_state13 (3) 
#define FSM_beamer_4_state14 (4) 
#define FSM_beamer_4_state15 (5) 
#define FSM_beamer_4_state3 (6) 
#define FSM_beamer_4_state16 (7) 
#define FSM_beamer_4_state17 (8) 
#define FSM_beamer_4_state18 (9) 
#define FSM_beamer_4_state19 (10) 
#define FSM_beamer_4_state11 (11) 
#define FSM_beamer_4_state20 (12) 
int32_t beamer_4_beamer_4_IntCheckOutput SECTION(".core9.data") = -1;

static inline void beamer_4_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_4_complex_rb[i][0] = 1;
		beamer_4_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_4_inputData_index = (beamer_4_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_4_read_ra_val ( ) {
	int32_t i;
	int64_t ra_val [18];
	for(int beamer_4_read_ra_val_i = 0; beamer_4_read_ra_val_i < 18; beamer_4_read_ra_val_i++){
		ra_val[beamer_4_read_ra_val_i] = beamer_4_ch6_buffer[beamer_4_read_ra_val_i]; //read input 
	}
	*beamer_4_ch6_ready = 1; // channel ready to receive new data
	*beamer_4_ch6_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_4_complex_ra[i][1] = ra_val[i];
		i = (i + 1);

	}

	beamer_4_beam1_i = 0;

	beamer_4_beam2_i = 0;

}
static inline void beamer_4_read_rb_val ( ) {
	int32_t i;
	int64_t rb_val [18];
	for(int beamer_4_read_rb_val_i = 0; beamer_4_read_rb_val_i < 18; beamer_4_read_rb_val_i++){
		rb_val[beamer_4_read_rb_val_i] = beamer_4_ch7_buffer[beamer_4_read_rb_val_i]; //read input 
	}
	*beamer_4_ch7_ready = 1; // channel ready to receive new data
	*beamer_4_ch7_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 18 )) {
		beamer_4_complex_rb[i][1] = rb_val[i];
		i = (i + 1);

	}

}
static inline void beamer_4_beam_int_loop_1 ( ) {
	
	beamer_4_complex_p0_pos = beamer_4_complex_ra[beamer_4_beam1_i + beamer_4_beam1_counter + 0][0];

	beamer_4_complex_p1_pos = beamer_4_complex_ra[beamer_4_beam1_i + beamer_4_beam1_counter + 3][0];

	beamer_4_complex_p2_pos = beamer_4_complex_ra[beamer_4_beam1_i + beamer_4_beam1_counter + 6][0];

	beamer_4_complex_p3_pos = beamer_4_complex_ra[beamer_4_beam1_i + beamer_4_beam1_counter + 9][0];

	beamer_4_input_state = 1;

	beamer_4_beam1_counter = (beamer_4_beam1_counter + 3);

	if ((beamer_4_beam1_counter == 9)){ 
		beamer_4_beam1_counter = 0;

		beamer_4_beam1_i = (beamer_4_beam1_i + 1);

	}

}
static inline void beamer_4_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_4_beam_int_loop_2 ( ) {
	
	beamer_4_complex_p0_pos = beamer_4_complex_rb[beamer_4_beam2_i + beamer_4_beam2_counter + 0][0];

	beamer_4_complex_p1_pos = beamer_4_complex_rb[beamer_4_beam2_i + beamer_4_beam2_counter + 3][0];

	beamer_4_complex_p2_pos = beamer_4_complex_rb[beamer_4_beam2_i + beamer_4_beam2_counter + 6][0];

	beamer_4_complex_p3_pos = beamer_4_complex_rb[beamer_4_beam2_i + beamer_4_beam2_counter + 9][0];

	beamer_4_input_state = 1;

	beamer_4_beam2_counter = (beamer_4_beam2_counter + 3);

	if ((beamer_4_beam2_counter == 9)){ 
		beamer_4_beam2_counter = 0;

		beamer_4_beam2_i = (beamer_4_beam2_i + 1);

	}

}
static inline void beamer_4_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_4_store_ba_results ( ) {
	
	beamer_4_complex_ba[beamer_4_ba_result_index][1] = beamer_4_complex_output_p;
	beamer_4_ba_result_index = (beamer_4_ba_result_index + 3);

	if ((beamer_4_ba_result_index == 9)){ 
		beamer_4_ba_result_index = 1;

	}

	if ((beamer_4_ba_result_index == 10)){ 
		beamer_4_ba_result_index = 2;

	}

	if ((beamer_4_ba_result_index == 11)){ 
		beamer_4_ba_result_index = 0;

	}

}
static inline void beamer_4_store_bb_results ( ) {
	
	beamer_4_complex_bb[beamer_4_bb_result_index][1] = beamer_4_complex_output_p;
	beamer_4_bb_result_index = (beamer_4_bb_result_index + 3);

	if ((beamer_4_bb_result_index == 9)){ 
		beamer_4_bb_result_index = 1;

	}

	if ((beamer_4_bb_result_index == 10)){ 
		beamer_4_bb_result_index = 2;

	}

	if ((beamer_4_bb_result_index == 11)){ 
		beamer_4_bb_result_index = 0;

	}

}
static inline void beamer_4_correlation ( ) {
	int32_t i;
	int64_t localba [9];
	int64_t localbb [9];
	
	i = 0;

	while (( i < 9 )) {
		localba[i] = beamer_4_complex_ba[i][1];
		localbb[i] = beamer_4_complex_bb[i][1];
		i = (i + 1);

	}

	for(int beamer_4_correlation_i = 0; beamer_4_correlation_i < 9; beamer_4_correlation_i++){
		beamer_4_ch18_buffer[beamer_4_correlation_i] = localba[beamer_4_correlation_i]; //write output 
	}
	*beamer_4_ch18_ready = 0; //channel NOT ready to receive new data
	*beamer_4_ch18_valid = 1; //(because) channel has new data 
	
	for(int beamer_4_correlation_i = 0; beamer_4_correlation_i < 9; beamer_4_correlation_i++){
		beamer_4_ch19_buffer[beamer_4_correlation_i] = localbb[beamer_4_correlation_i]; //write output 
	}
	*beamer_4_ch19_ready = 0; //channel NOT ready to receive new data
	*beamer_4_ch19_valid = 1; //(because) channel has new data 
	
}
static inline void beamer_4_set_cubic_inputs ( ) {
	
	if ((beamer_4_input_state == 1)){ 
		beamer_4_complex_input1_p_pos = beamer_4_complex_p0_pos;

		beamer_4_complex_input1_p_val = beamer_4_complex_p0_val;

		beamer_4_complex_input2_p_pos = beamer_4_complex_p1_pos;

		beamer_4_complex_input2_p_val = beamer_4_complex_p1_val;

		beamer_4_input_state = 2;

	}
	else {
		if ((beamer_4_input_state == 2)){ 
			beamer_4_complex_p01 = beamer_4_complex_output_p;

			beamer_4_complex_input1_p_pos = beamer_4_complex_p1_pos;

			beamer_4_complex_input1_p_val = beamer_4_complex_p1_val;

			beamer_4_complex_input2_p_pos = beamer_4_complex_p2_pos;

			beamer_4_complex_input2_p_val = beamer_4_complex_p2_val;

			beamer_4_input_state = 3;

		}
		else {
			if ((beamer_4_input_state == 3)){ 
				beamer_4_complex_p12 = beamer_4_complex_output_p;

				beamer_4_complex_input1_p_pos = beamer_4_complex_p2_pos;

				beamer_4_complex_input1_p_val = beamer_4_complex_p2_val;

				beamer_4_complex_input2_p_pos = beamer_4_complex_p3_pos;

				beamer_4_complex_input2_p_val = beamer_4_complex_p3_val;

				beamer_4_input_state = 4;

			}
			else {
				if ((beamer_4_input_state == 4)){ 
					beamer_4_complex_p23 = beamer_4_complex_output_p;

					beamer_4_complex_input1_p_pos = beamer_4_complex_p0_pos;

					beamer_4_complex_input1_p_val = beamer_4_complex_p01;

					beamer_4_complex_input2_p_pos = beamer_4_complex_p3_pos;

					beamer_4_complex_input2_p_val = beamer_4_complex_p12;

					beamer_4_input_state = 5;

				}
				else {
					if ((beamer_4_input_state == 5)){ 
						beamer_4_complex_p02 = beamer_4_complex_output_p;

						beamer_4_complex_input1_p_pos = beamer_4_complex_p1_pos;

						beamer_4_complex_input1_p_val = beamer_4_complex_p12;

						beamer_4_complex_input2_p_pos = beamer_4_complex_p3_pos;

						beamer_4_complex_input2_p_val = beamer_4_complex_p23;

						beamer_4_input_state = 6;

					}
					else {
						if ((beamer_4_input_state == 6)){ 
							beamer_4_complex_p13 = beamer_4_complex_output_p;

							beamer_4_complex_input1_p_pos = beamer_4_complex_p0_pos;

							beamer_4_complex_input1_p_val = beamer_4_complex_p02;

							beamer_4_complex_input2_p_pos = beamer_4_complex_p3_pos;

							beamer_4_complex_input2_p_val = beamer_4_complex_p13;

							beamer_4_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_4_set_cubic_inputs_done ( ) {
	
}
static inline void beamer_4___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_4_complex_input1_p_pos, beamer_4_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_4_complex_input2_p_pos, beamer_4_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_4_complex_output_p = outputReg;
}
static inline void beamer_4_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_4_complex_ba[i][0] = beamer_4_complex_ra[i][0];
		beamer_4_complex_bb[i][0] = beamer_4_complex_rb[i][0];
		i = (i + 1);

	}

}
int int_state_vars_beamer_4 = 1;
void initStateVarsbeamer_4() {
beamer_4_beamer_4_State = FSM_beamer_4_state1;

}

int beamer_4(void)
{
  
	//InputPorts
 	extern int ch6_ready; 
	extern int ch6_valid; 
	extern uint64_t ch6_buffer[ch6_size];
	extern int ch7_ready; 
	extern int ch7_valid; 
	extern uint64_t ch7_buffer[ch7_size];
	beamer_4_ch6_buffer =  ch6_buffer; 
	beamer_4_ch6_ready = &ch6_ready; 
	beamer_4_ch6_valid = &ch6_valid; 
	beamer_4_ch7_buffer =  ch7_buffer; 
	beamer_4_ch7_ready = &ch7_ready; 
	beamer_4_ch7_valid = &ch7_valid; 

	//OutputPorts
	extern int ch18_ready; 
	extern int ch18_valid; 
	extern uint64_t ch18_buffer[ch18_size];
	extern int ch19_ready; 
	extern int ch19_valid; 
	extern uint64_t ch19_buffer[ch19_size];
	beamer_4_ch18_buffer = ch18_buffer; 
	beamer_4_ch18_ready = &ch18_ready; 
	beamer_4_ch18_valid = &ch18_valid; 
	beamer_4_ch19_buffer = ch19_buffer; 
	beamer_4_ch19_ready = &ch19_ready; 
	beamer_4_ch19_valid = &ch19_valid; 
    
	if(int_state_vars_beamer_4 == 1){
		int_state_vars_beamer_4 = 0;
		initStateVarsbeamer_4();
	}
if ((beamer_4_beamer_4_IntCheckOutput == -1)){ 
	
beamer_4Schedule:

	
 switch (beamer_4_beamer_4_State) {
   case FSM_beamer_4_state1:
     		if (( beamer_4_inputData_index < NOF_PIXELS )){ 
			beamer_4_set_ra_rb_pos();
			beamer_4_beamer_4_State = FSM_beamer_4_state2;

			goto beamer_4Schedule;
		}

		     break;

   case FSM_beamer_4_state2:
     		if (*beamer_4_ch6_valid == 1){ 
							beamer_4_read_ra_val();
				beamer_4_beamer_4_State = FSM_beamer_4_state12;

				goto beamer_4Schedule;

		}

		     break;

   case FSM_beamer_4_state12:
     		if (( beamer_4_beam1_i < 3 )){ 
			beamer_4_beam_int_loop_1();
			beamer_4_beamer_4_State = FSM_beamer_4_state13;

			goto beamer_4Schedule;
		}

					beamer_4_beam_int_loop_1_done();
			beamer_4_beamer_4_State = FSM_beamer_4_state3;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state13:
     		if ((beamer_4_input_state != 0)){ 
			beamer_4_set_cubic_inputs();
			beamer_4_beamer_4_State = FSM_beamer_4_state15;

			goto beamer_4Schedule;
		}

					beamer_4_set_cubic_inputs_done();
			beamer_4_beamer_4_State = FSM_beamer_4_state14;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state14:
     					beamer_4_store_ba_results();
			beamer_4_beamer_4_State = FSM_beamer_4_state12;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state15:
     					beamer_4___acc__cubic();
			beamer_4_beamer_4_State = FSM_beamer_4_state13;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state3:
     		if (*beamer_4_ch7_valid == 1){ 
							beamer_4_read_rb_val();
				beamer_4_beamer_4_State = FSM_beamer_4_state16;

				goto beamer_4Schedule;

		}

		     break;

   case FSM_beamer_4_state16:
     		if (( beamer_4_beam2_i < 3 )){ 
			beamer_4_beam_int_loop_2();
			beamer_4_beamer_4_State = FSM_beamer_4_state17;

			goto beamer_4Schedule;
		}

					beamer_4_beam_int_loop_2_done();
			beamer_4_beamer_4_State = FSM_beamer_4_state11;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state17:
     		if ((beamer_4_input_state != 0)){ 
			beamer_4_set_cubic_inputs();
			beamer_4_beamer_4_State = FSM_beamer_4_state19;

			goto beamer_4Schedule;
		}

					beamer_4_set_cubic_inputs_done();
			beamer_4_beamer_4_State = FSM_beamer_4_state18;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state18:
     					beamer_4_store_bb_results();
			beamer_4_beamer_4_State = FSM_beamer_4_state16;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state19:
     					beamer_4___acc__cubic();
			beamer_4_beamer_4_State = FSM_beamer_4_state17;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state11:
     					beamer_4_set_ba_bb_pos();
			beamer_4_beamer_4_State = FSM_beamer_4_state20;

			goto beamer_4Schedule;

		     break;

   case FSM_beamer_4_state20:
     					
beamer_4_Action_0:

			if ((*beamer_4_ch18_ready == 1 && *beamer_4_ch19_ready == 1)){ 
				beamer_4_correlation();
				beamer_4_beamer_4_State = FSM_beamer_4_state1;

				goto beamer_4Schedule;
			}
			else {
				beamer_4_beamer_4_IntCheckOutput = 0;

				return(0);
			}


		     break;

}

	beamer_4_beamer_4_IntCheckOutput = -1;

}
else {
	
 switch (beamer_4_beamer_4_IntCheckOutput) {
   case 0:
     		beamer_4_beamer_4_IntCheckOutput = -1;

		goto beamer_4_Action_0;
}

}
goto beamer_4Schedule;
}
