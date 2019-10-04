//code from conv.cal, instance convB
#include <stdint.h>
#include <string.h>
#include "convB.h"
#include "common.h"


//OutputPorts
uint64_t* convB_ch2_buffer SECTION(".core2.data");
volatile int* convB_ch2_ready SECTION(".core2.data");
volatile int* convB_ch2_valid SECTION(".core2.data");

#define filterRowSize (7) 
#define filterColSize (7) 
#define numberOfFilters (64) 
int32_t convB_filterCounter SECTION(".core2.data") = 0;
int32_t convB_inputColCounter SECTION(".core2.data") = 0;
int32_t convB_inputRowCounter SECTION(".core2.data") = 0;
#define stride (2) 
#define inputColSize (230) 
#define inputRowSize (230) 
float convB_result SECTION(".core2.data");
float convB_inputImage[inputRowSize][inputColSize] SECTION(".core2.data");

int32_t convB_convB_IntCheckOutput SECTION(".core2.data") = -1;
int convB_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void convB___acc__applyFilter ( ) {
while(*convB_ch2_ready == 0);// Wait for the ready signal. 
	*convB_ch2_buffer = convB_result;//write output
	*convB_ch2_ready = 0; //channel NOT ready to receive new data
	*convB_ch2_valid = 1; //(because) channel has new data 
	
	//Lets execute the custom instructions
	uint64_t acc_input0;
	uint64_t acc_input1;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &convB_filterCounter, 4);
	memcpy(&acc_input0, &convB_inputColCounter, 4);
	memcpy(((char*)&acc_input1) + 4, &convB_inputRowCounter, 4);
	uint32_t tmpInput3 = ((char*)convB_inputImage) + 0;
	memcpy(&acc_input1, &tmpInput3, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, acc_input1, FUNCT_FIRE );

	//Lets read the results
	memcpy(&convB_result, &outputReg, 4);
}
static inline void convB_applyFilter_done ( ) {
		convB_filterCounter = 0;

		convB_inputColCounter = (convB_inputColCounter + stride);

		if (convB_inputColCounter + filterColSize > inputColSize){ 
			convB_inputRowCounter = (convB_inputRowCounter + stride);

			convB_inputColCounter = 0;

		}

}
int convB(void)
{
  
	//OutputPorts
	extern int ch2_ready; 
	extern int ch2_valid; 
	extern uint64_t ch2_buffer[1];
	convB_ch2_buffer = ch2_buffer; 
	convB_ch2_ready = &ch2_ready; 
	convB_ch2_valid = &ch2_valid; 
if ((convB_convB_IntCheckOutput == -1)){ 
		
convBSchedule:

		if (convB_filterCounter < numberOfFilters && convB_inputRowCounter + filterRowSize <= inputRowSize){ 
			
convB_Action_0:

			if (1){ 
				convB___acc__applyFilter();
				goto convBSchedule;
			}
			else {
				convB_convB_IntCheckOutput = 0;

				return(0);
			}

		}

		if (convB_inputRowCounter + filterRowSize <= inputRowSize){ 
			convB_applyFilter_done();
			goto convBSchedule;
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
