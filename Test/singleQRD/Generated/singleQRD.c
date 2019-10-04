//code from singleQRD.cal, instance singleQRD
#include <stdint.h>
#include <stdio.h>


#define ROW_SIZE (16) 
#define COL_SIZE (16) 
static float r [(ROW_SIZE * COL_SIZE)];

static float x_in [(ROW_SIZE + 1)];

static float c;
static float s;
static float inputMatrix [(ROW_SIZE * COL_SIZE)] =  {5.124575, 7.898948, 7.946213, 3.592056, 6.081988, 7.166724, 7.788865, 9.798719, 4.258254, 1.054377, 7.652938, 3.552302, 2.828004, 1.762015, 2.638748, 8.069129, 2.522771, 1.012173, 8.776333, 6.71655, 4.709401, 1.210326, 1.280568, 3.150382, 9.152067, 2.220713, 4.314055, 2.801475, 0.355802, 4.751442, 2.452192, 8.104572, 8.535061, 1.283802, 0.308171, 1.881512, 6.372757, 4.749593, 5.185006, 8.183881, 0.145697, 9.572844, 4.968377, 2.484793, 3.972274, 0.72254, 4.236591, 8.985795, 3.74719, 1.811495, 6.834885, 9.154308, 5.894849, 0.924535, 4.470197, 0.745557, 2.168096, 6.29106, 6.742811, 0.373962, 4.722142, 6.529717, 9.824009, 7.356618, 6.461459, 9.131959, 7.072122, 0.483971, 1.670396, 8.949241, 4.018287, 3.546607, 8.672633, 0.835284, 1.438314, 5.03481, 6.390177, 3.856355, 2.28259, 2.083286, 9.260374, 6.927009, 4.018142, 0.385422, 1.099953, 3.724873, 9.097155, 9.176734, 6.069993, 8.241838, 9.264992, 1.061532, 3.45995, 2.737167, 2.078934, 3.678259, 6.428624, 0.599322, 6.768367, 8.416201, 2.400816, 6.837505, 0.179495, 4.902166, 7.376048, 9.049492, 7.510052, 1.206717, 5.326238, 2.406306, 4.195184, 9.811339, 8.330168, 8.243491, 5.997973, 8.827311, 5.079985, 6.432596, 3.651846, 9.114349, 1.086232, 7.299483, 4.097865, 8.284714, 0.099244, 9.042177, 1.308067, 3.394185, 6.530458, 2.984305, 6.574254, 5.616988, 9.094666, 5.588702, 5.533086, 7.406141, 4.161861, 0.238815, 9.648564, 6.822, 0.37036, 4.103983, 8.835959, 5.350417, 6.909482, 7.122869, 4.538856, 0.413352, 0.563682, 8.213211, 3.64162, 3.405092, 1.848284, 4.093572, 8.746218, 8.198015, 4.431138, 8.115096, 3.752868, 9.309067, 4.522346, 4.953636, 6.954018, 4.096635, 1.076255, 2.290696, 4.178736, 1.015898, 5.95605, 5.30129, 3.462898, 9.802859, 9.976361, 8.45441, 2.433835, 3.138024, 6.622229, 8.626863, 4.287552, 5.543465, 5.243287, 7.461806, 2.883427, 3.698015, 4.793037, 1.159368, 1.629081, 2.267589, 0.671444, 9.046292, 4.284649, 2.955473, 4.077998, 8.90247, 5.945147, 3.556053, 8.246637, 4.732425, 0.047543, 5.104174, 6.272343, 6.639598, 9.528616, 1.437121, 6.459073, 0.140771, 9.6605, 8.103308, 7.141063, 7.821795, 4.805562, 5.816616, 8.541925, 0.016668, 2.015325, 4.703988, 5.374593, 0.995246, 5.829943, 5.670019, 8.307987, 6.37059, 9.468715, 1.161778, 7.457226, 0.0993, 7.410219, 0.187684, 1.784756, 1.066501, 8.859654, 6.758221, 9.879946, 3.690862, 4.245235, 3.524249, 2.964446, 4.37368, 2.311288, 2.500651, 4.752189, 0.592439, 2.946092, 0.001511, 6.350062, 6.068312, 2.986027, 0.368879, 3.349494, 5.183024, 7.386629, 0.150104, 9.933439, 1.343407, 0.192133, 6.214067};

static int32_t x_in_counter = 0;
static float SquareRoot_ret;
static int32_t row_counter = 0;
static int32_t col_counter = 0;
static int32_t inputCounter = 0;
static int32_t outputCounter = 0;
static int32_t singleQRD_State;
#define FSM_singleQRD_state1 (0) 
#define FSM_singleQRD_state2 (1) 
#define FSM_singleQRD_state3 (2) 
static void SquareRoot (float ns);

static inline void singleQRD_read_x_in ( ) {
	printf("0\n");
	x_in[x_in_counter] = inputMatrix[inputCounter];
	x_in_counter = (x_in_counter + 1);

	inputCounter = (inputCounter + 1);

  }
static inline void singleQRD_read_x_in_done ( ) {
	printf("1\n");
	x_in_counter = 0;

  }
static inline void singleQRD_read_x_in_not_done ( ) {
	printf("2\n");
	outputCounter = (outputCounter + 1);

  }
static inline void singleQRD_calculate_boundary_part1 ( ) {
	c = 1.0;

	s = 1.0;

	col_counter = (col_counter + 1);

  }
static inline void singleQRD___acc__calculate_boundary_part2 ( ) {
int32_t index;
	index = row_counter * ROW_SIZE + col_counter;

	//Lets execute the custom instructions
	uint64_t acc_input0;
	uint64_t acc_input1;
	uint64_t acc_input2;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &ROW_SIZE, 4);
	memcpy(&acc_input0, &r[index], 4);
	memcpy(((char*)&acc_input1) + 4, &x_in[col_counter], 4);
	memcpy(&acc_input1, &row_counter, 4);
	memcpy(((char*)&acc_input2) + 4, &col_counter, 4);

	//Output registers - each will hold two outputs
	uint64_t outputReg0;
	uint64_t outputReg1;

	//Time to call the custom instructions
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg0, acc_input0, acc_input1, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg0, acc_input2, 0, FUNCT_FIRE );

	//Save the results (and read any extra result)
	float results0[2];
	memcpy(&results0[0], &outputReg0, 8);

	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg1, 0, 0, FUNCT_READ);
	float results1[2];
	memcpy(&results1[0], &outputReg1, 8);

	//Set the outputs
	r[index] = results0[0];
	c = results0[1];
	s = results1[0];
	col_counter = results1[1];
}
static inline void singleQRD_row_done ( ) {
	printf("4\n");
	row_counter = 0;

	col_counter = 0;

  }
static inline void singleQRD_calculate_inner ( ) {
	float tmp;
	int32_t index;
	printf("5\n");
	index = row_counter * ROW_SIZE + col_counter;

	tmp = c * x_in[col_counter] - s * r[index];

	r[index] = s * x_in[col_counter] + c * r[index];
	x_in[col_counter] = tmp;
	col_counter = (col_counter + 1);

  }
static inline void singleQRD_col_done ( ) {
	printf("6\n");
	row_counter = (row_counter + 1);

	col_counter = row_counter;

  }
static inline void singleQRD_jump_to_read ( ) {
	printf("7\n");
	col_counter = 0;

	row_counter = 0;

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

int int_state_vars_singleQRD = 1;
void initStateVarssingleQRD() {
SquareRoot_ret = 0.0;
singleQRD_State = FSM_singleQRD_state1;

}

int main(void)
{
      if(int_state_vars_singleQRD==1){
        int_state_vars_singleQRD = 0;
        initStateVarssingleQRD();
	}

singleQRDSchedule:
if (( row_counter < COL_SIZE )){ 
	singleQRD___acc__calculate_boundary_part2();
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
     	if (row_counter < COL_SIZE && x_in[row_counter] == 0.0){ 
		singleQRD_calculate_boundary_part1();
		singleQRD_State = FSM_singleQRD_state3;

		goto singleQRDSchedule;
	}

			singleQRD_row_done();
		singleQRD_State = FSM_singleQRD_state1;

		goto singleQRDSchedule;

	     break;

   case FSM_singleQRD_state3:
     	if (( col_counter < ROW_SIZE )){ 
		singleQRD_calculate_inner();
		singleQRD_State = FSM_singleQRD_state3;

		goto singleQRDSchedule;
	}

	if (( row_counter < COL_SIZE )){ 
		singleQRD_col_done();
		singleQRD_State = FSM_singleQRD_state2;

		goto singleQRDSchedule;
	}

	     break;

}
goto singleQRDSchedule;
}
