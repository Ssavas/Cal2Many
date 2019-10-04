//code from beam_actor.cal, instance beamer
#include <stdint.h>
#include <string.h>
#include "beamer.h"
#include "common.h"

//InputPorts
uint64_t* beamer_ch0_buffer SECTION(".core1.data");
uint64_t* beamer_ch1_buffer SECTION(".core1.data");
volatile int* beamer_ch0_ready SECTION(".core1.data");
volatile int* beamer_ch0_valid SECTION(".core1.data");
volatile int* beamer_ch1_ready SECTION(".core1.data");
volatile int* beamer_ch1_valid SECTION(".core1.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS (216) 
#define RA_RB_SIZE ((NOF_PIXELS_KERNEL / 2)) 
float beamer_C_mag_ret SECTION(".core1.data");
int64_t beamer_complex_p0_pos SECTION(".core1.data");
int64_t beamer_complex_p0_val SECTION(".core1.data");
int64_t beamer_complex_p1_pos SECTION(".core1.data");
int64_t beamer_complex_p1_val SECTION(".core1.data");
int64_t beamer_complex_p2_pos SECTION(".core1.data");
int64_t beamer_complex_p2_val SECTION(".core1.data");
int64_t beamer_complex_p3_pos SECTION(".core1.data");
int64_t beamer_complex_p3_val SECTION(".core1.data");
int64_t beamer_complex_p01 SECTION(".core1.data");
int64_t beamer_complex_p12 SECTION(".core1.data");
int64_t beamer_complex_p23 SECTION(".core1.data");
int64_t beamer_complex_p02 SECTION(".core1.data");
int64_t beamer_complex_p13 SECTION(".core1.data");
int64_t beamer_complex_input1_p_pos SECTION(".core1.data");
int64_t beamer_complex_input1_p_val SECTION(".core1.data");
int64_t beamer_complex_input2_p_pos SECTION(".core1.data");
int64_t beamer_complex_input2_p_val SECTION(".core1.data");
int64_t beamer_complex_output_p SECTION(".core1.data");
int64_t beamer_correlation_input1 SECTION(".core1.data");
int64_t beamer_correlation_input2 SECTION(".core1.data");
int32_t beamer_input_state SECTION(".core1.data");
int32_t beamer_beam1_i SECTION(".core1.data") = 0;
int32_t beamer_beam1_counter SECTION(".core1.data") = 0;
int32_t beamer_beam2_i SECTION(".core1.data") = 0;
int32_t beamer_beam2_counter SECTION(".core1.data") = 0;
int32_t beamer_ba_result_index SECTION(".core1.data") = 0;
int32_t beamer_bb_result_index SECTION(".core1.data") = 0;
int32_t beamer_correlation_counter SECTION(".core1.data") = 0;
int32_t beamer_ra_val_counter SECTION(".core1.data") = 0;
int32_t beamer_rb_val_counter SECTION(".core1.data") = 0;
int32_t beamer_inputData_index SECTION(".core1.data") = 0;
float beamer_total_sum SECTION(".core1.data");
int64_t beamer_complex_ra[RA_RB_SIZE][2] SECTION(".core1.data");

int64_t beamer_complex_rb[RA_RB_SIZE][2] SECTION(".core1.data");

int64_t beamer_complex_ba[NOF_PIXELS_KERNEL][2] SECTION(".core1.data");

int64_t beamer_complex_bb[NOF_PIXELS_KERNEL][2] SECTION(".core1.data");

int32_t beamer_beamer_State SECTION(".core1.data");
#define FSM_beamer_state1 (0) 
#define FSM_beamer_state2 (1) 
#define FSM_beamer_state12 (2) 
#define FSM_beamer_state13 (3) 
#define FSM_beamer_state14 (4) 
#define FSM_beamer_state15 (5) 
#define FSM_beamer_state3 (6) 
#define FSM_beamer_state16 (7) 
#define FSM_beamer_state17 (8) 
#define FSM_beamer_state18 (9) 
#define FSM_beamer_state19 (10) 
#define FSM_beamer_state11 (11) 
#define FSM_beamer_state20 (12) 
#define FSM_beamer_state21 (13) 
static void C_mag (int ns);
int beamer_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void beamer_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 18 )) {
		beamer_complex_rb[i][0] = 1;
		beamer_complex_ra[i][0] = 1;
		i = (i + 6);

	}

	beamer_inputData_index = (beamer_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void beamer_read_ra_val ( ) {
	int64_t ra_val;
	while(*beamer_ch0_valid == 0);//Blocking read
	ra_val = *beamer_ch0_buffer; //read input 
	*beamer_ch0_ready = 1; // channel ready to receive new data
	*beamer_ch0_valid = 0; // no valid input left on the channel
	
	
	beamer_complex_ra[beamer_ra_val_counter][1] = ra_val;
	beamer_ra_val_counter = (beamer_ra_val_counter + 1);

}
static inline void beamer_read_ra_val_done ( ) {
	
	beamer_ra_val_counter = 0;

	beamer_beam1_i = 0;

	beamer_beam2_i = 0;

}
static inline void beamer_read_rb_val ( ) {
	int64_t rb_val;
	while(*beamer_ch1_valid == 0);//Blocking read
	rb_val = *beamer_ch1_buffer; //read input 
	*beamer_ch1_ready = 1; // channel ready to receive new data
	*beamer_ch1_valid = 0; // no valid input left on the channel
	
	
	beamer_complex_rb[beamer_rb_val_counter][1] = rb_val;
	beamer_rb_val_counter = (beamer_rb_val_counter + 1);

}
static inline void beamer_read_rb_val_done ( ) {
	
	beamer_rb_val_counter = 0;

}
static inline void beamer_beam_int_loop_1 ( ) {
	
	beamer_complex_p0_pos = beamer_complex_ra[beamer_beam1_i + beamer_beam1_counter + 0][0];

	beamer_complex_p1_pos = beamer_complex_ra[beamer_beam1_i + beamer_beam1_counter + 3][0];

	beamer_complex_p2_pos = beamer_complex_ra[beamer_beam1_i + beamer_beam1_counter + 6][0];

	beamer_complex_p3_pos = beamer_complex_ra[beamer_beam1_i + beamer_beam1_counter + 9][0];

	beamer_input_state = 1;

	beamer_beam1_counter = (beamer_beam1_counter + 3);

	if ((beamer_beam1_counter == 9)){ 
		beamer_beam1_counter = 0;

		beamer_beam1_i = (beamer_beam1_i + 1);

	}

}
static inline void beamer_beam_int_loop_1_done ( ) {
	
}
static inline void beamer_beam_int_loop_2 ( ) {
	
	beamer_complex_p0_pos = beamer_complex_rb[beamer_beam2_i + beamer_beam2_counter + 0][0];

	beamer_complex_p1_pos = beamer_complex_rb[beamer_beam2_i + beamer_beam2_counter + 3][0];

	beamer_complex_p2_pos = beamer_complex_rb[beamer_beam2_i + beamer_beam2_counter + 6][0];

	beamer_complex_p3_pos = beamer_complex_rb[beamer_beam2_i + beamer_beam2_counter + 9][0];

	beamer_input_state = 1;

	beamer_beam2_counter = (beamer_beam2_counter + 3);

	if ((beamer_beam2_counter == 9)){ 
		beamer_beam2_counter = 0;

		beamer_beam2_i = (beamer_beam2_i + 1);

	}

}
static inline void beamer_beam_int_loop_2_done ( ) {
	
}
static inline void beamer_store_ba_results ( ) {
	
	beamer_complex_ba[beamer_ba_result_index][1] = beamer_complex_output_p;
	beamer_ba_result_index = (beamer_ba_result_index + 3);

	if ((beamer_ba_result_index == 9)){ 
		beamer_ba_result_index = 1;

	}

	if ((beamer_ba_result_index == 10)){ 
		beamer_ba_result_index = 2;

	}

	if ((beamer_ba_result_index == 11)){ 
		beamer_ba_result_index = 0;

	}

}
static inline void beamer_store_bb_results ( ) {
	
	beamer_complex_bb[beamer_bb_result_index][1] = beamer_complex_output_p;
	beamer_bb_result_index = (beamer_bb_result_index + 3);

	if ((beamer_bb_result_index == 9)){ 
		beamer_bb_result_index = 1;

	}

	if ((beamer_bb_result_index == 10)){ 
		beamer_bb_result_index = 2;

	}

	if ((beamer_bb_result_index == 11)){ 
		beamer_bb_result_index = 0;

	}

}
static inline void beamer_set_correlation_inputs ( ) {
	beamer_correlation_input1 = beamer_complex_ba[beamer_correlation_counter][1];

	beamer_correlation_input2 = beamer_complex_bb[beamer_correlation_counter][1];

	beamer_correlation_counter = (beamer_correlation_counter + 1);

}
static inline void beamer___acc__correlation ( ) {

	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &beamer_total_sum, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_correlation_input1, beamer_correlation_input2, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	beamer_total_sum = outputReg;
}
static inline void beamer_correlation_done ( ) {
	beamer_correlation_counter = 0;

}
static inline void beamer_set_cubic_inputs ( ) {
	
	if ((beamer_input_state == 1)){ 
		beamer_complex_input1_p_pos = beamer_complex_p0_pos;

		beamer_complex_input1_p_val = beamer_complex_p0_val;

		beamer_complex_input2_p_pos = beamer_complex_p1_pos;

		beamer_complex_input2_p_val = beamer_complex_p1_val;

		beamer_input_state = 2;

	}
	else {
		if ((beamer_input_state == 2)){ 
			beamer_complex_p01 = beamer_complex_output_p;

			beamer_complex_input1_p_pos = beamer_complex_p1_pos;

			beamer_complex_input1_p_val = beamer_complex_p1_val;

			beamer_complex_input2_p_pos = beamer_complex_p2_pos;

			beamer_complex_input2_p_val = beamer_complex_p2_val;

			beamer_input_state = 3;

		}
		else {
			if ((beamer_input_state == 3)){ 
				beamer_complex_p12 = beamer_complex_output_p;

				beamer_complex_input1_p_pos = beamer_complex_p2_pos;

				beamer_complex_input1_p_val = beamer_complex_p2_val;

				beamer_complex_input2_p_pos = beamer_complex_p3_pos;

				beamer_complex_input2_p_val = beamer_complex_p3_val;

				beamer_input_state = 4;

			}
			else {
				if ((beamer_input_state == 4)){ 
					beamer_complex_p23 = beamer_complex_output_p;

					beamer_complex_input1_p_pos = beamer_complex_p0_pos;

					beamer_complex_input1_p_val = beamer_complex_p01;

					beamer_complex_input2_p_pos = beamer_complex_p3_pos;

					beamer_complex_input2_p_val = beamer_complex_p12;

					beamer_input_state = 5;

				}
				else {
					if ((beamer_input_state == 5)){ 
						beamer_complex_p02 = beamer_complex_output_p;

						beamer_complex_input1_p_pos = beamer_complex_p1_pos;

						beamer_complex_input1_p_val = beamer_complex_p12;

						beamer_complex_input2_p_pos = beamer_complex_p3_pos;

						beamer_complex_input2_p_val = beamer_complex_p23;

						beamer_input_state = 6;

					}
					else {
						if ((beamer_input_state == 6)){ 
							beamer_complex_p13 = beamer_complex_output_p;

							beamer_complex_input1_p_pos = beamer_complex_p0_pos;

							beamer_complex_input1_p_val = beamer_complex_p02;

							beamer_complex_input2_p_pos = beamer_complex_p3_pos;

							beamer_complex_input2_p_val = beamer_complex_p13;

							beamer_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void beamer_set_cubic_inputs_done ( ) {
	
}
static inline void beamer___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, beamer_complex_input1_p_pos, beamer_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, beamer_complex_input2_p_pos, beamer_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	beamer_complex_output_p = outputReg;
}
static inline void beamer_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	
	while (( i < 6 )) {
		beamer_complex_ba[i][0] = beamer_complex_ra[i][0];
		beamer_complex_bb[i][0] = beamer_complex_rb[i][0];
		i = (i + 1);

	}

}
static void C_mag (int ns) { 
	beamer_C_mag_ret = 1;


 }

int int_state_vars_beamer SECTION(".core1.data") = 1;
void initStateVarsbeamer() {
	beamer_total_sum = 0.0;
beamer_beamer_State = FSM_beamer_state1;

}

int beamer(void)
{
  
	//InputPorts
 	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[ch0_size];
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[ch1_size];
	beamer_ch0_buffer =  ch0_buffer; 
	beamer_ch0_ready = &ch0_ready; 
	beamer_ch0_valid = &ch0_valid; 
	beamer_ch1_buffer =  ch1_buffer; 
	beamer_ch1_ready = &ch1_ready; 
	beamer_ch1_valid = &ch1_valid; 
    
	if(int_state_vars_beamer == 1){
		int_state_vars_beamer = 0;
		initStateVarsbeamer();
	}

beamerSchedule:

 switch (beamer_beamer_State) {
   case FSM_beamer_state1:
     	if (( beamer_inputData_index < NOF_PIXELS )){ 
		beamer_set_ra_rb_pos();
		beamer_beamer_State = FSM_beamer_state2;

		goto beamerSchedule;
	}

	     break;

   case FSM_beamer_state2:
     	if (1){ 
		if (( beamer_ra_val_counter < 18 )){ 
			beamer_read_ra_val();
			beamer_beamer_State = FSM_beamer_state2;

			goto beamerSchedule;
		}

	}

			beamer_read_ra_val_done();
		beamer_beamer_State = FSM_beamer_state12;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state12:
     	if (( beamer_beam1_i < 3 )){ 
		beamer_beam_int_loop_1();
		beamer_beamer_State = FSM_beamer_state13;

		goto beamerSchedule;
	}

			beamer_beam_int_loop_1_done();
		beamer_beamer_State = FSM_beamer_state3;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state13:
     	if ((beamer_input_state != 0)){ 
		beamer_set_cubic_inputs();
		beamer_beamer_State = FSM_beamer_state15;

		goto beamerSchedule;
	}

			beamer_set_cubic_inputs_done();
		beamer_beamer_State = FSM_beamer_state14;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state14:
     			beamer_store_ba_results();
		beamer_beamer_State = FSM_beamer_state12;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state15:
     			beamer___acc__cubic();
		beamer_beamer_State = FSM_beamer_state13;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state3:
     	if (1){ 
		if (( beamer_rb_val_counter < 18 )){ 
			beamer_read_rb_val();
			beamer_beamer_State = FSM_beamer_state3;

			goto beamerSchedule;
		}

	}

			beamer_read_rb_val_done();
		beamer_beamer_State = FSM_beamer_state16;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state16:
     	if (( beamer_beam2_i < 3 )){ 
		beamer_beam_int_loop_2();
		beamer_beamer_State = FSM_beamer_state17;

		goto beamerSchedule;
	}

			beamer_beam_int_loop_2_done();
		beamer_beamer_State = FSM_beamer_state11;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state17:
     	if ((beamer_input_state != 0)){ 
		beamer_set_cubic_inputs();
		beamer_beamer_State = FSM_beamer_state19;

		goto beamerSchedule;
	}

			beamer_set_cubic_inputs_done();
		beamer_beamer_State = FSM_beamer_state18;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state18:
     			beamer_store_bb_results();
		beamer_beamer_State = FSM_beamer_state16;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state19:
     			beamer___acc__cubic();
		beamer_beamer_State = FSM_beamer_state17;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state11:
     			beamer_set_ba_bb_pos();
		beamer_beamer_State = FSM_beamer_state20;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state20:
     	if (( beamer_correlation_counter < 9 )){ 
		beamer_set_correlation_inputs();
		beamer_beamer_State = FSM_beamer_state21;

		goto beamerSchedule;
	}

			beamer_correlation_done();
		beamer_beamer_State = FSM_beamer_state1;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state21:
     			beamer___acc__correlation();
		beamer_beamer_State = FSM_beamer_state20;

		goto beamerSchedule;

	     break;

}
goto beamerSchedule;
}
