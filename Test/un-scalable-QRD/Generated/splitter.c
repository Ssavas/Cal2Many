//code from splitter.cal, instance splitter
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(19, 0, 1, 1, 32),
	COMM_CHANNEL(19, 1, 9, 2, 32),
	COMM_CHANNEL(19, 2, 10, 3, 32),
	COMM_CHANNEL(19, 3, 11, 4, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t   input;
//OutputPorts
 comm_handle_t ch10, ch11, ch12, ch13;
static float matrix [16] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

static int counter = 0;
static int splitter_State;
#define FSM_splitter_start (0) 
#define FSM_splitter_data2 (1) 
#define FSM_splitter_data3 (2) 
#define FSM_splitter_data4 (3) 
static int splitter_IntCheckOutput = -1;

static void  splitter_a1 () { 
		counter = (counter + 1);
		int tmpvar_0_out1 = matrix[counter];
	comm_write(ch10, &tmpvar_0_out1, 4); // send 4 bytes 

  }
static void  splitter_a2 () { 
		counter = (counter + 1);
		int tmpvar_1_out2 = matrix[counter];
	comm_write(ch11, &tmpvar_1_out2, 4); // send 4 bytes 

  }
static void  splitter_a3 () { 
		counter = (counter + 1);
		int tmpvar_2_out3 = matrix[counter];
	comm_write(ch12, &tmpvar_2_out3, 4); // send 4 bytes 

  }
static void  splitter_a4 () { 
		counter = (counter + 1);
		int tmpvar_3_out4 = matrix[counter];
	comm_write(ch13, &tmpvar_3_out4, 4); // send 4 bytes 

  }
int int_state_vars_splitter = 1;
void initStateVarssplitter() {
splitter_State = FSM_splitter_start;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 
	//OutputPorts
	ch10 = comm_get_whandle(channels, NUM_CHANNELS, 0);
	if(!ch10) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch11 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch11) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch12 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch12) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch13 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch13) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_splitter==1){
        int_state_vars_splitter = 0;
        initStateVarssplitter();
	}
if ((splitter_IntCheckOutput == -1)){ 
		
splitterSchedule:

		
 switch (splitter_State) {
   case FSM_splitter_start:
     							
splitter_Action_0:

				if ((comm_space(ch10) >= 1)){ 
						splitter_a1();
						splitter_State = FSM_splitter_data2;
						goto splitterSchedule;
				}
				else {
						splitter_IntCheckOutput = 0;
						return(0);
				}


			     break;

   case FSM_splitter_data2:
     							
splitter_Action_1:

				if ((comm_space(ch11) >= 1)){ 
						splitter_a2();
						splitter_State = FSM_splitter_data3;
						goto splitterSchedule;
				}
				else {
						splitter_IntCheckOutput = 1;
						return(0);
				}


			     break;

   case FSM_splitter_data3:
     							
splitter_Action_2:

				if ((comm_space(ch12) >= 1)){ 
						splitter_a3();
						splitter_State = FSM_splitter_data4;
						goto splitterSchedule;
				}
				else {
						splitter_IntCheckOutput = 2;
						return(0);
				}


			     break;

   case FSM_splitter_data4:
     							
splitter_Action_3:

				if ((comm_space(ch13) >= 1)){ 
						splitter_a4();
						splitter_State = FSM_splitter_start;
						goto splitterSchedule;
				}
				else {
						splitter_IntCheckOutput = 3;
						return(0);
				}


			     break;

}

		splitter_IntCheckOutput = -1;
}
else {
		
 switch (splitter_IntCheckOutput) {
   case 0:
     			splitter_IntCheckOutput = -1;
			goto splitter_Action_0;
   case 1:
     			splitter_IntCheckOutput = -1;
			goto splitter_Action_1;
   case 2:
     			splitter_IntCheckOutput = -1;
			goto splitter_Action_2;
   case 3:
     			splitter_IntCheckOutput = -1;
			goto splitter_Action_3;
}

}
goto splitterSchedule;
}
