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
#define outputRowSize (115) 
#define outputColSize (115) 
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
int32_t conv1Inst_colorIndex = 0;
int32_t conv1Inst_applyFilterCounter = 0;
float conv1Inst_inputImage[numberOfInputChannels][inputRowSize][inputColSize];

float conv1Inst_output[numberOfFilters][outputRowSize][outputColSize];

int32_t conv1Inst_conv1Inst_State;
#define FSM_conv1Inst_state1 (0) 
#define FSM_conv1Inst_state2 (1) 
#define FSM_conv1Inst_state3 (2) 
#define FSM_conv1Inst_state4 (3) 
#define FSM_conv1Inst_state5 (4) 
#define FSM_conv1Inst_state6 (5) 
static void conv7 (int conv1Inst_filterCounter, float inputImageAddr);
int conv1Inst_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void conv1Inst___acc__applyFilter ( ) {

	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &conv1Inst_filterCounter, 4);
	uint32_t tmpInput1 = ((char*)conv1Inst_inputImage) + sizeof(float) * (conv1Inst_colorIndex * inputRowSize * inputColSize + conv1Inst_inputRowCounter * inputColSize + conv1Inst_inputColCounter);
	memcpy(&acc_input0, &tmpInput1, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	memcpy(&conv1Inst_applyResult, &outputReg, 4);
}
static inline void conv1Inst_accumulate ( ) {
	int32_t rowIndex;
	int32_t colIndex;
	if ((conv1Inst_colorIndex == 0)){ 
		conv1Inst_outputR = conv1Inst_applyResult;

		conv1Inst_colorIndex = (conv1Inst_colorIndex + 1);

	}
	else {
		if ((conv1Inst_colorIndex == 1)){ 
			conv1Inst_outputG = conv1Inst_applyResult;

			conv1Inst_colorIndex = (conv1Inst_colorIndex + 1);

		}
		else {
			if ((conv1Inst_colorIndex == 2)){ 
				conv1Inst_outputB = conv1Inst_applyResult;

				rowIndex = (conv1Inst_inputRowCounter >> 1);

				colIndex = (conv1Inst_inputColCounter >> 1);

				conv1Inst_output[conv1Inst_filterCounter][rowIndex][colIndex] = conv1Inst_outputR + conv1Inst_outputG + conv1Inst_outputB;
				conv1Inst_inputColCounter = (conv1Inst_inputColCounter + stride);

				if (conv1Inst_inputColCounter + filterColSize > inputColSize){ 
					conv1Inst_inputColCounter = 0;

					conv1Inst_inputRowCounter = (conv1Inst_inputRowCounter + stride);

				}

				if (conv1Inst_inputRowCounter + filterRowSize > inputRowSize){ 
					conv1Inst_filterCounter = (conv1Inst_filterCounter + 1);

					conv1Inst_inputRowCounter = 0;

				}

				conv1Inst_colorIndex = 0;

			}

		}

	}

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
		conv1Inst___acc__applyFilter();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state2;

		goto conv1InstSchedule;
	}

	     break;

   case FSM_conv1Inst_state2:
     			conv1Inst_accumulate();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state3;

		goto conv1InstSchedule;

	     break;

   case FSM_conv1Inst_state3:
     	if (( conv1Inst_filterCounter < numberOfFilters )){ 
		conv1Inst___acc__applyFilter();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state4;

		goto conv1InstSchedule;
	}

	     break;

   case FSM_conv1Inst_state4:
     			conv1Inst_accumulate();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state5;

		goto conv1InstSchedule;

	     break;

   case FSM_conv1Inst_state5:
     	if (( conv1Inst_filterCounter < numberOfFilters )){ 
		conv1Inst___acc__applyFilter();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state6;

		goto conv1InstSchedule;
	}

	     break;

   case FSM_conv1Inst_state6:
     			conv1Inst_accumulate();
		conv1Inst_conv1Inst_State = FSM_conv1Inst_state1;

		goto conv1InstSchedule;

	     break;

}
goto conv1InstSchedule;
}
