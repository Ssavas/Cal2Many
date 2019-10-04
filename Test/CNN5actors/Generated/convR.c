//code from conv.cal, instance convR
#include <stdint.h>
#include <string.h>
#include "convR.h"
#include "common.h"

//InputPorts
uint64_t* convR_ch0_buffer SECTION(".core1.data");
volatile int* convR_ch0_ready SECTION(".core1.data");
volatile int* convR_ch0_valid SECTION(".core1.data");

//OutputPorts
uint64_t* convR_ch3_buffer SECTION(".core1.data");
volatile int* convR_ch3_ready SECTION(".core1.data");
volatile int* convR_ch3_valid SECTION(".core1.data");

#define filterRowSize (7) 
#define filterColSize (7) 
#define numberOfFilters (64) 
int32_t convR_inputCounter SECTION(".core1.data") = 0;
int32_t convR_filterCounter SECTION(".core1.data") = 0;
int32_t convR_inputColCounter SECTION(".core1.data") = 0;
int32_t convR_inputRowCounter SECTION(".core1.data") = 0;
#define stride (2) 
#define inputColSize (230) 
#define inputRowSize (230) 
float convR_applyResult SECTION(".core1.data");
float convR_conv7_ret SECTION(".core1.data") = 0;
float convR_inputImage [49] SECTION(".core1.data");

int32_t convR_convR_State SECTION(".core1.data");
#define FSM_convR_state1 (0) 
#define FSM_convR_state2 (1) 
int32_t convR_convR_IntCheckOutput SECTION(".core1.data") = -1;
int convR_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void convR_initReadInput ( ) {
	float value;
	while(*convR_ch0_valid == 0);//Blocking read
	value = *convR_ch0_buffer; //read input 
	*convR_ch0_ready = 1; // channel ready to receive new data
	*convR_ch0_valid = 0; // no valid input left on the channel
	
	convR_inputImage[convR_inputCounter] = value;
	convR_inputCounter = (convR_inputCounter + 1);

}
static inline void convR_readInput ( ) {
	float value;
	while(*convR_ch0_valid == 0);//Blocking read
	value = *convR_ch0_buffer; //read input 
	*convR_ch0_ready = 1; // channel ready to receive new data
	*convR_ch0_valid = 0; // no valid input left on the channel
	
	convR_inputImage[convR_inputCounter] = value;
	convR_inputCounter = (convR_inputCounter + 1);

}
static inline void convR_readInput_done ( ) {
	convR_inputCounter = 0;

}
static inline void convR___acc__applyFilter ( ) {
while(*convR_ch3_ready == 0);// Wait for the ready signal. 
	*convR_ch3_buffer = convR_applyResult;//write output
	*convR_ch3_ready = 0; //channel NOT ready to receive new data
	*convR_ch3_valid = 1; //(because) channel has new data 
	
	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &convR_filterCounter, 4);
	uint32_t tmpInput1 = ((char*)convR_inputImage) + 0;
	memcpy(&acc_input0, &tmpInput1, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	memcpy(&convR_applyResult, &outputReg, 4);
}
static inline void convR_applyFilter_done ( ) {
		convR_filterCounter = 0;

		convR_inputColCounter = (convR_inputColCounter + stride);

		if (convR_inputColCounter + filterColSize > inputColSize){ 
			convR_inputRowCounter = (convR_inputRowCounter + stride);

			convR_inputColCounter = 0;

		}

}
int int_state_vars_convR SECTION(".core1.data") = 1;
void initStateVarsconvR() {
	convR_applyResult = 0.0;
convR_convR_State = FSM_convR_state1;

}

int convR(void)
{
  
	//InputPorts
 	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[1];
	convR_ch0_buffer =  ch0_buffer; 
	convR_ch0_ready = &ch0_ready; 
	convR_ch0_valid = &ch0_valid; 

	//OutputPorts
	extern int ch3_ready; 
	extern int ch3_valid; 
	extern uint64_t ch3_buffer[1];
	convR_ch3_buffer = ch3_buffer; 
	convR_ch3_ready = &ch3_ready; 
	convR_ch3_valid = &ch3_valid; 
    
	if(int_state_vars_convR == 1){
		int_state_vars_convR = 0;
		initStateVarsconvR();
	}
if ((convR_convR_IntCheckOutput == -1)){ 
		
convRSchedule:

		
 switch (convR_convR_State) {
   case FSM_convR_state1:
     			if (1){ 
				if (( convR_inputCounter < 49 ) && (convR_inputColCounter == 0) && convR_inputRowCounter + filterRowSize <= inputRowSize){ 
					convR_initReadInput();
					convR_convR_State = FSM_convR_state1;

					goto convRSchedule;
				}

			}

			if (1){ 
				if (convR_inputCounter < 14 && convR_inputRowCounter + filterRowSize <= inputRowSize){ 
					convR_readInput();
					convR_convR_State = FSM_convR_state1;

					goto convRSchedule;
				}

			}

			if (convR_inputRowCounter + filterRowSize <= inputRowSize){ 
				convR_readInput_done();
				convR_convR_State = FSM_convR_state2;

				goto convRSchedule;
			}

			     break;

   case FSM_convR_state2:
     			if (( convR_filterCounter < numberOfFilters )){ 
				
convR_Action_0:

				if (1){ 
					convR___acc__applyFilter();
					convR_convR_State = FSM_convR_state2;

					goto convRSchedule;
				}
				else {
					convR_convR_IntCheckOutput = 0;

					return(0);
				}

			}

							convR_applyFilter_done();
				convR_convR_State = FSM_convR_state1;

				goto convRSchedule;

			     break;

}

		convR_convR_IntCheckOutput = -1;

	}
	else {
		
 switch (convR_convR_IntCheckOutput) {
   case 0:
     			convR_convR_IntCheckOutput = -1;

			goto convR_Action_0;
}

	}
goto convRSchedule;
}
