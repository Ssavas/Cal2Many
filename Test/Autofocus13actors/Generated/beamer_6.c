//code from beam_actor.cal, instance beamer_6
#include <stdint.h>
#include <string.h>
#include "beamer_6.h"
#include "common.h"

//InputPorts
uint64_t* beamer_6_ch10_buffer SECTION(".core11.data");
uint64_t* beamer_6_ch11_buffer SECTION(".core11.data");
volatile int* beamer_6_ch10_ready SECTION(".core11.data");
volatile int* beamer_6_ch10_valid SECTION(".core11.data");
volatile int* beamer_6_ch11_ready SECTION(".core11.data");
volatile int* beamer_6_ch11_valid SECTION(".core11.data");

//OutputPorts
uint64_t* beamer_6_ch22_buffer SECTION(".core11.data");
uint64_t* beamer_6_ch23_buffer SECTION(".core11.data");
volatile int* beamer_6_ch22_ready SECTION(".core11.data");
volatile int* beamer_6_ch22_valid SECTION(".core11.data");
volatile int* beamer_6_ch23_ready SECTION(".core11.data");
volatile int* beamer_6_ch23_valid SECTION(".core11.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t beamer_6_complex_p0_pos SECTION(".core11.data");
int64_t beamer_6_complex_p0_val SECTION(".core11.data");
int64_t beamer_6_complex_p1_pos SECTION(".core11.data");
int64_t beamer_6_complex_p1_val SECTION(".core11.data");
int64_t beamer_6_complex_p2_pos SECTION(".core11.data");
int64_t beamer_6_complex_p2_val SECTION(".core11.data");
int64_t beamer_6_complex_p3_pos SECTION(".core11.data");
int64_t beamer_6_complex_p3_val SECTION(".core11.data");
int64_t beamer_6_complex_p01 SECTION(".core11.data");
int64_t beamer_6_complex_p12 SECTION(".core11.data");
int64_t beamer_6_complex_p23 SECTION(".core11.data");
int64_t beamer_6_complex_p02 SECTION(".core11.data");
int64_t beamer_6_complex_p13 SECTION(".core11.data");
int64_t beamer_6_complex_input1_p_pos SECTION(".core11.data");
int64_t beamer_6_complex_input1_p_val SECTION(".core11.data");
int64_t beamer_6_complex_input2_p_pos SECTION(".core11.data");
int64_t beamer_6_complex_input2_p_val SECTION(".core11.data");
int64_t beamer_6_complex_output_p SECTION(".core11.data");
int32_t beamer_6_input_state SECTION(".core11.data");
int32_t beamer_6_beam1_i SECTION(".core11.data") = 0;
int32_t beamer_6_beam1_counter SECTION(".core11.data") = 0;
int32_t beamer_6_beam2_i SECTION(".core11.data") = 0;
int32_t beamer_6_beam2_counter SECTION(".core11.data") = 0;
int32_t beamer_6_ba_result_index SECTION(".core11.data") = 0;
int32_t beamer_6_bb_result_index SECTION(".core11.data") = 0;
int32_t beamer_6_inputData_index SECTION(".core11.data") = 0;
int32_t beamer_6_ra_val_counter SECTION(".core11.data") = 0;
int32_t beamer_6_rb_val_counter SECTION(".core11.data") = 0;
int64_t beamer_6_complex_ra[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core11.data");

int64_t beamer_6_complex_rb[(NOF_PIXELS_KERNEL / 2)][2] SECTION(".core11.data");

int64_t beamer_6_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core11.data");

int64_t beamer_6_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core11.data");

int32_t beamer_6_beamer_6_State SECTION(".core11.data");
#define FSM_beamer_6_state1 (0) 
#define FSM_beamer_6_state2 (1) 
#define FSM_beamer_6_state12 (2) 
#define FSM_beamer_6_state13 (3) 
#define FSM_beamer_6_state14 (4) 
#define FSM_beamer_6_state15 (5) 
#define FSM_beamer_6_state3 (6) 
#define FSM_beamer_6_state16 (7) 
#define FSM_beamer_6_state17 (8) 
#define FSM_beamer_6_state18 (9) 
#define FSM_beamer_6_state19 (10) 
#define FSM_beamer_6_state11 (11) 
#define FSM_beamer_6_state20 (12) 
int32_t beamer_6_beamer_6_IntCheckOutput SECTION(".core11.data") = -1;
int beamer_6_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void beamer_6_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_6_complex_rb[i][0] = 1;
		beamer_6_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_6_inputData_index = (beamer_6_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_6_read_ra_val ( ) {
	int64_t ra_val;
	while(*beamer_6_ch10_valid == 0);//Blocking read
	ra_val = *beamer_6_ch10_buffer; //read input 
	*beamer_6_ch10_ready = 1; // channel ready to receive new data
	*beamer_6_ch10_valid = 0; // no valid input left on the channel
	
	beamer_6_complex_ra[beamer_6_ra_val_counter][1] = ra_val;
	beamer_6_ra_val_counter = (beamer_6_ra_val_counter + 1);

}
static inline void beamer_6_read_ra_val_done ( ) {
	beamer_6_ra_val_counter = 0;

	beamer_6_beam1_i = 0;

	beamer_6_beam2_i = 0;

}
static inline void beamer_6_read_rb_val ( ) {
	int64_t rb_val;
	while(*beamer_6_ch11_valid == 0);//Blocking read
	rb_val = *beamer_6_ch11_buffer; //read input 
	*beamer_6_ch11_ready = 1; // channel ready to receive new data
	*beamer_6_ch11_valid = 0; // no valid input left on the channel
	
	beamer_6_complex_rb[beamer_6_rb_val_counter][1] = rb_val;
	beamer_6_rb_val_counter = (beamer_6_rb_val_counter + 1);

}
static inline void beamer_6_read_rb_val_done ( ) {
	beamer_6_rb_val_counter = 0;

}
static inline void beamer_6_beam_int_loop_1 ( ) {
	
	beamer_6_complex_p0_pos = beamer_6_complex_ra[beamer_6_beam1_i + beamer_6_beam1_counter + 0][0];

	beamer_6_complex_p1_pos = beamer_6_complex_ra[beamer_6_beam1_i + beamer_6_beam1_counter + 3][0];

	beamer_6_complex_p2_pos = beamer_6_complex_ra[beamer_6_beam1_i + beamer_6_beam1_counter + 6][0];

	beamer_6_complex_p3_pos = beamer_6_complex_ra[beamer_6_beam1_i + beamer_6_beam1_counter + 9][0];

	beamer_6_input_state = 1;

	beamer_6_beam1_counter = (beamer_6_beam1_counter + 3);

	if ((beamer_6_beam1_counter == 9)){ 
		beamer_6_beam1_counter = 0;

		beamer_6_beam1_i = (beamer_6_beam1_i + 1);

	}

}
static inline void beamer_6_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_6_beam_int_loop_2 ( ) {
	
	beamer_6_complex_p0_pos = beamer_6_complex_rb[beamer_6_beam2_i + beamer_6_beam2_counter + 0][0];

	beamer_6_complex_p1_pos = beamer_6_complex_rb[beamer_6_beam2_i + beamer_6_beam2_counter + 3][0];

	beamer_6_complex_p2_pos = beamer_6_complex_rb[beamer_6_beam2_i + beamer_6_beam2_counter + 6][0];

	beamer_6_complex_p3_pos = beamer_6_complex_rb[beamer_6_beam2_i + beamer_6_beam2_counter + 9][0];

	beamer_6_input_state = 1;

	beamer_6_beam2_counter = (beamer_6_beam2_counter + 3);

	if ((beamer_6_beam2_counter == 9)){ 
		beamer_6_beam2_counter = 0;

		beamer_6_beam2_i = (beamer_6_beam2_i + 1);

	}

}
static inline void beamer_6_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_6_store_ba_results ( ) {
	
	beamer_6_complex_ba[beamer_6_ba_result_index][1] = beamer_6_complex_output_p;
	beamer_6_ba_result_index = (beamer_6_ba_result_index + 3);

	if ((beamer_6_ba_result_index == 9)){ 
		beamer_6_ba_result_index = 1;

	}

	if ((beamer_6_ba_result_index == 10)){ 
		beamer_6_ba_result_index = 2;

	}

	if ((beamer_6_ba_result_index == 11)){ 
		beamer_6_ba_result_index = 0;

	}

}
static inline void beamer_6_store_bb_results ( ) {
	
	beamer_6_complex_bb[beamer_6_bb_result_index][1] = beamer_6_complex_output_p;
	beamer_6_bb_result_index = (beamer_6_bb_result_index + 3);

	if ((beamer_6_bb_result_index == 9)){ 
		beamer_6_bb_result_index = 1;

	}

	if ((beamer_6_bb_result_index == 10)){ 
		beamer_6_bb_result_index = 2;

	}

	if ((beamer_6_bb_result_index == 11)){ 
		beamer_6_bb_result_index = 0;

	}

}
static inline void beamer_6_correlation ( ) {
	int32_t i;
	int64_t localba [9];
	int64_t localbb [9];
	
	i = 0;

	while (( i < 9 )) {
		localba[i] = beamer_6_complex_ba[i][1];
		localbb[i] = beamer_6_complex_bb[i][1];
		i = (i + 1);

	}

	while(*beamer_6_ch22_ready == 0);// Wait for the ready signal. 
	for(int beamer_6_correlation_i = 0; beamer_6_correlation_i < 9; beamer_6_correlation_i++){
		beamer_6_ch22_buffer[beamer_6_correlation_i] = localba[beamer_6_correlation_i]; //write output 
	}
	*beamer_6_ch22_ready = 0; //channel NOT ready to receive new data
	*beamer_6_ch22_valid = 1; //(because) channel has new data 
	
	while(*beamer_6_ch23_ready == 0);// Wait for the ready signal. 
	for(int beamer_6_correlation_i = 0; beamer_6_correlation_i < 9; beamer_6_correlation_i++){
		beamer_6_ch23_buffer[beamer_6_correlation_i] = localbb[beamer_6_correlation_i]; //write output 
	}
	*beamer_6_ch23_ready = 0; //channel NOT ready to receive new data
	*beamer_6_ch23_valid = 1; //(because) channel has new data 
	
}
static inline void beamer_6_set_cubic_inputs ( ) {
	
	if ((beamer_6_input_state == 1)){ 
		beamer_6_complex_input1_p_pos = beamer_6_complex_p0_pos;

		beamer_6_complex_input1_p_val = beamer_6_complex_p0_val;

		beamer_6_complex_input2_p_pos = beamer_6_complex_p1_pos;

		beamer_6_complex_input2_p_val = beamer_6_complex_p1_val;

		beamer_6_input_state = 2;

	}
	else {
		if ((beamer_6_input_state == 2)){ 
			beamer_6_complex_p01 = beamer_6_complex_output_p;

			beamer_6_complex_input1_p_pos = beamer_6_complex_p1_pos;

			beamer_6_complex_input1_p_val = beamer_6_complex_p1_val;

			beamer_6_complex_input2_p_pos = beamer_6_complex_p2_pos;

			beamer_6_complex_input2_p_val = beamer_6_complex_p2_val;

			beamer_6_input_state = 3;

		}
		else {
			if ((beamer_6_input_state == 3)){ 
				beamer_6_complex_p12 = beamer_6_complex_output_p;

				beamer_6_complex_input1_p_pos = beamer_6_complex_p2_pos;

				beamer_6_complex_input1_p_val = beamer_6_complex_p2_val;

				beamer_6_complex_input2_p_pos = beamer_6_complex_p3_pos;

				beamer_6_complex_input2_p_val = beamer_6_complex_p3_val;

				beamer_6_input_state = 4;

			}
			else {
				if ((beamer_6_input_state == 4)){ 
					beamer_6_complex_p23 = beamer_6_complex_output_p;

					beamer_6_complex_input1_p_pos = beamer_6_complex_p0_pos;

					beamer_6_complex_input1_p_val = beamer_6_complex_p01;

					beamer_6_complex_input2_p_pos = beamer_6_complex_p3_pos;

					beamer_6_complex_input2_p_val = beamer_6_complex_p12;

					beamer_6_input_state = 5;

				}
				else {
					if ((beamer_6_input_state == 5)){ 
						beamer_6_complex_p02 = beamer_6_complex_output_p;

						beamer_6_complex_input1_p_pos = beamer_6_complex_p1_pos;

						beamer_6_complex_input1_p_val = beamer_6_complex_p12;

						beamer_6_complex_input2_p_pos = beamer_6_complex_p3_pos;

						beamer_6_complex_input2_p_val = beamer_6_complex_p23;

						beamer_6_input_state = 6;

					}
					else {
						if ((beamer_6_input_state == 6)){ 
							beamer_6_complex_p13 = beamer_6_complex_output_p;

							beamer_6_complex_input1_p_pos = beamer_6_complex_p0_pos;

							beamer_6_complex_input1_p_val = beamer_6_complex_p02;

							beamer_6_complex_input2_p_pos = beamer_6_complex_p3_pos;

							beamer_6_complex_input2_p_val = beamer_6_complex_p13;

							beamer_6_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_6_set_cubic_inputs_done ( ) {
	
}
static inline void beamer_6___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_6_complex_input1_p_pos, beamer_6_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_6_complex_input2_p_pos, beamer_6_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_6_complex_output_p = outputReg;
}
static inline void beamer_6_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_6_complex_ba[i][0] = beamer_6_complex_ra[i][0];
		beamer_6_complex_bb[i][0] = beamer_6_complex_rb[i][0];
		i = (i + 1);

	}

}
int int_state_vars_beamer_6 SECTION(".core11.data") = 1;
void initStateVarsbeamer_6() {
	beamer_6_beamer_6_State = FSM_beamer_6_state1;

}

int beamer_6(void)
{
  
	//InputPorts
 	extern int ch10_ready; 
	extern int ch10_valid; 
	extern uint64_t ch10_buffer[ch10_size];
	extern int ch11_ready; 
	extern int ch11_valid; 
	extern uint64_t ch11_buffer[ch11_size];
	beamer_6_ch10_buffer =  ch10_buffer; 
	beamer_6_ch10_ready = &ch10_ready; 
	beamer_6_ch10_valid = &ch10_valid; 
	beamer_6_ch11_buffer =  ch11_buffer; 
	beamer_6_ch11_ready = &ch11_ready; 
	beamer_6_ch11_valid = &ch11_valid; 

	//OutputPorts
	extern int ch22_ready; 
	extern int ch22_valid; 
	extern uint64_t ch22_buffer[ch22_size];
	extern int ch23_ready; 
	extern int ch23_valid; 
	extern uint64_t ch23_buffer[ch23_size];
	beamer_6_ch22_buffer = ch22_buffer; 
	beamer_6_ch22_ready = &ch22_ready; 
	beamer_6_ch22_valid = &ch22_valid; 
	beamer_6_ch23_buffer = ch23_buffer; 
	beamer_6_ch23_ready = &ch23_ready; 
	beamer_6_ch23_valid = &ch23_valid; 
    
	if(int_state_vars_beamer_6 == 1){
		int_state_vars_beamer_6 = 0;
		initStateVarsbeamer_6();
	}
if ((beamer_6_beamer_6_IntCheckOutput == -1)){ 
	
beamer_6Schedule:

	
 switch (beamer_6_beamer_6_State) {
   case FSM_beamer_6_state1:
     		if (( beamer_6_inputData_index < NOF_PIXELS )){ 
			beamer_6_set_ra_rb_pos();
			beamer_6_beamer_6_State = FSM_beamer_6_state2;

			goto beamer_6Schedule;
		}

		     break;

   case FSM_beamer_6_state2:
     		if (1){ 
			if (( beamer_6_ra_val_counter < 18 )){ 
				beamer_6_read_ra_val();
				beamer_6_beamer_6_State = FSM_beamer_6_state2;

				goto beamer_6Schedule;
			}

		}

					beamer_6_read_ra_val_done();
			beamer_6_beamer_6_State = FSM_beamer_6_state12;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state12:
     		if (( beamer_6_beam1_i < 3 )){ 
			beamer_6_beam_int_loop_1();
			beamer_6_beamer_6_State = FSM_beamer_6_state13;

			goto beamer_6Schedule;
		}

					beamer_6_beam_int_loop_1_done();
			beamer_6_beamer_6_State = FSM_beamer_6_state3;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state13:
     		if ((beamer_6_input_state != 0)){ 
			beamer_6_set_cubic_inputs();
			beamer_6_beamer_6_State = FSM_beamer_6_state15;

			goto beamer_6Schedule;
		}

					beamer_6_set_cubic_inputs_done();
			beamer_6_beamer_6_State = FSM_beamer_6_state14;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state14:
     					beamer_6_store_ba_results();
			beamer_6_beamer_6_State = FSM_beamer_6_state12;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state15:
     					beamer_6___acc__cubic();
			beamer_6_beamer_6_State = FSM_beamer_6_state13;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state3:
     		if (1){ 
			if (( beamer_6_rb_val_counter < 18 )){ 
				beamer_6_read_rb_val();
				beamer_6_beamer_6_State = FSM_beamer_6_state3;

				goto beamer_6Schedule;
			}

		}

					beamer_6_read_rb_val_done();
			beamer_6_beamer_6_State = FSM_beamer_6_state16;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state16:
     		if (( beamer_6_beam2_i < 3 )){ 
			beamer_6_beam_int_loop_2();
			beamer_6_beamer_6_State = FSM_beamer_6_state17;

			goto beamer_6Schedule;
		}

					beamer_6_beam_int_loop_2_done();
			beamer_6_beamer_6_State = FSM_beamer_6_state11;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state17:
     		if ((beamer_6_input_state != 0)){ 
			beamer_6_set_cubic_inputs();
			beamer_6_beamer_6_State = FSM_beamer_6_state19;

			goto beamer_6Schedule;
		}

					beamer_6_set_cubic_inputs_done();
			beamer_6_beamer_6_State = FSM_beamer_6_state18;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state18:
     					beamer_6_store_bb_results();
			beamer_6_beamer_6_State = FSM_beamer_6_state16;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state19:
     					beamer_6___acc__cubic();
			beamer_6_beamer_6_State = FSM_beamer_6_state17;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state11:
     					beamer_6_set_ba_bb_pos();
			beamer_6_beamer_6_State = FSM_beamer_6_state20;

			goto beamer_6Schedule;

		     break;

   case FSM_beamer_6_state20:
     					
beamer_6_Action_0:

			if ((1 && 1)){ 
				beamer_6_correlation();
				beamer_6_beamer_6_State = FSM_beamer_6_state1;

				goto beamer_6Schedule;
			}
			else {
				beamer_6_beamer_6_IntCheckOutput = 0;

				return(0);
			}


		     break;

}

	beamer_6_beamer_6_IntCheckOutput = -1;

}
else {
	
 switch (beamer_6_beamer_6_IntCheckOutput) {
   case 0:
     		beamer_6_beamer_6_IntCheckOutput = -1;

		goto beamer_6_Action_0;
}

}
goto beamer_6Schedule;
}
