//code from conv1.cal, instance conv1Inst
#include <stdint.h>
#include <string.h>
#include "conv1Inst.h"
#include "common.h"


#define filterRowSize (7) 
#define filterColSize (7) 
#define rowPadding (6) 
#define colPadding (6) 
#define inputRowSize (230) 
#define inputColSize (230) 
#define stride (2) 
#define numberOfFilters (64) 
#define numberOfInputChannels (3) 
int32_t conv1Inst_filterCounter = 0;
float conv1Inst_applyResult = 0;
float conv1Inst_outputR = 0;
float conv1Inst_outputG = 0;
float conv1Inst_outputB = 0;
float conv1Inst_conv7_ret = 0;
int32_t conv1Inst_inputRowCounter = 0;
int32_t conv1Inst_inputColCounter = 0;
float conv1Inst_inputImageR[inputRowSize][inputColSize];

float conv1Inst_inputImageG[inputRowSize][inputColSize];

float conv1Inst_inputImageB[inputRowSize][inputColSize];

float conv1Inst_patch[filterRowSize][filterColSize];

float conv1Inst_output[numberOfFilters][(inputRowSize / 2)][(inputColSize / 2)];

int32_t conv1Inst_conv1Inst_State;
#define FSM_conv1Inst_state1 (0) 
#define FSM_conv1Inst_state15 (1) 
#define FSM_conv1Inst_state2 (2) 
#define FSM_conv1Inst_state25 (3) 
#define FSM_conv1Inst_state3 (4) 
#define FSM_conv1Inst_state4 (5) 
#define FSM_conv1Inst_state5 (6) 
static void conv7 (float counter, float patch[7][7]);
int conv1Inst_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void conv1Inst_convR ( ) {
	int32_t i;
	int32_t j;
	i = 0;

	j = 0;

	while (( i < filterRowSize )) {
		j = 0;

		while (( j < filterRowSize )) {
			conv1Inst_patch[i][j] = conv1Inst_inputImageR[(conv1Inst_inputRowCounter + i)][(conv1Inst_inputColCounter + j)];
			j = (j + 1);

		}

		i = (i + 1);

	}

}
static inline void conv1Inst_convG ( ) {
	int32_t i;
	int32_t j;
	i = 0;

	j = 0;

	conv1Inst_outputR = conv1Inst_applyResult;

	while (( i < filterRowSize )) {
		j = 0;

		while (( j < filterRowSize )) {
			conv1Inst_patch[i][j] = conv1Inst_inputImageG[(conv1Inst_inputRowCounter + i)][(conv1Inst_inputColCounter + j)];
			j = (j + 1);

		}

		i = (i + 1);

	}

}
static inline void conv1Inst_convB ( ) {
	int32_t i;
	int32_t j;
	i = 0;

	j = 0;

	conv1Inst_outputG = conv1Inst_applyResult;

	while (( i < filterRowSize )) {
		j = 0;

		while (( j < filterRowSize )) {
			conv1Inst_patch[i][j] = conv1Inst_inputImageG[(conv1Inst_inputRowCounter + i)][(conv1Inst_inputColCounter + j)];
			j = (j + 1);

		}

		i = (i + 1);

	}

}
static inline void conv1Inst___acc__applyFilter ( ) {

	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &conv1Inst_filterCounter, 4);
	uint32_t tmpInput1 = conv1Inst_patch;
	memcpy(&acc_input0, &tmpInput1, 4);
	uint32_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	conv1Inst_applyResult = outputReg;
}
static inline void conv1Inst_accumulate ( ) {
	int32_t rowIndex;
	int32_t colIndex;
	rowIndex = (conv1Inst_inputRowCounter / 2);

	colIndex = (conv1Inst_inputColCounter / 2);

	conv1Inst_outputB = conv1Inst_applyResult;

	conv1Inst_output[conv1Inst_filterCounter][rowIndex][colIndex] = conv1Inst_outputR + conv1Inst_outputB + conv1Inst_outputG;
	conv1Inst_inputRowCounter = (conv1Inst_inputRowCounter + stride);

	if (conv1Inst_inputRowCounter + filterRowSize >= inputRowSize){ 
		conv1Inst_inputRowCounter = 0;

		conv1Inst_inputColCounter = (conv1Inst_inputColCounter + stride);

	}

	if (conv1Inst_inputColCounter + filterRowSize >= inputColSize){ 
		conv1Inst_filterCounter = (conv1Inst_filterCounter + 1);

		conv1Inst_inputColCounter = 0;

	}

}
static void conv7 (float counter, float patch[7][7]) { 

 }

int int_state_vars_conv1Inst = 1; 
void initStateVarsconv1Inst() {
	conv1Inst_conv1Inst_State = FSM_conv1Inst_state1;

}

int conv1Inst(void)
{
      
	if(int_state_vars_conv1Inst == 1){
		int_state_vars_conv1Inst = 0;
		initStateVarsconv1Inst();
	}

conv1InstSchedule:

 switch (conv1Inst_conv1Inst_State) {
   case FSM_conv1Inst_state1:
     	if (( conv1Inst_filterCounter < numberOfFilters )){ 
		conv1Inst_convR();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state15;

		goto conv1InstSchedule;
	}

	     break;

   case FSM_conv1Inst_state15:
     			conv1Inst___acc__applyFilter();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state2;

		goto conv1InstSchedule;

	     break;

   case FSM_conv1Inst_state2:
     	if (( conv1Inst_filterCounter < numberOfFilters )){ 
		conv1Inst_convG();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state25;

		goto conv1InstSchedule;
	}

	     break;

   case FSM_conv1Inst_state25:
     			conv1Inst___acc__applyFilter();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state3;

		goto conv1InstSchedule;

	     break;

   case FSM_conv1Inst_state3:
     	if (( conv1Inst_filterCounter < numberOfFilters )){ 
		conv1Inst_convB();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state4;

		goto conv1InstSchedule;
	}

	     break;

   case FSM_conv1Inst_state4:
     			conv1Inst___acc__applyFilter();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state5;

		goto conv1InstSchedule;

	     break;

   case FSM_conv1Inst_state5:
     			conv1Inst_accumulate();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state1;

		goto conv1InstSchedule;

	     break;

}
goto conv1InstSchedule;
}
