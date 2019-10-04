//code from singleQRD.cal, instance singleQRD

#include <complex.h>
#include "singleQRD.h"
#include "include/calChannel.h"

#include <stdio.h>

static int ROW_SIZE = 16;
static int COL_SIZE = 16;
static float r [(ROW_SIZE * COL_SIZE)];

static float x_in [ROW_SIZE];

static float c;
static float s;
static float inputMatrix [(ROW_SIZE * COL_SIZE)];

static int x_in_counter = 0;
static float SquareRoot_ret;
static int row_counter = 0;
static int col_counter = 0;
static int inputCounter = 0;
static int outputCounter = 0;
static int singleQRD_State;
#define FSM_singleQRD_state1 (0) 
#define FSM_singleQRD_state2 (1) 
#define FSM_singleQRD_state3 (2) 
static void SquareRoot (int ns);

static void  singleQRD_read_x_in () { 
    printf("0\n");
        
//list copy is false
x_in[x_in_counter] = inputMatrix[inputCounter];
    x_in_counter = (x_in_counter + 1);
    inputCounter = (inputCounter + 1);
  }
static void  singleQRD_read_x_in_done () { 
    printf("1\n");
    x_in_counter = 0;
  }
static void  singleQRD_read_x_in_not_done () { 
    printf("2\n");
    outputCounter = (outputCounter + 1);
  }
static void  singleQRD___acc__calculate_boundary () { 
  float a;
  float b;
  float r_tmp;
  int index;
    if ((x_in[row_counter] == 0.0)){ 
              c = 1.0;
        s = 0.0;
}
    else {
              index = row_counter * ROW_SIZE + col_counter;
        a = (r[index] * r[index]);
        b = (x_in[col_counter] * x_in[col_counter]);
        SquareRoot((a + b));
        r_tmp = SquareRoot_ret;
        c = (r[index] / r_tmp);
        s = (x_in[col_counter] / r_tmp);
                
//list copy is false
r[index] = r_tmp;
}

    col_counter = (col_counter + 1);
  }
static void  singleQRD_row_done () { 
    printf("4\n");
    row_counter = 0;
    col_counter = 0;
  }
static void  singleQRD_calculate_inner () { 
  float tmp;
  int index;
    printf("5\n");
    index = row_counter * ROW_SIZE + col_counter;
    tmp = c * x_in[col_counter] - s * r[index];
        
//list copy is false
r[index] = s * x_in[col_counter] + c * r[index];
        
//list copy is false
x_in[col_counter] = tmp;
    col_counter = (col_counter + 1);
  }
static void  singleQRD_col_done () { 
    printf("6\n");
    row_counter = (row_counter + 1);
    col_counter = row_counter;
  }
static void  singleQRD_jump_to_read () { 
    printf("7\n");
    col_counter = 0;
    row_counter = 0;
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
int int_state_vars_singleQRD=1;
void initStateVarssingleQRD() {
  inputMatrix[0] = 5.124575;
  inputMatrix[1] = 7.898948;
  inputMatrix[2] = 7.946213;
  inputMatrix[3] = 3.592056;
  inputMatrix[4] = 6.081988;
  inputMatrix[5] = 7.166724;
  inputMatrix[6] = 7.788865;
  inputMatrix[7] = 9.798719;
  inputMatrix[8] = 4.258254;
  inputMatrix[9] = 1.054377;
  inputMatrix[10] = 7.652938;
  inputMatrix[11] = 3.552302;
  inputMatrix[12] = 2.828004;
  inputMatrix[13] = 1.762015;
  inputMatrix[14] = 2.638748;
  inputMatrix[15] = 8.069129;
  inputMatrix[16] = 2.522771;
  inputMatrix[17] = 1.012173;
  inputMatrix[18] = 8.776333;
  inputMatrix[19] = 6.71655;
  inputMatrix[20] = 4.709401;
  inputMatrix[21] = 1.210326;
  inputMatrix[22] = 1.280568;
  inputMatrix[23] = 3.150382;
  inputMatrix[24] = 9.152067;
  inputMatrix[25] = 2.220713;
  inputMatrix[26] = 4.314055;
  inputMatrix[27] = 2.801475;
  inputMatrix[28] = 0.355802;
  inputMatrix[29] = 4.751442;
  inputMatrix[30] = 2.452192;
  inputMatrix[31] = 8.104572;
  inputMatrix[32] = 8.535061;
  inputMatrix[33] = 1.283802;
  inputMatrix[34] = 0.308171;
  inputMatrix[35] = 1.881512;
  inputMatrix[36] = 6.372757;
  inputMatrix[37] = 4.749593;
  inputMatrix[38] = 5.185006;
  inputMatrix[39] = 8.183881;
  inputMatrix[40] = 0.145697;
  inputMatrix[41] = 9.572844;
  inputMatrix[42] = 4.968377;
  inputMatrix[43] = 2.484793;
  inputMatrix[44] = 3.972274;
  inputMatrix[45] = 0.72254;
  inputMatrix[46] = 4.236591;
  inputMatrix[47] = 8.985795;
  inputMatrix[48] = 3.74719;
  inputMatrix[49] = 1.811495;
  inputMatrix[50] = 6.834885;
  inputMatrix[51] = 9.154308;
  inputMatrix[52] = 5.894849;
  inputMatrix[53] = 0.924535;
  inputMatrix[54] = 4.470197;
  inputMatrix[55] = 0.745557;
  inputMatrix[56] = 2.168096;
  inputMatrix[57] = 6.29106;
  inputMatrix[58] = 6.742811;
  inputMatrix[59] = 0.373962;
  inputMatrix[60] = 4.722142;
  inputMatrix[61] = 6.529717;
  inputMatrix[62] = 9.824009;
  inputMatrix[63] = 7.356618;
  inputMatrix[64] = 6.461459;
  inputMatrix[65] = 9.131959;
  inputMatrix[66] = 7.072122;
  inputMatrix[67] = 0.483971;
  inputMatrix[68] = 1.670396;
  inputMatrix[69] = 8.949241;
  inputMatrix[70] = 4.018287;
  inputMatrix[71] = 3.546607;
  inputMatrix[72] = 8.672633;
  inputMatrix[73] = 0.835284;
  inputMatrix[74] = 1.438314;
  inputMatrix[75] = 5.03481;
  inputMatrix[76] = 6.390177;
  inputMatrix[77] = 3.856355;
  inputMatrix[78] = 2.28259;
  inputMatrix[79] = 2.083286;
  inputMatrix[80] = 9.260374;
  inputMatrix[81] = 6.927009;
  inputMatrix[82] = 4.018142;
  inputMatrix[83] = 0.385422;
  inputMatrix[84] = 1.099953;
  inputMatrix[85] = 3.724873;
  inputMatrix[86] = 9.097155;
  inputMatrix[87] = 9.176734;
  inputMatrix[88] = 6.069993;
  inputMatrix[89] = 8.241838;
  inputMatrix[90] = 9.264992;
  inputMatrix[91] = 1.061532;
  inputMatrix[92] = 3.45995;
  inputMatrix[93] = 2.737167;
  inputMatrix[94] = 2.078934;
  inputMatrix[95] = 3.678259;
  inputMatrix[96] = 6.428624;
  inputMatrix[97] = 0.599322;
  inputMatrix[98] = 6.768367;
  inputMatrix[99] = 8.416201;
  inputMatrix[100] = 2.400816;
  inputMatrix[101] = 6.837505;
  inputMatrix[102] = 0.179495;
  inputMatrix[103] = 4.902166;
  inputMatrix[104] = 7.376048;
  inputMatrix[105] = 9.049492;
  inputMatrix[106] = 7.510052;
  inputMatrix[107] = 1.206717;
  inputMatrix[108] = 5.326238;
  inputMatrix[109] = 2.406306;
  inputMatrix[110] = 4.195184;
  inputMatrix[111] = 9.811339;
  inputMatrix[112] = 8.330168;
  inputMatrix[113] = 8.243491;
  inputMatrix[114] = 5.997973;
  inputMatrix[115] = 8.827311;
  inputMatrix[116] = 5.079985;
  inputMatrix[117] = 6.432596;
  inputMatrix[118] = 3.651846;
  inputMatrix[119] = 9.114349;
  inputMatrix[120] = 1.086232;
  inputMatrix[121] = 7.299483;
  inputMatrix[122] = 4.097865;
  inputMatrix[123] = 8.284714;
  inputMatrix[124] = 0.099244;
  inputMatrix[125] = 9.042177;
  inputMatrix[126] = 1.308067;
  inputMatrix[127] = 3.394185;
  inputMatrix[128] = 6.530458;
  inputMatrix[129] = 2.984305;
  inputMatrix[130] = 6.574254;
  inputMatrix[131] = 5.616988;
  inputMatrix[132] = 9.094666;
  inputMatrix[133] = 5.588702;
  inputMatrix[134] = 5.533086;
  inputMatrix[135] = 7.406141;
  inputMatrix[136] = 4.161861;
  inputMatrix[137] = 0.238815;
  inputMatrix[138] = 9.648564;
  inputMatrix[139] = 6.822;
  inputMatrix[140] = 0.37036;
  inputMatrix[141] = 4.103983;
  inputMatrix[142] = 8.835959;
  inputMatrix[143] = 5.350417;
  inputMatrix[144] = 6.909482;
  inputMatrix[145] = 7.122869;
  inputMatrix[146] = 4.538856;
  inputMatrix[147] = 0.413352;
  inputMatrix[148] = 0.563682;
  inputMatrix[149] = 8.213211;
  inputMatrix[150] = 3.64162;
  inputMatrix[151] = 3.405092;
  inputMatrix[152] = 1.848284;
  inputMatrix[153] = 4.093572;
  inputMatrix[154] = 8.746218;
  inputMatrix[155] = 8.198015;
  inputMatrix[156] = 4.431138;
  inputMatrix[157] = 8.115096;
  inputMatrix[158] = 3.752868;
  inputMatrix[159] = 9.309067;
  inputMatrix[160] = 4.522346;
  inputMatrix[161] = 4.953636;
  inputMatrix[162] = 6.954018;
  inputMatrix[163] = 4.096635;
  inputMatrix[164] = 1.076255;
  inputMatrix[165] = 2.290696;
  inputMatrix[166] = 4.178736;
  inputMatrix[167] = 1.015898;
  inputMatrix[168] = 5.95605;
  inputMatrix[169] = 5.30129;
  inputMatrix[170] = 3.462898;
  inputMatrix[171] = 9.802859;
  inputMatrix[172] = 9.976361;
  inputMatrix[173] = 8.45441;
  inputMatrix[174] = 2.433835;
  inputMatrix[175] = 3.138024;
  inputMatrix[176] = 6.622229;
  inputMatrix[177] = 8.626863;
  inputMatrix[178] = 4.287552;
  inputMatrix[179] = 5.543465;
  inputMatrix[180] = 5.243287;
  inputMatrix[181] = 7.461806;
  inputMatrix[182] = 2.883427;
  inputMatrix[183] = 3.698015;
  inputMatrix[184] = 4.793037;
  inputMatrix[185] = 1.159368;
  inputMatrix[186] = 1.629081;
  inputMatrix[187] = 2.267589;
  inputMatrix[188] = 0.671444;
  inputMatrix[189] = 9.046292;
  inputMatrix[190] = 4.284649;
  inputMatrix[191] = 2.955473;
  inputMatrix[192] = 4.077998;
  inputMatrix[193] = 8.90247;
  inputMatrix[194] = 5.945147;
  inputMatrix[195] = 3.556053;
  inputMatrix[196] = 8.246637;
  inputMatrix[197] = 4.732425;
  inputMatrix[198] = 0.047543;
  inputMatrix[199] = 5.104174;
  inputMatrix[200] = 6.272343;
  inputMatrix[201] = 6.639598;
  inputMatrix[202] = 9.528616;
  inputMatrix[203] = 1.437121;
  inputMatrix[204] = 6.459073;
  inputMatrix[205] = 0.140771;
  inputMatrix[206] = 9.6605;
  inputMatrix[207] = 8.103308;
  inputMatrix[208] = 7.141063;
  inputMatrix[209] = 7.821795;
  inputMatrix[210] = 4.805562;
  inputMatrix[211] = 5.816616;
  inputMatrix[212] = 8.541925;
  inputMatrix[213] = 0.016668;
  inputMatrix[214] = 2.015325;
  inputMatrix[215] = 4.703988;
  inputMatrix[216] = 5.374593;
  inputMatrix[217] = 0.995246;
  inputMatrix[218] = 5.829943;
  inputMatrix[219] = 5.670019;
  inputMatrix[220] = 8.307987;
  inputMatrix[221] = 6.37059;
  inputMatrix[222] = 9.468715;
  inputMatrix[223] = 1.161778;
  inputMatrix[224] = 7.457226;
  inputMatrix[225] = 0.0993;
  inputMatrix[226] = 7.410219;
  inputMatrix[227] = 0.187684;
  inputMatrix[228] = 1.784756;
  inputMatrix[229] = 1.066501;
  inputMatrix[230] = 8.859654;
  inputMatrix[231] = 6.758221;
  inputMatrix[232] = 9.879946;
  inputMatrix[233] = 3.690862;
  inputMatrix[234] = 4.245235;
  inputMatrix[235] = 3.524249;
  inputMatrix[236] = 2.964446;
  inputMatrix[237] = 4.37368;
  inputMatrix[238] = 2.311288;
  inputMatrix[239] = 2.500651;
  inputMatrix[240] = 4.752189;
  inputMatrix[241] = 0.592439;
  inputMatrix[242] = 2.946092;
  inputMatrix[243] = 0.001511;
  inputMatrix[244] = 6.350062;
  inputMatrix[245] = 6.068312;
  inputMatrix[246] = 2.986027;
  inputMatrix[247] = 0.368879;
  inputMatrix[248] = 3.349494;
  inputMatrix[249] = 5.183024;
  inputMatrix[250] = 7.386629;
  inputMatrix[251] = 0.150104;
  inputMatrix[252] = 9.933439;
  inputMatrix[253] = 1.343407;
  inputMatrix[254] = 0.192133;
  inputMatrix[255] = 6.214067;
SquareRoot_ret = 0.0;
singleQRD_State = FSM_singleQRD_state1;

}

/****  ****/
int Scheduler_singleQRD() {
    if(int_state_vars_singleQRD==1){
        int_state_vars_singleQRD=0;
        initStateVarssingleQRD();}

singleQRDSchedule:
if ((row_counter < COL_SIZE)){ 
                singleQRD___acc__calculate_boundary();
         goto singleQRDSchedule;

}
       singleQRD_jump_to_read();
       goto singleQRDSchedule;


 switch (singleQRD_State) {
   case FSM_singleQRD_state1:
            if (x_in_counter < ROW_SIZE && inputCounter < ROW_SIZE * COL_SIZE){ 
                    singleQRD_read_x_in();
           singleQRD_State = FSM_singleQRD_state1;
           goto singleQRDSchedule;

}

       if (outputCounter < ROW_SIZE * COL_SIZE){ 
                    singleQRD_read_x_in_not_done();
           singleQRD_State = FSM_singleQRD_state1;
           goto singleQRDSchedule;

}

       if ((x_in_counter == ROW_SIZE)){ 
                    singleQRD_read_x_in_done();
           singleQRD_State = FSM_singleQRD_state2;
           goto singleQRDSchedule;

}

            break;

   case FSM_singleQRD_state2:
                     singleQRD_row_done();
         singleQRD_State = FSM_singleQRD_state1;
         goto singleQRDSchedule;


            break;

   case FSM_singleQRD_state3:
            if ((col_counter < ROW_SIZE)){ 
                    singleQRD_calculate_inner();
           singleQRD_State = FSM_singleQRD_state3;
           goto singleQRDSchedule;

}

       if ((row_counter < COL_SIZE)){ 
                    singleQRD_col_done();
           singleQRD_State = FSM_singleQRD_state2;
           goto singleQRDSchedule;

}

            break;

}
goto singleQRDSchedule;

}
