//code from combiner.cal, instance combiner
#include <stdint.h>
#include <string.h>
#include "combiner.h"
#include "common.h"

//InputPorts
uint64_t* combiner_ch3_buffer SECTION(".core4.data");
uint64_t* combiner_ch4_buffer SECTION(".core4.data");
uint64_t* combiner_ch5_buffer SECTION(".core4.data");
volatile int* combiner_ch3_ready SECTION(".core4.data");
volatile int* combiner_ch3_valid SECTION(".core4.data");
volatile int* combiner_ch4_ready SECTION(".core4.data");
volatile int* combiner_ch4_valid SECTION(".core4.data");
volatile int* combiner_ch5_ready SECTION(".core4.data");
volatile int* combiner_ch5_valid SECTION(".core4.data");

int32_t combiner_counter SECTION(".core4.data") = 0;
int combiner_checkFlag(volatile int* flag){
	while(*flag == 0);
	return 1;
}
static inline void combiner_accumulate ( ) {
	float result;
	float RValue;
	float GValue;
	float BValue;
	while(*combiner_ch3_valid == 0);//Blocking read
	RValue = *combiner_ch3_buffer; //read input 
	*combiner_ch3_ready = 1; // channel ready to receive new data
	*combiner_ch3_valid = 0; // no valid input left on the channel
	
	while(*combiner_ch4_valid == 0);//Blocking read
	GValue = *combiner_ch4_buffer; //read input 
	*combiner_ch4_ready = 1; // channel ready to receive new data
	*combiner_ch4_valid = 0; // no valid input left on the channel
	
	while(*combiner_ch5_valid == 0);//Blocking read
	BValue = *combiner_ch5_buffer; //read input 
	*combiner_ch5_ready = 1; // channel ready to receive new data
	*combiner_ch5_valid = 0; // no valid input left on the channel
	
	result = RValue + GValue + BValue;

	combiner_counter = (combiner_counter + 1);

}
int combiner(void)
{
  
	//InputPorts
 	extern int ch3_ready; 
	extern int ch3_valid; 
	extern uint64_t ch3_buffer[1];
	extern int ch4_ready; 
	extern int ch4_valid; 
	extern uint64_t ch4_buffer[1];
	extern int ch5_ready; 
	extern int ch5_valid; 
	extern uint64_t ch5_buffer[1];
	combiner_ch3_buffer =  ch3_buffer; 
	combiner_ch3_ready = &ch3_ready; 
	combiner_ch3_valid = &ch3_valid; 
	combiner_ch4_buffer =  ch4_buffer; 
	combiner_ch4_ready = &ch4_ready; 
	combiner_ch4_valid = &ch4_valid; 
	combiner_ch5_buffer =  ch5_buffer; 
	combiner_ch5_ready = &ch5_ready; 
	combiner_ch5_valid = &ch5_valid; 

combinerSchedule:
if ((1 && (1 && 1))){ 
	if (( combiner_counter < 802816 )){ 
		combiner_accumulate();
		goto combinerSchedule;
	}

}
goto combinerSchedule;
}
