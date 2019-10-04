//code from Autofocus.cal, instance autofocus

#include <complex.h>
#include "autofocus.h"
#include "include/calChannel.h"

#include <stdio.h>

static float SquareRoot_ret;
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
static float d0_real;
static float d0_imag;
static float d1_real;
static float d1_imag;
static float d2_real;
static float d2_imag;
static float d3_real;
static float d3_imag;
static float p01_real;
static float p01_imag;
static float p12_real;
static float p12_imag;
static float p23_real;
static float p23_imag;
static float p02_real;
static float p02_imag;
static float p13_real;
static float p13_imag;
static float input1_p_pos_real;
static float input1_p_pos_imag;
static float input1_p_val_real;
static float input1_p_val_imag;
static float input2_p_pos_real;
static float input2_p_pos_imag;
static float input2_p_val_real;
static float input2_p_val_imag;
static float input1_d_real;
static float input1_d_imag;
static float input2_d_real;
static float input2_d_imag;
static float output_p_real;
static float output_p_imag;
static int input_state;
static int range1_i = 0;
static int range1_counter = 0;
static int range2_i = 0;
static int range2_counter = 0;
static int ra_result_index = 0;
static int rb_result_index = 0;
static int beam1_i = 0;
static int beam1_counter = 0;
static int beam2_i = 0;
static int beam2_counter = 0;
static int ba_result_index = 0;
static int bb_result_index = 0;
static int inputData_index = 0;
static float total_sum;
static int NOF_PIXELS_KERNEL = 36;
static int NOF_PIXELS = 216;
static float pa[NOF_PIXELS_KERNEL][2][2];

static float pb[NOF_PIXELS_KERNEL][2][2];

static float ra[NOF_PIXELS_KERNEL][2][2];

static float rb[NOF_PIXELS_KERNEL][2][2];

static float ba[NOF_PIXELS_KERNEL][2][2];

static float bb[NOF_PIXELS_KERNEL][2][2];

static float inputData1[NOF_PIXELS][2][2];

static float inputData2[NOF_PIXELS][2][2];

static int autofocus_State;
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
static void SquareRoot (int ns);

static void  autofocus_set_pa_pb () { 
  int j;
    j = 0;
    printf("%d\n",);
    while ((j < NOF_PIXELS_KERNEL)) {                
//list copy is false
pa[j][0][0] = 1.0;
                
//list copy is false
pa[j][0][1] = 1.0;
                
//list copy is false
pa[j][1][0] = 1.0;
                
//list copy is false
pa[j][1][1] = 1.0;
                
//list copy is false
pb[j][0][0] = 1.0;
                
//list copy is false
pb[j][0][1] = 1.0;
                
//list copy is false
pb[j][1][0] = 1.0;
                
//list copy is false
pb[j][1][1] = 1.0;
        j = (j + 1);
}

    inputData_index = (inputData_index + NOF_PIXELS_KERNEL);
  }
static void  autofocus_set_pa_pb_done () { 
    inputData_index = 0;
    total_sum = 0.0;
  }
static void  autofocus_set_ra_rb_pos () { 
  int i;
    i = 0;
    printf("set_ra_rb_pos\n");
    while ((i < 36)) {                
//list copy is false
rb[i][0][0] = pb[i][0][0];
                
//list copy is false
rb[i][0][1] = pb[i][0][1];
                
//list copy is false
ra[i][0][0] = pa[i][0][0];
                
//list copy is false
ra[i][0][1] = pa[i][0][1];
        i = (i + 6);
        range1_i = 0;
        range2_i = 0;
}

  }
static void  autofocus_range_int_loop_1 () { 
    printf("%d\n",);
    p0_pos_real = pa[range1_i + range1_counter + 0][0][0];
    p0_pos_imag = pa[range1_i + range1_counter + 0][0][1];
    p1_pos_real = pa[range1_i + range1_counter + 1][0][0];
    p1_pos_imag = pa[range1_i + range1_counter + 1][0][1];
    p2_pos_real = pa[range1_i + range1_counter + 2][0][0];
    p2_pos_imag = pa[range1_i + range1_counter + 2][0][1];
    p3_pos_real = pa[range1_i + range1_counter + 3][0][0];
    p3_pos_imag = pa[range1_i + range1_counter + 3][0][1];
    input_state = 1;
    range1_counter = (range1_counter + 1);
    if ((range1_counter == 3)){ 
              range1_counter = 0;
        range1_i = (range1_i + 6);
}

  }
static void  autofocus_range_int_loop_1_done () { 
    printf("range_int_loop_1_done\n");
  }
static void  autofocus_range_int_loop_2 () { 
    printf("%d\n",);
    p0_pos_real = pb[range2_i + range2_counter + 0][0][0];
    p0_pos_imag = pb[range2_i + range2_counter + 0][0][1];
    p1_pos_real = pb[range2_i + range2_counter + 1][0][0];
    p1_pos_imag = pb[range2_i + range2_counter + 1][0][1];
    p2_pos_real = pb[range2_i + range2_counter + 2][0][0];
    p2_pos_imag = pb[range2_i + range2_counter + 2][0][1];
    p3_pos_real = pb[range2_i + range2_counter + 3][0][0];
    p3_pos_imag = pb[range2_i + range2_counter + 3][0][1];
    input_state = 1;
    range2_counter = (range2_counter + 1);
    if ((range2_counter == 3)){ 
              range2_counter = 0;
        range2_i = (range2_i + 6);
}

  }
static void  autofocus_range_int_loop_2_done () { 
    printf("range_int_loop_2_done\n");
  }
static void  autofocus_store_ra_results () { 
    printf("store_ra_results\n");
        
//list copy is false
ra[ra_result_index][1][0] = output_p_real;
        
//list copy is false
ra[ra_result_index][1][1] = output_p_imag;
    if ((ra_result_index < 18)){ 
              ra_result_index = (ra_result_index + 1);
}
    else {
              ra_result_index = 0;
}

  }
static void  autofocus_store_rb_results () { 
    printf("store_rb_results\n");
        
//list copy is false
rb[rb_result_index][1][0] = output_p_real;
        
//list copy is false
rb[rb_result_index][1][1] = output_p_imag;
    if ((rb_result_index < 18)){ 
              rb_result_index = (rb_result_index + 1);
}
    else {
              rb_result_index = 0;
}

  }
static void  autofocus_set_cubic_inputs () { 
    printf("set_cubic_inputs\n");
    if ((input_state == 1)){ 
              input1_p_pos_real = p0_pos_real;
        input1_p_pos_imag = p0_pos_imag;
        input1_p_val_real = p0_val_real;
        input1_p_val_imag = p0_val_imag;
        input2_p_pos_real = p1_pos_real;
        input2_p_pos_imag = p1_pos_imag;
        input2_p_val_real = p1_val_real;
        input2_p_val_imag = p1_val_imag;
        input1_d_real = d0_real;
        input1_d_imag = d0_imag;
        input2_d_real = d1_real;
        input2_d_imag = d1_imag;
        input_state = 2;
}

    if ((input_state == 2)){ 
              p01_real = output_p_real;
        p01_imag = output_p_imag;
        input1_p_pos_real = p1_pos_real;
        input1_p_pos_imag = p1_pos_imag;
        input1_p_val_real = p1_val_real;
        input1_p_val_imag = p1_val_imag;
        input2_p_pos_real = p2_pos_real;
        input2_p_pos_imag = p2_pos_imag;
        input2_p_val_real = p2_val_real;
        input2_p_val_imag = p2_val_imag;
        input1_d_real = d1_real;
        input1_d_imag = d1_imag;
        input2_d_real = d2_real;
        input2_d_imag = d2_imag;
        input_state = 3;
}

    if ((input_state == 3)){ 
              p12_real = output_p_real;
        p12_imag = output_p_imag;
        input1_p_pos_real = p2_pos_real;
        input1_p_pos_imag = p2_pos_imag;
        input1_p_val_real = p2_val_real;
        input1_p_val_imag = p2_val_imag;
        input2_p_pos_real = p3_pos_real;
        input2_p_pos_imag = p3_pos_imag;
        input2_p_val_real = p3_val_real;
        input2_p_val_imag = p3_val_imag;
        input1_d_real = d2_real;
        input1_d_imag = d2_imag;
        input2_d_real = d3_real;
        input2_d_imag = d3_imag;
        input_state = 4;
}

    if ((input_state == 4)){ 
              p23_real = output_p_real;
        p23_imag = output_p_imag;
        input1_p_pos_real = p0_pos_real;
        input1_p_pos_imag = p0_pos_imag;
        input1_p_val_real = p01_real;
        input1_p_val_imag = p01_imag;
        input2_p_pos_real = p3_pos_real;
        input2_p_pos_imag = p3_pos_imag;
        input2_p_val_real = p12_real;
        input2_p_val_imag = p12_imag;
        input1_d_real = d0_real;
        input1_d_imag = d0_imag;
        input2_d_real = d2_real;
        input2_d_imag = d2_imag;
        input_state = 5;
}

    if ((input_state == 5)){ 
              p02_real = output_p_real;
        p02_imag = output_p_imag;
        input1_p_pos_real = p1_pos_real;
        input1_p_pos_imag = p1_pos_imag;
        input1_p_val_real = p12_real;
        input1_p_val_imag = p12_imag;
        input2_p_pos_real = p3_pos_real;
        input2_p_pos_imag = p3_pos_imag;
        input2_p_val_real = p23_real;
        input2_p_val_imag = p23_imag;
        input1_d_real = d1_real;
        input1_d_imag = d1_imag;
        input2_d_real = d3_real;
        input2_d_imag = d3_imag;
        input_state = 6;
}

    if ((input_state == 6)){ 
              p13_real = output_p_real;
        p13_imag = output_p_imag;
        input1_p_pos_real = p0_pos_real;
        input1_p_pos_imag = p0_pos_imag;
        input1_p_val_real = p02_real;
        input1_p_val_imag = p02_imag;
        input2_p_pos_real = p3_pos_real;
        input2_p_pos_imag = p3_pos_imag;
        input2_p_val_real = p13_real;
        input2_p_val_imag = p13_imag;
        input1_d_real = d0_real;
        input1_d_imag = d0_imag;
        input2_d_real = d3_real;
        input2_d_imag = d3_imag;
        input_state = 0;
}

  }
static void  autofocus_set_cubic_inputs_done () { 
    printf("set_cubic_inputs_done\n");
  }
static void  autofocus___acc__cubic () { 
  float tmp0_real;
  float tmp0_imag;
  float tmp00;
  float tmp01;
  float tmp02;
  float tmp1_real;
  float tmp1_imag;
  float tmp2_real;
  float tmp2_imag;
  float tmp3_real;
  float tmp3_imag;
  float denom;
    printf("cubic\n");
    tmp00 = (input1_p_val_real * input2_d_real);
    tmp01 = (input1_p_val_imag * input2_d_imag);
    tmp0_real = (tmp00 - tmp01);
    tmp00 = (input1_p_val_real * input2_d_imag);
    tmp01 = (input1_p_val_imag * input2_d_real);
    tmp0_imag = (tmp00 + tmp01);
    tmp00 = (input2_p_val_real * input1_d_real);
    tmp01 = (input2_p_val_imag * input1_d_imag);
    tmp1_real = (tmp00 - tmp01);
    tmp00 = (input2_p_val_real * input1_d_imag);
    tmp01 = (input2_p_val_imag * input1_d_real);
    tmp1_imag = (tmp00 + tmp01);
    tmp2_real = (tmp0_real - tmp1_real);
    tmp2_imag = (tmp0_imag - tmp1_imag);
    tmp3_real = (input1_p_pos_real - input2_p_pos_real);
    tmp3_imag = (input1_p_pos_imag - input2_p_pos_imag);
    tmp00 = (tmp3_real * tmp3_real);
    tmp01 = (tmp3_imag * tmp3_imag);
    tmp02 = (tmp00 + tmp01);
    denom = (tmp02 + 1.2E-20);
    tmp00 = (tmp2_real * tmp3_real);
    tmp01 = (tmp2_imag * tmp3_imag);
    tmp02 = (tmp00 + tmp01);
    output_p_real = (tmp02 / denom);
    tmp00 = (tmp2_imag * tmp3_real);
    tmp01 = (tmp2_real * tmp3_imag);
    tmp02 = (tmp00 - tmp01);
    output_p_imag = (tmp02 / denom);
  }
static void  autofocus_set_ba_bb_pos () { 
  int i;
    i = 0;
    printf("set_ra_rb_pos\n");
    while ((i < 6)) {                
//list copy is false
ba[i][0][0] = ra[i][0][0];
                
//list copy is false
ba[i][0][1] = ra[i][0][1];
                
//list copy is false
bb[i][0][0] = rb[i][0][0];
                
//list copy is false
bb[i][0][1] = rb[i][0][1];
        i = (i + 1);
        beam1_i = 0;
        beam2_i = 0;
}

  }
static void  autofocus_beam_int_loop_1 () { 
    printf("%d\n",);
    p0_pos_real = ra[beam1_i + beam1_counter + 0][0][0];
    p0_pos_imag = ra[beam1_i + beam1_counter + 0][0][1];
    p1_pos_real = ra[beam1_i + beam1_counter + 3][0][0];
    p1_pos_imag = ra[beam1_i + beam1_counter + 3][0][1];
    p2_pos_real = ra[beam1_i + beam1_counter + 6][0][0];
    p2_pos_imag = ra[beam1_i + beam1_counter + 6][0][1];
    p3_pos_real = ra[beam1_i + beam1_counter + 9][0][0];
    p3_pos_imag = ra[beam1_i + beam1_counter + 9][0][1];
    input_state = 1;
    beam1_counter = (beam1_counter + 3);
    if ((beam1_counter == 9)){ 
              beam1_counter = 0;
        beam1_i = (beam1_i + 1);
}

  }
static void  autofocus_beam_int_loop_1_done () { 
    printf("beam_int_loop_1_done\n");
  }
static void  autofocus_beam_int_loop_2 () { 
    printf("%d\n",);
    p0_pos_real = rb[beam2_i + beam2_counter + 0][0][0];
    p0_pos_imag = rb[beam2_i + beam2_counter + 0][0][1];
    p1_pos_real = rb[beam2_i + beam2_counter + 3][0][0];
    p1_pos_imag = rb[beam2_i + beam2_counter + 3][0][1];
    p2_pos_real = rb[beam2_i + beam2_counter + 6][0][0];
    p2_pos_imag = rb[beam2_i + beam2_counter + 6][0][1];
    p3_pos_real = rb[beam2_i + beam2_counter + 9][0][0];
    p3_pos_imag = rb[beam2_i + beam2_counter + 9][0][1];
    input_state = 1;
    beam2_counter = (beam2_counter + 3);
    if ((beam2_counter == 9)){ 
              beam2_counter = 0;
        beam2_i = (beam2_i + 1);
}

  }
static void  autofocus_beam_int_loop_2_done () { 
    printf("beam_int_loop_2_done\n");
  }
static void  autofocus_store_ba_results () { 
    printf("%d\n",);
        
//list copy is false
ba[ba_result_index][1][0] = output_p_real;
        
//list copy is false
ba[ba_result_index][1][1] = output_p_imag;
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
static void  autofocus_store_bb_results () { 
    printf("store_bb_results\n");
        
//list copy is false
bb[bb_result_index][1][0] = output_p_real;
        
//list copy is false
bb[bb_result_index][1][1] = output_p_imag;
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
static void  autofocus_correlation () { 
  float tmp1;
  float sum;
  int i;
    printf("correlation\n");
    i = 0;
    sum = 0.0;
    while ((i < 9)) {        SquareRoot(ba[i][1][0] * ba[i][1][0] + ba[i][1][1] * ba[i][1][1]);
        tmp1 = SquareRoot_ret;
        SquareRoot(bb[i][1][0] * bb[i][1][0] + bb[i][1][1] * bb[i][1][1]);
        sum = (sum + tmp1 * tmp1 * SquareRoot_ret * SquareRoot_ret);
        i = (i + 1);
}

    total_sum = (total_sum + sum);
    printf("%d\n",);
  }
static void SquareRoot (   int ns) { 
       float i = 0.0;
       float x1;
       float x2;
       int j = 0;
       while (((i * i) <= ns)) {           i = (i + 0.1);
}

       x1 = i;
       while ((j < 10)) {           x2 = ns;
           x2 = (x2 / x1);
           x2 = (x2 + x1);
           x2 = (x2 / 2);
           x1 = x2;
           j = (j + 1);
}

       SquareRoot_ret = x2;

 }
int int_state_vars_autofocus=1;
void initStateVarsautofocus() {
total_sum = 0.0;
  inputData1[0] = 1.0;
  inputData1[1] = 1.0;
autofocus_State = FSM_autofocus_state1;

}

/****  ****/
int Scheduler_autofocus() {
    if(int_state_vars_autofocus==1){
        int_state_vars_autofocus=0;
        initStateVarsautofocus();}

autofocusSchedule:
       autofocus_set_pa_pb_done();
       goto autofocusSchedule;


 switch (autofocus_State) {
   case FSM_autofocus_state1:
            if ((inputData_index < NOF_PIXELS)){ 
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
            if ((range1_i < 36)){ 
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
                     autofocus___acc__cubic();
         autofocus_State = FSM_autofocus_state4;
         goto autofocusSchedule;


            break;

   case FSM_autofocus_state7:
            if ((range2_i < 36)){ 
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
                     autofocus___acc__cubic();
         autofocus_State = FSM_autofocus_state8;
         goto autofocusSchedule;


            break;

   case FSM_autofocus_state11:
                     autofocus_set_ba_bb_pos();
         autofocus_State = FSM_autofocus_state12;
         goto autofocusSchedule;


            break;

   case FSM_autofocus_state12:
            if ((beam1_i < 3)){ 
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
                     autofocus___acc__cubic();
         autofocus_State = FSM_autofocus_state13;
         goto autofocusSchedule;


            break;

   case FSM_autofocus_state16:
            if ((beam2_i < 3)){ 
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
                     autofocus___acc__cubic();
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
