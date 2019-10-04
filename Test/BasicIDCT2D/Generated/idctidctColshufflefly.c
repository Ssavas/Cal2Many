//code from ShuffleFly.cal, instance idctidctColshufflefly
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(17, 4, 18, 0, 32),
	COMM_CHANNEL(17, 5, 18, 1, 32),
	COMM_CHANNEL(18, 2, 19, 0, 32),
	COMM_CHANNEL(18, 3, 19, 1, 32),
	COMM_CHANNEL(18, 4, 19, 2, 32),
	COMM_CHANNEL(18, 5, 19, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch23, ch24;
//OutputPorts
 comm_handle_t ch25, ch26, ch27, ch28;
static int D0;
static int D1;
static int idctidctColshufflefly_State;
#define FSM_idctidctColshufflefly_s0 (0) 
#define FSM_idctidctColshufflefly_s1 (1) 
static int idctidctColshufflefly_IntCheckOutput = -1;

static void  idctidctColshufflefly_a0 () { 
	int a;
	int b;
	  comm_read(ch23, &a, 4); // read 4 bytes 

	  comm_read(ch24, &b, 4); // read 4 bytes 

	  D0 = a;
	  D1 = b;
  }
static void  idctidctColshufflefly_a1 () { 
	int d2;
	int d3;
	  comm_read(ch23, &d2, 4); // read 4 bytes 

	  comm_read(ch24, &d3, 4); // read 4 bytes 

	  int tmpvar_0_Y0 = (D0 + d2);
	comm_write(ch25, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = (D0 - d2);
	comm_write(ch26, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = (D1 + d3);
	comm_write(ch27, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = (D1 - d3);
	comm_write(ch28, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int int_state_vars_idctidctColshufflefly = 1;
void initStateVarsidctidctColshufflefly() {
idctidctColshufflefly_State = FSM_idctidctColshufflefly_s0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch23 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch23) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch24 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch24) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch25 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch25) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch26 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch26) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch27 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch27) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch28 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch28) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctidctColshufflefly==1){
        int_state_vars_idctidctColshufflefly = 0;
        initStateVarsidctidctColshufflefly();
	}
if ((idctidctColshufflefly_IntCheckOutput == -1)){ 
      
idctidctColshuffleflySchedule:

    
 switch (idctidctColshufflefly_State) {
   case FSM_idctidctColshufflefly_s0:
           if (((comm_level(ch23) >= 1) && (comm_level(ch24) >= 1))){ 
                              idctidctColshufflefly_a0();
            idctidctColshufflefly_State = FSM_idctidctColshufflefly_s1;
            goto idctidctColshuffleflySchedule;

}

           break;

   case FSM_idctidctColshufflefly_s1:
           if (((comm_level(ch23) >= 1) && (comm_level(ch24) >= 1))){ 
                              
idctidctColshufflefly_Action_0:

            if (((comm_space(ch25) >= 1) && ((comm_space(ch26) >= 1) && ((comm_space(ch27) >= 1) && (comm_space(ch28) >= 1))))){ 
                              idctidctColshufflefly_a1();
                idctidctColshufflefly_State = FSM_idctidctColshufflefly_s0;
                goto idctidctColshuffleflySchedule;
}
            else {
                              idctidctColshufflefly_IntCheckOutput = 0;
                return(0);
}


}

           break;

}

    idctidctColshufflefly_IntCheckOutput = -1;
}
else {
      
 switch (idctidctColshufflefly_IntCheckOutput) {
   case 0:
           idctidctColshufflefly_IntCheckOutput = -1;
      goto idctidctColshufflefly_Action_0;
}

}
goto idctidctColshuffleflySchedule;
}
