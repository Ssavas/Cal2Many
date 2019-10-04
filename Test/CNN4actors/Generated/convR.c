//code from conv.cal, instance convR
#include <stdint.h>
#include <string.h>
#include "convR.h"
#include "common.h"


//OutputPorts
uint64_t* convR_ch0_buffer;
volatile int* convR_ch0_ready;
volatile int* convR_ch0_valid;

#define filterRowSize (7) 
#define filterColSize (7) 
#define numberOfFilters (64) 
int32_t convR_filterCounter = 0;
int32_t convR_inputColCounter = 0;
int32_t convR_inputRowCounter = 0;
#define stride (2) 
#define inputColSize (230) 
#define inputRowSize (230) 
float convR_result;
float convR_inputImage[inputRowSize][inputColSize];

int32_t convR_convR_IntCheckOutput = -1;
int convR_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void convR___acc__applyFilter ( ) {
while(*convR_ch0_ready == 0);// Wait for the ready signal. 
	*convR_ch0_buffer = convR_result;//write output
	*convR_ch0_ready = 0; //channel NOT ready to receive new data
	*convR_ch0_valid = 1; //(because) channel has new data 
	
	//Lets execute the custom instructions
	uint64_t acc_input0;
	uint64_t acc_input1;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &convR_filterCounter, 4);
	memcpy(&acc_input0, &convR_inputColCounter, 4);
	memcpy(((char*)&acc_input1) + 4, &convR_inputRowCounter, 4);
	uint32_t tmpInput3 = ((char*)convR_inputImage) + 0;
	memcpy(&acc_input1, &tmpInput3, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, acc_input1, FUNCT_FIRE );

	//Lets read the results
	memcpy(&convR_result, &outputReg, 4);
}
static inline void convR_applyFilter_done ( ) {
		convR_filterCounter = 0;

		convR_inputColCounter = (convR_inputColCounter + stride);

		if (convR_inputColCounter + filterColSize > inputColSize){ 
			convR_inputRowCounter = (convR_inputRowCounter + stride);

			convR_inputColCounter = 0;

		}

}
int convR(void)
{
  
	//OutputPorts
	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[1];
	convR_ch0_buffer = ch0_buffer; 
	convR_ch0_ready = &ch0_ready; 
	convR_ch0_valid = &ch0_valid; 
if ((convR_convR_IntCheckOutput == -1)){ 
		
convRSchedule:

		if (convR_filterCounter < numberOfFilters && convR_inputRowCounter + filterRowSize <= inputRowSize){ 
			
convR_Action_0:

			if (1){ 
				convR___acc__applyFilter();
				goto convRSchedule;
			}
			else {
				convR_convR_IntCheckOutput = 0;

				return(0);
			}

		}

		if (convR_inputRowCounter + filterRowSize <= inputRowSize){ 
			convR_applyFilter_done();
			goto convRSchedule;
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
