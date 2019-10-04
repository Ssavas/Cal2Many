//code from Transpose.cal, instance idcttrans
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(10, 4, 11, 0, 32),
	COMM_CHANNEL(10, 5, 11, 1, 32),
	COMM_CHANNEL(10, 6, 11, 2, 32),
	COMM_CHANNEL(10, 7, 11, 3, 32),
	COMM_CHANNEL(11, 4, 16, 4, 32),
	COMM_CHANNEL(11, 5, 16, 5, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch33, ch34, ch35, ch36;
//OutputPorts
 comm_handle_t ch43, ch44;
static int mem[2][8][8];

static int rcount = 0;
static int ccount = 0;
static int select = 0;
static int idcttrans_IntCheckOutput = -1;

static void  idcttrans_untag_action_0 () { 
	int row;
	int quad;
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch33, &a, 4); // read 4 bytes 

	  comm_read(ch34, &b, 4); // read 4 bytes 

	  comm_read(ch35, &c, 4); // read 4 bytes 

	  comm_read(ch36, &d, 4); // read 4 bytes 

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
static void  idcttrans_untag_action_1 () { 
	int a;
	int b;
	int col;
	int pair;
	int i;
	  col = ((64 - ccount) >> 3);
	  pair = (((64 - ccount) >> 1) & 3);
	  i = (select^1);
	  a = ((pair == 0) ? 0 : ((pair == 1) ? 2 : ((pair == 2) ? 1 : 5)));
	  b = ((pair == 0) ? 4 : ((pair == 1) ? 6 : ((pair == 2) ? 7 : 3)));
	  ccount = (ccount - 2);
	  int tmpvar_0_Y0 = mem[i][a][col];
	comm_write(ch43, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = mem[i][b][col];
	comm_write(ch44, &tmpvar_1_Y1, 4); // send 4 bytes 

  }
static void  idcttrans_untag_action_2 () { 
	  select = (select^1);
	  ccount = 64;
	  rcount = 0;
  }
int int_state_vars_idcttrans = 1;
void initStateVarsidcttrans() {

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
 	ch33 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch33) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch34 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch34) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch35 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch35) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch36 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch36) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch43 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch43) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch44 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch44) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idcttrans==1){
        int_state_vars_idcttrans = 0;
        initStateVarsidcttrans();
	}
if ((idcttrans_IntCheckOutput == -1)){ 
      
idcttransSchedule:

    if (((comm_level(ch33) >= 1) && ((comm_level(ch34) >= 1) && ((comm_level(ch35) >= 1) && (comm_level(ch36) >= 1))))){ 
              if ((rcount < 64)){ 
                      idcttrans_untag_action_0();
            goto idcttransSchedule;
}

}

    if ((ccount > 0)){ 
              
idcttrans_Action_0:

        if (((comm_space(ch43) >= 1) && (comm_space(ch44) >= 1))){ 
                      idcttrans_untag_action_1();
            goto idcttransSchedule;
}
        else {
                      idcttrans_IntCheckOutput = 0;
            return(0);
}

}

    if (((ccount == 0) && (rcount == 64))){ 
              idcttrans_untag_action_2();
        goto idcttransSchedule;
}

    idcttrans_IntCheckOutput = -1;
}
else {
      
 switch (idcttrans_IntCheckOutput) {
   case 0:
           idcttrans_IntCheckOutput = -1;
      goto idcttrans_Action_0;
}

}
goto idcttransSchedule;
}
