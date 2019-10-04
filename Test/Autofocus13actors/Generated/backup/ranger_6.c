//code from range_actor.cal, instance ranger_6
#include <stdint.h>
#include <string.h>
#include "ranger_6.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_6_ch10_buffer SECTION(".core5.data");
uint64_t* ranger_6_ch11_buffer SECTION(".core5.data");
int* ranger_6_ch10_ready SECTION(".core5.data");
int* ranger_6_ch10_valid SECTION(".core5.data");
int* ranger_6_ch11_ready SECTION(".core5.data");
int* ranger_6_ch11_valid SECTION(".core5.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t ranger_6_complex_p0_pos SECTION(".core5.data");
int64_t ranger_6_complex_p0_val SECTION(".core5.data");
int64_t ranger_6_complex_p1_pos SECTION(".core5.data");
int64_t ranger_6_complex_p1_val SECTION(".core5.data");
int64_t ranger_6_complex_p2_pos SECTION(".core5.data");
int64_t ranger_6_complex_p2_val SECTION(".core5.data");
int64_t ranger_6_complex_p3_pos SECTION(".core5.data");
int64_t ranger_6_complex_p3_val SECTION(".core5.data");
int64_t ranger_6_complex_p01 SECTION(".core5.data");
int64_t ranger_6_complex_p12 SECTION(".core5.data");
int64_t ranger_6_complex_p23 SECTION(".core5.data");
int64_t ranger_6_complex_p02 SECTION(".core5.data");
int64_t ranger_6_complex_p13 SECTION(".core5.data");
int64_t ranger_6_complex_input1_p_pos SECTION(".core5.data");
int64_t ranger_6_complex_input1_p_val SECTION(".core5.data");
int64_t ranger_6_complex_input2_p_pos SECTION(".core5.data");
int64_t ranger_6_complex_input2_p_val SECTION(".core5.data");
int64_t ranger_6_complex_output_p SECTION(".core5.data");
int32_t ranger_6_input_state SECTION(".core5.data");
int32_t ranger_6_range1_i SECTION(".core5.data") = 0;
int32_t ranger_6_range1_counter SECTION(".core5.data") = 0;
int32_t ranger_6_range2_i SECTION(".core5.data") = 0;
int32_t ranger_6_range2_counter SECTION(".core5.data") = 0;
int32_t ranger_6_inputData_index SECTION(".core5.data") = 0;
int64_t ranger_6_complex_pa[NOF_PIXELS_KERNEL][2] SECTION(".core5.data");

int64_t ranger_6_complex_pb[NOF_PIXELS_KERNEL][2] SECTION(".core5.data");

int32_t ranger_6_ranger_6_State SECTION(".core5.data");
#define FSM_ranger_6_state1 (0) 
#define FSM_ranger_6_state3 (1) 
#define FSM_ranger_6_state4 (2) 
#define FSM_ranger_6_state5 (3) 
#define FSM_ranger_6_state6 (4) 
#define FSM_ranger_6_state7 (5) 
#define FSM_ranger_6_state8 (6) 
#define FSM_ranger_6_state9 (7) 
#define FSM_ranger_6_state10 (8) 
int32_t ranger_6_ranger_6_IntCheckOutput SECTION(".core5.data") = -1;

static inline void ranger_6_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_6_complex_pa[j][0] = 1;
		ranger_6_complex_pa[j][1] = 1;
		ranger_6_complex_pb[j][0] = 1;
		ranger_6_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_6_range1_i = 0;

	ranger_6_range2_i = 0;

	ranger_6_inputData_index = (ranger_6_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_6_range_int_loop_1 ( ) {
	
	ranger_6_complex_p0_pos = ranger_6_complex_pa[ranger_6_range1_i + ranger_6_range1_counter + 0][0];

	ranger_6_complex_p1_pos = ranger_6_complex_pa[ranger_6_range1_i + ranger_6_range1_counter + 1][0];

	ranger_6_complex_p2_pos = ranger_6_complex_pa[ranger_6_range1_i + ranger_6_range1_counter + 2][0];

	ranger_6_complex_p3_pos = ranger_6_complex_pa[ranger_6_range1_i + ranger_6_range1_counter + 3][0];

	ranger_6_input_state = 1;

	ranger_6_range1_counter = (ranger_6_range1_counter + 1);

	if ((ranger_6_range1_counter == 3)){ 
		ranger_6_range1_counter = 0;

		ranger_6_range1_i = (ranger_6_range1_i + 6);

	}

}
static inline void ranger_6_range_int_loop_1_done ( ) {
	
}
static inline void ranger_6_range_int_loop_2 ( ) {
	
	ranger_6_complex_p0_pos = ranger_6_complex_pb[ranger_6_range2_i + ranger_6_range2_counter + 0][0];

	ranger_6_complex_p1_pos = ranger_6_complex_pb[ranger_6_range2_i + ranger_6_range2_counter + 1][0];

	ranger_6_complex_p2_pos = ranger_6_complex_pb[ranger_6_range2_i + ranger_6_range2_counter + 2][0];

	ranger_6_complex_p3_pos = ranger_6_complex_pb[ranger_6_range2_i + ranger_6_range2_counter + 3][0];

	ranger_6_input_state = 1;

	ranger_6_range2_counter = (ranger_6_range2_counter + 1);

	if ((ranger_6_range2_counter == 3)){ 
		ranger_6_range2_counter = 0;

		ranger_6_range2_i = (ranger_6_range2_i + 6);

	}

}
static inline void ranger_6_range_int_loop_2_done ( ) {
	
}
static inline void ranger_6_store_ra_results ( ) {
	
	*ranger_6_ch10_buffer = ranger_6_complex_output_p;//write output
	*ranger_6_ch10_ready = 0; //channel NOT ready to receive new data
	*ranger_6_ch10_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_6_store_rb_results ( ) {
	
	*ranger_6_ch11_buffer = ranger_6_complex_output_p;//write output
	*ranger_6_ch11_ready = 0; //channel NOT ready to receive new data
	*ranger_6_ch11_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_6_set_cubic_inputs ( ) {
	
	if ((ranger_6_input_state == 1)){ 
		ranger_6_complex_input1_p_pos = ranger_6_complex_p0_pos;

		ranger_6_complex_input1_p_val = ranger_6_complex_p0_val;

		ranger_6_complex_input2_p_pos = ranger_6_complex_p1_pos;

		ranger_6_complex_input2_p_val = ranger_6_complex_p1_val;

		ranger_6_input_state = 2;

	}
	else {
		if ((ranger_6_input_state == 2)){ 
			ranger_6_complex_p01 = ranger_6_complex_output_p;

			ranger_6_complex_input1_p_pos = ranger_6_complex_p1_pos;

			ranger_6_complex_input1_p_val = ranger_6_complex_p1_val;

			ranger_6_complex_input2_p_pos = ranger_6_complex_p2_pos;

			ranger_6_complex_input2_p_val = ranger_6_complex_p2_val;

			ranger_6_input_state = 3;

		}
		else {
			if ((ranger_6_input_state == 3)){ 
				ranger_6_complex_p12 = ranger_6_complex_output_p;

				ranger_6_complex_input1_p_pos = ranger_6_complex_p2_pos;

				ranger_6_complex_input1_p_val = ranger_6_complex_p2_val;

				ranger_6_complex_input2_p_pos = ranger_6_complex_p3_pos;

				ranger_6_complex_input2_p_val = ranger_6_complex_p3_val;

				ranger_6_input_state = 4;

			}
			else {
				if ((ranger_6_input_state == 4)){ 
					ranger_6_complex_p23 = ranger_6_complex_output_p;

					ranger_6_complex_input1_p_pos = ranger_6_complex_p0_pos;

					ranger_6_complex_input1_p_val = ranger_6_complex_p01;

					ranger_6_complex_input2_p_pos = ranger_6_complex_p3_pos;

					ranger_6_complex_input2_p_val = ranger_6_complex_p12;

					ranger_6_input_state = 5;

				}
				else {
					if ((ranger_6_input_state == 5)){ 
						ranger_6_complex_p02 = ranger_6_complex_output_p;

						ranger_6_complex_input1_p_pos = ranger_6_complex_p1_pos;

						ranger_6_complex_input1_p_val = ranger_6_complex_p12;

						ranger_6_complex_input2_p_pos = ranger_6_complex_p3_pos;

						ranger_6_complex_input2_p_val = ranger_6_complex_p23;

						ranger_6_input_state = 6;

					}
					else {
						if ((ranger_6_input_state == 6)){ 
							ranger_6_complex_p13 = ranger_6_complex_output_p;

							ranger_6_complex_input1_p_pos = ranger_6_complex_p0_pos;

							ranger_6_complex_input1_p_val = ranger_6_complex_p02;

							ranger_6_complex_input2_p_pos = ranger_6_complex_p3_pos;

							ranger_6_complex_input2_p_val = ranger_6_complex_p13;

							ranger_6_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_6_set_cubic_inputs_done ( ) {
	
}
static inline void ranger_6___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_6_complex_input1_p_pos, ranger_6_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_6_complex_input2_p_pos, ranger_6_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_6_complex_output_p = outputReg;
}
int int_state_vars_ranger_6 = 1;
void initStateVarsranger_6() {
ranger_6_ranger_6_State = FSM_ranger_6_state1;

}

int ranger_6(void)
{
  
	//OutputPorts
	extern int ch10_ready; 
	extern int ch10_valid; 
	extern uint64_t ch10_buffer[ch10_size];
	extern int ch11_ready; 
	extern int ch11_valid; 
	extern uint64_t ch11_buffer[ch11_size];
	ranger_6_ch10_buffer = ch10_buffer; 
	ranger_6_ch10_ready = &ch10_ready; 
	ranger_6_ch10_valid = &ch10_valid; 
	ranger_6_ch11_buffer = ch11_buffer; 
	ranger_6_ch11_ready = &ch11_ready; 
	ranger_6_ch11_valid = &ch11_valid; 
    
	if(int_state_vars_ranger_6 == 1){
		int_state_vars_ranger_6 = 0;
		initStateVarsranger_6();
	}
if ((ranger_6_ranger_6_IntCheckOutput == -1)){ 
	
ranger_6Schedule:

	
 switch (ranger_6_ranger_6_State) {
   case FSM_ranger_6_state1:
     		if (( ranger_6_inputData_index < NOF_PIXELS )){ 
			ranger_6_set_pa_pb();
			ranger_6_ranger_6_State = FSM_ranger_6_state3;

			goto ranger_6Schedule;
		}

		     break;

   case FSM_ranger_6_state3:
     		if (( ranger_6_range1_i < NOF_PIXELS_KERNEL )){ 
			ranger_6_range_int_loop_1();
			ranger_6_ranger_6_State = FSM_ranger_6_state4;

			goto ranger_6Schedule;
		}

					ranger_6_range_int_loop_1_done();
			ranger_6_ranger_6_State = FSM_ranger_6_state7;

			goto ranger_6Schedule;

		     break;

   case FSM_ranger_6_state4:
     		if ((ranger_6_input_state != 0)){ 
			ranger_6_set_cubic_inputs();
			ranger_6_ranger_6_State = FSM_ranger_6_state6;

			goto ranger_6Schedule;
		}

					ranger_6_set_cubic_inputs_done();
			ranger_6_ranger_6_State = FSM_ranger_6_state5;

			goto ranger_6Schedule;

		     break;

   case FSM_ranger_6_state5:
     					
ranger_6_Action_0:

			if (*ranger_6_ch10_ready == 1){ 
				ranger_6_store_ra_results();
				ranger_6_ranger_6_State = FSM_ranger_6_state3;

				goto ranger_6Schedule;
			}
			else {
				ranger_6_ranger_6_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_6_state6:
     					ranger_6___acc__cubic();
			ranger_6_ranger_6_State = FSM_ranger_6_state4;

			goto ranger_6Schedule;

		     break;

   case FSM_ranger_6_state7:
     		if (( ranger_6_range2_i < NOF_PIXELS_KERNEL )){ 
			ranger_6_range_int_loop_2();
			ranger_6_ranger_6_State = FSM_ranger_6_state8;

			goto ranger_6Schedule;
		}

					ranger_6_range_int_loop_2_done();
			ranger_6_ranger_6_State = FSM_ranger_6_state1;

			goto ranger_6Schedule;

		     break;

   case FSM_ranger_6_state8:
     		if ((ranger_6_input_state != 0)){ 
			ranger_6_set_cubic_inputs();
			ranger_6_ranger_6_State = FSM_ranger_6_state10;

			goto ranger_6Schedule;
		}

					ranger_6_set_cubic_inputs_done();
			ranger_6_ranger_6_State = FSM_ranger_6_state9;

			goto ranger_6Schedule;

		     break;

   case FSM_ranger_6_state9:
     					
ranger_6_Action_1:

			if (*ranger_6_ch11_ready == 1){ 
				ranger_6_store_rb_results();
				ranger_6_ranger_6_State = FSM_ranger_6_state7;

				goto ranger_6Schedule;
			}
			else {
				ranger_6_ranger_6_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_6_state10:
     					ranger_6___acc__cubic();
			ranger_6_ranger_6_State = FSM_ranger_6_state8;

			goto ranger_6Schedule;

		     break;

}

	ranger_6_ranger_6_IntCheckOutput = -1;

}
else {
	
 switch (ranger_6_ranger_6_IntCheckOutput) {
   case 0:
     		ranger_6_ranger_6_IntCheckOutput = -1;

		goto ranger_6_Action_0;
   case 1:
     		ranger_6_ranger_6_IntCheckOutput = -1;

		goto ranger_6_Action_1;
}

}
goto ranger_6Schedule;
}
