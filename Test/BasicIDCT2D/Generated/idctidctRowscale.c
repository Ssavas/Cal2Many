//code from Scale.cal, instance idctidctRowscale
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(1, 0, 2, 0, 32),
	COMM_CHANNEL(1, 1, 2, 1, 32),
	COMM_CHANNEL(2, 2, 3, 0, 32),
	COMM_CHANNEL(2, 3, 3, 1, 32),
	COMM_CHANNEL(2, 4, 3, 2, 32),
	COMM_CHANNEL(2, 5, 3, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch41, ch42;
//OutputPorts
 comm_handle_t ch5, ch6, ch7, ch8;
static int W0 [4] =  {2048, 2676, 2841, 1609};

static int W1 [4] =  {2048, 1108, 565, 2408};

static int ww0;
static int ww1 = 2048;
static int index = 0;
static int idctidctRowscale_IntCheckOutput = -1;

static void  idctidctRowscale_untag_action_0 () { 
	int w0;
	int w1;
	int a;
	int b;
	  comm_read(ch41, &a, 4); // read 4 bytes 

	  comm_read(ch42, &b, 4); // read 4 bytes 

	  w0 = ww0;
	  w1 = ww1;
	  index = ((index + 1) & 3);
	  ww0 = W0[index];
	  ww1 = W1[index];
	  int tmpvar_0_Y0 = (a * w0);
	comm_write(ch5, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = (a * w1);
	comm_write(ch6, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = (b * w0);
	comm_write(ch7, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = (b * w1);
	comm_write(ch8, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int int_state_vars_idctidctRowscale = 1;
void initStateVarsidctidctRowscale() {
ww0 = W0[0];

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch41 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch41) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch42 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch42) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch5 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch5) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch6 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch6) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch7 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch7) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch8 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch8) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctidctRowscale==1){
        int_state_vars_idctidctRowscale = 0;
        initStateVarsidctidctRowscale();
	}
if ((idctidctRowscale_IntCheckOutput == -1)){ 
      
idctidctRowscaleSchedule:

    if (((comm_level(ch41) >= 1) && (comm_level(ch42) >= 1))){ 
                        
idctidctRowscale_Action_0:

          if (((comm_space(ch5) >= 1) && ((comm_space(ch6) >= 1) && ((comm_space(ch7) >= 1) && (comm_space(ch8) >= 1))))){ 
                          idctidctRowscale_untag_action_0();
              goto idctidctRowscaleSchedule;
}
          else {
                          idctidctRowscale_IntCheckOutput = 0;
              return(0);
}


}

    idctidctRowscale_IntCheckOutput = -1;
}
else {
      
 switch (idctidctRowscale_IntCheckOutput) {
   case 0:
           idctidctRowscale_IntCheckOutput = -1;
      goto idctidctRowscale_Action_0;
}

}
goto idctidctRowscaleSchedule;
}
