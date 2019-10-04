//code from Retranspose.cal, instance idctretrans
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(25, 0, 26, 0, 32),
	COMM_CHANNEL(25, 1, 26, 1, 32),
	COMM_CHANNEL(25, 2, 26, 2, 32),
	COMM_CHANNEL(25, 3, 26, 3, 32),
	COMM_CHANNEL(26, 4, 27, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch0, ch1, ch2, ch3;
//OutputPorts
 comm_handle_t ch4;
static int mem[2][8][8];

static int rcount = 0;
static int ccount = 0;
static int select = 0;
static int idctretrans_IntCheckOutput = -1;

static void  idctretrans_untag_action_0 () { 
	int row;
	int quad;
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch0, &a, 4); // read 4 bytes 

	  comm_read(ch1, &b, 4); // read 4 bytes 

	  comm_read(ch2, &c, 4); // read 4 bytes 

	  comm_read(ch3, &d, 4); // read 4 bytes 

	  row = (rcount >> 3);
	  quad = ((rcount >> 2) & 1);
	  if ((quad == 0)){ 
	    	      	      mem[select][row][0] = a;
	      	      mem[select][row][7] = b;
	      	      mem[select][row][3] = c;
	      	      mem[select][row][4] = d;
}
	  else {
	    	      	      mem[select][row][1] = a;
	      	      mem[select][row][6] = b;
	      	      mem[select][row][2] = c;
	      	      mem[select][row][5] = d;
}

	  rcount = (rcount + 4);
  }
static void  idctretrans_untag_action_1 () { 
	int col;
	int row;
	int i;
	  col = ((64 - ccount) >> 3);
	  row = ((64 - ccount) & 7);
	  i = (select^1);
	  ccount = (ccount - 1);
	  int tmpvar_0_Y = mem[i][row][col];
	comm_write(ch4, &tmpvar_0_Y, 4); // send 4 bytes 

  }
static void  idctretrans_untag_action_2 () { 
	  select = (select^1);
	  ccount = 64;
	  rcount = 0;
  }
int int_state_vars_idctretrans = 1;
void initStateVarsidctretrans() {

for( int k = (1 - 1); k < 8; k ++)

for( int j = (1 - 1); j < 8; j ++)

for( int i = (1 - 1); i < 2; i ++)
mem[i][j][k] = 0;
}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch0 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch0) {
		HOST(26) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch1 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch1) {
		HOST(26) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch2 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch2) {
		HOST(26) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch3 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch3) {
		HOST(26) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch4 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch4) {
		HOST(26) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctretrans==1){
        int_state_vars_idctretrans = 0;
        initStateVarsidctretrans();
	}
if ((idctretrans_IntCheckOutput == -1)){ 
      
idctretransSchedule:

    if (((comm_level(ch0) >= 1) && ((comm_level(ch1) >= 1) && ((comm_level(ch2) >= 1) && (comm_level(ch3) >= 1))))){ 
              if ((rcount < 64)){ 
                      idctretrans_untag_action_0();
            goto idctretransSchedule;
}

}

    if ((ccount > 0)){ 
              
idctretrans_Action_0:

        if ((comm_space(ch4) >= 1)){ 
                      idctretrans_untag_action_1();
            goto idctretransSchedule;
}
        else {
                      idctretrans_IntCheckOutput = 0;
            return(0);
}

}

    if (((ccount == 0) && (rcount == 64))){ 
              idctretrans_untag_action_2();
        goto idctretransSchedule;
}

    idctretrans_IntCheckOutput = -1;
}
else {
      
 switch (idctretrans_IntCheckOutput) {
   case 0:
           idctretrans_IntCheckOutput = -1;
      goto idctretrans_Action_0;
}

}
goto idctretransSchedule;
}
