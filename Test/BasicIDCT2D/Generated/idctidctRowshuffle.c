//code from Shuffle.cal, instance idctidctRowshuffle
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(8, 2, 9, 0, 32),
	COMM_CHANNEL(8, 3, 9, 1, 32),
	COMM_CHANNEL(8, 4, 9, 2, 32),
	COMM_CHANNEL(8, 5, 9, 3, 32),
	COMM_CHANNEL(9, 4, 10, 0, 32),
	COMM_CHANNEL(9, 5, 10, 1, 32),
	COMM_CHANNEL(9, 6, 10, 2, 32),
	COMM_CHANNEL(9, 7, 10, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch11, ch12, ch13, ch14;
//OutputPorts
 comm_handle_t ch15, ch16, ch17, ch18;
static int x4;
static int x5;
static int x6h;
static int x7h;
static int x6l;
static int x7l;
static int idctidctRowshuffle_State;
#define FSM_idctidctRowshuffle_s0 (0) 
#define FSM_idctidctRowshuffle_s1 (1) 
#define FSM_idctidctRowshuffle_s2 (2) 
static int idctidctRowshuffle_IntCheckOutput = -1;

static void  idctidctRowshuffle_a0 () { 
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch11, &a, 4); // read 4 bytes 

	  comm_read(ch12, &b, 4); // read 4 bytes 

	  comm_read(ch13, &c, 4); // read 4 bytes 

	  comm_read(ch14, &d, 4); // read 4 bytes 

	  x4 = c;
	  x5 = d;
	  comm_write(ch15, &a, 4); // send 4 bytes 

	  comm_write(ch16, &b, 4); // send 4 bytes 

  }
static void  idctidctRowshuffle_a1 () { 
	int ah;
	int bh;
	int al;
	int bl;
	int x2;
	int a;
	int x3;
	int b;
	  comm_read(ch11, &x2, 4); // read 4 bytes 

	  comm_read(ch12, &a, 4); // read 4 bytes 

	  comm_read(ch13, &x3, 4); // read 4 bytes 

	  comm_read(ch14, &b, 4); // read 4 bytes 

	  ah = (a >> 8);
	  bh = (b >> 8);
	  al = (a & 255);
	  bl = (b & 255);
	  x6h = (181 * (ah + bh));
	  x7h = (181 * (ah - bh));
	  x6l = ((181 * (al + bl)) + 128);
	  x7l = ((181 * (al - bl)) + 128);
	  comm_write(ch17, &x2, 4); // send 4 bytes 

	  comm_write(ch18, &x3, 4); // send 4 bytes 

  }
static void  idctidctRowshuffle_a2 () { 
	  comm_write(ch15, &x4, 4); // send 4 bytes 

	  comm_write(ch16, &x5, 4); // send 4 bytes 

	  int tmpvar_6_Y2 = (x6h + (x6l >> 8));
	comm_write(ch17, &tmpvar_6_Y2, 4); // send 4 bytes 

	  int tmpvar_7_Y3 = (x7h + (x7l >> 8));
	comm_write(ch18, &tmpvar_7_Y3, 4); // send 4 bytes 

  }
int int_state_vars_idctidctRowshuffle = 1;
void initStateVarsidctidctRowshuffle() {
idctidctRowshuffle_State = FSM_idctidctRowshuffle_s0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch11 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch11) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch12 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch12) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch13 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch13) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch14 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch14) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch15 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch15) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch16 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch16) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch17 = comm_get_whandle(channels, NUM_CHANNELS, 6);
	if(!ch17) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch18 = comm_get_whandle(channels, NUM_CHANNELS, 7);
	if(!ch18) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctidctRowshuffle==1){
        int_state_vars_idctidctRowshuffle = 0;
        initStateVarsidctidctRowshuffle();
	}
if ((idctidctRowshuffle_IntCheckOutput == -1)){ 
      
idctidctRowshuffleSchedule:

    
 switch (idctidctRowshuffle_State) {
   case FSM_idctidctRowshuffle_s0:
           if (((comm_level(ch11) >= 1) && ((comm_level(ch12) >= 1) && ((comm_level(ch13) >= 1) && (comm_level(ch14) >= 1))))){ 
                              
idctidctRowshuffle_Action_0:

            if (((comm_space(ch15) >= 1) && (comm_space(ch16) >= 1))){ 
                              idctidctRowshuffle_a0();
                idctidctRowshuffle_State = FSM_idctidctRowshuffle_s1;
                goto idctidctRowshuffleSchedule;
}
            else {
                              idctidctRowshuffle_IntCheckOutput = 0;
                return(0);
}


}

           break;

   case FSM_idctidctRowshuffle_s1:
           if (((comm_level(ch11) >= 1) && ((comm_level(ch12) >= 1) && ((comm_level(ch13) >= 1) && (comm_level(ch14) >= 1))))){ 
                              
idctidctRowshuffle_Action_1:

            if (((comm_space(ch17) >= 1) && (comm_space(ch18) >= 1))){ 
                              idctidctRowshuffle_a1();
                idctidctRowshuffle_State = FSM_idctidctRowshuffle_s2;
                goto idctidctRowshuffleSchedule;
}
            else {
                              idctidctRowshuffle_IntCheckOutput = 1;
                return(0);
}


}

           break;

   case FSM_idctidctRowshuffle_s2:
                   
idctidctRowshuffle_Action_2:

        if (((comm_space(ch15) >= 1) && ((comm_space(ch16) >= 1) && ((comm_space(ch17) >= 1) && (comm_space(ch18) >= 1))))){ 
                      idctidctRowshuffle_a2();
            idctidctRowshuffle_State = FSM_idctidctRowshuffle_s0;
            goto idctidctRowshuffleSchedule;
}
        else {
                      idctidctRowshuffle_IntCheckOutput = 2;
            return(0);
}


           break;

}

    idctidctRowshuffle_IntCheckOutput = -1;
}
else {
      
 switch (idctidctRowshuffle_IntCheckOutput) {
   case 0:
           idctidctRowshuffle_IntCheckOutput = -1;
      goto idctidctRowshuffle_Action_0;
   case 1:
           idctidctRowshuffle_IntCheckOutput = -1;
      goto idctidctRowshuffle_Action_1;
   case 2:
           idctidctRowshuffle_IntCheckOutput = -1;
      goto idctidctRowshuffle_Action_2;
}

}
goto idctidctRowshuffleSchedule;
}
