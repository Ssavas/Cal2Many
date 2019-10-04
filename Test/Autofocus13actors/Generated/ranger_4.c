//code from range_actor.cal, instance ranger_4
#include <stdint.h>
#include <string.h>
#include "ranger_4.h"
#include "common.h"


//OutputPorts
uint64_t* ranger_4_ch6_buffer SECTION(".core3.data");
uint64_t* ranger_4_ch7_buffer SECTION(".core3.data");
volatile int* ranger_4_ch6_ready SECTION(".core3.data");
volatile int* ranger_4_ch6_valid SECTION(".core3.data");
volatile int* ranger_4_ch7_ready SECTION(".core3.data");
volatile int* ranger_4_ch7_valid SECTION(".core3.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS ((216 / 6)) 
int64_t ranger_4_complex_p0_pos SECTION(".core3.data");
int64_t ranger_4_complex_p0_val SECTION(".core3.data");
int64_t ranger_4_complex_p1_pos SECTION(".core3.data");
int64_t ranger_4_complex_p1_val SECTION(".core3.data");
int64_t ranger_4_complex_p2_pos SECTION(".core3.data");
int64_t ranger_4_complex_p2_val SECTION(".core3.data");
int64_t ranger_4_complex_p3_pos SECTION(".core3.data");
int64_t ranger_4_complex_p3_val SECTION(".core3.data");
int64_t ranger_4_complex_p01 SECTION(".core3.data");
int64_t ranger_4_complex_p12 SECTION(".core3.data");
int64_t ranger_4_complex_p23 SECTION(".core3.data");
int64_t ranger_4_complex_p02 SECTION(".core3.data");
int64_t ranger_4_complex_p13 SECTION(".core3.data");
int64_t ranger_4_complex_input1_p_pos SECTION(".core3.data");
int64_t ranger_4_complex_input1_p_val SECTION(".core3.data");
int64_t ranger_4_complex_input2_p_pos SECTION(".core3.data");
int64_t ranger_4_complex_input2_p_val SECTION(".core3.data");
int64_t ranger_4_complex_output_p SECTION(".core3.data");
int32_t ranger_4_input_state SECTION(".core3.data");
int32_t ranger_4_range1_i SECTION(".core3.data") = 0;
int32_t ranger_4_range1_counter SECTION(".core3.data") = 0;
int32_t ranger_4_range2_i SECTION(".core3.data") = 0;
int32_t ranger_4_range2_counter SECTION(".core3.data") = 0;
int32_t ranger_4_inputData_index SECTION(".core3.data") = 0;
int64_t ranger_4_complex_pa[NOF_PIXELS_KERNEL][2] SECTION(".core3.data");

int64_t ranger_4_complex_pb[NOF_PIXELS_KERNEL][2] SECTION(".core3.data");

int32_t ranger_4_ranger_4_State SECTION(".core3.data");
#define FSM_ranger_4_state1 (0) 
#define FSM_ranger_4_state3 (1) 
#define FSM_ranger_4_state4 (2) 
#define FSM_ranger_4_state5 (3) 
#define FSM_ranger_4_state6 (4) 
#define FSM_ranger_4_state7 (5) 
#define FSM_ranger_4_state8 (6) 
#define FSM_ranger_4_state9 (7) 
#define FSM_ranger_4_state10 (8) 
int32_t ranger_4_ranger_4_IntCheckOutput SECTION(".core3.data") = -1;
int ranger_4_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void ranger_4_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	
	while (( j < NOF_PIXELS_KERNEL )) {
		ranger_4_complex_pa[j][0] = 1;
		ranger_4_complex_pa[j][1] = 1;
		ranger_4_complex_pb[j][0] = 1;
		ranger_4_complex_pb[j][1] = 1;
		j = (j + 1);

	}

	ranger_4_range1_i = 0;

	ranger_4_range2_i = 0;

	ranger_4_inputData_index = (ranger_4_inputData_index + NOF_PIXELS_KERNEL);

}
static inline void ranger_4_range_int_loop_1 ( ) {
	
	ranger_4_complex_p0_pos = ranger_4_complex_pa[ranger_4_range1_i + ranger_4_range1_counter + 0][0];

	ranger_4_complex_p1_pos = ranger_4_complex_pa[ranger_4_range1_i + ranger_4_range1_counter + 1][0];

	ranger_4_complex_p2_pos = ranger_4_complex_pa[ranger_4_range1_i + ranger_4_range1_counter + 2][0];

	ranger_4_complex_p3_pos = ranger_4_complex_pa[ranger_4_range1_i + ranger_4_range1_counter + 3][0];

	ranger_4_input_state = 1;

	ranger_4_range1_counter = (ranger_4_range1_counter + 1);

	if ((ranger_4_range1_counter == 3)){ 
		ranger_4_range1_counter = 0;

		ranger_4_range1_i = (ranger_4_range1_i + 6);

	}

}
static inline void ranger_4_range_int_loop_1_done ( ) {
	
}
static inline void ranger_4_range_int_loop_2 ( ) {
	
	ranger_4_complex_p0_pos = ranger_4_complex_pb[ranger_4_range2_i + ranger_4_range2_counter + 0][0];

	ranger_4_complex_p1_pos = ranger_4_complex_pb[ranger_4_range2_i + ranger_4_range2_counter + 1][0];

	ranger_4_complex_p2_pos = ranger_4_complex_pb[ranger_4_range2_i + ranger_4_range2_counter + 2][0];

	ranger_4_complex_p3_pos = ranger_4_complex_pb[ranger_4_range2_i + ranger_4_range2_counter + 3][0];

	ranger_4_input_state = 1;

	ranger_4_range2_counter = (ranger_4_range2_counter + 1);

	if ((ranger_4_range2_counter == 3)){ 
		ranger_4_range2_counter = 0;

		ranger_4_range2_i = (ranger_4_range2_i + 6);

	}

}
static inline void ranger_4_range_int_loop_2_done ( ) {
	
}
static inline void ranger_4_store_ra_results ( ) {
	
	while(*ranger_4_ch6_ready == 0);// Wait for the ready signal. 
	*ranger_4_ch6_buffer = ranger_4_complex_output_p;//write output
	*ranger_4_ch6_ready = 0; //channel NOT ready to receive new data
	*ranger_4_ch6_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_4_store_rb_results ( ) {
	
	while(*ranger_4_ch7_ready == 0);// Wait for the ready signal. 
	*ranger_4_ch7_buffer = ranger_4_complex_output_p;//write output
	*ranger_4_ch7_ready = 0; //channel NOT ready to receive new data
	*ranger_4_ch7_valid = 1; //(because) channel has new data 
	
}
static inline void ranger_4_set_cubic_inputs ( ) {
	
	if ((ranger_4_input_state == 1)){ 
		ranger_4_complex_input1_p_pos = ranger_4_complex_p0_pos;

		ranger_4_complex_input1_p_val = ranger_4_complex_p0_val;

		ranger_4_complex_input2_p_pos = ranger_4_complex_p1_pos;

		ranger_4_complex_input2_p_val = ranger_4_complex_p1_val;

		ranger_4_input_state = 2;

	}
	else {
		if ((ranger_4_input_state == 2)){ 
			ranger_4_complex_p01 = ranger_4_complex_output_p;

			ranger_4_complex_input1_p_pos = ranger_4_complex_p1_pos;

			ranger_4_complex_input1_p_val = ranger_4_complex_p1_val;

			ranger_4_complex_input2_p_pos = ranger_4_complex_p2_pos;

			ranger_4_complex_input2_p_val = ranger_4_complex_p2_val;

			ranger_4_input_state = 3;

		}
		else {
			if ((ranger_4_input_state == 3)){ 
				ranger_4_complex_p12 = ranger_4_complex_output_p;

				ranger_4_complex_input1_p_pos = ranger_4_complex_p2_pos;

				ranger_4_complex_input1_p_val = ranger_4_complex_p2_val;

				ranger_4_complex_input2_p_pos = ranger_4_complex_p3_pos;

				ranger_4_complex_input2_p_val = ranger_4_complex_p3_val;

				ranger_4_input_state = 4;

			}
			else {
				if ((ranger_4_input_state == 4)){ 
					ranger_4_complex_p23 = ranger_4_complex_output_p;

					ranger_4_complex_input1_p_pos = ranger_4_complex_p0_pos;

					ranger_4_complex_input1_p_val = ranger_4_complex_p01;

					ranger_4_complex_input2_p_pos = ranger_4_complex_p3_pos;

					ranger_4_complex_input2_p_val = ranger_4_complex_p12;

					ranger_4_input_state = 5;

				}
				else {
					if ((ranger_4_input_state == 5)){ 
						ranger_4_complex_p02 = ranger_4_complex_output_p;

						ranger_4_complex_input1_p_pos = ranger_4_complex_p1_pos;

						ranger_4_complex_input1_p_val = ranger_4_complex_p12;

						ranger_4_complex_input2_p_pos = ranger_4_complex_p3_pos;

						ranger_4_complex_input2_p_val = ranger_4_complex_p23;

						ranger_4_input_state = 6;

					}
					else {
						if ((ranger_4_input_state == 6)){ 
							ranger_4_complex_p13 = ranger_4_complex_output_p;

							ranger_4_complex_input1_p_pos = ranger_4_complex_p0_pos;

							ranger_4_complex_input1_p_val = ranger_4_complex_p02;

							ranger_4_complex_input2_p_pos = ranger_4_complex_p3_pos;

							ranger_4_complex_input2_p_val = ranger_4_complex_p13;

							ranger_4_input_state = 0;

						}

					}

				}

			}

		}

	}

}
static inline void ranger_4_set_cubic_inputs_done ( ) {
	
}
static inline void ranger_4___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, ranger_4_complex_input1_p_pos, ranger_4_complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, ranger_4_complex_input2_p_pos, ranger_4_complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	ranger_4_complex_output_p = outputReg;
}
int int_state_vars_ranger_4 SECTION(".core3.data") = 1;
void initStateVarsranger_4() {
	ranger_4_ranger_4_State = FSM_ranger_4_state1;

}

int ranger_4(void)
{
  
	//OutputPorts
	extern int ch6_ready; 
	extern int ch6_valid; 
	extern uint64_t ch6_buffer[ch6_size];
	extern int ch7_ready; 
	extern int ch7_valid; 
	extern uint64_t ch7_buffer[ch7_size];
	ranger_4_ch6_buffer = ch6_buffer; 
	ranger_4_ch6_ready = &ch6_ready; 
	ranger_4_ch6_valid = &ch6_valid; 
	ranger_4_ch7_buffer = ch7_buffer; 
	ranger_4_ch7_ready = &ch7_ready; 
	ranger_4_ch7_valid = &ch7_valid; 
    
	if(int_state_vars_ranger_4 == 1){
		int_state_vars_ranger_4 = 0;
		initStateVarsranger_4();
	}
if ((ranger_4_ranger_4_IntCheckOutput == -1)){ 
	
ranger_4Schedule:

	
 switch (ranger_4_ranger_4_State) {
   case FSM_ranger_4_state1:
     		if (( ranger_4_inputData_index < NOF_PIXELS )){ 
			ranger_4_set_pa_pb();
			ranger_4_ranger_4_State = FSM_ranger_4_state3;

			goto ranger_4Schedule;
		}

		     break;

   case FSM_ranger_4_state3:
     		if (( ranger_4_range1_i < NOF_PIXELS_KERNEL )){ 
			ranger_4_range_int_loop_1();
			ranger_4_ranger_4_State = FSM_ranger_4_state4;

			goto ranger_4Schedule;
		}

					ranger_4_range_int_loop_1_done();
			ranger_4_ranger_4_State = FSM_ranger_4_state7;

			goto ranger_4Schedule;

		     break;

   case FSM_ranger_4_state4:
     		if ((ranger_4_input_state != 0)){ 
			ranger_4_set_cubic_inputs();
			ranger_4_ranger_4_State = FSM_ranger_4_state6;

			goto ranger_4Schedule;
		}

					ranger_4_set_cubic_inputs_done();
			ranger_4_ranger_4_State = FSM_ranger_4_state5;

			goto ranger_4Schedule;

		     break;

   case FSM_ranger_4_state5:
     					
ranger_4_Action_0:

			if (1){ 
				ranger_4_store_ra_results();
				ranger_4_ranger_4_State = FSM_ranger_4_state3;

				goto ranger_4Schedule;
			}
			else {
				ranger_4_ranger_4_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_4_state6:
     					ranger_4___acc__cubic();
			ranger_4_ranger_4_State = FSM_ranger_4_state4;

			goto ranger_4Schedule;

		     break;

   case FSM_ranger_4_state7:
     		if (( ranger_4_range2_i < NOF_PIXELS_KERNEL )){ 
			ranger_4_range_int_loop_2();
			ranger_4_ranger_4_State = FSM_ranger_4_state8;

			goto ranger_4Schedule;
		}

					ranger_4_range_int_loop_2_done();
			ranger_4_ranger_4_State = FSM_ranger_4_state1;

			goto ranger_4Schedule;

		     break;

   case FSM_ranger_4_state8:
     		if ((ranger_4_input_state != 0)){ 
			ranger_4_set_cubic_inputs();
			ranger_4_ranger_4_State = FSM_ranger_4_state10;

			goto ranger_4Schedule;
		}

					ranger_4_set_cubic_inputs_done();
			ranger_4_ranger_4_State = FSM_ranger_4_state9;

			goto ranger_4Schedule;

		     break;

   case FSM_ranger_4_state9:
     					
ranger_4_Action_1:

			if (1){ 
				ranger_4_store_rb_results();
				ranger_4_ranger_4_State = FSM_ranger_4_state7;

				goto ranger_4Schedule;
			}
			else {
				ranger_4_ranger_4_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_4_state10:
     					ranger_4___acc__cubic();
			ranger_4_ranger_4_State = FSM_ranger_4_state8;

			goto ranger_4Schedule;

		     break;

}

	ranger_4_ranger_4_IntCheckOutput = -1;

}
else {
	
 switch (ranger_4_ranger_4_IntCheckOutput) {
   case 0:
     		ranger_4_ranger_4_IntCheckOutput = -1;

		goto ranger_4_Action_0;
   case 1:
     		ranger_4_ranger_4_IntCheckOutput = -1;

		goto ranger_4_Action_1;
}

}
goto ranger_4Schedule;
}
