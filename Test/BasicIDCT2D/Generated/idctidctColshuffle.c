//code from Shuffle.cal, instance idctidctColshuffle
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(18, 2, 19, 0, 32),
	COMM_CHANNEL(18, 3, 19, 1, 32),
	COMM_CHANNEL(18, 4, 19, 2, 32),
	COMM_CHANNEL(18, 5, 19, 3, 32),
	COMM_CHANNEL(19, 4, 24, 0, 32),
	COMM_CHANNEL(19, 5, 24, 1, 32),
	COMM_CHANNEL(19, 6, 24, 2, 32),
	COMM_CHANNEL(19, 7, 24, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch25, ch26, ch27, ch28;
//OutputPorts
 comm_handle_t ch29, ch30, ch31, ch32;
static int x4;
static int x5;
static int x6h;
static int x7h;
static int x6l;
static int x7l;
static int idctidctColshuffle_State;
#define FSM_idctidctColshuffle_s0 (0) 
#define FSM_idctidctColshuffle_s1 (1) 
#define FSM_idctidctColshuffle_s2 (2) 
static int idctidctColshuffle_IntCheckOutput = -1;

static void  idctidctColshuffle_a0 () { 
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch25, &a, 4); // read 4 bytes 

	  comm_read(ch26, &b, 4); // read 4 bytes 

	  comm_read(ch27, &c, 4); // read 4 bytes 

	  comm_read(ch28, &d, 4); // read 4 bytes 

	  x4 = c;
	  x5 = d;
	  comm_write(ch29, &a, 4); // send 4 bytes 

	  comm_write(ch30, &b, 4); // send 4 bytes 

  }
static void  idctidctColshuffle_a1 () { 
	int ah;
	int bh;
	int al;
	int bl;
	int x2;
	int a;
	int x3;
	int b;
	  comm_read(ch25, &x2, 4); // read 4 bytes 

	  comm_read(ch26, &a, 4); // read 4 bytes 

	  comm_read(ch27, &x3, 4); // read 4 bytes 

	  comm_read(ch28, &b, 4); // read 4 bytes 

	  ah = (a >> 8);
	  bh = (b >> 8);
	  al = (a & 255);
	  bl = (b & 255);
	  x6h = (181 * (ah + bh));
	  x7h = (181 * (ah - bh));
	  x6l = ((181 * (al + bl)) + 128);
	  x7l = ((181 * (al - bl)) + 128);
	  comm_write(ch31, &x2, 4); // send 4 bytes 

	  comm_write(ch32, &x3, 4); // send 4 bytes 

  }
static void  idctidctColshuffle_a2 () { 
	  comm_write(ch29, &x4, 4); // send 4 bytes 

	  comm_write(ch30, &x5, 4); // send 4 bytes 

	  int tmpvar_6_Y2 = (x6h + (x6l >> 8));
	comm_write(ch31, &tmpvar_6_Y2, 4); // send 4 bytes 

	  int tmpvar_7_Y3 = (x7h + (x7l >> 8));
	comm_write(ch32, &tmpvar_7_Y3, 4); // send 4 bytes 

  }
int int_state_vars_idctidctColshuffle = 1;
void initStateVarsidctidctColshuffle() {
idctidctColshuffle_State = FSM_idctidctColshuffle_s0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch25 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch25) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch26 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch26) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch27 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch27) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch28 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch28) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch29 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch29) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch30 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch30) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch31 = comm_get_whandle(channels, NUM_CHANNELS, 6);
	if(!ch31) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch32 = comm_get_whandle(channels, NUM_CHANNELS, 7);
	if(!ch32) {
		HOST(19) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctidctColshuffle==1){
        int_state_vars_idctidctColshuffle = 0;
        initStateVarsidctidctColshuffle();
	}
if ((idctidctColshuffle_IntCheckOutput == -1)){ 
      
idctidctColshuffleSchedule:

    
 switch (idctidctColshuffle_State) {
   case FSM_idctidctColshuffle_s0:
           if (((comm_level(ch25) >= 1) && ((comm_level(ch26) >= 1) && ((comm_level(ch27) >= 1) && (comm_level(ch28) >= 1))))){ 
                              
idctidctColshuffle_Action_0:

            if (((comm_space(ch29) >= 1) && (comm_space(ch30) >= 1))){ 
                              idctidctColshuffle_a0();
                idctidctColshuffle_State = FSM_idctidctColshuffle_s1;
                goto idctidctColshuffleSchedule;
}
            else {
                              idctidctColshuffle_IntCheckOutput = 0;
                return(0);
}


}

           break;

   case FSM_idctidctColshuffle_s1:
           if (((comm_level(ch25) >= 1) && ((comm_level(ch26) >= 1) && ((comm_level(ch27) >= 1) && (comm_level(ch28) >= 1))))){ 
                              
idctidctColshuffle_Action_1:

            if (((comm_space(ch31) >= 1) && (comm_space(ch32) >= 1))){ 
                              idctidctColshuffle_a1();
                idctidctColshuffle_State = FSM_idctidctColshuffle_s2;
                goto idctidctColshuffleSchedule;
}
            else {
                              idctidctColshuffle_IntCheckOutput = 1;
                return(0);
}


}

           break;

   case FSM_idctidctColshuffle_s2:
                   
idctidctColshuffle_Action_2:

        if (((comm_space(ch29) >= 1) && ((comm_space(ch30) >= 1) && ((comm_space(ch31) >= 1) && (comm_space(ch32) >= 1))))){ 
                      idctidctColshuffle_a2();
            idctidctColshuffle_State = FSM_idctidctColshuffle_s0;
            goto idctidctColshuffleSchedule;
}
        else {
                      idctidctColshuffle_IntCheckOutput = 2;
            return(0);
}


           break;

}

    idctidctColshuffle_IntCheckOutput = -1;
}
else {
      
 switch (idctidctColshuffle_IntCheckOutput) {
   case 0:
           idctidctColshuffle_IntCheckOutput = -1;
      goto idctidctColshuffle_Action_0;
   case 1:
           idctidctColshuffle_IntCheckOutput = -1;
      goto idctidctColshuffle_Action_1;
   case 2:
           idctidctColshuffle_IntCheckOutput = -1;
      goto idctidctColshuffle_Action_2;
}

}
goto idctidctColshuffleSchedule;
}
