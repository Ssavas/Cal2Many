//code from correlation_actor.cal, instance correlator
#include <stdint.h>
#include <string.h>
#include "correlator.h"
#include "common.h"

//InputPorts
uint64_t* correlator_ch12_buffer SECTION(".core12.data");
uint64_t* correlator_ch13_buffer SECTION(".core12.data");
uint64_t* correlator_ch14_buffer SECTION(".core12.data");
uint64_t* correlator_ch15_buffer SECTION(".core12.data");
uint64_t* correlator_ch16_buffer SECTION(".core12.data");
uint64_t* correlator_ch17_buffer SECTION(".core12.data");
uint64_t* correlator_ch18_buffer SECTION(".core12.data");
uint64_t* correlator_ch19_buffer SECTION(".core12.data");
uint64_t* correlator_ch20_buffer SECTION(".core12.data");
uint64_t* correlator_ch21_buffer SECTION(".core12.data");
uint64_t* correlator_ch22_buffer SECTION(".core12.data");
uint64_t* correlator_ch23_buffer SECTION(".core12.data");
int* correlator_ch12_ready SECTION(".core12.data");
int* correlator_ch12_valid SECTION(".core12.data");
int* correlator_ch13_ready SECTION(".core12.data");
int* correlator_ch13_valid SECTION(".core12.data");
int* correlator_ch14_ready SECTION(".core12.data");
int* correlator_ch14_valid SECTION(".core12.data");
int* correlator_ch15_ready SECTION(".core12.data");
int* correlator_ch15_valid SECTION(".core12.data");
int* correlator_ch16_ready SECTION(".core12.data");
int* correlator_ch16_valid SECTION(".core12.data");
int* correlator_ch17_ready SECTION(".core12.data");
int* correlator_ch17_valid SECTION(".core12.data");
int* correlator_ch18_ready SECTION(".core12.data");
int* correlator_ch18_valid SECTION(".core12.data");
int* correlator_ch19_ready SECTION(".core12.data");
int* correlator_ch19_valid SECTION(".core12.data");
int* correlator_ch20_ready SECTION(".core12.data");
int* correlator_ch20_valid SECTION(".core12.data");
int* correlator_ch21_ready SECTION(".core12.data");
int* correlator_ch21_valid SECTION(".core12.data");
int* correlator_ch22_ready SECTION(".core12.data");
int* correlator_ch22_valid SECTION(".core12.data");
int* correlator_ch23_ready SECTION(".core12.data");
int* correlator_ch23_valid SECTION(".core12.data");

#define NOF_PIXELS_KERNEL (36) 
#define NOF_PIXELS (216) 
float correlator_SquareRoot_ret SECTION(".core12.data");
float correlator_total_sum SECTION(".core12.data");
int32_t correlator_correlation_counter SECTION(".core12.data") = 0;
int64_t correlator_correlation_input1 SECTION(".core12.data");
int64_t correlator_correlation_input2 SECTION(".core12.data");
float correlator_C_mag_ret SECTION(".core12.data");
int32_t correlator_iterationCounter SECTION(".core12.data") = 0;
int64_t correlator_complex_ba [(NOF_PIXELS_KERNEL / 4)] SECTION(".core12.data");

int64_t correlator_complex_bb [(NOF_PIXELS_KERNEL / 4)] SECTION(".core12.data");

int32_t correlator_correlator_State SECTION(".core12.data");
#define FSM_correlator_state1 (0) 
#define FSM_correlator_state2 (1) 
#define FSM_correlator_state3 (2) 
#define FSM_correlator_state4 (3) 
#define FSM_correlator_state5 (4) 
#define FSM_correlator_state6 (5) 
#define FSM_correlator_state7 (6) 
#define FSM_correlator_state8 (7) 
static void C_mag (int ns);

static inline void correlator_readInputs1 ( ) {
	int32_t i;
	int64_t ba [9];
	int64_t bb [9];
	for(int correlator_readInputs1_i = 0; correlator_readInputs1_i < 9; correlator_readInputs1_i++){
		ba[correlator_readInputs1_i] = correlator_ch12_buffer[correlator_readInputs1_i]; //read input 
	}
	*correlator_ch12_ready = 1; // channel ready to receive new data
	*correlator_ch12_valid = 0; // no valid input left on the channel
	
	for(int correlator_readInputs1_i = 0; correlator_readInputs1_i < 9; correlator_readInputs1_i++){
		bb[correlator_readInputs1_i] = correlator_ch13_buffer[correlator_readInputs1_i]; //read input 
	}
	*correlator_ch13_ready = 1; // channel ready to receive new data
	*correlator_ch13_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 9 )) {
		correlator_complex_ba[i] = ba[i];
		correlator_complex_bb[i] = bb[i];
		i = (i + 1);

	}

	correlator_iterationCounter = (correlator_iterationCounter + 1);

}
static inline void correlator_readInputs2 ( ) {
	int32_t i;
	int64_t ba [9];
	int64_t bb [9];
	for(int correlator_readInputs2_i = 0; correlator_readInputs2_i < 9; correlator_readInputs2_i++){
		ba[correlator_readInputs2_i] = correlator_ch14_buffer[correlator_readInputs2_i]; //read input 
	}
	*correlator_ch14_ready = 1; // channel ready to receive new data
	*correlator_ch14_valid = 0; // no valid input left on the channel
	
	for(int correlator_readInputs2_i = 0; correlator_readInputs2_i < 9; correlator_readInputs2_i++){
		bb[correlator_readInputs2_i] = correlator_ch15_buffer[correlator_readInputs2_i]; //read input 
	}
	*correlator_ch15_ready = 1; // channel ready to receive new data
	*correlator_ch15_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 9 )) {
		correlator_complex_ba[i] = ba[i];
		correlator_complex_bb[i] = bb[i];
		i = (i + 1);

	}

	correlator_iterationCounter = (correlator_iterationCounter + 1);

}
static inline void correlator_readInputs3 ( ) {
	int32_t i;
	int64_t ba [9];
	int64_t bb [9];
	for(int correlator_readInputs3_i = 0; correlator_readInputs3_i < 9; correlator_readInputs3_i++){
		ba[correlator_readInputs3_i] = correlator_ch16_buffer[correlator_readInputs3_i]; //read input 
	}
	*correlator_ch16_ready = 1; // channel ready to receive new data
	*correlator_ch16_valid = 0; // no valid input left on the channel
	
	for(int correlator_readInputs3_i = 0; correlator_readInputs3_i < 9; correlator_readInputs3_i++){
		bb[correlator_readInputs3_i] = correlator_ch17_buffer[correlator_readInputs3_i]; //read input 
	}
	*correlator_ch17_ready = 1; // channel ready to receive new data
	*correlator_ch17_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 9 )) {
		correlator_complex_ba[i] = ba[i];
		correlator_complex_bb[i] = bb[i];
		i = (i + 1);

	}

	correlator_iterationCounter = (correlator_iterationCounter + 1);

}
static inline void correlator_readInputs4 ( ) {
	int32_t i;
	int64_t ba [9];
	int64_t bb [9];
	for(int correlator_readInputs4_i = 0; correlator_readInputs4_i < 9; correlator_readInputs4_i++){
		ba[correlator_readInputs4_i] = correlator_ch18_buffer[correlator_readInputs4_i]; //read input 
	}
	*correlator_ch18_ready = 1; // channel ready to receive new data
	*correlator_ch18_valid = 0; // no valid input left on the channel
	
	for(int correlator_readInputs4_i = 0; correlator_readInputs4_i < 9; correlator_readInputs4_i++){
		bb[correlator_readInputs4_i] = correlator_ch19_buffer[correlator_readInputs4_i]; //read input 
	}
	*correlator_ch19_ready = 1; // channel ready to receive new data
	*correlator_ch19_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 9 )) {
		correlator_complex_ba[i] = ba[i];
		correlator_complex_bb[i] = bb[i];
		i = (i + 1);

	}

	correlator_iterationCounter = (correlator_iterationCounter + 1);

}
static inline void correlator_readInputs5 ( ) {
	int32_t i;
	int64_t ba [9];
	int64_t bb [9];
	for(int correlator_readInputs5_i = 0; correlator_readInputs5_i < 9; correlator_readInputs5_i++){
		ba[correlator_readInputs5_i] = correlator_ch20_buffer[correlator_readInputs5_i]; //read input 
	}
	*correlator_ch20_ready = 1; // channel ready to receive new data
	*correlator_ch20_valid = 0; // no valid input left on the channel
	
	for(int correlator_readInputs5_i = 0; correlator_readInputs5_i < 9; correlator_readInputs5_i++){
		bb[correlator_readInputs5_i] = correlator_ch21_buffer[correlator_readInputs5_i]; //read input 
	}
	*correlator_ch21_ready = 1; // channel ready to receive new data
	*correlator_ch21_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 9 )) {
		correlator_complex_ba[i] = ba[i];
		correlator_complex_bb[i] = bb[i];
		i = (i + 1);

	}

	correlator_iterationCounter = (correlator_iterationCounter + 1);

}
static inline void correlator_readInputs6 ( ) {
	int32_t i;
	int64_t ba [9];
	int64_t bb [9];
	for(int correlator_readInputs6_i = 0; correlator_readInputs6_i < 9; correlator_readInputs6_i++){
		ba[correlator_readInputs6_i] = correlator_ch22_buffer[correlator_readInputs6_i]; //read input 
	}
	*correlator_ch22_ready = 1; // channel ready to receive new data
	*correlator_ch22_valid = 0; // no valid input left on the channel
	
	for(int correlator_readInputs6_i = 0; correlator_readInputs6_i < 9; correlator_readInputs6_i++){
		bb[correlator_readInputs6_i] = correlator_ch23_buffer[correlator_readInputs6_i]; //read input 
	}
	*correlator_ch23_ready = 1; // channel ready to receive new data
	*correlator_ch23_valid = 0; // no valid input left on the channel
	
	i = 0;

	while (( i < 9 )) {
		correlator_complex_ba[i] = ba[i];
		correlator_complex_bb[i] = bb[i];
		i = (i + 1);

	}

	correlator_iterationCounter = (correlator_iterationCounter + 1);

}
static inline void correlator___acc__correlation ( ) {

	//Lets execute the custom instructions
	uint64_t acc_input0;

	//Copy two floating point numbers into 64 bit registers 
	memcpy(((char*)&acc_input0) + 4, &correlator_total_sum, 4);
	uint64_t outputReg;
	ROCC_INSTRUCTION_NO_BLOCK(XCUSTOM_ACC, outputReg, correlator_correlation_input1, correlator_correlation_input2, FUNCT_IN1 );
	ROCC_INSTRUCTION(XCUSTOM_ACC, outputReg, acc_input0, 0, FUNCT_FIRE );

	//Lets read the results
	correlator_total_sum = outputReg;
}
static inline void correlator_set_correlation_inputs ( ) {
	correlator_correlation_input1 = correlator_complex_ba[correlator_correlation_counter];

	correlator_correlation_input2 = correlator_complex_bb[correlator_correlation_counter];

	correlator_correlation_counter = (correlator_correlation_counter + 1);

}
static inline void correlator_correlation_done1 ( ) {
	correlator_correlation_counter = 0;

}
static inline void correlator_correlation_done2 ( ) {
	correlator_correlation_counter = 0;

}
static inline void correlator_correlation_done3 ( ) {
	correlator_correlation_counter = 0;

}
static inline void correlator_correlation_done4 ( ) {
	correlator_correlation_counter = 0;

}
static inline void correlator_correlation_done5 ( ) {
	correlator_correlation_counter = 0;

}
static inline void correlator_correlation_done6 ( ) {
	
	correlator_correlation_counter = 0;

}
static void C_mag (int ns) { 
	correlator_C_mag_ret = 1;


 }

int int_state_vars_correlator = 1;
void initStateVarscorrelator() {
correlator_total_sum = 0.0;
correlator_correlator_State = FSM_correlator_state1;

}

int correlator(void)
{
  
	//InputPorts
 	extern int ch12_ready; 
	extern int ch12_valid; 
	extern uint64_t ch12_buffer[ch12_size];
	extern int ch13_ready; 
	extern int ch13_valid; 
	extern uint64_t ch13_buffer[ch13_size];
	extern int ch14_ready; 
	extern int ch14_valid; 
	extern uint64_t ch14_buffer[ch14_size];
	extern int ch15_ready; 
	extern int ch15_valid; 
	extern uint64_t ch15_buffer[ch15_size];
	extern int ch16_ready; 
	extern int ch16_valid; 
	extern uint64_t ch16_buffer[ch16_size];
	extern int ch17_ready; 
	extern int ch17_valid; 
	extern uint64_t ch17_buffer[ch17_size];
	extern int ch18_ready; 
	extern int ch18_valid; 
	extern uint64_t ch18_buffer[ch18_size];
	extern int ch19_ready; 
	extern int ch19_valid; 
	extern uint64_t ch19_buffer[ch19_size];
	extern int ch20_ready; 
	extern int ch20_valid; 
	extern uint64_t ch20_buffer[ch20_size];
	extern int ch21_ready; 
	extern int ch21_valid; 
	extern uint64_t ch21_buffer[ch21_size];
	extern int ch22_ready; 
	extern int ch22_valid; 
	extern uint64_t ch22_buffer[ch22_size];
	extern int ch23_ready; 
	extern int ch23_valid; 
	extern uint64_t ch23_buffer[ch23_size];
	correlator_ch12_buffer =  ch12_buffer; 
	correlator_ch12_ready = &ch12_ready; 
	correlator_ch12_valid = &ch12_valid; 
	correlator_ch13_buffer =  ch13_buffer; 
	correlator_ch13_ready = &ch13_ready; 
	correlator_ch13_valid = &ch13_valid; 
	correlator_ch14_buffer =  ch14_buffer; 
	correlator_ch14_ready = &ch14_ready; 
	correlator_ch14_valid = &ch14_valid; 
	correlator_ch15_buffer =  ch15_buffer; 
	correlator_ch15_ready = &ch15_ready; 
	correlator_ch15_valid = &ch15_valid; 
	correlator_ch16_buffer =  ch16_buffer; 
	correlator_ch16_ready = &ch16_ready; 
	correlator_ch16_valid = &ch16_valid; 
	correlator_ch17_buffer =  ch17_buffer; 
	correlator_ch17_ready = &ch17_ready; 
	correlator_ch17_valid = &ch17_valid; 
	correlator_ch18_buffer =  ch18_buffer; 
	correlator_ch18_ready = &ch18_ready; 
	correlator_ch18_valid = &ch18_valid; 
	correlator_ch19_buffer =  ch19_buffer; 
	correlator_ch19_ready = &ch19_ready; 
	correlator_ch19_valid = &ch19_valid; 
	correlator_ch20_buffer =  ch20_buffer; 
	correlator_ch20_ready = &ch20_ready; 
	correlator_ch20_valid = &ch20_valid; 
	correlator_ch21_buffer =  ch21_buffer; 
	correlator_ch21_ready = &ch21_ready; 
	correlator_ch21_valid = &ch21_valid; 
	correlator_ch22_buffer =  ch22_buffer; 
	correlator_ch22_ready = &ch22_ready; 
	correlator_ch22_valid = &ch22_valid; 
	correlator_ch23_buffer =  ch23_buffer; 
	correlator_ch23_ready = &ch23_ready; 
	correlator_ch23_valid = &ch23_valid; 
    
	if(int_state_vars_correlator == 1){
		int_state_vars_correlator = 0;
		initStateVarscorrelator();
	}

correlatorSchedule:

 switch (correlator_correlator_State) {
   case FSM_correlator_state1:
     	if ((*correlator_ch12_valid == 1 && *correlator_ch13_valid == 1)){ 
		if (correlator_iterationCounter < NOF_PIXELS_KERNEL / 6){ 
			correlator_readInputs1();
			correlator_correlator_State = FSM_correlator_state2;

			goto correlatorSchedule;
		}

	}

	     break;

   case FSM_correlator_state2:
     	if (( correlator_correlation_counter < 9 )){ 
		correlator_set_correlation_inputs();
		correlator_correlator_State = FSM_correlator_state3;

		goto correlatorSchedule;
	}

	if ((correlator_iterationCounter == 1)){ 
		correlator_correlation_done1();
		correlator_correlator_State = FSM_correlator_state4;

		goto correlatorSchedule;
	}

	if ((correlator_iterationCounter == 2)){ 
		correlator_correlation_done2();
		correlator_correlator_State = FSM_correlator_state5;

		goto correlatorSchedule;
	}

	if ((correlator_iterationCounter == 3)){ 
		correlator_correlation_done3();
		correlator_correlator_State = FSM_correlator_state6;

		goto correlatorSchedule;
	}

	if ((correlator_iterationCounter == 4)){ 
		correlator_correlation_done4();
		correlator_correlator_State = FSM_correlator_state7;

		goto correlatorSchedule;
	}

	if ((correlator_iterationCounter == 5)){ 
		correlator_correlation_done5();
		correlator_correlator_State = FSM_correlator_state8;

		goto correlatorSchedule;
	}

	if ((correlator_iterationCounter == 6)){ 
		correlator_correlation_done6();
		correlator_correlator_State = FSM_correlator_state1;

		goto correlatorSchedule;
	}

	     break;

   case FSM_correlator_state3:
     			correlator___acc__correlation();
		correlator_correlator_State = FSM_correlator_state2;

		goto correlatorSchedule;

	     break;

   case FSM_correlator_state4:
     	if ((*correlator_ch14_valid == 1 && *correlator_ch15_valid == 1)){ 
					correlator_readInputs2();
			correlator_correlator_State = FSM_correlator_state2;

			goto correlatorSchedule;

	}

	     break;

   case FSM_correlator_state5:
     	if ((*correlator_ch16_valid == 1 && *correlator_ch17_valid == 1)){ 
					correlator_readInputs3();
			correlator_correlator_State = FSM_correlator_state2;

			goto correlatorSchedule;

	}

	     break;

   case FSM_correlator_state6:
     	if ((*correlator_ch18_valid == 1 && *correlator_ch19_valid == 1)){ 
					correlator_readInputs4();
			correlator_correlator_State = FSM_correlator_state2;

			goto correlatorSchedule;

	}

	     break;

   case FSM_correlator_state7:
     	if ((*correlator_ch20_valid == 1 && *correlator_ch21_valid == 1)){ 
					correlator_readInputs5();
			correlator_correlator_State = FSM_correlator_state2;

			goto correlatorSchedule;

	}

	     break;

   case FSM_correlator_state8:
     	if ((*correlator_ch22_valid == 1 && *correlator_ch23_valid == 1)){ 
					correlator_readInputs6();
			correlator_correlator_State = FSM_correlator_state2;

			goto correlatorSchedule;

	}

	     break;

}
goto correlatorSchedule;
}
