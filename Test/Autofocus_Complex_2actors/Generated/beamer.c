//code from beam_actor.cal, instance beamer
#include <stdint.h>
#include <stdio.h>

//InputPorts
 comm_handle_t ch0, ch1;
#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS (216) 
static float C_mag_ret;
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
static int64_t correlation_input1;
static int64_t correlation_input2;
static int32_t input_state;
static int32_t beam1_i = 0;
static int32_t beam1_counter = 0;
static int32_t beam2_i = 0;
static int32_t beam2_counter = 0;
static int32_t ba_result_index = 0;
static int32_t bb_result_index = 0;
static int32_t correlation_counter = 0;
static int32_t inputData_index = 0;
static float total_sum;
static int64_t complex_ra[(NOF_PIXELS_KERNEL / 2)][2];

static int64_t complex_rb[(NOF_PIXELS_KERNEL / 2)][2];

static int64_t complex_ba[NOF_PIXELS_KERNEL][2];

static int64_t complex_bb[NOF_PIXELS_KERNEL][2];

static int32_t beamer_State;
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

static inline void beamer_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	printf("set_ra_rb_pos\n");
	while (( i < 18 )) {
		complex_rb[i][0] = 1;
		complex_ra[i][0] = 1;
		i = (i + 6);

}

	inputData_index = (inputData_index + NOF_PIXELS_KERNEL);

  }
static inline void beamer_read_ra_val ( ) {
	int32_t i;
	int64_t ra_val [18];
	comm_read(ch0, &ra_val, 4); // read 4 bytes 

	i = 0;

	while (( i < 18 )) {
		complex_ra[i][1] = ra_val[i];
		i = (i + 1);

}

	beam1_i = 0;

	beam2_i = 0;

  }
static inline void beamer_read_rb_val ( ) {
	int32_t i;
	int64_t rb_val [18];
	comm_read(ch1, &rb_val, 4); // read 4 bytes 

	i = 0;

	while (( i < 18 )) {
		complex_rb[i][1] = rb_val[i];
		i = (i + 1);

}

  }
static inline void beamer_beam_int_loop_1 ( ) {
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
static inline void beamer_beam_int_loop_1_done ( ) {
	printf("beam_int_loop_1_done\n");
  }
static inline void beamer_beam_int_loop_2 ( ) {
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
static inline void beamer_beam_int_loop_2_done ( ) {
	printf("beam_int_loop_2_done\n");
  }
static inline void beamer_store_ba_results ( ) {
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
static inline void beamer_store_bb_results ( ) {
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
static inline void beamer_set_correlation_inputs ( ) {
	correlation_input1 = complex_ba[correlation_counter][1];

	correlation_input2 = complex_bb[correlation_counter][1];

	correlation_counter = (correlation_counter + 1);

  }
static inline void beamer___acc__correlation ( ) {

	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &total_sum, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, correlation_input1, correlation_input2, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	total_sum = outputReg;
}
static inline void beamer_correlation_done ( ) {
	correlation_counter = 0;

  }
static inline void beamer_set_cubic_inputs ( ) {
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
static inline void beamer_set_cubic_inputs_done ( ) {
	printf("set_cubic_inputs_done\n");
  }
static inline void beamer___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, complex_input1_p_pos, complex_input1_p_val, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, complex_input2_p_pos, complex_input2_p_val, FUNCT_FIRE );

	//Lets read the results
	complex_output_p = outputReg;
}
static inline void beamer_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	printf("set_ra_rb_pos\n");
	while (( i < 6 )) {
		complex_ba[i][0] = complex_ra[i][0];
		complex_bb[i][0] = complex_rb[i][0];
		i = (i + 1);

}

  }
static void C_mag (int ns) { 
	C_mag_ret = 1;


 }

int int_state_vars_beamer = 1;
void initStateVarsbeamer() {
total_sum = 0.0;
beamer_State = FSM_beamer_state1;

}

int main(void)
{
  
	//InputPorts
 	ch0 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch0) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch1 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch1) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_beamer==1){
        int_state_vars_beamer = 0;
        initStateVarsbeamer();
	}

beamerSchedule:

 switch (beamer_State) {
   case FSM_beamer_state1:
     	if (( inputData_index < NOF_PIXELS )){ 
		beamer_set_ra_rb_pos();
		beamer_State = FSM_beamer_state2;

		goto beamerSchedule;
	}

	     break;

   case FSM_beamer_state2:
     	if ((comm_level(ch0) >= 1)){ 
					beamer_read_ra_val();
			beamer_State = FSM_beamer_state12;

			goto beamerSchedule;

	}

	     break;

   case FSM_beamer_state12:
     	if (( beam1_i < 3 )){ 
		beamer_beam_int_loop_1();
		beamer_State = FSM_beamer_state13;

		goto beamerSchedule;
	}

			beamer_beam_int_loop_1_done();
		beamer_State = FSM_beamer_state3;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state13:
     	if ((input_state != 0)){ 
		beamer_set_cubic_inputs();
		beamer_State = FSM_beamer_state15;

		goto beamerSchedule;
	}

			beamer_set_cubic_inputs_done();
		beamer_State = FSM_beamer_state14;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state14:
     			beamer_store_ba_results();
		beamer_State = FSM_beamer_state12;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state15:
     			beamer___acc__cubic();
		beamer_State = FSM_beamer_state13;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state3:
     	if ((comm_level(ch1) >= 1)){ 
					beamer_read_rb_val();
			beamer_State = FSM_beamer_state16;

			goto beamerSchedule;

	}

	     break;

   case FSM_beamer_state16:
     	if (( beam2_i < 3 )){ 
		beamer_beam_int_loop_2();
		beamer_State = FSM_beamer_state17;

		goto beamerSchedule;
	}

			beamer_beam_int_loop_2_done();
		beamer_State = FSM_beamer_state11;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state17:
     	if ((input_state != 0)){ 
		beamer_set_cubic_inputs();
		beamer_State = FSM_beamer_state19;

		goto beamerSchedule;
	}

			beamer_set_cubic_inputs_done();
		beamer_State = FSM_beamer_state18;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state18:
     			beamer_store_bb_results();
		beamer_State = FSM_beamer_state16;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state19:
     			beamer___acc__cubic();
		beamer_State = FSM_beamer_state17;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state11:
     			beamer_set_ba_bb_pos();
		beamer_State = FSM_beamer_state20;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state20:
     	if (( correlation_counter < 9 )){ 
		beamer_set_correlation_inputs();
		beamer_State = FSM_beamer_state21;

		goto beamerSchedule;
	}

			beamer_correlation_done();
		beamer_State = FSM_beamer_state1;

		goto beamerSchedule;

	     break;

   case FSM_beamer_state21:
     			beamer___acc__correlation();
		beamer_State = FSM_beamer_state20;

		goto beamerSchedule;

	     break;

}
goto beamerSchedule;
}
