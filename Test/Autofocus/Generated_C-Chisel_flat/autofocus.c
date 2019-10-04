//code from autofocus.cal, instance autofocus
#include <stdint.h>


static float SquareRoot_result;
#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS (216) 
static float p0_pos_real;
static float p0_pos_imag;
static float p1_pos_real;
static float p1_pos_imag;
static float p2_pos_real;
static float p2_pos_imag;
static float p3_pos_real;
static float p3_pos_imag;
static float p0_val_real;
static float p0_val_imag;
static float p1_val_real;
static float p1_val_imag;
static float p2_val_real;
static float p2_val_imag;
static float p3_val_real;
static float p3_val_imag;
static float p03_real;
static float p03_imag;
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
static float pa[NOF_PIXELS_KERNEL][2][2];

static float pb[NOF_PIXELS_KERNEL][2][2];

static float ra[NOF_PIXELS_KERNEL][2][2];

static float rb[NOF_PIXELS_KERNEL][2][2];

static float ba[NOF_PIXELS_KERNEL][2][2];

static float bb[NOF_PIXELS_KERNEL][2][2];

static int32_t autofocus_State;
#define FSM_autofocus_state1 (0) 
#define FSM_autofocus_state2 (1) 
#define FSM_autofocus_state3 (2) 
#define FSM_autofocus_state6 (3) 
#define FSM_autofocus_state5 (4) 
#define FSM_autofocus_state7 (5) 
#define FSM_autofocus_state10 (6) 
#define FSM_autofocus_state9 (7) 
#define FSM_autofocus_state11 (8) 
#define FSM_autofocus_state12 (9) 
#define FSM_autofocus_state15 (10) 
#define FSM_autofocus_state14 (11) 
#define FSM_autofocus_state16 (12) 
#define FSM_autofocus_state19 (13) 
#define FSM_autofocus_state18 (14) 
#define FSM_autofocus_state20 (15) 
static void SquareRoot (float ns);

static void autofocus_set_pa_pb ( ) {
	int32_t j;
	j = 0;

	while (( j < NOF_PIXELS_KERNEL )) {
		pa[j][0][0] = 1.0;
		pa[j][0][1] = 1.0;
		pa[j][1][0] = 1.0;
		pa[j][1][1] = 1.0;
		pb[j][0][0] = 1.0;
		pb[j][0][1] = 1.0;
		pb[j][1][0] = 1.0;
		pb[j][1][1] = 1.0;
		j = (j + 1);

}

	inputData_index = (inputData_index + NOF_PIXELS_KERNEL);

  }
static void autofocus_set_ra_rb_pos ( ) {
	int32_t i;
	i = 0;

	while (( i < 36 )) {
		rb[i][0][0] = pb[i][0][0];
		rb[i][0][1] = pb[i][0][1];
		ra[i][0][0] = pa[i][0][0];
		ra[i][0][1] = pa[i][0][1];
		i = (i + 6);

		range1_i = 0;

		range2_i = 0;

}

  }
static void autofocus_range_int_loop_1 ( ) {
	p0_pos_real = pa[range1_i + range1_counter + 0][0][0];

	p0_pos_imag = pa[range1_i + range1_counter + 0][0][1];

	p1_pos_real = pa[range1_i + range1_counter + 1][0][0];

	p1_pos_imag = pa[range1_i + range1_counter + 1][0][1];

	p2_pos_real = pa[range1_i + range1_counter + 2][0][0];

	p2_pos_imag = pa[range1_i + range1_counter + 2][0][1];

	p3_pos_real = pa[range1_i + range1_counter + 3][0][0];

	p3_pos_imag = pa[range1_i + range1_counter + 3][0][1];

	range1_counter = (range1_counter + 1);

	if ((range1_counter == 3)){ 
		range1_counter = 0;

		range1_i = (range1_i + 6);

	}

  }
static void autofocus_range_int_loop_1_done ( ) {
  }
static void autofocus_range_int_loop_2 ( ) {
	p0_pos_real = pb[range2_i + range2_counter + 0][0][0];

	p0_pos_imag = pb[range2_i + range2_counter + 0][0][1];

	p1_pos_real = pb[range2_i + range2_counter + 1][0][0];

	p1_pos_imag = pb[range2_i + range2_counter + 1][0][1];

	p2_pos_real = pb[range2_i + range2_counter + 2][0][0];

	p2_pos_imag = pb[range2_i + range2_counter + 2][0][1];

	p3_pos_real = pb[range2_i + range2_counter + 3][0][0];

	p3_pos_imag = pb[range2_i + range2_counter + 3][0][1];

	range2_counter = (range2_counter + 1);

	if ((range2_counter == 3)){ 
		range2_counter = 0;

		range2_i = (range2_i + 6);

	}

  }
static void autofocus_range_int_loop_2_done ( ) {
  }
static void autofocus_store_ra_results ( ) {
	ra[ra_result_index][1][0] = p03_real;
	ra[ra_result_index][1][1] = p03_imag;
	if (( ra_result_index < 18 )){ 
		ra_result_index = (ra_result_index + 1);

	}
	else {
		ra_result_index = 0;

	}

  }
static void autofocus_store_rb_results ( ) {
	rb[rb_result_index][1][0] = p03_real;
	rb[rb_result_index][1][1] = p03_imag;
	if (( rb_result_index < 18 )){ 
		rb_result_index = (rb_result_index + 1);

	}
	else {
		rb_result_index = 0;

	}

  }
static void autofocus___acc__cubic ( ) {

	//Lets execute the custom instructions
	uint64_t acc_input0;
	uint64_t acc_input1;
	uint64_t acc_input2;
	uint64_t acc_input3;
	uint64_t acc_input4;
	uint64_t acc_input5;
	uint64_t acc_input6;
	uint64_t acc_input7;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &p0_pos_real, 4);
	memcpy(&acc_input0, &p0_pos_imag, 4);
	memcpy(((char*)&acc_input1) + 4, &p1_pos_real, 4);
	memcpy(&acc_input1, &p1_pos_imag, 4);
	memcpy(((char*)&acc_input2) + 4, &p2_pos_real, 4);
	memcpy(&acc_input2, &p2_pos_imag, 4);
	memcpy(((char*)&acc_input3) + 4, &p3_pos_real, 4);
	memcpy(&acc_input3, &p3_pos_imag, 4);
	memcpy(((char*)&acc_input4) + 4, &p0_val_real, 4);
	memcpy(&acc_input4, &p0_val_imag, 4);
	memcpy(((char*)&acc_input5) + 4, &p1_val_real, 4);
	memcpy(&acc_input5, &p1_val_imag, 4);
	memcpy(((char*)&acc_input6) + 4, &p2_val_real, 4);
	memcpy(&acc_input6, &p2_val_imag, 4);
	memcpy(((char*)&acc_input7) + 4, &p3_val_real, 4);
	memcpy(&acc_input7, &p3_val_imag, 4);

	//Output registers - each will hold two outputs
	uint64_t outputReg0;

	//Time to call the custom instructions
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg0, acc_input0, acc_input1, FUNCT_IN1 );
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg0, acc_input2, acc_input3, FUNCT_IN2 );
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg0, acc_input4, acc_input5, FUNCT_IN3 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg1, acc_input6, acc_input7, FUNCT_FIRE );

	//Save the results
	float results0[2];
	memcpy(&results0[0], &outputReg0, 8);

	//Set the outputs
	p03_real = results0[0];
	p03_imag = results0[1];
}
static void autofocus_set_ba_bb_pos ( ) {
	int32_t i;
	i = 0;

	while (( i < 6 )) {
		ba[i][0][0] = ra[i][0][0];
		ba[i][0][1] = ra[i][0][1];
		bb[i][0][0] = rb[i][0][0];
		bb[i][0][1] = rb[i][0][1];
		i = (i + 1);

		beam1_i = 0;

		beam2_i = 0;

}

  }
static void autofocus_beam_int_loop_1 ( ) {
	p0_pos_real = ra[beam1_i + beam1_counter + 0][0][0];

	p0_pos_imag = ra[beam1_i + beam1_counter + 0][0][1];

	p1_pos_real = ra[beam1_i + beam1_counter + 3][0][0];

	p1_pos_imag = ra[beam1_i + beam1_counter + 3][0][1];

	p2_pos_real = ra[beam1_i + beam1_counter + 6][0][0];

	p2_pos_imag = ra[beam1_i + beam1_counter + 6][0][1];

	p3_pos_real = ra[beam1_i + beam1_counter + 9][0][0];

	p3_pos_imag = ra[beam1_i + beam1_counter + 9][0][1];

	beam1_counter = (beam1_counter + 3);

	if ((beam1_counter == 9)){ 
		beam1_counter = 0;

		beam1_i = (beam1_i + 1);

	}

  }
static void autofocus_beam_int_loop_1_done ( ) {
  }
static void autofocus_beam_int_loop_2 ( ) {
	p0_pos_real = rb[beam2_i + beam2_counter + 0][0][0];

	p0_pos_imag = rb[beam2_i + beam2_counter + 0][0][1];

	p1_pos_real = rb[beam2_i + beam2_counter + 3][0][0];

	p1_pos_imag = rb[beam2_i + beam2_counter + 3][0][1];

	p2_pos_real = rb[beam2_i + beam2_counter + 6][0][0];

	p2_pos_imag = rb[beam2_i + beam2_counter + 6][0][1];

	p3_pos_real = rb[beam2_i + beam2_counter + 9][0][0];

	p3_pos_imag = rb[beam2_i + beam2_counter + 9][0][1];

	beam2_counter = (beam2_counter + 3);

	if ((beam2_counter == 9)){ 
		beam2_counter = 0;

		beam2_i = (beam2_i + 1);

	}

  }
static void autofocus_beam_int_loop_2_done ( ) {
  }
static void autofocus_store_ba_results ( ) {
	ba[ba_result_index][1][0] = p03_real;
	ba[ba_result_index][1][1] = p03_imag;
	ba_result_index = (ba_result_index + 3);

	if ((ba_result_index == 9)){ 
		ba_result_index = 1;

	}
	else {
		if ((ba_result_index == 10)){ 
			ba_result_index = 2;

		}
		else {
			if ((ba_result_index == 11)){ 
				ba_result_index = 0;

			}

		}

	}

  }
static void autofocus_store_bb_results ( ) {
	bb[bb_result_index][1][0] = p03_real;
	bb[bb_result_index][1][1] = p03_imag;
	bb_result_index = (bb_result_index + 3);

	if ((bb_result_index == 9)){ 
		bb_result_index = 1;

	}
	else {
		if ((bb_result_index == 10)){ 
			bb_result_index = 2;

		}
		else {
			if ((bb_result_index == 11)){ 
				bb_result_index = 0;

			}

		}

	}

  }
static void autofocus_correlation ( ) {
	float tmp1;
	float sum;
	int32_t i;
	i = 0;

	sum = 0.0;

	while (( i < 9 )) {
		SquareRoot(ba[i][1][0] * ba[i][1][0] + ba[i][1][1] * ba[i][1][1]);
		tmp1 = SquareRoot_result;

		SquareRoot(bb[i][1][0] * bb[i][1][0] + bb[i][1][1] * bb[i][1][1]);
		sum = (sum + tmp1 * tmp1 * SquareRoot_result * SquareRoot_result);

		i = (i + 1);

}

	total_sum = (total_sum + sum);

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

	SquareRoot_result = x2;


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
		autofocus_State = FSM_autofocus_state6;

		goto autofocusSchedule;
	}

			autofocus_range_int_loop_1_done();
		autofocus_State = FSM_autofocus_state7;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state6:
     			autofocus___acc__cubic();
		autofocus_State = FSM_autofocus_state5;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state5:
     			autofocus_store_ra_results();
		autofocus_State = FSM_autofocus_state3;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state7:
     	if (( range2_i < 36 )){ 
		autofocus_range_int_loop_2();
		autofocus_State = FSM_autofocus_state10;

		goto autofocusSchedule;
	}

			autofocus_range_int_loop_2_done();
		autofocus_State = FSM_autofocus_state11;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state10:
     			autofocus___acc__cubic();
		autofocus_State = FSM_autofocus_state9;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state9:
     			autofocus_store_rb_results();
		autofocus_State = FSM_autofocus_state7;

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
		autofocus_State = FSM_autofocus_state15;

		goto autofocusSchedule;
	}

			autofocus_beam_int_loop_1_done();
		autofocus_State = FSM_autofocus_state16;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state15:
     			autofocus___acc__cubic();
		autofocus_State = FSM_autofocus_state14;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state14:
     			autofocus_store_ba_results();
		autofocus_State = FSM_autofocus_state12;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state16:
     	if (( beam2_i < 3 )){ 
		autofocus_beam_int_loop_2();
		autofocus_State = FSM_autofocus_state19;

		goto autofocusSchedule;
	}

			autofocus_beam_int_loop_2_done();
		autofocus_State = FSM_autofocus_state20;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state19:
     			autofocus___acc__cubic();
		autofocus_State = FSM_autofocus_state18;

		goto autofocusSchedule;

	     break;

   case FSM_autofocus_state18:
     			autofocus_store_bb_results();
		autofocus_State = FSM_autofocus_state16;

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
