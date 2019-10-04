//code from combiner.cal, instance combiner
#include <stdint.h>
#include <string.h>
#include "combiner.h"
#include "common.h"

//InputPorts
uint64_t* combiner_ch0_buffer SECTION(".core3.data");
uint64_t* combiner_ch1_buffer SECTION(".core3.data");
uint64_t* combiner_ch2_buffer SECTION(".core3.data");
volatile int* combiner_ch0_ready SECTION(".core3.data");
volatile int* combiner_ch0_valid SECTION(".core3.data");
volatile int* combiner_ch1_ready SECTION(".core3.data");
volatile int* combiner_ch1_valid SECTION(".core3.data");
volatile int* combiner_ch2_ready SECTION(".core3.data");
volatile int* combiner_ch2_valid SECTION(".core3.data");

int32_t combiner_counter SECTION(".core3.data") = 0;
int combiner_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void combiner_accumulate ( ) {
	float result;
	float RValue;
	float GValue;
	float BValue;
	while(*combiner_ch0_valid == 0);//Blocking read
	RValue = *combiner_ch0_buffer; //read input 
	*combiner_ch0_ready = 1; // channel ready to receive new data
	*combiner_ch0_valid = 0; // no valid input left on the channel
	
	while(*combiner_ch1_valid == 0);//Blocking read
	GValue = *combiner_ch1_buffer; //read input 
	*combiner_ch1_ready = 1; // channel ready to receive new data
	*combiner_ch1_valid = 0; // no valid input left on the channel
	
	while(*combiner_ch2_valid == 0);//Blocking read
	BValue = *combiner_ch2_buffer; //read input 
	*combiner_ch2_ready = 1; // channel ready to receive new data
	*combiner_ch2_valid = 0; // no valid input left on the channel
	
	result = RValue + GValue + BValue;

	combiner_counter = (combiner_counter + 1);

}
int combiner(void)
{
  
	//InputPorts
 	extern int ch0_ready; 
	extern int ch0_valid; 
	extern uint64_t ch0_buffer[1];
	extern int ch1_ready; 
	extern int ch1_valid; 
	extern uint64_t ch1_buffer[1];
	extern int ch2_ready; 
	extern int ch2_valid; 
	extern uint64_t ch2_buffer[1];
	combiner_ch0_buffer =  ch0_buffer; 
	combiner_ch0_ready = &ch0_ready; 
	combiner_ch0_valid = &ch0_valid; 
	combiner_ch1_buffer =  ch1_buffer; 
	combiner_ch1_ready = &ch1_ready; 
	combiner_ch1_valid = &ch1_valid; 
	combiner_ch2_buffer =  ch2_buffer; 
	combiner_ch2_ready = &ch2_ready; 
	combiner_ch2_valid = &ch2_valid; 

combinerSchedule:
if ((1 && (1 && 1))){ 
	if (( combiner_counter < 802816 )){ 
		combiner_accumulate();
		goto combinerSchedule;
	}

}
goto combinerSchedule;
}
