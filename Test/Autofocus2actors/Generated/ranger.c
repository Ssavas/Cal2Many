//code from range_actor.cal, instance ranger
#include <stdint.h>
#include <string.h>
#include "ranger.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_ch0_buffer;
uint64_t* ranger_ch1_buffer;
volatile int* ranger_ch0_ready;
volatile int* ranger_ch0_valid;
volatile int* ranger_ch1_ready;
volatile int* ranger_ch1_valid;

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS (216) 
float ranger_complex_SquareRoot_ret;
float ranger_SquareRoot_ret;
int64_t ranger_complex_p0_pos;
int64_t ranger_complex_p0_val;
int64_t ranger_complex_p1_pos;
int64_t ranger_complex_p1_val;
int64_t ranger_complex_p2_pos;
int64_t ranger_complex_p2_val;
int64_t ranger_complex_p3_pos;
int64_t ranger_complex_p3_val;
int64_t ranger_complex_p01;
int64_t ranger_complex_p12;
int64_t ranger_complex_p23;
int64_t ranger_complex_p02;
int64_t ranger_complex_p13;
int64_t ranger_complex_input1_p_pos;
int64_t ranger_complex_input1_p_val;
int64_t ranger_complex_input2_p_pos;
int64_t ranger_complex_input2_p_val;
int64_t ranger_complex_output_p;
int32_t ranger_input_state;
int32_t ranger_range1_i = 0;
int32_t ranger_range1_counter = 0;
int32_t ranger_range2_i = 0;
int32_t ranger_range2_counter = 0;
int32_t ranger_ra_result_index = 0;
int32_t ranger_rb_result_index = 0;
int32_t ranger_beam1_i = 0;
int32_t ranger_beam1_counter = 0;
int32_t ranger_beam2_i = 0;
int32_t ranger_beam2_counter = 0;
int32_t ranger_ba_result_index = 0;
int32_t ranger_bb_result_index = 0;
int32_t ranger_inputData_index = 0;
float ranger_total_sum;
int64_t ranger_complex_pa[NOF_PIXELS_KERNEL][2];

int64_t ranger_complex_pb[NOF_PIXELS_KERNEL][2];

int64_t ranger_complex_ra[NOF_PIXELS_KERNEL][2];

int64_t ranger_complex_rb[NOF_PIXELS_KERNEL][2];

int64_t ranger_complex_ba[NOF_PIXELS_KERNEL][2];

int64_t ranger_complex_bb[NOF_PIXELS_KERNEL][2];

int32_t ranger_ranger_State;
#define FSM_ranger_state1 (0) 
#define FSM_ranger_state3 (1) 
#define FSM_ranger_state4 (2) 
#define FSM_ranger_state5 (3) 
#define FSM_ranger_state6 (4) 
#define FSM_ranger_state7 (5) 
#define FSM_ranger_state8 (6) 
#define FSM_ranger_state9 (7) 
#define FSM_ranger_state10 (8) 
int32_t ranger_ranger_IntCheckOutput = -1;
int ranger_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void ranger_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_complex_pa[j][0] = 1;
		ranger_complex_pa[j][1] = 1;
		ranger_complex_pb[j][0] = 1;
		ranger_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_range1_i = 0;

	ranger_range2_i = 0;

	ranger_inputData_index = (ranger_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_range_int_loop_1 ( ) {
	
	ranger_complex_p0_pos = ranger_complex_pa[ranger_range1_i + ranger_range1_counter + 0][0];

	ranger_complex_p1_pos = ranger_complex_pa[ranger_range1_i + ranger_range1_counter + 1][0];

	ranger_complex_p2_pos = ranger_complex_pa[ranger_range1_i + ranger_range1_counter + 2][0];

	ranger_complex_p3_pos = ranger_complex_pa[ranger_range1_i + ranger_range1_counter + 3][0];

	ranger_input_state = 1;

	ranger_range1_counter = (ranger_range1_counter + 1);

	if ((ranger_range1_counter == 3)){ 
		ranger_range1_counter = 0;

		ranger_range1_i = (ranger_range1_i + 6);

	}

}
static inline void ranger_range_int_loop_1_done ( ) {
	
}
static inline void ranger_range_int_loop_2 ( ) {
	
	ranger_complex_p0_pos = ranger_complex_pb[ranger_range2_i + ranger_range2_counter + 0][0];

	ranger_complex_p1_pos = ranger_complex_pb[ranger_range2_i + ranger_range2_counter + 1][0];

	ranger_complex_p2_pos = ranger_complex_pb[ranger_range2_i + ranger_range2_counter + 2][0];

	ranger_complex_p3_pos = ranger_complex_pb[ranger_range2_i + ranger_range2_counter + 3][0];

	ranger_input_state = 1;

	ranger_range2_counter = (ranger_range2_counter + 1);

	if ((ranger_range2_counter == 3)){ 
		ranger_range2_counter = 0;

		ranger_range2_i = (ranger_range2_i + 6);

	}

}
static inline void ranger_range_int_loop_2_done ( ) {
	
}
static inline void ranger_store_ra_results ( ) {
	
	while(*ranger_ch0_ready == 0);// Wait for the ready signal. 
	*ranger_ch0_buffer = ranger_complex_output_p;//write output
	*ranger_ch0_ready = 0; //channel NOT ready to receive new data
	*ranger_ch0_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_store_rb_results ( ) {
	
	while(*ranger_ch1_ready == 0);// Wait for the ready signal. 
	*ranger_ch1_buffer = ranger_complex_output_p;//write output
	*ranger_ch1_ready = 0; //channel NOT ready to receive new data
	*ranger_ch1_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_set_cubic_inputs ( ) {
	
	if ((ranger_input_state == 1)){ 
		ranger_complex_input1_p_pos = ranger_complex_p0_pos;

		ranger_complex_input1_p_val = ranger_complex_p0_val;

		ranger_complex_input2_p_pos = ranger_complex_p1_pos;

		ranger_complex_input2_p_val = ranger_complex_p1_val;

		ranger_input_state = 2;

	}
	else {
		if ((ranger_input_state == 2)){ 
			ranger_complex_p01 = ranger_complex_output_p;

			ranger_complex_input1_p_pos = ranger_complex_p1_pos;

			ranger_complex_input1_p_val = ranger_complex_p1_val;

			ranger_complex_input2_p_pos = ranger_complex_p2_pos;

			ranger_complex_input2_p_val = ranger_complex_p2_val;

			ranger_input_state = 3;

		}
		else {
			if ((ranger_input_state == 3)){ 
				ranger_complex_p12 = ranger_complex_output_p;

				ranger_complex_input1_p_pos = ranger_complex_p2_pos;

				ranger_complex_input1_p_val = ranger_complex_p2_val;

				ranger_complex_input2_p_pos = ranger_complex_p3_pos;

				ranger_complex_input2_p_val = ranger_complex_p3_val;

				ranger_input_state = 4;

			}
			else {
				if ((ranger_input_state == 4)){ 
					ranger_complex_p23 = ranger_complex_output_p;

					ranger_complex_input1_p_pos = ranger_complex_p0_pos;

					ranger_complex_input1_p_val = ranger_complex_p01;

					ranger_complex_input2_p_pos = ranger_complex_p3_pos;

					ranger_complex_input2_p_val = ranger_complex_p12;

					ranger_input_state = 5;

				}
				else {
					if ((ranger_input_state == 5)){ 
						ranger_complex_p02 = ranger_complex_output_p;

						ranger_complex_input1_p_pos = ranger_complex_p1_pos;

						ranger_complex_input1_p_val = ranger_complex_p12;

						ranger_complex_input2_p_pos = ranger_complex_p3_pos;

						ranger_complex_input2_p_val = ranger_complex_p23;

						ranger_input_state = 6;

					}
					else {
						if ((ranger_input_state == 6)){ 
							ranger_complex_p13 = ranger_complex_output_p;

							ranger_complex_input1_p_pos = ranger_complex_p0_pos;

							ranger_complex_input1_p_val = ranger_complex_p02;

							ranger_complex_input2_p_pos = ranger_complex_p3_pos;

							ranger_complex_input2_p_val = ranger_complex_p13;

							ranger_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_set_cubic_inputs_done ( ) {
	
}
static inline void ranger___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_complex_input1_p_pos, ranger_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_complex_input2_p_pos, ranger_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_complex_output_p = outputReg;
}
int int_state_vars_ranger = 1; 
void initStateVarsranger() {
	ranger_total_sum = 0.0;
ranger_ranger_State = FSM_ranger_state1;

}

int ranger(void)
{
  
	//OutputPorts
	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[ch0_size];
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[ch1_size];
	ranger_ch0_buffer = ch0_buffer; 
	ranger_ch0_ready = &ch0_ready; 
	ranger_ch0_valid = &ch0_valid; 
	ranger_ch1_buffer = ch1_buffer; 
	ranger_ch1_ready = &ch1_ready; 
	ranger_ch1_valid = &ch1_valid; 
    
	if(int_state_vars_ranger == 1){
		int_state_vars_ranger = 0;
		initStateVarsranger();
	}
if ((ranger_ranger_IntCheckOutput == -1)){ 
	
rangerSchedule:

	
 switch (ranger_ranger_State) {
   case FSM_ranger_state1:
     		if (( ranger_inputData_index < NOF_PIXELS )){ 
			ranger_set_pa_pb();
			ranger_ranger_State = FSM_ranger_state3;

			goto rangerSchedule;
		}

		     break;

   case FSM_ranger_state3:
     		if (( ranger_range1_i < 36 )){ 
			ranger_range_int_loop_1();
			ranger_ranger_State = FSM_ranger_state4;

			goto rangerSchedule;
		}

					ranger_range_int_loop_1_done();
			ranger_ranger_State = FSM_ranger_state7;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state4:
     		if ((ranger_input_state != 0)){ 
			ranger_set_cubic_inputs();
			ranger_ranger_State = FSM_ranger_state6;

			goto rangerSchedule;
		}

					ranger_set_cubic_inputs_done();
			ranger_ranger_State = FSM_ranger_state5;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state5:
     					
ranger_Action_0:

			if (1){ 
				ranger_store_ra_results();
				ranger_ranger_State = FSM_ranger_state3;

				goto rangerSchedule;
			}
			else {
				ranger_ranger_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_state6:
     					ranger___acc__cubic();
			ranger_ranger_State = FSM_ranger_state4;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state7:
     		if (( ranger_range2_i < 36 )){ 
			ranger_range_int_loop_2();
			ranger_ranger_State = FSM_ranger_state8;

			goto rangerSchedule;
		}

					ranger_range_int_loop_2_done();
			ranger_ranger_State = FSM_ranger_state1;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state8:
     		if ((ranger_input_state != 0)){ 
			ranger_set_cubic_inputs();
			ranger_ranger_State = FSM_ranger_state10;

			goto rangerSchedule;
		}

					ranger_set_cubic_inputs_done();
			ranger_ranger_State = FSM_ranger_state9;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state9:
     					
ranger_Action_1:

			if (1){ 
				ranger_store_rb_results();
				ranger_ranger_State = FSM_ranger_state7;

				goto rangerSchedule;
			}
			else {
				ranger_ranger_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_state10:
     					ranger___acc__cubic();
			ranger_ranger_State = FSM_ranger_state8;

			goto rangerSchedule;

		     break;

}

	ranger_ranger_IntCheckOutput = -1;

}
else {
	
 switch (ranger_ranger_IntCheckOutput) {
   case 0:
     		ranger_ranger_IntCheckOutput = -1;

		goto ranger_Action_0;
   case 1:
     		ranger_ranger_IntCheckOutput = -1;

		goto ranger_Action_1;
}

}
goto rangerSchedule;
}
