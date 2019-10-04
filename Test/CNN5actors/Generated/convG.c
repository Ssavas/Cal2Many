//code from conv.cal, instance convG
#include <stdint.h>
#include <string.h>
#include "convG.h"
#include "common.h"

//InputPorts
uint64_t* convG_ch1_buffer SECTION(".core2.data");
volatile int* convG_ch1_ready SECTION(".core2.data");
volatile int* convG_ch1_valid SECTION(".core2.data");

//OutputPorts
uint64_t* convG_ch4_buffer SECTION(".core2.data");
volatile int* convG_ch4_ready SECTION(".core2.data");
volatile int* convG_ch4_valid SECTION(".core2.data");

#define filterRowSize (7) 
#define filterColSize (7) 
#define numberOfFilters (64) 
int32_t convG_inputCounter SECTION(".core2.data") = 0;
int32_t convG_filterCounter SECTION(".core2.data") = 0;
int32_t convG_inputColCounter SECTION(".core2.data") = 0;
int32_t convG_inputRowCounter SECTION(".core2.data") = 0;
#define stride (2) 
#define inputColSize (230) 
#define inputRowSize (230) 
float convG_applyResult SECTION(".core2.data");
float convG_conv7_ret SECTION(".core2.data") = 0;
float convG_inputImage [49] SECTION(".core2.data");

int32_t convG_convG_State SECTION(".core2.data");
#define FSM_convG_state1 (0) 
#define FSM_convG_state2 (1) 
int32_t convG_convG_IntCheckOutput SECTION(".core2.data") = -1;
int convG_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void convG_initReadInput ( ) {
	float value;
	while(*convG_ch1_valid == 0);//Blocking read
	value = *convG_ch1_buffer; //read input 
	*convG_ch1_ready = 1; // channel ready to receive new data
	*convG_ch1_valid = 0; // no valid input left on the channel
	
	convG_inputImage[convG_inputCounter] = value;
	convG_inputCounter = (convG_inputCounter + 1);

}
static inline void convG_readInput ( ) {
	float value;
	while(*convG_ch1_valid == 0);//Blocking read
	value = *convG_ch1_buffer; //read input 
	*convG_ch1_ready = 1; // channel ready to receive new data
	*convG_ch1_valid = 0; // no valid input left on the channel
	
	convG_inputImage[convG_inputCounter] = value;
	convG_inputCounter = (convG_inputCounter + 1);

}
static inline void convG_readInput_done ( ) {
	convG_inputCounter = 0;

}
static inline void convG___acc__applyFilter ( ) {
while(*convG_ch4_ready == 0);// Wait for the ready signal. 
	*convG_ch4_buffer = convG_applyResult;//write output
	*convG_ch4_ready = 0; //channel NOT ready to receive new data
	*convG_ch4_valid = 1; //(because) channel has new data 
	
	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &convG_filterCounter, 4);
	uint32_t tmpInput1 = ((char*)convG_inputImage) + 0;
	memcpy(&acc_input0, &tmpInput1, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	memcpy(&convG_applyResult, &outputReg, 4);
}
static inline void convG_applyFilter_done ( ) {
		convG_filterCounter = 0;

		convG_inputColCounter = (convG_inputColCounter + stride);

		if (convG_inputColCounter + filterColSize > inputColSize){ 
			convG_inputRowCounter = (convG_inputRowCounter + stride);

			convG_inputColCounter = 0;

		}

}
int int_state_vars_convG SECTION(".core2.data") = 1;
void initStateVarsconvG() {
	convG_applyResult = 0.0;
convG_convG_State = FSM_convG_state1;

}

int convG(void)
{
  
	//InputPorts
 	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[1];
	convG_ch1_buffer =  ch1_buffer; 
	convG_ch1_ready = &ch1_ready; 
	convG_ch1_valid = &ch1_valid; 

	//OutputPorts
	extern int ch4_ready; 
	extern int ch4_valid; 
	extern uint64_t ch4_buffer[1];
	convG_ch4_buffer = ch4_buffer; 
	convG_ch4_ready = &ch4_ready; 
	convG_ch4_valid = &ch4_valid; 
    
	if(int_state_vars_convG == 1){
		int_state_vars_convG = 0;
		initStateVarsconvG();
	}
if ((convG_convG_IntCheckOutput == -1)){ 
		
convGSchedule:

		
 switch (convG_convG_State) {
   case FSM_convG_state1:
     			if (1){ 
				if (( convG_inputCounter < 49 ) && (convG_inputColCounter == 0) && convG_inputRowCounter + filterRowSize <= inputRowSize){ 
					convG_initReadInput();
					convG_convG_State = FSM_convG_state1;

					goto convGSchedule;
				}

			}

			if (1){ 
				if (convG_inputCounter < 14 && convG_inputRowCounter + filterRowSize <= inputRowSize){ 
					convG_readInput();
					convG_convG_State = FSM_convG_state1;

					goto convGSchedule;
				}

			}

			if (convG_inputRowCounter + filterRowSize <= inputRowSize){ 
				convG_readInput_done();
				convG_convG_State = FSM_convG_state2;

				goto convGSchedule;
			}

			     break;

   case FSM_convG_state2:
     			if (( convG_filterCounter < numberOfFilters )){ 
				
convG_Action_0:

				if (1){ 
					convG___acc__applyFilter();
					convG_convG_State = FSM_convG_state2;

					goto convGSchedule;
				}
				else {
					convG_convG_IntCheckOutput = 0;

					return(0);
				}

			}

							convG_applyFilter_done();
				convG_convG_State = FSM_convG_state1;

				goto convGSchedule;

			     break;

}

		convG_convG_IntCheckOutput = -1;

	}
	else {
		
 switch (convG_convG_IntCheckOutput) {
   case 0:
     			convG_convG_IntCheckOutput = -1;

			goto convG_Action_0;
}

	}
goto convGSchedule;
}
