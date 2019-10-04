//code from splitter.cal, instance splitter
#include <stdint.h>
#include <string.h>
#include "splitter.h"
#include "common.h"


//OutputPorts
uint64_t* splitter_ch0_buffer;
uint64_t* splitter_ch1_buffer;
uint64_t* splitter_ch2_buffer;
volatile int* splitter_ch0_ready;
volatile int* splitter_ch0_valid;
volatile int* splitter_ch1_ready;
volatile int* splitter_ch1_valid;
volatile int* splitter_ch2_ready;
volatile int* splitter_ch2_valid;

#define inputRowSize (230) 
#define inputColSize (230) 
#define numberOfInputChannels (3) 
#define filterRowSize (7) 
#define filterColSize (7) 
#define stride (2) 
int32_t splitter_inputRowCounter = 0;
int32_t splitter_inputColCounter = 0;
int32_t splitter_colorIndex = 0;
int32_t splitter_i = 0;
int32_t splitter_j = 0;
float splitter_inputImage[numberOfInputChannels][inputRowSize][inputColSize];

int32_t splitter_splitter_State;
#define FSM_splitter_state1 (0) 
#define FSM_splitter_state2 (1) 
#define FSM_splitter_state3 (2) 
int32_t splitter_splitter_IntCheckOutput = -1;
int splitter_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void splitter_initSendR ( ) {
	float value;
	value = splitter_inputImage[splitter_colorIndex][(splitter_inputRowCounter + splitter_i)][splitter_j];

	splitter_j = (splitter_j + 1);

	if ((splitter_j == filterRowSize)){ 
		splitter_j = 0;

		splitter_i = (splitter_i + 1);

	}

	while(*splitter_ch0_ready == 0);// Wait for the ready signal. 
	*splitter_ch0_buffer = value;//write output
	*splitter_ch0_ready = 0; //channel NOT ready to receive new data
	*splitter_ch0_valid = 1; //(because) channel has new data 
	
}
static inline void splitter_sendR ( ) {
	float value;
	value = splitter_inputImage[splitter_colorIndex][(splitter_inputRowCounter + splitter_i)][splitter_inputColCounter + 5 + splitter_j];

	splitter_j = (splitter_j + 1);

	if ((splitter_j == stride)){ 
		splitter_j = 0;

		splitter_i = (splitter_i + 1);

	}

	while(*splitter_ch0_ready == 0);// Wait for the ready signal. 
	*splitter_ch0_buffer = value;//write output
	*splitter_ch0_ready = 0; //channel NOT ready to receive new data
	*splitter_ch0_valid = 1; //(because) channel has new data 
	
}
static inline void splitter_sendR_done ( ) {
	splitter_i = 0;

	splitter_j = 0;

	splitter_colorIndex = 1;

}
static inline void splitter_initSendG ( ) {
	float value;
	value = splitter_inputImage[splitter_colorIndex][(splitter_inputRowCounter + splitter_i)][(splitter_inputColCounter + splitter_j)];

	splitter_j = (splitter_j + 1);

	if ((splitter_j == 7)){ 
		splitter_j = 0;

		splitter_i = (splitter_i + 1);

	}

	while(*splitter_ch1_ready == 0);// Wait for the ready signal. 
	*splitter_ch1_buffer = value;//write output
	*splitter_ch1_ready = 0; //channel NOT ready to receive new data
	*splitter_ch1_valid = 1; //(because) channel has new data 
	
}
static inline void splitter_sendG ( ) {
	float value;
	value = splitter_inputImage[splitter_colorIndex][(splitter_inputRowCounter + splitter_i)][splitter_inputColCounter + 5 + splitter_j];

	splitter_j = (splitter_j + 1);

	if ((splitter_j == stride)){ 
		splitter_j = 0;

		splitter_i = (splitter_i + 1);

	}

	while(*splitter_ch1_ready == 0);// Wait for the ready signal. 
	*splitter_ch1_buffer = value;//write output
	*splitter_ch1_ready = 0; //channel NOT ready to receive new data
	*splitter_ch1_valid = 1; //(because) channel has new data 
	
}
static inline void splitter_sendG_done ( ) {
	splitter_i = 0;

	splitter_j = 0;

	splitter_colorIndex = 2;

}
static inline void splitter_initSendB ( ) {
	float value;
	value = splitter_inputImage[splitter_colorIndex][(splitter_inputRowCounter + splitter_i)][splitter_inputColCounter + 5 + splitter_j];

	splitter_j = (splitter_j + 1);

	if ((splitter_j == 7)){ 
		splitter_j = 0;

		splitter_i = (splitter_i + 1);

	}

	while(*splitter_ch2_ready == 0);// Wait for the ready signal. 
	*splitter_ch2_buffer = value;//write output
	*splitter_ch2_ready = 0; //channel NOT ready to receive new data
	*splitter_ch2_valid = 1; //(because) channel has new data 
	
}
static inline void splitter_sendB ( ) {
	float value;
	value = splitter_inputImage[splitter_colorIndex][(splitter_inputRowCounter + splitter_i)][(splitter_inputColCounter + splitter_j)];

	splitter_j = (splitter_j + 1);

	if ((splitter_j == stride)){ 
		splitter_j = 0;

		splitter_i = (splitter_i + 1);

	}

	while(*splitter_ch2_ready == 0);// Wait for the ready signal. 
	*splitter_ch2_buffer = value;//write output
	*splitter_ch2_ready = 0; //channel NOT ready to receive new data
	*splitter_ch2_valid = 1; //(because) channel has new data 
	
}
static inline void splitter_sendB_done ( ) {
	splitter_i = 0;

	splitter_j = 0;

	splitter_colorIndex = 0;

	splitter_inputColCounter = (splitter_inputColCounter + stride);

	if (splitter_inputColCounter + filterColSize > inputColSize){ 
		splitter_inputColCounter = 0;

		splitter_inputRowCounter = (splitter_inputRowCounter + stride);

	}

}
int int_state_vars_splitter = 1; 
void initStateVarssplitter() {
	splitter_splitter_State = FSM_splitter_state1;

}

int splitter(void)
{
  
	//OutputPorts
	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[1];
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[1];
	extern int ch2_ready; 
	extern int ch2_valid; 
	extern uint64_t ch2_buffer[1];
	splitter_ch0_buffer = ch0_buffer; 
	splitter_ch0_ready = &ch0_ready; 
	splitter_ch0_valid = &ch0_valid; 
	splitter_ch1_buffer = ch1_buffer; 
	splitter_ch1_ready = &ch1_ready; 
	splitter_ch1_valid = &ch1_valid; 
	splitter_ch2_buffer = ch2_buffer; 
	splitter_ch2_ready = &ch2_ready; 
	splitter_ch2_valid = &ch2_valid; 
    
	if(int_state_vars_splitter == 1){
		int_state_vars_splitter = 0;
		initStateVarssplitter();
	}
if ((splitter_splitter_IntCheckOutput == -1)){ 
	
splitterSchedule:

	
 switch (splitter_splitter_State) {
   case FSM_splitter_state1:
     		if (( splitter_i < filterColSize ) && splitter_inputRowCounter + filterRowSize <= inputRowSize && (splitter_inputColCounter == 0)){ 
			
splitter_Action_0:

			if (1){ 
				splitter_initSendR();
				splitter_splitter_State = FSM_splitter_state1;

				goto splitterSchedule;
			}
			else {
				splitter_splitter_IntCheckOutput = 0;

				return(0);
			}

		}

		if ((( splitter_i < filterColSize ) && splitter_inputRowCounter + filterRowSize <= inputRowSize)){ 
			
splitter_Action_1:

			if (1){ 
				splitter_sendR();
				splitter_splitter_State = FSM_splitter_state1;

				goto splitterSchedule;
			}
			else {
				splitter_splitter_IntCheckOutput = 1;

				return(0);
			}

		}

					splitter_sendR_done();
			splitter_splitter_State = FSM_splitter_state2;

			goto splitterSchedule;

		     break;

   case FSM_splitter_state2:
     		if ((( splitter_i < filterColSize ) && (splitter_inputColCounter == 0))){ 
			
splitter_Action_2:

			if (1){ 
				splitter_initSendG();
				splitter_splitter_State = FSM_splitter_state2;

				goto splitterSchedule;
			}
			else {
				splitter_splitter_IntCheckOutput = 2;

				return(0);
			}

		}

		if (( splitter_i < filterColSize )){ 
			
splitter_Action_3:

			if (1){ 
				splitter_sendG();
				splitter_splitter_State = FSM_splitter_state2;

				goto splitterSchedule;
			}
			else {
				splitter_splitter_IntCheckOutput = 3;

				return(0);
			}

		}

					splitter_sendG_done();
			splitter_splitter_State = FSM_splitter_state3;

			goto splitterSchedule;

		     break;

   case FSM_splitter_state3:
     		if ((( splitter_i < filterColSize ) && (splitter_inputColCounter == 0))){ 
			
splitter_Action_4:

			if (1){ 
				splitter_initSendB();
				splitter_splitter_State = FSM_splitter_state3;

				goto splitterSchedule;
			}
			else {
				splitter_splitter_IntCheckOutput = 4;

				return(0);
			}

		}

		if (( splitter_i < filterColSize )){ 
			
splitter_Action_5:

			if (1){ 
				splitter_sendB();
				splitter_splitter_State = FSM_splitter_state3;

				goto splitterSchedule;
			}
			else {
				splitter_splitter_IntCheckOutput = 5;

				return(0);
			}

		}

					splitter_sendB_done();
			splitter_splitter_State = FSM_splitter_state1;

			goto splitterSchedule;

		     break;

}

	splitter_splitter_IntCheckOutput = -1;

}
else {
	
 switch (splitter_splitter_IntCheckOutput) {
   case 0:
     		splitter_splitter_IntCheckOutput = -1;

		goto splitter_Action_0;
   case 1:
     		splitter_splitter_IntCheckOutput = -1;

		goto splitter_Action_1;
   case 2:
     		splitter_splitter_IntCheckOutput = -1;

		goto splitter_Action_2;
   case 3:
     		splitter_splitter_IntCheckOutput = -1;

		goto splitter_Action_3;
   case 4:
     		splitter_splitter_IntCheckOutput = -1;

		goto splitter_Action_4;
   case 5:
     		splitter_splitter_IntCheckOutput = -1;

		goto splitter_Action_5;
}

}
goto splitterSchedule;
}
