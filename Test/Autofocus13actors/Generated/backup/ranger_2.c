//code from range_actor.cal, instance ranger_2
#include <stdint.h>
#include <string.h>
#include "ranger_2.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_2_ch2_buffer SECTION(".core1.data");
uint64_t* ranger_2_ch3_buffer SECTION(".core1.data");
int* ranger_2_ch2_ready SECTION(".core1.data");
int* ranger_2_ch2_valid SECTION(".core1.data");
int* ranger_2_ch3_ready SECTION(".core1.data");
int* ranger_2_ch3_valid SECTION(".core1.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t ranger_2_complex_p0_pos SECTION(".core1.data");
int64_t ranger_2_complex_p0_val SECTION(".core1.data");
int64_t ranger_2_complex_p1_pos SECTION(".core1.data");
int64_t ranger_2_complex_p1_val SECTION(".core1.data");
int64_t ranger_2_complex_p2_pos SECTION(".core1.data");
int64_t ranger_2_complex_p2_val SECTION(".core1.data");
int64_t ranger_2_complex_p3_pos SECTION(".core1.data");
int64_t ranger_2_complex_p3_val SECTION(".core1.data");
int64_t ranger_2_complex_p01 SECTION(".core1.data");
int64_t ranger_2_complex_p12 SECTION(".core1.data");
int64_t ranger_2_complex_p23 SECTION(".core1.data");
int64_t ranger_2_complex_p02 SECTION(".core1.data");
int64_t ranger_2_complex_p13 SECTION(".core1.data");
int64_t ranger_2_complex_input1_p_pos SECTION(".core1.data");
int64_t ranger_2_complex_input1_p_val SECTION(".core1.data");
int64_t ranger_2_complex_input2_p_pos SECTION(".core1.data");
int64_t ranger_2_complex_input2_p_val SECTION(".core1.data");
int64_t ranger_2_complex_output_p SECTION(".core1.data");
int32_t ranger_2_input_state SECTION(".core1.data");
int32_t ranger_2_range1_i SECTION(".core1.data") = 0;
int32_t ranger_2_range1_counter SECTION(".core1.data") = 0;
int32_t ranger_2_range2_i SECTION(".core1.data") = 0;
int32_t ranger_2_range2_counter SECTION(".core1.data") = 0;
int32_t ranger_2_inputData_index SECTION(".core1.data") = 0;
int64_t ranger_2_complex_pa[NOF_PIXELS_KERNEL][2] SECTION(".core1.data");

int64_t ranger_2_complex_pb[NOF_PIXELS_KERNEL][2] SECTION(".core1.data");

int32_t ranger_2_ranger_2_State SECTION(".core1.data");
#define FSM_ranger_2_state1 (0) 
#define FSM_ranger_2_state3 (1) 
#define FSM_ranger_2_state4 (2) 
#define FSM_ranger_2_state5 (3) 
#define FSM_ranger_2_state6 (4) 
#define FSM_ranger_2_state7 (5) 
#define FSM_ranger_2_state8 (6) 
#define FSM_ranger_2_state9 (7) 
#define FSM_ranger_2_state10 (8) 
int32_t ranger_2_ranger_2_IntCheckOutput SECTION(".core1.data") = -1;

static inline void ranger_2_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_2_complex_pa[j][0] = 1;
		ranger_2_complex_pa[j][1] = 1;
		ranger_2_complex_pb[j][0] = 1;
		ranger_2_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_2_range1_i = 0;

	ranger_2_range2_i = 0;

	ranger_2_inputData_index = (ranger_2_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_2_range_int_loop_1 ( ) {
	
	ranger_2_complex_p0_pos = ranger_2_complex_pa[ranger_2_range1_i + ranger_2_range1_counter + 0][0];

	ranger_2_complex_p1_pos = ranger_2_complex_pa[ranger_2_range1_i + ranger_2_range1_counter + 1][0];

	ranger_2_complex_p2_pos = ranger_2_complex_pa[ranger_2_range1_i + ranger_2_range1_counter + 2][0];

	ranger_2_complex_p3_pos = ranger_2_complex_pa[ranger_2_range1_i + ranger_2_range1_counter + 3][0];

	ranger_2_input_state = 1;

	ranger_2_range1_counter = (ranger_2_range1_counter + 1);

	if ((ranger_2_range1_counter == 3)){ 
		ranger_2_range1_counter = 0;

		ranger_2_range1_i = (ranger_2_range1_i + 6);

	}

}
static inline void ranger_2_range_int_loop_1_done ( ) {
	
}
static inline void ranger_2_range_int_loop_2 ( ) {
	
	ranger_2_complex_p0_pos = ranger_2_complex_pb[ranger_2_range2_i + ranger_2_range2_counter + 0][0];

	ranger_2_complex_p1_pos = ranger_2_complex_pb[ranger_2_range2_i + ranger_2_range2_counter + 1][0];

	ranger_2_complex_p2_pos = ranger_2_complex_pb[ranger_2_range2_i + ranger_2_range2_counter + 2][0];

	ranger_2_complex_p3_pos = ranger_2_complex_pb[ranger_2_range2_i + ranger_2_range2_counter + 3][0];

	ranger_2_input_state = 1;

	ranger_2_range2_counter = (ranger_2_range2_counter + 1);

	if ((ranger_2_range2_counter == 3)){ 
		ranger_2_range2_counter = 0;

		ranger_2_range2_i = (ranger_2_range2_i + 6);

	}

}
static inline void ranger_2_range_int_loop_2_done ( ) {
	
}
static inline void ranger_2_store_ra_results ( ) {
	
	*ranger_2_ch2_buffer = ranger_2_complex_output_p;//write output
	*ranger_2_ch2_ready = 0; //channel NOT ready to receive new data
	*ranger_2_ch2_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_2_store_rb_results ( ) {
	
	*ranger_2_ch3_buffer = ranger_2_complex_output_p;//write output
	*ranger_2_ch3_ready = 0; //channel NOT ready to receive new data
	*ranger_2_ch3_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_2_set_cubic_inputs ( ) {
	
	if ((ranger_2_input_state == 1)){ 
		ranger_2_complex_input1_p_pos = ranger_2_complex_p0_pos;

		ranger_2_complex_input1_p_val = ranger_2_complex_p0_val;

		ranger_2_complex_input2_p_pos = ranger_2_complex_p1_pos;

		ranger_2_complex_input2_p_val = ranger_2_complex_p1_val;

		ranger_2_input_state = 2;

	}
	else {
		if ((ranger_2_input_state == 2)){ 
			ranger_2_complex_p01 = ranger_2_complex_output_p;

			ranger_2_complex_input1_p_pos = ranger_2_complex_p1_pos;

			ranger_2_complex_input1_p_val = ranger_2_complex_p1_val;

			ranger_2_complex_input2_p_pos = ranger_2_complex_p2_pos;

			ranger_2_complex_input2_p_val = ranger_2_complex_p2_val;

			ranger_2_input_state = 3;

		}
		else {
			if ((ranger_2_input_state == 3)){ 
				ranger_2_complex_p12 = ranger_2_complex_output_p;

				ranger_2_complex_input1_p_pos = ranger_2_complex_p2_pos;

				ranger_2_complex_input1_p_val = ranger_2_complex_p2_val;

				ranger_2_complex_input2_p_pos = ranger_2_complex_p3_pos;

				ranger_2_complex_input2_p_val = ranger_2_complex_p3_val;

				ranger_2_input_state = 4;

			}
			else {
				if ((ranger_2_input_state == 4)){ 
					ranger_2_complex_p23 = ranger_2_complex_output_p;

					ranger_2_complex_input1_p_pos = ranger_2_complex_p0_pos;

					ranger_2_complex_input1_p_val = ranger_2_complex_p01;

					ranger_2_complex_input2_p_pos = ranger_2_complex_p3_pos;

					ranger_2_complex_input2_p_val = ranger_2_complex_p12;

					ranger_2_input_state = 5;

				}
				else {
					if ((ranger_2_input_state == 5)){ 
						ranger_2_complex_p02 = ranger_2_complex_output_p;

						ranger_2_complex_input1_p_pos = ranger_2_complex_p1_pos;

						ranger_2_complex_input1_p_val = ranger_2_complex_p12;

						ranger_2_complex_input2_p_pos = ranger_2_complex_p3_pos;

						ranger_2_complex_input2_p_val = ranger_2_complex_p23;

						ranger_2_input_state = 6;

					}
					else {
						if ((ranger_2_input_state == 6)){ 
							ranger_2_complex_p13 = ranger_2_complex_output_p;

							ranger_2_complex_input1_p_pos = ranger_2_complex_p0_pos;

							ranger_2_complex_input1_p_val = ranger_2_complex_p02;

							ranger_2_complex_input2_p_pos = ranger_2_complex_p3_pos;

							ranger_2_complex_input2_p_val = ranger_2_complex_p13;

							ranger_2_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_2_set_cubic_inputs_done ( ) {
	
}
static inline void ranger_2___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_2_complex_input1_p_pos, ranger_2_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_2_complex_input2_p_pos, ranger_2_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_2_complex_output_p = outputReg;
}
int int_state_vars_ranger_2 = 1;
void initStateVarsranger_2() {
ranger_2_ranger_2_State = FSM_ranger_2_state1;

}

int ranger_2(void)
{
  
	//OutputPorts
	extern int ch2_ready; 
	extern int ch2_valid; 
	extern uint64_t ch2_buffer[ch2_size];
	extern int ch3_ready; 
	extern int ch3_valid; 
	extern uint64_t ch3_buffer[ch3_size];
	ranger_2_ch2_buffer = ch2_buffer; 
	ranger_2_ch2_ready = &ch2_ready; 
	ranger_2_ch2_valid = &ch2_valid; 
	ranger_2_ch3_buffer = ch3_buffer; 
	ranger_2_ch3_ready = &ch3_ready; 
	ranger_2_ch3_valid = &ch3_valid; 
    
	if(int_state_vars_ranger_2 == 1){
		int_state_vars_ranger_2 = 0;
		initStateVarsranger_2();
	}
if ((ranger_2_ranger_2_IntCheckOutput == -1)){ 
	
ranger_2Schedule:

	
 switch (ranger_2_ranger_2_State) {
   case FSM_ranger_2_state1:
     		if (( ranger_2_inputData_index < NOF_PIXELS )){ 
			ranger_2_set_pa_pb();
			ranger_2_ranger_2_State = FSM_ranger_2_state3;

			goto ranger_2Schedule;
		}

		     break;

   case FSM_ranger_2_state3:
     		if (( ranger_2_range1_i < NOF_PIXELS_KERNEL )){ 
			ranger_2_range_int_loop_1();
			ranger_2_ranger_2_State = FSM_ranger_2_state4;

			goto ranger_2Schedule;
		}

					ranger_2_range_int_loop_1_done();
			ranger_2_ranger_2_State = FSM_ranger_2_state7;

			goto ranger_2Schedule;

		     break;

   case FSM_ranger_2_state4:
     		if ((ranger_2_input_state != 0)){ 
			ranger_2_set_cubic_inputs();
			ranger_2_ranger_2_State = FSM_ranger_2_state6;

			goto ranger_2Schedule;
		}

					ranger_2_set_cubic_inputs_done();
			ranger_2_ranger_2_State = FSM_ranger_2_state5;

			goto ranger_2Schedule;

		     break;

   case FSM_ranger_2_state5:
     					
ranger_2_Action_0:

			if (*ranger_2_ch2_ready == 1){ 
				ranger_2_store_ra_results();
				ranger_2_ranger_2_State = FSM_ranger_2_state3;

				goto ranger_2Schedule;
			}
			else {
				ranger_2_ranger_2_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_2_state6:
     					ranger_2___acc__cubic();
			ranger_2_ranger_2_State = FSM_ranger_2_state4;

			goto ranger_2Schedule;

		     break;

   case FSM_ranger_2_state7:
     		if (( ranger_2_range2_i < NOF_PIXELS_KERNEL )){ 
			ranger_2_range_int_loop_2();
			ranger_2_ranger_2_State = FSM_ranger_2_state8;

			goto ranger_2Schedule;
		}

					ranger_2_range_int_loop_2_done();
			ranger_2_ranger_2_State = FSM_ranger_2_state1;

			goto ranger_2Schedule;

		     break;

   case FSM_ranger_2_state8:
     		if ((ranger_2_input_state != 0)){ 
			ranger_2_set_cubic_inputs();
			ranger_2_ranger_2_State = FSM_ranger_2_state10;

			goto ranger_2Schedule;
		}

					ranger_2_set_cubic_inputs_done();
			ranger_2_ranger_2_State = FSM_ranger_2_state9;

			goto ranger_2Schedule;

		     break;

   case FSM_ranger_2_state9:
     					
ranger_2_Action_1:

			if (*ranger_2_ch3_ready == 1){ 
				ranger_2_store_rb_results();
				ranger_2_ranger_2_State = FSM_ranger_2_state7;

				goto ranger_2Schedule;
			}
			else {
				ranger_2_ranger_2_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_2_state10:
     					ranger_2___acc__cubic();
			ranger_2_ranger_2_State = FSM_ranger_2_state8;

			goto ranger_2Schedule;

		     break;

}

	ranger_2_ranger_2_IntCheckOutput = -1;

}
else {
	
 switch (ranger_2_ranger_2_IntCheckOutput) {
   case 0:
     		ranger_2_ranger_2_IntCheckOutput = -1;

		goto ranger_2_Action_0;
   case 1:
     		ranger_2_ranger_2_IntCheckOutput = -1;

		goto ranger_2_Action_1;
}

}
goto ranger_2Schedule;
}
