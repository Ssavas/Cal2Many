//code from range_actor.cal, instance ranger
#include <stdint.h>
#include <stdio.h>


//OutputPorts
 comm_handle_t ch0, ch1;
#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS (216) 
static float complex_SquareRoot_ret;
static float SquareRoot_ret;
static int64_t complex_p0_pos;
static int64_t complex_p0_val;
static int64_t complex_p1_pos;
static int64_t complex_p1_val;
static int64_t complex_p2_pos;
static int64_t complex_p2_val;
static int64_t complex_p3_pos;
static int64_t complex_p3_val;
static int64_t complex_p01;
static int64_t complex_p12;
static int64_t complex_p23;
static int64_t complex_p02;
static int64_t complex_p13;
static int64_t complex_input1_p_pos;
static int64_t complex_input1_p_val;
static int64_t complex_input2_p_pos;
static int64_t complex_input2_p_val;
static int64_t complex_output_p;
static int32_t input_state;
static int32_t range1_i = 0;
static int32_t range1_counter = 0;
static int32_t range2_i = 0;
static int32_t range2_counter = 0;
static int32_t ra_result_index = 0;
static int32_t rb_result_index = 0;
static int32_t beam1_i = 0;
static int32_t beam1_counter = 0;
static int32_t beam2_i = 0;
static int32_t beam2_counter = 0;
static int32_t ba_result_index = 0;
static int32_t bb_result_index = 0;
static int32_t inputData_index = 0;
static float total_sum;
static int64_t complex_pa[NOF_PIXELS_KERNEL][2];

static int64_t complex_pb[NOF_PIXELS_KERNEL][2];

static int64_t complex_ra[NOF_PIXELS_KERNEL][2];

static int64_t complex_rb[NOF_PIXELS_KERNEL][2];

static int64_t complex_ba[NOF_PIXELS_KERNEL][2];

static int64_t complex_bb[NOF_PIXELS_KERNEL][2];

static int32_t ranger_State;
#define FSM_ranger_state1 (0) 
#define FSM_ranger_state3 (1) 
#define FSM_ranger_state4 (2) 
#define FSM_ranger_state5 (3) 
#define FSM_ranger_state6 (4) 
#define FSM_ranger_state7 (5) 
#define FSM_ranger_state8 (6) 
#define FSM_ranger_state9 (7) 
#define FSM_ranger_state10 (8) 
static int32_t ranger_IntCheckOutput = -1;

static inline void ranger_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	printf("%d\n",);
	while (( j < NOF_PIXELS_KERNEL )) {
		complex_pa[j][0] = 1;
		complex_pa[j][1] = 1;
		complex_pb[j][0] = 1;
		complex_pb[j][1] = 1;
		j = (j + 1);

}

	range1_i = 0;

	range2_i = 0;

	inputData_index = (inputData_index + NOF_PIXELS_KERNEL);

  }
static inline void ranger_range_int_loop_1 ( ) {
	printf("%d\n",);
	complex_p0_pos = complex_pa[range1_i + range1_counter + 0][0];

	complex_p1_pos = complex_pa[range1_i + range1_counter + 1][0];

	complex_p2_pos = complex_pa[range1_i + range1_counter + 2][0];

	complex_p3_pos = complex_pa[range1_i + range1_counter + 3][0];

	input_state = 1;

	range1_counter = (range1_counter + 1);

	if ((range1_counter == 3)){ 
		range1_counter = 0;

		range1_i = (range1_i + 6);

	}

  }
static inline void ranger_range_int_loop_1_done ( ) {
	printf("range_int_loop_1_done\n");
  }
static inline void ranger_range_int_loop_2 ( ) {
	printf("%d\n",);
	complex_p0_pos = complex_pb[range2_i + range2_counter + 0][0];

	complex_p1_pos = complex_pb[range2_i + range2_counter + 1][0];

	complex_p2_pos = complex_pb[range2_i + range2_counter + 2][0];

	complex_p3_pos = complex_pb[range2_i + range2_counter + 3][0];

	input_state = 1;

	range2_counter = (range2_counter + 1);

	if ((range2_counter == 3)){ 
		range2_counter = 0;

		range2_i = (range2_i + 6);

	}

  }
static inline void ranger_range_int_loop_2_done ( ) {
	printf("range_int_loop_2_done\n");
  }
static inline void ranger_store_ra_results ( ) {
	printf("%d\n",);
	comm_write(ch0, &complex_output_p, 4); // send 4 bytes 

  }
static inline void ranger_store_rb_results ( ) {
	printf("%d\n",);
	comm_write(ch1, &complex_output_p, 4); // send 4 bytes 

  }
static inline void ranger_set_cubic_inputs ( ) {
	printf("set_cubic_inputs\n");
	if ((input_state == 1)){ 
		complex_input1_p_pos = complex_p0_pos;

		complex_input1_p_val = complex_p0_val;

		complex_input2_p_pos = complex_p1_pos;

		complex_input2_p_val = complex_p1_val;

		input_state = 2;

	}
	else {
		if ((input_state == 2)){ 
			complex_p01 = complex_output_p;

			complex_input1_p_pos = complex_p1_pos;

			complex_input1_p_val = complex_p1_val;

			complex_input2_p_pos = complex_p2_pos;

			complex_input2_p_val = complex_p2_val;

			input_state = 3;

		}
		else {
			if ((input_state == 3)){ 
				complex_p12 = complex_output_p;

				complex_input1_p_pos = complex_p2_pos;

				complex_input1_p_val = complex_p2_val;

				complex_input2_p_pos = complex_p3_pos;

				complex_input2_p_val = complex_p3_val;

				input_state = 4;

			}
			else {
				if ((input_state == 4)){ 
					complex_p23 = complex_output_p;

					complex_input1_p_pos = complex_p0_pos;

					complex_input1_p_val = complex_p01;

					complex_input2_p_pos = complex_p3_pos;

					complex_input2_p_val = complex_p12;

					input_state = 5;

				}
				else {
					if ((input_state == 5)){ 
						complex_p02 = complex_output_p;

						complex_input1_p_pos = complex_p1_pos;

						complex_input1_p_val = complex_p12;

						complex_input2_p_pos = complex_p3_pos;

						complex_input2_p_val = complex_p23;

						input_state = 6;

					}
					else {
						if ((input_state == 6)){ 
							complex_p13 = complex_output_p;

							complex_input1_p_pos = complex_p0_pos;

							complex_input1_p_val = complex_p02;

							complex_input2_p_pos = complex_p3_pos;

							complex_input2_p_val = complex_p13;

							input_state = 0;

						}

					}

				}

			}

		}

	}

  }
static inline void ranger_set_cubic_inputs_done ( ) {
	printf("set_cubic_inputs_done\n");
  }
static inline void ranger___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, complex_input1_p_pos, complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, complex_input2_p_pos, complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	complex_output_p = outputReg;
}
int int_state_vars_ranger = 1;
void initStateVarsranger() {
total_sum = 0.0;
ranger_State = FSM_ranger_state1;

}

int main(void)
{
  
	//OutputPorts
	ch0 = comm_get_whandle(channels, NUM_CHANNELS, 0);
	if(!ch0) {
		HOST(1) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch1 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch1) {
		HOST(1) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_ranger==1){
        int_state_vars_ranger = 0;
        initStateVarsranger();
	}
if ((ranger_IntCheckOutput == -1)){ 
	
rangerSchedule:

	
 switch (ranger_State) {
   case FSM_ranger_state1:
     		if (( inputData_index < NOF_PIXELS )){ 
			ranger_set_pa_pb();
			ranger_State = FSM_ranger_state3;

			goto rangerSchedule;
		}

		     break;

   case FSM_ranger_state3:
     		if (( range1_i < 36 )){ 
			ranger_range_int_loop_1();
			ranger_State = FSM_ranger_state4;

			goto rangerSchedule;
		}

					ranger_range_int_loop_1_done();
			ranger_State = FSM_ranger_state7;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state4:
     		if ((input_state != 0)){ 
			ranger_set_cubic_inputs();
			ranger_State = FSM_ranger_state6;

			goto rangerSchedule;
		}

					ranger_set_cubic_inputs_done();
			ranger_State = FSM_ranger_state5;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state5:
     					
ranger_Action_0:

			if ((comm_space(ch0) >= 1)){ 
				ranger_store_ra_results();
				ranger_State = FSM_ranger_state3;

				goto rangerSchedule;
			}
			else {
				ranger_IntCheckOutput = 0;

				return(0);
			}


		     break;

   case FSM_ranger_state6:
     					ranger___acc__cubic();
			ranger_State = FSM_ranger_state4;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state7:
     		if (( range2_i < 36 )){ 
			ranger_range_int_loop_2();
			ranger_State = FSM_ranger_state8;

			goto rangerSchedule;
		}

					ranger_range_int_loop_2_done();
			ranger_State = FSM_ranger_state1;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state8:
     		if ((input_state != 0)){ 
			ranger_set_cubic_inputs();
			ranger_State = FSM_ranger_state10;

			goto rangerSchedule;
		}

					ranger_set_cubic_inputs_done();
			ranger_State = FSM_ranger_state9;

			goto rangerSchedule;

		     break;

   case FSM_ranger_state9:
     					
ranger_Action_1:

			if ((comm_space(ch1) >= 1)){ 
				ranger_store_rb_results();
				ranger_State = FSM_ranger_state7;

				goto rangerSchedule;
			}
			else {
				ranger_IntCheckOutput = 1;

				return(0);
			}


		     break;

   case FSM_ranger_state10:
     					ranger___acc__cubic();
			ranger_State = FSM_ranger_state8;

			goto rangerSchedule;

		     break;

}

	ranger_IntCheckOutput = -1;

}
else {
	
 switch (ranger_IntCheckOutput) {
   case 0:
     		ranger_IntCheckOutput = -1;

		goto ranger_Action_0;
   case 1:
     		ranger_IntCheckOutput = -1;

		goto ranger_Action_1;
}

}
goto rangerSchedule;
}
