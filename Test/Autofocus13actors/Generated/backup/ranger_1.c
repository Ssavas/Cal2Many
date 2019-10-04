//code from range_actor.cal, instance ranger_1
#include <stdint.h>
#include <string.h>
#include "ranger_1.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_1_ch0_buffer;
uint64_t* ranger_1_ch1_buffer;
int* ranger_1_ch0_ready;
int* ranger_1_ch0_valid;
int* ranger_1_ch1_ready;
int* ranger_1_ch1_valid;

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t ranger_1_complex_p0_pos SECTION(".core0.data");
int64_t ranger_1_complex_p0_val SECTION(".core0.data");
int64_t ranger_1_complex_p1_pos SECTION(".core0.data");
int64_t ranger_1_complex_p1_val SECTION(".core0.data");
int64_t ranger_1_complex_p2_pos SECTION(".core0.data");
int64_t ranger_1_complex_p2_val SECTION(".core0.data");
int64_t ranger_1_complex_p3_pos SECTION(".core0.data");
int64_t ranger_1_complex_p3_val SECTION(".core0.data");
int64_t ranger_1_complex_p01 SECTION(".core0.data");
int64_t ranger_1_complex_p12 SECTION(".core0.data");
int64_t ranger_1_complex_p23 SECTION(".core0.data");
int64_t ranger_1_complex_p02 SECTION(".core0.data");
int64_t ranger_1_complex_p13 SECTION(".core0.data");
int64_t ranger_1_complex_input1_p_pos SECTION(".core0.data");
int64_t ranger_1_complex_input1_p_val SECTION(".core0.data");
int64_t ranger_1_complex_input2_p_pos SECTION(".core0.data");
int64_t ranger_1_complex_input2_p_val SECTION(".core0.data");
int64_t ranger_1_complex_output_p SECTION(".core0.data");
int32_t ranger_1_input_state SECTION(".core0.data");
int32_t ranger_1_range1_i SECTION(".core0.data") = 0;
int32_t ranger_1_range1_counter SECTION(".core0.data") = 0;
int32_t ranger_1_range2_i SECTION(".core0.data") = 0;
int32_t ranger_1_range2_counter SECTION(".core0.data") = 0;
int32_t ranger_1_inputData_index SECTION(".core0.data") = 0;
int64_t ranger_1_complex_pa[NOF_PIXELS_KERNEL][2];

int64_t ranger_1_complex_pb[NOF_PIXELS_KERNEL][2];

int32_t ranger_1_ranger_1_State SECTION(".core0.data");
#define FSM_ranger_1_state1 (0) 
#define FSM_ranger_1_state3 (1) 
#define FSM_ranger_1_state4 (2) 
#define FSM_ranger_1_state5 (3) 
#define FSM_ranger_1_state6 (4) 
#define FSM_ranger_1_state7 (5) 
#define FSM_ranger_1_state8 (6) 
#define FSM_ranger_1_state9 (7) 
#define FSM_ranger_1_state10 (8) 
int32_t ranger_1_ranger_1_IntCheckOutput SECTION(".core0.data") = -1;

static inline void ranger_1_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_1_complex_pa[j][0] = 1;
		ranger_1_complex_pa[j][1] = 1;
		ranger_1_complex_pb[j][0] = 1;
		ranger_1_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_1_range1_i = 0;

	ranger_1_range2_i = 0;

	ranger_1_inputData_index = (ranger_1_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_1_range_int_loop_1 ( ) {
	
	ranger_1_complex_p0_pos = ranger_1_complex_pa[ranger_1_range1_i + ranger_1_range1_counter + 0][0];

	ranger_1_complex_p1_pos = ranger_1_complex_pa[ranger_1_range1_i + ranger_1_range1_counter + 1][0];

	ranger_1_complex_p2_pos = ranger_1_complex_pa[ranger_1_range1_i + ranger_1_range1_counter + 2][0];

	ranger_1_complex_p3_pos = ranger_1_complex_pa[ranger_1_range1_i + ranger_1_range1_counter + 3][0];

	ranger_1_input_state = 1;

	ranger_1_range1_counter = (ranger_1_range1_counter + 1);

	if ((ranger_1_range1_counter == 3)){ 
		ranger_1_range1_counter = 0;

		ranger_1_range1_i = (ranger_1_range1_i + 6);

	}

}
static inline void ranger_1_range_int_loop_1_done ( ) {
	
}
static inline void ranger_1_range_int_loop_2 ( ) {
	
	ranger_1_complex_p0_pos = ranger_1_complex_pb[ranger_1_range2_i + ranger_1_range2_counter + 0][0];

	ranger_1_complex_p1_pos = ranger_1_complex_pb[ranger_1_range2_i + ranger_1_range2_counter + 1][0];

	ranger_1_complex_p2_pos = ranger_1_complex_pb[ranger_1_range2_i + ranger_1_range2_counter + 2][0];

	ranger_1_complex_p3_pos = ranger_1_complex_pb[ranger_1_range2_i + ranger_1_range2_counter + 3][0];

	ranger_1_input_state = 1;

	ranger_1_range2_counter = (ranger_1_range2_counter + 1);

	if ((ranger_1_range2_counter == 3)){ 
		ranger_1_range2_counter = 0;

		ranger_1_range2_i = (ranger_1_range2_i + 6);

	}

}
static inline void ranger_1_range_int_loop_2_done ( ) {
	
}
static inline void ranger_1_store_ra_results ( ) {
	
	*ranger_1_ch0_buffer = ranger_1_complex_output_p;//write output
	*ranger_1_ch0_ready = 0; //channel NOT ready to receive new data
	*ranger_1_ch0_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_1_store_rb_results ( ) {
	
	*ranger_1_ch1_buffer = ranger_1_complex_output_p;//write output
	*ranger_1_ch1_ready = 0; //channel NOT ready to receive new data
	*ranger_1_ch1_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_1_set_cubic_inputs ( ) {
	
	if ((ranger_1_input_state == 1)){ 
		ranger_1_complex_input1_p_pos = ranger_1_complex_p0_pos;

		ranger_1_complex_input1_p_val = ranger_1_complex_p0_val;

		ranger_1_complex_input2_p_pos = ranger_1_complex_p1_pos;

		ranger_1_complex_input2_p_val = ranger_1_complex_p1_val;

		ranger_1_input_state = 2;

	}
	else {
		if ((ranger_1_input_state == 2)){ 
			ranger_1_complex_p01 = ranger_1_complex_output_p;

			ranger_1_complex_input1_p_pos = ranger_1_complex_p1_pos;

			ranger_1_complex_input1_p_val = ranger_1_complex_p1_val;

			ranger_1_complex_input2_p_pos = ranger_1_complex_p2_pos;

			ranger_1_complex_input2_p_val = ranger_1_complex_p2_val;

			ranger_1_input_state = 3;

		}
		else {
			if ((ranger_1_input_state == 3)){ 
				ranger_1_complex_p12 = ranger_1_complex_output_p;

				ranger_1_complex_input1_p_pos = ranger_1_complex_p2_pos;

				ranger_1_complex_input1_p_val = ranger_1_complex_p2_val;

				ranger_1_complex_input2_p_pos = ranger_1_complex_p3_pos;

				ranger_1_complex_input2_p_val = ranger_1_complex_p3_val;

				ranger_1_input_state = 4;

			}
			else {
				if ((ranger_1_input_state == 4)){ 
					ranger_1_complex_p23 = ranger_1_complex_output_p;

					ranger_1_complex_input1_p_pos = ranger_1_complex_p0_pos;

					ranger_1_complex_input1_p_val = ranger_1_complex_p01;

					ranger_1_complex_input2_p_pos = ranger_1_complex_p3_pos;

					ranger_1_complex_input2_p_val = ranger_1_complex_p12;

					ranger_1_input_state = 5;

				}
				else {
					if ((ranger_1_input_state == 5)){ 
						ranger_1_complex_p02 = ranger_1_complex_output_p;

						ranger_1_complex_input1_p_pos = ranger_1_complex_p1_pos;

						ranger_1_complex_input1_p_val = ranger_1_complex_p12;

						ranger_1_complex_input2_p_pos = ranger_1_complex_p3_pos;

						ranger_1_complex_input2_p_val = ranger_1_complex_p23;

						ranger_1_input_state = 6;

					}
					else {
						if ((ranger_1_input_state == 6)){ 
							ranger_1_complex_p13 = ranger_1_complex_output_p;

							ranger_1_complex_input1_p_pos = ranger_1_complex_p0_pos;

							ranger_1_complex_input1_p_val = ranger_1_complex_p02;

							ranger_1_complex_input2_p_pos = ranger_1_complex_p3_pos;

							ranger_1_complex_input2_p_val = ranger_1_complex_p13;

							ranger_1_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_1_set_cubic_inputs_done ( ) {
	
}
static inline void ranger_1___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_1_complex_input1_p_pos, ranger_1_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_1_complex_input2_p_pos, ranger_1_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_1_complex_output_p = outputReg;
}
int int_state_vars_ranger_1 = 1;
void initStateVarsranger_1() {
ranger_1_ranger_1_State = FSM_ranger_1_state1;

}

int ranger_1(void)
{
  
	//OutputPorts
	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[ch0_size];
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[ch1_size];
	ranger_1_ch0_buffer = ch0_buffer; 
	ranger_1_ch0_ready = &ch0_ready; 
	ranger_1_ch0_valid = &ch0_valid; 
	ranger_1_ch1_buffer = ch1_buffer; 
	ranger_1_ch1_ready = &ch1_ready; 
	ranger_1_ch1_valid = &ch1_valid; 
    
	if(int_state_vars_ranger_1 == 1){
		int_state_vars_ranger_1 = 0;
		initStateVarsranger_1();
	}
if ((ranger_1_ranger_1_IntCheckOutput == -1)){ 
	
ranger_1Schedule:

	
 switch (ranger_1_ranger_1_State) {
   case FSM_ranger_1_state1:
     		if (( ranger_1_inputData_index < NOF_PIXELS )){ 
			ranger_1_set_pa_pb();
			ranger_1_ranger_1_State = FSM_ranger_1_state3;

			goto ranger_1Schedule;
		}

		     break;

   case FSM_ranger_1_state3:
     		if (( ranger_1_range1_i < NOF_PIXELS_KERNEL )){ 
			ranger_1_range_int_loop_1();
			ranger_1_ranger_1_State = FSM_ranger_1_state4;

			goto ranger_1Schedule;
		}

					ranger_1_range_int_loop_1_done();
			ranger_1_ranger_1_State = FSM_ranger_1_state7;

			goto ranger_1Schedule;

		     break;

   case FSM_ranger_1_state4:
     		if ((ranger_1_input_state != 0)){ 
			ranger_1_set_cubic_inputs();
			ranger_1_ranger_1_State = FSM_ranger_1_state6;

			goto ranger_1Schedule;
		}

					ranger_1_set_cubic_inputs_done();
			ranger_1_ranger_1_State = FSM_ranger_1_state5;

			goto ranger_1Schedule;

		     break;

   case FSM_ranger_1_state5:
     					
ranger_1_Action_0:

			if (*ranger_1_ch0_ready == 1){ 
				ranger_1_store_ra_results();
				ranger_1_ranger_1_State = FSM_ranger_1_state3;

				goto ranger_1Schedule;
			}
			else {
				ranger_1_ranger_1_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_1_state6:
     					ranger_1___acc__cubic();
			ranger_1_ranger_1_State = FSM_ranger_1_state4;

			goto ranger_1Schedule;

		     break;

   case FSM_ranger_1_state7:
     		if (( ranger_1_range2_i < NOF_PIXELS_KERNEL )){ 
			ranger_1_range_int_loop_2();
			ranger_1_ranger_1_State = FSM_ranger_1_state8;

			goto ranger_1Schedule;
		}

					ranger_1_range_int_loop_2_done();
			ranger_1_ranger_1_State = FSM_ranger_1_state1;

			goto ranger_1Schedule;

		     break;

   case FSM_ranger_1_state8:
     		if ((ranger_1_input_state != 0)){ 
			ranger_1_set_cubic_inputs();
			ranger_1_ranger_1_State = FSM_ranger_1_state10;

			goto ranger_1Schedule;
		}

					ranger_1_set_cubic_inputs_done();
			ranger_1_ranger_1_State = FSM_ranger_1_state9;

			goto ranger_1Schedule;

		     break;

   case FSM_ranger_1_state9:
     					
ranger_1_Action_1:

			if (*ranger_1_ch1_ready == 1){ 
				ranger_1_store_rb_results();
				ranger_1_ranger_1_State = FSM_ranger_1_state7;

				goto ranger_1Schedule;
			}
			else {
				ranger_1_ranger_1_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_1_state10:
     					ranger_1___acc__cubic();
			ranger_1_ranger_1_State = FSM_ranger_1_state8;

			goto ranger_1Schedule;

		     break;

}

	ranger_1_ranger_1_IntCheckOutput = -1;

}
else {
	
 switch (ranger_1_ranger_1_IntCheckOutput) {
   case 0:
     		ranger_1_ranger_1_IntCheckOutput = -1;

		goto ranger_1_Action_0;
   case 1:
     		ranger_1_ranger_1_IntCheckOutput = -1;

		goto ranger_1_Action_1;
}

}
goto ranger_1Schedule;
}
