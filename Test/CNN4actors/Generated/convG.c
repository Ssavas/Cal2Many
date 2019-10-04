//code from conv.cal, instance convG
#include <stdint.h>
#include <string.h>
#include "convG.h"
#include "common.h"


//OutputPorts
uint64_t* convG_ch1_buffer SECTION(".core1.data");
volatile int* convG_ch1_ready SECTION(".core1.data");
volatile int* convG_ch1_valid SECTION(".core1.data");

#define filterRowSize (7) 
#define filterColSize (7) 
#define numberOfFilters (64) 
int32_t convG_filterCounter SECTION(".core1.data") = 0;
int32_t convG_inputColCounter SECTION(".core1.data") = 0;
int32_t convG_inputRowCounter SECTION(".core1.data") = 0;
#define stride (2) 
#define inputColSize (230) 
#define inputRowSize (230) 
float convG_result SECTION(".core1.data");
float convG_inputImage[inputRowSize][inputColSize] SECTION(".core1.data");

int32_t convG_convG_IntCheckOutput SECTION(".core1.data") = -1;
int convG_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void convG___acc__applyFilter ( ) {
while(*convG_ch1_ready == 0);// Wait for the ready signal. 
	*convG_ch1_buffer = convG_result;//write output
	*convG_ch1_ready = 0; //channel NOT ready to receive new data
	*convG_ch1_valid = 1; //(because) channel has new data 
	
	//Lets execute the custom instructions
	uint64_t acc_input0;
	uint64_t acc_input1;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &convG_filterCounter, 4);
	memcpy(&acc_input0, &convG_inputColCounter, 4);
	memcpy(((char*)&acc_input1) + 4, &convG_inputRowCounter, 4);
	uint32_t tmpInput3 = ((char*)convG_inputImage) + 0;
	memcpy(&acc_input1, &tmpInput3, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, acc_input1, FUNCT_FIRE );

	//Lets read the results
	memcpy(&convG_result, &outputReg, 4);
}
static inline void convG_applyFilter_done ( ) {
		convG_filterCounter = 0;

		convG_inputColCounter = (convG_inputColCounter + stride);

		if (convG_inputColCounter + filterColSize > inputColSize){ 
			convG_inputRowCounter = (convG_inputRowCounter + stride);

			convG_inputColCounter = 0;

		}

}
int convG(void)
{
  
	//OutputPorts
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[1];
	convG_ch1_buffer = ch1_buffer; 
	convG_ch1_ready = &ch1_ready; 
	convG_ch1_valid = &ch1_valid; 
if ((convG_convG_IntCheckOutput == -1)){ 
		
convGSchedule:

		if (convG_filterCounter < numberOfFilters && convG_inputRowCounter + filterRowSize <= inputRowSize){ 
			
convG_Action_0:

			if (1){ 
				convG___acc__applyFilter();
				goto convGSchedule;
			}
			else {
				convG_convG_IntCheckOutput = 0;

				return(0);
			}

		}

		if (convG_inputRowCounter + filterRowSize <= inputRowSize){ 
			convG_applyFilter_done();
			goto convGSchedule;
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
