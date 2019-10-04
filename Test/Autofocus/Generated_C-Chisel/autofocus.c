//code from autofocus_c.cal, instance autofocus
#include <stdint.h>
#include <stdio.h>


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

static int32_t autofocus_State;
#define FSM_autofocus_state1 (0) 
#define FSM_autofocus_state2 (1) 
#define FSM_autofocus_state3 (2) 
#define FSM_autofocus_state4 (3) 
#define FSM_autofocus_state5 (4) 
#define FSM_autofocus_state6 (5) 
#define FSM_autofocus_state7 (6) 
#define FSM_autofocus_state8 (7) 
#define FSM_autofocus_state9 (8) 
#define FSM_autofocus_state10 (9) 
#define FSM_autofocus_state11 (10) 
#define FSM_autofocus_state12 (11) 
#define FSM_autofocus_state13 (12) 
#define FSM_autofocus_state14 (13) 
#define FSM_autofocus_state15 (14) 
#define FSM_autofocus_state16 (15) 
#define FSM_autofocus_state17 (16) 
#define FSM_autofocus_state18 (17) 
#define FSM_autofocus_state19 (18) 
#define FSM_autofocus_state20 (19) 
static void SquareRoot (float ns);
static void complex_SquareRoot (int ns);

static inline void autofocus_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	printf("%d\n",);
	while (( j < NOF_PIXELS_KERNEL )) {
		complex_pa[j][0] = 1;
		complex_pa[j][1] = 1;
		complex_pb[j][0] = 1;
		complex_pb[j][0] = 1;
		j = (j + 1);

}

	inputData_index = (inputData_index + NOF_PIXELS_KERNEL);

  }
static inline void autofocus_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	printf("set_ra_rb_pos\n");
	while (( i < 36 )) {
		complex_rb[i][0] = complex_pb[i][0];
		complex_ra[i][0] = complex_pa[i][0];
		i = (i + 6);

		range1_i = 0;

		range2_i = 0;

}

  }
static inline void autofocus_range_int_loop_1 ( ) {
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
static inline void autofocus_range_int_loop_1_done ( ) {
	printf("range_int_loop_1_done\n");
  }
static inline void autofocus_range_int_loop_2 ( ) {
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
static inline void autofocus_range_int_loop_2_done ( ) {
	printf("range_int_loop_2_done\n");
  }
static inline void autofocus_store_ra_results ( ) {
	printf("store_ra_results\n");
	complex_ra[ra_result_index][1] = complex_output_p;
	if (( ra_result_index < 18 )){ 
		ra_result_index = (ra_result_index + 1);

	}
	else {
		ra_result_index = 0;

	}

  }
static inline void autofocus_store_rb_results ( ) {
	printf("store_rb_results\n");
	complex_rb[rb_result_index][1] = complex_output_p;
	if (( rb_result_index < 18 )){ 
		rb_result_index = (rb_result_index + 1);

	}
	else {
		rb_result_index = 0;

	}

  }
static inline void autofocus_set_cubic_inputs ( ) {
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
static inline void autofocus_set_cubic_inputs_done ( ) {
	printf("set_cubic_inputs_done\n");
  }
static inline void autofocus__acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, complex_input1_p_pos, complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, complex_input2_p_pos, complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	complex_output_p = outputReg;
}
static inline void autofocus_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	printf("set_ra_rb_pos\n");
	while (( i < 6 )) {
		complex_ba[i][0] = complex_ra[i][0];
		complex_bb[i][0] = complex_rb[i][0];
		i = (i + 1);

		beam1_i = 0;

		beam2_i = 0;

}

  }
static inline void autofocus_beam_int_loop_1 ( ) {
	printf("%d\n",);
	complex_p0_pos = complex_ra[beam1_i + beam1_counter + 0][0];

	complex_p1_pos = complex_ra[beam1_i + beam1_counter + 3][0];

	complex_p2_pos = complex_ra[beam1_i + beam1_counter + 6][0];

	complex_p3_pos = complex_ra[beam1_i + beam1_counter + 9][0];

	input_state = 1;

	beam1_counter = (beam1_counter + 3);

	if ((beam1_counter == 9)){ 
		beam1_counter = 0;

		beam1_i = (beam1_i + 1);

	}

  }
static inline void autofocus_beam_int_loop_1_done ( ) {
	printf("beam_int_loop_1_done\n");
  }
static inline void autofocus_beam_int_loop_2 ( ) {
	printf("%d\n",);
	complex_p0_pos = complex_rb[beam2_i + beam2_counter + 0][0];

	complex_p1_pos = complex_rb[beam2_i + beam2_counter + 3][0];

	complex_p2_pos = complex_rb[beam2_i + beam2_counter + 6][0];

	complex_p3_pos = complex_rb[beam2_i + beam2_counter + 9][0];

	input_state = 1;

	beam2_counter = (beam2_counter + 3);

	if ((beam2_counter == 9)){ 
		beam2_counter = 0;

		beam2_i = (beam2_i + 1);

	}

  }
static inline void autofocus_beam_int_loop_2_done ( ) {
	printf("beam_int_loop_2_done\n");
  }
static inline void autofocus_store_ba_results ( ) {
	printf("%d\n",);
	complex_ba[ba_result_index][1] = complex_output_p;
	ba_result_index = (ba_result_index + 3);

	if ((ba_result_index == 9)){ 
		ba_result_index = 1;

	}

	if ((ba_result_index == 10)){ 
		ba_result_index = 2;

	}

	if ((ba_result_index == 11)){ 
		ba_result_index = 0;

	}

  }
static inline void autofocus_store_bb_results ( ) {
	printf("store_bb_results\n");
	complex_bb[bb_result_index][1] = complex_output_p;
	bb_result_index = (bb_result_index + 3);

	if ((bb_result_index == 9)){ 
		bb_result_index = 1;

	}

	if ((bb_result_index == 10)){ 
		bb_result_index = 2;

	}

	if ((bb_result_index == 11)){ 
		bb_result_index = 0;

	}

  }
static inline void autofocus_correlation ( ) {
	float tmp1;
	float sum;
	int32_t i;
	printf("correlation\n");
	i = 0;

	sum = 0.0;

	while (( i < 9 )) {
		complex_SquareRoot(complex_ba[i][1]);
		tmp1 = SquareRoot_ret;

		complex_SquareRoot(complex_bb[i][1]);
		sum = (sum + tmp1 * tmp1 * SquareRoot_ret * SquareRoot_ret);

		i = (i + 1);

}

	total_sum = (total_sum + sum);

	printf("%d\n",);
  }
static void SquareRoot (float ns) { 
	float i = 0.0;
	float x1;
	float x2;
	int32_t j = 0;
	while (( (i * i) <= ns )) {
		i = (i + 0.1);

}

	x1 = i;

	while (( j < 10 )) {
		x2 = ns;

		x2 = (x2 / x1);

		x2 = (x2 + x1);

		x2 = (x2 / 2);

		x1 = x2;

		j = (j + 1);

}

	SquareRoot_ret = x2;


 }

static void complex_SquareRoot (int ns) { 

 }

int int_state_vars_autofocus = 1;
void initStateVarsautofocus() {
total_sum = 0.0;
autofocus_State = FSM_autofocus_state1;

}

int main(void)
{
      if(int_state_vars_autofocus==1){
        int_state_vars_autofocus = 0;
        initStateVarsautofocus();
	}

autofocusSchedule:

 switch (autofocus_State) {
   case FSM_autofocus_state1:
     	if (( inputData_index < NOF_PIXELS )){ 
		autofocus_set_pa_pb();
		autofocus_State = FSM_autofocus_state2;

		goto autofocusSchedule;
	}

	     break;

   case FSM_autofocus_state2:
     			autofocus_set_ra_rb_pos();
		autofocus_State = FSM_autofocus_state3;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state3:
     	if (( range1_i < 36 )){ 
		autofocus_range_int_loop_1();
		autofocus_State = FSM_autofocus_state4;

		goto autofocusSchedule;
	}

			autofocus_range_int_loop_1_done();
		autofocus_State = FSM_autofocus_state7;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state4:
     	if ((input_state != 0)){ 
		autofocus_set_cubic_inputs();
		autofocus_State = FSM_autofocus_state6;

		goto autofocusSchedule;
	}

			autofocus_set_cubic_inputs_done();
		autofocus_State = FSM_autofocus_state5;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state5:
     			autofocus_store_ra_results();
		autofocus_State = FSM_autofocus_state3;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state6:
     			autofocus__acc__cubic();
		autofocus_State = FSM_autofocus_state4;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state7:
     	if (( range2_i < 36 )){ 
		autofocus_range_int_loop_2();
		autofocus_State = FSM_autofocus_state8;

		goto autofocusSchedule;
	}

			autofocus_range_int_loop_2_done();
		autofocus_State = FSM_autofocus_state11;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state8:
     	if ((input_state != 0)){ 
		autofocus_set_cubic_inputs();
		autofocus_State = FSM_autofocus_state10;

		goto autofocusSchedule;
	}

			autofocus_set_cubic_inputs_done();
		autofocus_State = FSM_autofocus_state9;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state9:
     			autofocus_store_rb_results();
		autofocus_State = FSM_autofocus_state7;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state10:
     			autofocus__acc__cubic();
		autofocus_State = FSM_autofocus_state8;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state11:
     			autofocus_set_ba_bb_pos();
		autofocus_State = FSM_autofocus_state12;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state12:
     	if (( beam1_i < 3 )){ 
		autofocus_beam_int_loop_1();
		autofocus_State = FSM_autofocus_state13;

		goto autofocusSchedule;
	}

			autofocus_beam_int_loop_1_done();
		autofocus_State = FSM_autofocus_state16;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state13:
     	if ((input_state != 0)){ 
		autofocus_set_cubic_inputs();
		autofocus_State = FSM_autofocus_state15;

		goto autofocusSchedule;
	}

			autofocus_set_cubic_inputs_done();
		autofocus_State = FSM_autofocus_state14;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state14:
     			autofocus_store_ba_results();
		autofocus_State = FSM_autofocus_state12;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state15:
     			autofocus__acc__cubic();
		autofocus_State = FSM_autofocus_state13;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state16:
     	if (( beam2_i < 3 )){ 
		autofocus_beam_int_loop_2();
		autofocus_State = FSM_autofocus_state17;

		goto autofocusSchedule;
	}

			autofocus_beam_int_loop_2_done();
		autofocus_State = FSM_autofocus_state20;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state17:
     	if ((input_state != 0)){ 
		autofocus_set_cubic_inputs();
		autofocus_State = FSM_autofocus_state19;

		goto autofocusSchedule;
	}

			autofocus_set_cubic_inputs_done();
		autofocus_State = FSM_autofocus_state18;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state18:
     			autofocus_store_bb_results();
		autofocus_State = FSM_autofocus_state16;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state19:
     			autofocus__acc__cubic();
		autofocus_State = FSM_autofocus_state17;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state20:
     			autofocus_correlation();
		autofocus_State = FSM_autofocus_state1;

		goto autofocusSchedule;

	     break;

}
goto autofocusSchedule;
}
