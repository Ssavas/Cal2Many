//code from Scale.cal, instance idctidctColscale
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(11, 4, 16, 0, 32),
	COMM_CHANNEL(11, 5, 16, 1, 32),
	COMM_CHANNEL(16, 2, 17, 0, 32),
	COMM_CHANNEL(16, 3, 17, 1, 32),
	COMM_CHANNEL(16, 4, 17, 2, 32),
	COMM_CHANNEL(16, 5, 17, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch43, ch44;
//OutputPorts
 comm_handle_t ch19, ch20, ch21, ch22;
static int W0 [4] =  {2048, 2676, 2841, 1609};

static int W1 [4] =  {2048, 1108, 565, 2408};

static int ww0;
static int ww1 = 2048;
static int index = 0;
static int idctidctColscale_IntCheckOutput = -1;

static void  idctidctColscale_untag_action_0 () { 
	int w0;
	int w1;
	int a;
	int b;
	  comm_read(ch43, &a, 4); // read 4 bytes 

	  comm_read(ch44, &b, 4); // read 4 bytes 

	  w0 = ww0;
	  w1 = ww1;
	  index = ((index + 1) & 3);
	  ww0 = W0[index];
	  ww1 = W1[index];
	  int tmpvar_0_Y0 = (a * w0);
	comm_write(ch19, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = (a * w1);
	comm_write(ch20, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = (b * w0);
	comm_write(ch21, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = (b * w1);
	comm_write(ch22, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int int_state_vars_idctidctColscale = 1;
void initStateVarsidctidctColscale() {
ww0 = W0[0];

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch43 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch43) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch44 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch44) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch19 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch19) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch20 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch20) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch21 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch21) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch22 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch22) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctidctColscale==1){
        int_state_vars_idctidctColscale = 0;
        initStateVarsidctidctColscale();
	}
if ((idctidctColscale_IntCheckOutput == -1)){ 
      
idctidctColscaleSchedule:

    if (((comm_level(ch43) >= 1) && (comm_level(ch44) >= 1))){ 
                        
idctidctColscale_Action_0:

          if (((comm_space(ch19) >= 1) && ((comm_space(ch20) >= 1) && ((comm_space(ch21) >= 1) && (comm_space(ch22) >= 1))))){ 
                          idctidctColscale_untag_action_0();
              goto idctidctColscaleSchedule;
}
          else {
                          idctidctColscale_IntCheckOutput = 0;
              return(0);
}


}

    idctidctColscale_IntCheckOutput = -1;
}
else {
      
 switch (idctidctColscale_IntCheckOutput) {
   case 0:
           idctidctColscale_IntCheckOutput = -1;
      goto idctidctColscale_Action_0;
}

}
goto idctidctColscaleSchedule;
}
