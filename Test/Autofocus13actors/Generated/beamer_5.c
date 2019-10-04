//code from beam_actor.cal, instance beamer_5
#include <stdint.h>
#include <string.h>
#include "beamer_5.h"
#include "common.h"

//InputPorts
uint64_t* beamer_5_ch8_buffer SECTION(".core10.data");
uint64_t* beamer_5_ch9_buffer SECTION(".core10.data");
volatile int* beamer_5_ch8_ready SECTION(".core10.data");
volatile int* beamer_5_ch8_valid SECTION(".core10.data");
volatile int* beamer_5_ch9_ready SECTION(".core10.data");
volatile int* beamer_5_ch9_valid SECTION(".core10.data");

//OutputPorts
uint64_t* beamer_5_ch20_buffer SECTION(".core10.data");
uint64_t* beamer_5_ch21_buffer SECTION(".core10.data");
volatile int* beamer_5_ch20_ready SECTION(".core10.data");
volatile int* beamer_5_ch20_valid SECTION(".core10.data");
volatile int* beamer_5_ch21_ready SECTION(".core10.data");
volatile int* beamer_5_ch21_valid SECTION(".core10.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t beamer_5_complex_p0_pos SECTION(".core10.data");
int64_t beamer_5_complex_p0_val SECTION(".core10.data");
int64_t beamer_5_complex_p1_pos SECTION(".core10.data");
int64_t beamer_5_complex_p1_val SECTION(".core10.data");
int64_t beamer_5_complex_p2_pos SECTION(".core10.data");
int64_t beamer_5_complex_p2_val SECTION(".core10.data");
int64_t beamer_5_complex_p3_pos SECTION(".core10.data");
int64_t beamer_5_complex_p3_val SECTION(".core10.data");
int64_t beamer_5_complex_p01 SECTION(".core10.data");
int64_t beamer_5_complex_p12 SECTION(".core10.data");
int64_t beamer_5_complex_p23 SECTION(".core10.data");
int64_t beamer_5_complex_p02 SECTION(".core10.data");
int64_t beamer_5_complex_p13 SECTION(".core10.data");
int64_t beamer_5_complex_input1_p_pos SECTION(".core10.data");
int64_t beamer_5_complex_input1_p_val SECTION(".core10.data");
int64_t beamer_5_complex_input2_p_pos SECTION(".core10.data");
int64_t beamer_5_complex_input2_p_val SECTION(".core10.data");
int64_t beamer_5_complex_output_p SECTION(".core10.data");
int32_t beamer_5_input_state SECTION(".core10.data");
int32_t beamer_5_beam1_i SECTION(".core10.data") = 0;
int32_t beamer_5_beam1_counter SECTION(".core10.data") = 0;
int32_t beamer_5_beam2_i SECTION(".core10.data") = 0;
int32_t beamer_5_beam2_counter SECTION(".core10.data") = 0;
int32_t beamer_5_ba_result_index SECTION(".core10.data") = 0;
int32_t beamer_5_bb_result_index SECTION(".core10.data") = 0;
int32_t beamer_5_inputData_index SECTION(".core10.data") = 0;
int32_t beamer_5_ra_val_counter SECTION(".core10.data") = 0;
int32_t beamer_5_rb_val_counter SECTION(".core10.data") = 0;
int64_t beamer_5_complex_ra[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core10.data");

int64_t beamer_5_complex_rb[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core10.data");

int64_t beamer_5_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core10.data");

int64_t beamer_5_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core10.data");

int32_t beamer_5_beamer_5_State SECTION(".core10.data");
#define FSM_beamer_5_state1 (0) 
#define FSM_beamer_5_state2 (1) 
#define FSM_beamer_5_state12 (2) 
#define FSM_beamer_5_state13 (3) 
#define FSM_beamer_5_state14 (4) 
#define FSM_beamer_5_state15 (5) 
#define FSM_beamer_5_state3 (6) 
#define FSM_beamer_5_state16 (7) 
#define FSM_beamer_5_state17 (8) 
#define FSM_beamer_5_state18 (9) 
#define FSM_beamer_5_state19 (10) 
#define FSM_beamer_5_state11 (11) 
#define FSM_beamer_5_state20 (12) 
int32_t beamer_5_beamer_5_IntCheckOutput SECTION(".core10.data") = -1;
int beamer_5_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void beamer_5_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_5_complex_rb[i][0] = 1;
		beamer_5_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_5_inputData_index = (beamer_5_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_5_read_ra_val ( ) {
	int64_t ra_val;
	while(*beamer_5_ch8_valid == 0);//Blocking read
	ra_val = *beamer_5_ch8_buffer; //read input 
	*beamer_5_ch8_ready = 1; // channel ready to receive new data
	*beamer_5_ch8_valid = 0; // no valid input left on the channel
	
	beamer_5_complex_ra[beamer_5_ra_val_counter][1] = ra_val;
	beamer_5_ra_val_counter = (beamer_5_ra_val_counter + 1);

}
static inline void beamer_5_read_ra_val_done ( ) {
	beamer_5_ra_val_counter = 0;

	beamer_5_beam1_i = 0;

	beamer_5_beam2_i = 0;

}
static inline void beamer_5_read_rb_val ( ) {
	int64_t rb_val;
	while(*beamer_5_ch9_valid == 0);//Blocking read
	rb_val = *beamer_5_ch9_buffer; //read input 
	*beamer_5_ch9_ready = 1; // channel ready to receive new data
	*beamer_5_ch9_valid = 0; // no valid input left on the channel
	
	beamer_5_complex_rb[beamer_5_rb_val_counter][1] = rb_val;
	beamer_5_rb_val_counter = (beamer_5_rb_val_counter + 1);

}
static inline void beamer_5_read_rb_val_done ( ) {
	beamer_5_rb_val_counter = 0;

}
static inline void beamer_5_beam_int_loop_1 ( ) {
	
	beamer_5_complex_p0_pos = beamer_5_complex_ra[beamer_5_beam1_i + beamer_5_beam1_counter + 0][0];

	beamer_5_complex_p1_pos = beamer_5_complex_ra[beamer_5_beam1_i + beamer_5_beam1_counter + 3][0];

	beamer_5_complex_p2_pos = beamer_5_complex_ra[beamer_5_beam1_i + beamer_5_beam1_counter + 6][0];

	beamer_5_complex_p3_pos = beamer_5_complex_ra[beamer_5_beam1_i + beamer_5_beam1_counter + 9][0];

	beamer_5_input_state = 1;

	beamer_5_beam1_counter = (beamer_5_beam1_counter + 3);

	if ((beamer_5_beam1_counter == 9)){ 
		beamer_5_beam1_counter = 0;

		beamer_5_beam1_i = (beamer_5_beam1_i + 1);

	}

}
static inline void beamer_5_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_5_beam_int_loop_2 ( ) {
	
	beamer_5_complex_p0_pos = beamer_5_complex_rb[beamer_5_beam2_i + beamer_5_beam2_counter + 0][0];

	beamer_5_complex_p1_pos = beamer_5_complex_rb[beamer_5_beam2_i + beamer_5_beam2_counter + 3][0];

	beamer_5_complex_p2_pos = beamer_5_complex_rb[beamer_5_beam2_i + beamer_5_beam2_counter + 6][0];

	beamer_5_complex_p3_pos = beamer_5_complex_rb[beamer_5_beam2_i + beamer_5_beam2_counter + 9][0];

	beamer_5_input_state = 1;

	beamer_5_beam2_counter = (beamer_5_beam2_counter + 3);

	if ((beamer_5_beam2_counter == 9)){ 
		beamer_5_beam2_counter = 0;

		beamer_5_beam2_i = (beamer_5_beam2_i + 1);

	}

}
static inline void beamer_5_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_5_store_ba_results ( ) {
	
	beamer_5_complex_ba[beamer_5_ba_result_index][1] = beamer_5_complex_output_p;
	beamer_5_ba_result_index = (beamer_5_ba_result_index + 3);

	if ((beamer_5_ba_result_index == 9)){ 
		beamer_5_ba_result_index = 1;

	}

	if ((beamer_5_ba_result_index == 10)){ 
		beamer_5_ba_result_index = 2;

	}

	if ((beamer_5_ba_result_index == 11)){ 
		beamer_5_ba_result_index = 0;

	}

}
static inline void beamer_5_store_bb_results ( ) {
	
	beamer_5_complex_bb[beamer_5_bb_result_index][1] = beamer_5_complex_output_p;
	beamer_5_bb_result_index = (beamer_5_bb_result_index + 3);

	if ((beamer_5_bb_result_index == 9)){ 
		beamer_5_bb_result_index = 1;

	}

	if ((beamer_5_bb_result_index == 10)){ 
		beamer_5_bb_result_index = 2;

	}

	if ((beamer_5_bb_result_index == 11)){ 
		beamer_5_bb_result_index = 0;

	}

}
static inline void beamer_5_correlation ( ) {
	int32_t i;
	int64_t localba [9];
	int64_t localbb [9];
	
	i = 0;

	while (( i < 9 )) {
		localba[i] = beamer_5_complex_ba[i][1];
		localbb[i] = beamer_5_complex_bb[i][1];
		i = (i + 1);

	}

	while(*beamer_5_ch20_ready == 0);// Wait for the ready signal. 
	for(int beamer_5_correlation_i = 0; beamer_5_correlation_i < 9; beamer_5_correlation_i++){
		beamer_5_ch20_buffer[beamer_5_correlation_i] = localba[beamer_5_correlation_i]; //write output 
	}
	*beamer_5_ch20_ready = 0; //channel NOT ready to receive new data
	*beamer_5_ch20_valid = 1; //(because) channel has new data 
	
	while(*beamer_5_ch21_ready == 0);// Wait for the ready signal. 
	for(int beamer_5_correlation_i = 0; beamer_5_correlation_i < 9; beamer_5_correlation_i++){
		beamer_5_ch21_buffer[beamer_5_correlation_i] = localbb[beamer_5_correlation_i]; //write output 
	}
	*beamer_5_ch21_ready = 0; //channel NOT ready to receive new data
	*beamer_5_ch21_valid = 1; //(because) channel has new data 
	
}
static inline void beamer_5_set_cubic_inputs ( ) {
	
	if ((beamer_5_input_state == 1)){ 
		beamer_5_complex_input1_p_pos = beamer_5_complex_p0_pos;

		beamer_5_complex_input1_p_val = beamer_5_complex_p0_val;

		beamer_5_complex_input2_p_pos = beamer_5_complex_p1_pos;

		beamer_5_complex_input2_p_val = beamer_5_complex_p1_val;

		beamer_5_input_state = 2;

	}
	else {
		if ((beamer_5_input_state == 2)){ 
			beamer_5_complex_p01 = beamer_5_complex_output_p;

			beamer_5_complex_input1_p_pos = beamer_5_complex_p1_pos;

			beamer_5_complex_input1_p_val = beamer_5_complex_p1_val;

			beamer_5_complex_input2_p_pos = beamer_5_complex_p2_pos;

			beamer_5_complex_input2_p_val = beamer_5_complex_p2_val;

			beamer_5_input_state = 3;

		}
		else {
			if ((beamer_5_input_state == 3)){ 
				beamer_5_complex_p12 = beamer_5_complex_output_p;

				beamer_5_complex_input1_p_pos = beamer_5_complex_p2_pos;

				beamer_5_complex_input1_p_val = beamer_5_complex_p2_val;

				beamer_5_complex_input2_p_pos = beamer_5_complex_p3_pos;

				beamer_5_complex_input2_p_val = beamer_5_complex_p3_val;

				beamer_5_input_state = 4;

			}
			else {
				if ((beamer_5_input_state == 4)){ 
					beamer_5_complex_p23 = beamer_5_complex_output_p;

					beamer_5_complex_input1_p_pos = beamer_5_complex_p0_pos;

					beamer_5_complex_input1_p_val = beamer_5_complex_p01;

					beamer_5_complex_input2_p_pos = beamer_5_complex_p3_pos;

					beamer_5_complex_input2_p_val = beamer_5_complex_p12;

					beamer_5_input_state = 5;

				}
				else {
					if ((beamer_5_input_state == 5)){ 
						beamer_5_complex_p02 = beamer_5_complex_output_p;

						beamer_5_complex_input1_p_pos = beamer_5_complex_p1_pos;

						beamer_5_complex_input1_p_val = beamer_5_complex_p12;

						beamer_5_complex_input2_p_pos = beamer_5_complex_p3_pos;

						beamer_5_complex_input2_p_val = beamer_5_complex_p23;

						beamer_5_input_state = 6;

					}
					else {
						if ((beamer_5_input_state == 6)){ 
							beamer_5_complex_p13 = beamer_5_complex_output_p;

							beamer_5_complex_input1_p_pos = beamer_5_complex_p0_pos;

							beamer_5_complex_input1_p_val = beamer_5_complex_p02;

							beamer_5_complex_input2_p_pos = beamer_5_complex_p3_pos;

							beamer_5_complex_input2_p_val = beamer_5_complex_p13;

							beamer_5_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_5_set_cubic_inputs_done ( ) {
	
}
static inline void beamer_5___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_5_complex_input1_p_pos, beamer_5_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_5_complex_input2_p_pos, beamer_5_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_5_complex_output_p = outputReg;
}
static inline void beamer_5_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_5_complex_ba[i][0] = beamer_5_complex_ra[i][0];
		beamer_5_complex_bb[i][0] = beamer_5_complex_rb[i][0];
		i = (i + 1);

	}

}
int int_state_vars_beamer_5 SECTION(".core10.data") = 1;
void initStateVarsbeamer_5() {
	beamer_5_beamer_5_State = FSM_beamer_5_state1;

}

int beamer_5(void)
{
  
	//InputPorts
 	extern int ch8_ready; 
	extern int ch8_valid; 
	extern uint64_t ch8_buffer[ch8_size];
	extern int ch9_ready; 
	extern int ch9_valid; 
	extern uint64_t ch9_buffer[ch9_size];
	beamer_5_ch8_buffer =  ch8_buffer; 
	beamer_5_ch8_ready = &ch8_ready; 
	beamer_5_ch8_valid = &ch8_valid; 
	beamer_5_ch9_buffer =  ch9_buffer; 
	beamer_5_ch9_ready = &ch9_ready; 
	beamer_5_ch9_valid = &ch9_valid; 

	//OutputPorts
	extern int ch20_ready; 
	extern int ch20_valid; 
	extern uint64_t ch20_buffer[ch20_size];
	extern int ch21_ready; 
	extern int ch21_valid; 
	extern uint64_t ch21_buffer[ch21_size];
	beamer_5_ch20_buffer = ch20_buffer; 
	beamer_5_ch20_ready = &ch20_ready; 
	beamer_5_ch20_valid = &ch20_valid; 
	beamer_5_ch21_buffer = ch21_buffer; 
	beamer_5_ch21_ready = &ch21_ready; 
	beamer_5_ch21_valid = &ch21_valid; 
    
	if(int_state_vars_beamer_5 == 1){
		int_state_vars_beamer_5 = 0;
		initStateVarsbeamer_5();
	}
if ((beamer_5_beamer_5_IntCheckOutput == -1)){ 
	
beamer_5Schedule:

	
 switch (beamer_5_beamer_5_State) {
   case FSM_beamer_5_state1:
     		if (( beamer_5_inputData_index < NOF_PIXELS )){ 
			beamer_5_set_ra_rb_pos();
			beamer_5_beamer_5_State = FSM_beamer_5_state2;

			goto beamer_5Schedule;
		}

		     break;

   case FSM_beamer_5_state2:
     		if (1){ 
			if (( beamer_5_ra_val_counter < 18 )){ 
				beamer_5_read_ra_val();
				beamer_5_beamer_5_State = FSM_beamer_5_state2;

				goto beamer_5Schedule;
			}

		}

					beamer_5_read_ra_val_done();
			beamer_5_beamer_5_State = FSM_beamer_5_state12;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state12:
     		if (( beamer_5_beam1_i < 3 )){ 
			beamer_5_beam_int_loop_1();
			beamer_5_beamer_5_State = FSM_beamer_5_state13;

			goto beamer_5Schedule;
		}

					beamer_5_beam_int_loop_1_done();
			beamer_5_beamer_5_State = FSM_beamer_5_state3;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state13:
     		if ((beamer_5_input_state != 0)){ 
			beamer_5_set_cubic_inputs();
			beamer_5_beamer_5_State = FSM_beamer_5_state15;

			goto beamer_5Schedule;
		}

					beamer_5_set_cubic_inputs_done();
			beamer_5_beamer_5_State = FSM_beamer_5_state14;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state14:
     					beamer_5_store_ba_results();
			beamer_5_beamer_5_State = FSM_beamer_5_state12;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state15:
     					beamer_5___acc__cubic();
			beamer_5_beamer_5_State = FSM_beamer_5_state13;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state3:
     		if (1){ 
			if (( beamer_5_rb_val_counter < 18 )){ 
				beamer_5_read_rb_val();
				beamer_5_beamer_5_State = FSM_beamer_5_state3;

				goto beamer_5Schedule;
			}

		}

					beamer_5_read_rb_val_done();
			beamer_5_beamer_5_State = FSM_beamer_5_state16;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state16:
     		if (( beamer_5_beam2_i < 3 )){ 
			beamer_5_beam_int_loop_2();
			beamer_5_beamer_5_State = FSM_beamer_5_state17;

			goto beamer_5Schedule;
		}

					beamer_5_beam_int_loop_2_done();
			beamer_5_beamer_5_State = FSM_beamer_5_state11;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state17:
     		if ((beamer_5_input_state != 0)){ 
			beamer_5_set_cubic_inputs();
			beamer_5_beamer_5_State = FSM_beamer_5_state19;

			goto beamer_5Schedule;
		}

					beamer_5_set_cubic_inputs_done();
			beamer_5_beamer_5_State = FSM_beamer_5_state18;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state18:
     					beamer_5_store_bb_results();
			beamer_5_beamer_5_State = FSM_beamer_5_state16;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state19:
     					beamer_5___acc__cubic();
			beamer_5_beamer_5_State = FSM_beamer_5_state17;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state11:
     					beamer_5_set_ba_bb_pos();
			beamer_5_beamer_5_State = FSM_beamer_5_state20;

			goto beamer_5Schedule;

		     break;

   case FSM_beamer_5_state20:
     					
beamer_5_Action_0:

			if ((1 && 1)){ 
				beamer_5_correlation();
				beamer_5_beamer_5_State = FSM_beamer_5_state1;

				goto beamer_5Schedule;
			}
			else {
				beamer_5_beamer_5_IntCheckOutput = 0;

				return(0);
			}


		     break;

}

	beamer_5_beamer_5_IntCheckOutput = -1;

}
else {
	
 switch (beamer_5_beamer_5_IntCheckOutput) {
   case 0:
     		beamer_5_beamer_5_IntCheckOutput = -1;

		goto beamer_5_Action_0;
}

}
goto beamer_5Schedule;
}
