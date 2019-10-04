//code from conv.cal, instance convB
#include <stdint.h>
#include <string.h>
#include "convB.h"
#include "common.h"

//InputPorts
uint64_t* convB_ch2_buffer SECTION(".core3.data");
volatile int* convB_ch2_ready SECTION(".core3.data");
volatile int* convB_ch2_valid SECTION(".core3.data");

//OutputPorts
uint64_t* convB_ch5_buffer SECTION(".core3.data");
volatile int* convB_ch5_ready SECTION(".core3.data");
volatile int* convB_ch5_valid SECTION(".core3.data");

#define filterRowSize (7) 
#define filterColSize (7) 
#define numberOfFilters (64) 
int32_t convB_inputCounter SECTION(".core3.data") = 0;
int32_t convB_filterCounter SECTION(".core3.data") = 0;
int32_t convB_inputColCounter SECTION(".core3.data") = 0;
int32_t convB_inputRowCounter SECTION(".core3.data") = 0;
#define stride (2) 
#define inputColSize (230) 
#define inputRowSize (230) 
float convB_applyResult SECTION(".core3.data");
float convB_conv7_ret SECTION(".core3.data") = 0;
float convB_inputImage [49] SECTION(".core3.data");

int32_t convB_convB_State SECTION(".core3.data");
#define FSM_convB_state1 (0) 
#define FSM_convB_state2 (1) 
int32_t convB_convB_IntCheckOutput SECTION(".core3.data") = -1;
int convB_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void convB_initReadInput ( ) {
	float value;
	while(*convB_ch2_valid == 0);//Blocking read
	value = *convB_ch2_buffer; //read input 
	*convB_ch2_ready = 1; // channel ready to receive new data
	*convB_ch2_valid = 0; // no valid input left on the channel
	
	convB_inputImage[convB_inputCounter] = value;
	convB_inputCounter = (convB_inputCounter + 1);

}
static inline void convB_readInput ( ) {
	float value;
	while(*convB_ch2_valid == 0);//Blocking read
	value = *convB_ch2_buffer; //read input 
	*convB_ch2_ready = 1; // channel ready to receive new data
	*convB_ch2_valid = 0; // no valid input left on the channel
	
	convB_inputImage[convB_inputCounter] = value;
	convB_inputCounter = (convB_inputCounter + 1);

}
static inline void convB_readInput_done ( ) {
	convB_inputCounter = 0;

}
static inline void convB___acc__applyFilter ( ) {
while(*convB_ch5_ready == 0);// Wait for the ready signal. 
	*convB_ch5_buffer = convB_applyResult;//write output
	*convB_ch5_ready = 0; //channel NOT ready to receive new data
	*convB_ch5_valid = 1; //(because) channel has new data 
	
	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &convB_filterCounter, 4);
	uint32_t tmpInput1 = ((char*)convB_inputImage) + 0;
	memcpy(&acc_input0, &tmpInput1, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	memcpy(&convB_applyResult, &outputReg, 4);
}
static inline void convB_applyFilter_done ( ) {
		convB_filterCounter = 0;

		convB_inputColCounter = (convB_inputColCounter + stride);

		if (convB_inputColCounter + filterColSize > inputColSize){ 
			convB_inputRowCounter = (convB_inputRowCounter + stride);

			convB_inputColCounter = 0;

		}

}
int int_state_vars_convB SECTION(".core3.data") = 1;
void initStateVarsconvB() {
	convB_applyResult = 0.0;
convB_convB_State = FSM_convB_state1;

}

int convB(void)
{
  
	//InputPorts
 	extern int ch2_ready; 
	extern int ch2_valid; 
	extern uint64_t ch2_buffer[1];
	convB_ch2_buffer =  ch2_buffer; 
	convB_ch2_ready = &ch2_ready; 
	convB_ch2_valid = &ch2_valid; 

	//OutputPorts
	extern int ch5_ready; 
	extern int ch5_valid; 
	extern uint64_t ch5_buffer[1];
	convB_ch5_buffer = ch5_buffer; 
	convB_ch5_ready = &ch5_ready; 
	convB_ch5_valid = &ch5_valid; 
    
	if(int_state_vars_convB == 1){
		int_state_vars_convB = 0;
		initStateVarsconvB();
	}
if ((convB_convB_IntCheckOutput == -1)){ 
		
convBSchedule:

		
 switch (convB_convB_State) {
   case FSM_convB_state1:
     			if (1){ 
				if (( convB_inputCounter < 49 ) && (convB_inputColCounter == 0) && convB_inputRowCounter + filterRowSize <= inputRowSize){ 
					convB_initReadInput();
					convB_convB_State = FSM_convB_state1;

					goto convBSchedule;
				}

			}

			if (1){ 
				if (convB_inputCounter < 14 && convB_inputRowCounter + filterRowSize <= inputRowSize){ 
					convB_readInput();
					convB_convB_State = FSM_convB_state1;

					goto convBSchedule;
				}

			}

			if (convB_inputRowCounter + filterRowSize <= inputRowSize){ 
				convB_readInput_done();
				convB_convB_State = FSM_convB_state2;

				goto convBSchedule;
			}

			     break;

   case FSM_convB_state2:
     			if (( convB_filterCounter < numberOfFilters )){ 
				
convB_Action_0:

				if (1){ 
					convB___acc__applyFilter();
					convB_convB_State = FSM_convB_state2;

					goto convBSchedule;
				}
				else {
					convB_convB_IntCheckOutput = 0;

					return(0);
				}

			}

							convB_applyFilter_done();
				convB_convB_State = FSM_convB_state1;

				goto convBSchedule;

			     break;

}

		convB_convB_IntCheckOutput = -1;

	}
	else {
		
 switch (convB_convB_IntCheckOutput) {
   case 0:
     			convB_convB_IntCheckOutput = -1;

			goto convB_Action_0;
}

	}
goto convBSchedule;
}
