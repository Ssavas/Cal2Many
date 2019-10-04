//code from ShuffleFly.cal, instance idctidctRowshufflefly
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(3, 4, 8, 0, 32),
	COMM_CHANNEL(3, 5, 8, 1, 32),
	COMM_CHANNEL(8, 2, 9, 0, 32),
	COMM_CHANNEL(8, 3, 9, 1, 32),
	COMM_CHANNEL(8, 4, 9, 2, 32),
	COMM_CHANNEL(8, 5, 9, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch9, ch10;
//OutputPorts
 comm_handle_t ch11, ch12, ch13, ch14;
static int D0;
static int D1;
static int idctidctRowshufflefly_State;
#define FSM_idctidctRowshufflefly_s0 (0) 
#define FSM_idctidctRowshufflefly_s1 (1) 
static int idctidctRowshufflefly_IntCheckOutput = -1;

static void  idctidctRowshufflefly_a0 () { 
	int a;
	int b;
	  comm_read(ch9, &a, 4); // read 4 bytes 

	  comm_read(ch10, &b, 4); // read 4 bytes 

	  D0 = a;
	  D1 = b;
  }
static void  idctidctRowshufflefly_a1 () { 
	int d2;
	int d3;
	  comm_read(ch9, &d2, 4); // read 4 bytes 

	  comm_read(ch10, &d3, 4); // read 4 bytes 

	  int tmpvar_0_Y0 = (D0 + d2);
	comm_write(ch11, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = (D0 - d2);
	comm_write(ch12, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = (D1 + d3);
	comm_write(ch13, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = (D1 - d3);
	comm_write(ch14, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int int_state_vars_idctidctRowshufflefly = 1;
void initStateVarsidctidctRowshufflefly() {
idctidctRowshufflefly_State = FSM_idctidctRowshufflefly_s0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch9 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch9) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch10 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch10) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch11 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch11) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch12 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch12) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch13 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch13) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch14 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch14) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctidctRowshufflefly==1){
        int_state_vars_idctidctRowshufflefly = 0;
        initStateVarsidctidctRowshufflefly();
	}
if ((idctidctRowshufflefly_IntCheckOutput == -1)){ 
      
idctidctRowshuffleflySchedule:

    
 switch (idctidctRowshufflefly_State) {
   case FSM_idctidctRowshufflefly_s0:
           if (((comm_level(ch9) >= 1) && (comm_level(ch10) >= 1))){ 
                              idctidctRowshufflefly_a0();
            idctidctRowshufflefly_State = FSM_idctidctRowshufflefly_s1;
            goto idctidctRowshuffleflySchedule;

}

           break;

   case FSM_idctidctRowshufflefly_s1:
           if (((comm_level(ch9) >= 1) && (comm_level(ch10) >= 1))){ 
                              
idctidctRowshufflefly_Action_0:

            if (((comm_space(ch11) >= 1) && ((comm_space(ch12) >= 1) && ((comm_space(ch13) >= 1) && (comm_space(ch14) >= 1))))){ 
                              idctidctRowshufflefly_a1();
                idctidctRowshufflefly_State = FSM_idctidctRowshufflefly_s0;
                goto idctidctRowshuffleflySchedule;
}
            else {
                              idctidctRowshufflefly_IntCheckOutput = 0;
                return(0);
}


}

           break;

}

    idctidctRowshufflefly_IntCheckOutput = -1;
}
else {
      
 switch (idctidctRowshufflefly_IntCheckOutput) {
   case 0:
           idctidctRowshufflefly_IntCheckOutput = -1;
      goto idctidctRowshufflefly_Action_0;
}

}
goto idctidctRowshuffleflySchedule;
}
