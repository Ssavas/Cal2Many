//code from range_actor.cal, instance ranger_5
#include <stdint.h>
#include <string.h>
#include "ranger_5.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_5_ch8_buffer SECTION(".core4.data");
uint64_t* ranger_5_ch9_buffer SECTION(".core4.data");
int* ranger_5_ch8_ready SECTION(".core4.data");
int* ranger_5_ch8_valid SECTION(".core4.data");
int* ranger_5_ch9_ready SECTION(".core4.data");
int* ranger_5_ch9_valid SECTION(".core4.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t ranger_5_complex_p0_pos SECTION(".core4.data");
int64_t ranger_5_complex_p0_val SECTION(".core4.data");
int64_t ranger_5_complex_p1_pos SECTION(".core4.data");
int64_t ranger_5_complex_p1_val SECTION(".core4.data");
int64_t ranger_5_complex_p2_pos SECTION(".core4.data");
int64_t ranger_5_complex_p2_val SECTION(".core4.data");
int64_t ranger_5_complex_p3_pos SECTION(".core4.data");
int64_t ranger_5_complex_p3_val SECTION(".core4.data");
int64_t ranger_5_complex_p01 SECTION(".core4.data");
int64_t ranger_5_complex_p12 SECTION(".core4.data");
int64_t ranger_5_complex_p23 SECTION(".core4.data");
int64_t ranger_5_complex_p02 SECTION(".core4.data");
int64_t ranger_5_complex_p13 SECTION(".core4.data");
int64_t ranger_5_complex_input1_p_pos SECTION(".core4.data");
int64_t ranger_5_complex_input1_p_val SECTION(".core4.data");
int64_t ranger_5_complex_input2_p_pos SECTION(".core4.data");
int64_t ranger_5_complex_input2_p_val SECTION(".core4.data");
int64_t ranger_5_complex_output_p SECTION(".core4.data");
int32_t ranger_5_input_state SECTION(".core4.data");
int32_t ranger_5_range1_i SECTION(".core4.data") = 0;
int32_t ranger_5_range1_counter SECTION(".core4.data") = 0;
int32_t ranger_5_range2_i SECTION(".core4.data") = 0;
int32_t ranger_5_range2_counter SECTION(".core4.data") = 0;
int32_t ranger_5_inputData_index SECTION(".core4.data") = 0;
int64_t ranger_5_complex_pa[NOF_PIXELS_KERNEL][2] SECTION(".core4.data");

int64_t ranger_5_complex_pb[NOF_PIXELS_KERNEL][2] SECTION(".core4.data");

int32_t ranger_5_ranger_5_State SECTION(".core4.data");
#define FSM_ranger_5_state1 (0) 
#define FSM_ranger_5_state3 (1) 
#define FSM_ranger_5_state4 (2) 
#define FSM_ranger_5_state5 (3) 
#define FSM_ranger_5_state6 (4) 
#define FSM_ranger_5_state7 (5) 
#define FSM_ranger_5_state8 (6) 
#define FSM_ranger_5_state9 (7) 
#define FSM_ranger_5_state10 (8) 
int32_t ranger_5_ranger_5_IntCheckOutput SECTION(".core4.data") = -1;

static inline void ranger_5_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_5_complex_pa[j][0] = 1;
		ranger_5_complex_pa[j][1] = 1;
		ranger_5_complex_pb[j][0] = 1;
		ranger_5_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_5_range1_i = 0;

	ranger_5_range2_i = 0;

	ranger_5_inputData_index = (ranger_5_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_5_range_int_loop_1 ( ) {
	
	ranger_5_complex_p0_pos = ranger_5_complex_pa[ranger_5_range1_i + ranger_5_range1_counter + 0][0];

	ranger_5_complex_p1_pos = ranger_5_complex_pa[ranger_5_range1_i + ranger_5_range1_counter + 1][0];

	ranger_5_complex_p2_pos = ranger_5_complex_pa[ranger_5_range1_i + ranger_5_range1_counter + 2][0];

	ranger_5_complex_p3_pos = ranger_5_complex_pa[ranger_5_range1_i + ranger_5_range1_counter + 3][0];

	ranger_5_input_state = 1;

	ranger_5_range1_counter = (ranger_5_range1_counter + 1);

	if ((ranger_5_range1_counter == 3)){ 
		ranger_5_range1_counter = 0;

		ranger_5_range1_i = (ranger_5_range1_i + 6);

	}

}
static inline void ranger_5_range_int_loop_1_done ( ) {
	
}
static inline void ranger_5_range_int_loop_2 ( ) {
	
	ranger_5_complex_p0_pos = ranger_5_complex_pb[ranger_5_range2_i + ranger_5_range2_counter + 0][0];

	ranger_5_complex_p1_pos = ranger_5_complex_pb[ranger_5_range2_i + ranger_5_range2_counter + 1][0];

	ranger_5_complex_p2_pos = ranger_5_complex_pb[ranger_5_range2_i + ranger_5_range2_counter + 2][0];

	ranger_5_complex_p3_pos = ranger_5_complex_pb[ranger_5_range2_i + ranger_5_range2_counter + 3][0];

	ranger_5_input_state = 1;

	ranger_5_range2_counter = (ranger_5_range2_counter + 1);

	if ((ranger_5_range2_counter == 3)){ 
		ranger_5_range2_counter = 0;

		ranger_5_range2_i = (ranger_5_range2_i + 6);

	}

}
static inline void ranger_5_range_int_loop_2_done ( ) {
	
}
static inline void ranger_5_store_ra_results ( ) {
	
	*ranger_5_ch8_buffer = ranger_5_complex_output_p;//write output
	*ranger_5_ch8_ready = 0; //channel NOT ready to receive new data
	*ranger_5_ch8_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_5_store_rb_results ( ) {
	
	*ranger_5_ch9_buffer = ranger_5_complex_output_p;//write output
	*ranger_5_ch9_ready = 0; //channel NOT ready to receive new data
	*ranger_5_ch9_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_5_set_cubic_inputs ( ) {
	
	if ((ranger_5_input_state == 1)){ 
		ranger_5_complex_input1_p_pos = ranger_5_complex_p0_pos;

		ranger_5_complex_input1_p_val = ranger_5_complex_p0_val;

		ranger_5_complex_input2_p_pos = ranger_5_complex_p1_pos;

		ranger_5_complex_input2_p_val = ranger_5_complex_p1_val;

		ranger_5_input_state = 2;

	}
	else {
		if ((ranger_5_input_state == 2)){ 
			ranger_5_complex_p01 = ranger_5_complex_output_p;

			ranger_5_complex_input1_p_pos = ranger_5_complex_p1_pos;

			ranger_5_complex_input1_p_val = ranger_5_complex_p1_val;

			ranger_5_complex_input2_p_pos = ranger_5_complex_p2_pos;

			ranger_5_complex_input2_p_val = ranger_5_complex_p2_val;

			ranger_5_input_state = 3;

		}
		else {
			if ((ranger_5_input_state == 3)){ 
				ranger_5_complex_p12 = ranger_5_complex_output_p;

				ranger_5_complex_input1_p_pos = ranger_5_complex_p2_pos;

				ranger_5_complex_input1_p_val = ranger_5_complex_p2_val;

				ranger_5_complex_input2_p_pos = ranger_5_complex_p3_pos;

				ranger_5_complex_input2_p_val = ranger_5_complex_p3_val;

				ranger_5_input_state = 4;

			}
			else {
				if ((ranger_5_input_state == 4)){ 
					ranger_5_complex_p23 = ranger_5_complex_output_p;

					ranger_5_complex_input1_p_pos = ranger_5_complex_p0_pos;

					ranger_5_complex_input1_p_val = ranger_5_complex_p01;

					ranger_5_complex_input2_p_pos = ranger_5_complex_p3_pos;

					ranger_5_complex_input2_p_val = ranger_5_complex_p12;

					ranger_5_input_state = 5;

				}
				else {
					if ((ranger_5_input_state == 5)){ 
						ranger_5_complex_p02 = ranger_5_complex_output_p;

						ranger_5_complex_input1_p_pos = ranger_5_complex_p1_pos;

						ranger_5_complex_input1_p_val = ranger_5_complex_p12;

						ranger_5_complex_input2_p_pos = ranger_5_complex_p3_pos;

						ranger_5_complex_input2_p_val = ranger_5_complex_p23;

						ranger_5_input_state = 6;

					}
					else {
						if ((ranger_5_input_state == 6)){ 
							ranger_5_complex_p13 = ranger_5_complex_output_p;

							ranger_5_complex_input1_p_pos = ranger_5_complex_p0_pos;

							ranger_5_complex_input1_p_val = ranger_5_complex_p02;

							ranger_5_complex_input2_p_pos = ranger_5_complex_p3_pos;

							ranger_5_complex_input2_p_val = ranger_5_complex_p13;

							ranger_5_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_5_set_cubic_inputs_done ( ) {
	
}
static inline void ranger_5___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_5_complex_input1_p_pos, ranger_5_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_5_complex_input2_p_pos, ranger_5_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_5_complex_output_p = outputReg;
}
int int_state_vars_ranger_5 = 1;
void initStateVarsranger_5() {
ranger_5_ranger_5_State = FSM_ranger_5_state1;

}

int ranger_5(void)
{
  
	//OutputPorts
	extern int ch8_ready; 
	extern int ch8_valid; 
	extern uint64_t ch8_buffer[ch8_size];
	extern int ch9_ready; 
	extern int ch9_valid; 
	extern uint64_t ch9_buffer[ch9_size];
	ranger_5_ch8_buffer = ch8_buffer; 
	ranger_5_ch8_ready = &ch8_ready; 
	ranger_5_ch8_valid = &ch8_valid; 
	ranger_5_ch9_buffer = ch9_buffer; 
	ranger_5_ch9_ready = &ch9_ready; 
	ranger_5_ch9_valid = &ch9_valid; 
    
	if(int_state_vars_ranger_5 == 1){
		int_state_vars_ranger_5 = 0;
		initStateVarsranger_5();
	}
if ((ranger_5_ranger_5_IntCheckOutput == -1)){ 
	
ranger_5Schedule:

	
 switch (ranger_5_ranger_5_State) {
   case FSM_ranger_5_state1:
     		if (( ranger_5_inputData_index < NOF_PIXELS )){ 
			ranger_5_set_pa_pb();
			ranger_5_ranger_5_State = FSM_ranger_5_state3;

			goto ranger_5Schedule;
		}

		     break;

   case FSM_ranger_5_state3:
     		if (( ranger_5_range1_i < NOF_PIXELS_KERNEL )){ 
			ranger_5_range_int_loop_1();
			ranger_5_ranger_5_State = FSM_ranger_5_state4;

			goto ranger_5Schedule;
		}

					ranger_5_range_int_loop_1_done();
			ranger_5_ranger_5_State = FSM_ranger_5_state7;

			goto ranger_5Schedule;

		     break;

   case FSM_ranger_5_state4:
     		if ((ranger_5_input_state != 0)){ 
			ranger_5_set_cubic_inputs();
			ranger_5_ranger_5_State = FSM_ranger_5_state6;

			goto ranger_5Schedule;
		}

					ranger_5_set_cubic_inputs_done();
			ranger_5_ranger_5_State = FSM_ranger_5_state5;

			goto ranger_5Schedule;

		     break;

   case FSM_ranger_5_state5:
     					
ranger_5_Action_0:

			if (*ranger_5_ch8_ready == 1){ 
				ranger_5_store_ra_results();
				ranger_5_ranger_5_State = FSM_ranger_5_state3;

				goto ranger_5Schedule;
			}
			else {
				ranger_5_ranger_5_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_5_state6:
     					ranger_5___acc__cubic();
			ranger_5_ranger_5_State = FSM_ranger_5_state4;

			goto ranger_5Schedule;

		     break;

   case FSM_ranger_5_state7:
     		if (( ranger_5_range2_i < NOF_PIXELS_KERNEL )){ 
			ranger_5_range_int_loop_2();
			ranger_5_ranger_5_State = FSM_ranger_5_state8;

			goto ranger_5Schedule;
		}

					ranger_5_range_int_loop_2_done();
			ranger_5_ranger_5_State = FSM_ranger_5_state1;

			goto ranger_5Schedule;

		     break;

   case FSM_ranger_5_state8:
     		if ((ranger_5_input_state != 0)){ 
			ranger_5_set_cubic_inputs();
			ranger_5_ranger_5_State = FSM_ranger_5_state10;

			goto ranger_5Schedule;
		}

					ranger_5_set_cubic_inputs_done();
			ranger_5_ranger_5_State = FSM_ranger_5_state9;

			goto ranger_5Schedule;

		     break;

   case FSM_ranger_5_state9:
     					
ranger_5_Action_1:

			if (*ranger_5_ch9_ready == 1){ 
				ranger_5_store_rb_results();
				ranger_5_ranger_5_State = FSM_ranger_5_state7;

				goto ranger_5Schedule;
			}
			else {
				ranger_5_ranger_5_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_5_state10:
     					ranger_5___acc__cubic();
			ranger_5_ranger_5_State = FSM_ranger_5_state8;

			goto ranger_5Schedule;

		     break;

}

	ranger_5_ranger_5_IntCheckOutput = -1;

}
else {
	
 switch (ranger_5_ranger_5_IntCheckOutput) {
   case 0:
     		ranger_5_ranger_5_IntCheckOutput = -1;

		goto ranger_5_Action_0;
   case 1:
     		ranger_5_ranger_5_IntCheckOutput = -1;

		goto ranger_5_Action_1;
}

}
goto ranger_5Schedule;
}
