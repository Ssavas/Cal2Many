//code from range_actor.cal, instance ranger_3
#include <stdint.h>
#include <string.h>
#include "ranger_3.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_3_ch4_buffer SECTION(".core2.data");
uint64_t* ranger_3_ch5_buffer SECTION(".core2.data");
int* ranger_3_ch4_ready SECTION(".core2.data");
int* ranger_3_ch4_valid SECTION(".core2.data");
int* ranger_3_ch5_ready SECTION(".core2.data");
int* ranger_3_ch5_valid SECTION(".core2.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t ranger_3_complex_p0_pos SECTION(".core2.data");
int64_t ranger_3_complex_p0_val SECTION(".core2.data");
int64_t ranger_3_complex_p1_pos SECTION(".core2.data");
int64_t ranger_3_complex_p1_val SECTION(".core2.data");
int64_t ranger_3_complex_p2_pos SECTION(".core2.data");
int64_t ranger_3_complex_p2_val SECTION(".core2.data");
int64_t ranger_3_complex_p3_pos SECTION(".core2.data");
int64_t ranger_3_complex_p3_val SECTION(".core2.data");
int64_t ranger_3_complex_p01 SECTION(".core2.data");
int64_t ranger_3_complex_p12 SECTION(".core2.data");
int64_t ranger_3_complex_p23 SECTION(".core2.data");
int64_t ranger_3_complex_p02 SECTION(".core2.data");
int64_t ranger_3_complex_p13 SECTION(".core2.data");
int64_t ranger_3_complex_input1_p_pos SECTION(".core2.data");
int64_t ranger_3_complex_input1_p_val SECTION(".core2.data");
int64_t ranger_3_complex_input2_p_pos SECTION(".core2.data");
int64_t ranger_3_complex_input2_p_val SECTION(".core2.data");
int64_t ranger_3_complex_output_p SECTION(".core2.data");
int32_t ranger_3_input_state SECTION(".core2.data");
int32_t ranger_3_range1_i SECTION(".core2.data") = 0;
int32_t ranger_3_range1_counter SECTION(".core2.data") = 0;
int32_t ranger_3_range2_i SECTION(".core2.data") = 0;
int32_t ranger_3_range2_counter SECTION(".core2.data") = 0;
int32_t ranger_3_inputData_index SECTION(".core2.data") = 0;
int64_t ranger_3_complex_pa[NOF_PIXELS_KERNEL][2] SECTION(".core2.data");

int64_t ranger_3_complex_pb[NOF_PIXELS_KERNEL][2] SECTION(".core2.data");

int32_t ranger_3_ranger_3_State SECTION(".core2.data");
#define FSM_ranger_3_state1 (0) 
#define FSM_ranger_3_state3 (1) 
#define FSM_ranger_3_state4 (2) 
#define FSM_ranger_3_state5 (3) 
#define FSM_ranger_3_state6 (4) 
#define FSM_ranger_3_state7 (5) 
#define FSM_ranger_3_state8 (6) 
#define FSM_ranger_3_state9 (7) 
#define FSM_ranger_3_state10 (8) 
int32_t ranger_3_ranger_3_IntCheckOutput SECTION(".core2.data") = -1;

static inline void ranger_3_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_3_complex_pa[j][0] = 1;
		ranger_3_complex_pa[j][1] = 1;
		ranger_3_complex_pb[j][0] = 1;
		ranger_3_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_3_range1_i = 0;

	ranger_3_range2_i = 0;

	ranger_3_inputData_index = (ranger_3_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_3_range_int_loop_1 ( ) {
	
	ranger_3_complex_p0_pos = ranger_3_complex_pa[ranger_3_range1_i + ranger_3_range1_counter + 0][0];

	ranger_3_complex_p1_pos = ranger_3_complex_pa[ranger_3_range1_i + ranger_3_range1_counter + 1][0];

	ranger_3_complex_p2_pos = ranger_3_complex_pa[ranger_3_range1_i + ranger_3_range1_counter + 2][0];

	ranger_3_complex_p3_pos = ranger_3_complex_pa[ranger_3_range1_i + ranger_3_range1_counter + 3][0];

	ranger_3_input_state = 1;

	ranger_3_range1_counter = (ranger_3_range1_counter + 1);

	if ((ranger_3_range1_counter == 3)){ 
		ranger_3_range1_counter = 0;

		ranger_3_range1_i = (ranger_3_range1_i + 6);

	}

}
static inline void ranger_3_range_int_loop_1_done ( ) {
	
}
static inline void ranger_3_range_int_loop_2 ( ) {
	
	ranger_3_complex_p0_pos = ranger_3_complex_pb[ranger_3_range2_i + ranger_3_range2_counter + 0][0];

	ranger_3_complex_p1_pos = ranger_3_complex_pb[ranger_3_range2_i + ranger_3_range2_counter + 1][0];

	ranger_3_complex_p2_pos = ranger_3_complex_pb[ranger_3_range2_i + ranger_3_range2_counter + 2][0];

	ranger_3_complex_p3_pos = ranger_3_complex_pb[ranger_3_range2_i + ranger_3_range2_counter + 3][0];

	ranger_3_input_state = 1;

	ranger_3_range2_counter = (ranger_3_range2_counter + 1);

	if ((ranger_3_range2_counter == 3)){ 
		ranger_3_range2_counter = 0;

		ranger_3_range2_i = (ranger_3_range2_i + 6);

	}

}
static inline void ranger_3_range_int_loop_2_done ( ) {
	
}
static inline void ranger_3_store_ra_results ( ) {
	
	*ranger_3_ch4_buffer = ranger_3_complex_output_p;//write output
	*ranger_3_ch4_ready = 0; //channel NOT ready to receive new data
	*ranger_3_ch4_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_3_store_rb_results ( ) {
	
	*ranger_3_ch5_buffer = ranger_3_complex_output_p;//write output
	*ranger_3_ch5_ready = 0; //channel NOT ready to receive new data
	*ranger_3_ch5_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_3_set_cubic_inputs ( ) {
	
	if ((ranger_3_input_state == 1)){ 
		ranger_3_complex_input1_p_pos = ranger_3_complex_p0_pos;

		ranger_3_complex_input1_p_val = ranger_3_complex_p0_val;

		ranger_3_complex_input2_p_pos = ranger_3_complex_p1_pos;

		ranger_3_complex_input2_p_val = ranger_3_complex_p1_val;

		ranger_3_input_state = 2;

	}
	else {
		if ((ranger_3_input_state == 2)){ 
			ranger_3_complex_p01 = ranger_3_complex_output_p;

			ranger_3_complex_input1_p_pos = ranger_3_complex_p1_pos;

			ranger_3_complex_input1_p_val = ranger_3_complex_p1_val;

			ranger_3_complex_input2_p_pos = ranger_3_complex_p2_pos;

			ranger_3_complex_input2_p_val = ranger_3_complex_p2_val;

			ranger_3_input_state = 3;

		}
		else {
			if ((ranger_3_input_state == 3)){ 
				ranger_3_complex_p12 = ranger_3_complex_output_p;

				ranger_3_complex_input1_p_pos = ranger_3_complex_p2_pos;

				ranger_3_complex_input1_p_val = ranger_3_complex_p2_val;

				ranger_3_complex_input2_p_pos = ranger_3_complex_p3_pos;

				ranger_3_complex_input2_p_val = ranger_3_complex_p3_val;

				ranger_3_input_state = 4;

			}
			else {
				if ((ranger_3_input_state == 4)){ 
					ranger_3_complex_p23 = ranger_3_complex_output_p;

					ranger_3_complex_input1_p_pos = ranger_3_complex_p0_pos;

					ranger_3_complex_input1_p_val = ranger_3_complex_p01;

					ranger_3_complex_input2_p_pos = ranger_3_complex_p3_pos;

					ranger_3_complex_input2_p_val = ranger_3_complex_p12;

					ranger_3_input_state = 5;

				}
				else {
					if ((ranger_3_input_state == 5)){ 
						ranger_3_complex_p02 = ranger_3_complex_output_p;

						ranger_3_complex_input1_p_pos = ranger_3_complex_p1_pos;

						ranger_3_complex_input1_p_val = ranger_3_complex_p12;

						ranger_3_complex_input2_p_pos = ranger_3_complex_p3_pos;

						ranger_3_complex_input2_p_val = ranger_3_complex_p23;

						ranger_3_input_state = 6;

					}
					else {
						if ((ranger_3_input_state == 6)){ 
							ranger_3_complex_p13 = ranger_3_complex_output_p;

							ranger_3_complex_input1_p_pos = ranger_3_complex_p0_pos;

							ranger_3_complex_input1_p_val = ranger_3_complex_p02;

							ranger_3_complex_input2_p_pos = ranger_3_complex_p3_pos;

							ranger_3_complex_input2_p_val = ranger_3_complex_p13;

							ranger_3_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_3_set_cubic_inputs_done ( ) {
	
}
static inline void ranger_3___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_3_complex_input1_p_pos, ranger_3_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_3_complex_input2_p_pos, ranger_3_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_3_complex_output_p = outputReg;
}
int int_state_vars_ranger_3 = 1;
void initStateVarsranger_3() {
ranger_3_ranger_3_State = FSM_ranger_3_state1;

}

int ranger_3(void)
{
  
	//OutputPorts
	extern int ch4_ready; 
	extern int ch4_valid; 
	extern uint64_t ch4_buffer[ch4_size];
	extern int ch5_ready; 
	extern int ch5_valid; 
	extern uint64_t ch5_buffer[ch5_size];
	ranger_3_ch4_buffer = ch4_buffer; 
	ranger_3_ch4_ready = &ch4_ready; 
	ranger_3_ch4_valid = &ch4_valid; 
	ranger_3_ch5_buffer = ch5_buffer; 
	ranger_3_ch5_ready = &ch5_ready; 
	ranger_3_ch5_valid = &ch5_valid; 
    
	if(int_state_vars_ranger_3 == 1){
		int_state_vars_ranger_3 = 0;
		initStateVarsranger_3();
	}
if ((ranger_3_ranger_3_IntCheckOutput == -1)){ 
	
ranger_3Schedule:

	
 switch (ranger_3_ranger_3_State) {
   case FSM_ranger_3_state1:
     		if (( ranger_3_inputData_index < NOF_PIXELS )){ 
			ranger_3_set_pa_pb();
			ranger_3_ranger_3_State = FSM_ranger_3_state3;

			goto ranger_3Schedule;
		}

		     break;

   case FSM_ranger_3_state3:
     		if (( ranger_3_range1_i < NOF_PIXELS_KERNEL )){ 
			ranger_3_range_int_loop_1();
			ranger_3_ranger_3_State = FSM_ranger_3_state4;

			goto ranger_3Schedule;
		}

					ranger_3_range_int_loop_1_done();
			ranger_3_ranger_3_State = FSM_ranger_3_state7;

			goto ranger_3Schedule;

		     break;

   case FSM_ranger_3_state4:
     		if ((ranger_3_input_state != 0)){ 
			ranger_3_set_cubic_inputs();
			ranger_3_ranger_3_State = FSM_ranger_3_state6;

			goto ranger_3Schedule;
		}

					ranger_3_set_cubic_inputs_done();
			ranger_3_ranger_3_State = FSM_ranger_3_state5;

			goto ranger_3Schedule;

		     break;

   case FSM_ranger_3_state5:
     					
ranger_3_Action_0:

			if (*ranger_3_ch4_ready == 1){ 
				ranger_3_store_ra_results();
				ranger_3_ranger_3_State = FSM_ranger_3_state3;

				goto ranger_3Schedule;
			}
			else {
				ranger_3_ranger_3_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_3_state6:
     					ranger_3___acc__cubic();
			ranger_3_ranger_3_State = FSM_ranger_3_state4;

			goto ranger_3Schedule;

		     break;

   case FSM_ranger_3_state7:
     		if (( ranger_3_range2_i < NOF_PIXELS_KERNEL )){ 
			ranger_3_range_int_loop_2();
			ranger_3_ranger_3_State = FSM_ranger_3_state8;

			goto ranger_3Schedule;
		}

					ranger_3_range_int_loop_2_done();
			ranger_3_ranger_3_State = FSM_ranger_3_state1;

			goto ranger_3Schedule;

		     break;

   case FSM_ranger_3_state8:
     		if ((ranger_3_input_state != 0)){ 
			ranger_3_set_cubic_inputs();
			ranger_3_ranger_3_State = FSM_ranger_3_state10;

			goto ranger_3Schedule;
		}

					ranger_3_set_cubic_inputs_done();
			ranger_3_ranger_3_State = FSM_ranger_3_state9;

			goto ranger_3Schedule;

		     break;

   case FSM_ranger_3_state9:
     					
ranger_3_Action_1:

			if (*ranger_3_ch5_ready == 1){ 
				ranger_3_store_rb_results();
				ranger_3_ranger_3_State = FSM_ranger_3_state7;

				goto ranger_3Schedule;
			}
			else {
				ranger_3_ranger_3_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_3_state10:
     					ranger_3___acc__cubic();
			ranger_3_ranger_3_State = FSM_ranger_3_state8;

			goto ranger_3Schedule;

		     break;

}

	ranger_3_ranger_3_IntCheckOutput = -1;

}
else {
	
 switch (ranger_3_ranger_3_IntCheckOutput) {
   case 0:
     		ranger_3_ranger_3_IntCheckOutput = -1;

		goto ranger_3_Action_0;
   case 1:
     		ranger_3_ranger_3_IntCheckOutput = -1;

		goto ranger_3_Action_1;
}

}
goto ranger_3Schedule;
}
