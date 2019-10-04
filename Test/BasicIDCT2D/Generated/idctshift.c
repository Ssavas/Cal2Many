//code from Shift.cal, instance idctshift
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(24, 4, 25, 0, 32),
	COMM_CHANNEL(24, 5, 25, 1, 32),
	COMM_CHANNEL(24, 6, 25, 2, 32),
	COMM_CHANNEL(24, 7, 25, 3, 32),
	COMM_CHANNEL(25, 4, 26, 0, 32),
	COMM_CHANNEL(25, 5, 26, 1, 32),
	COMM_CHANNEL(25, 6, 26, 2, 32),
	COMM_CHANNEL(25, 7, 26, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch37, ch38, ch39, ch40;
//OutputPorts
 comm_handle_t ch0, ch1, ch2, ch3;
static int idctshift_IntCheckOutput = -1;

static void  idctshift_untag_action_0 () { 
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch37, &a, 4); // read 4 bytes 

	  comm_read(ch38, &b, 4); // read 4 bytes 

	  comm_read(ch39, &c, 4); // read 4 bytes 

	  comm_read(ch40, &d, 4); // read 4 bytes 

	  int tmpvar_0_Y0 = (a >> 6);
	comm_write(ch0, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = (b >> 6);
	comm_write(ch1, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = (c >> 6);
	comm_write(ch2, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = (d >> 6);
	comm_write(ch3, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch37 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch37) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch38 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch38) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch39 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch39) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch40 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch40) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch0 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch0) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch1 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch1) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch2 = comm_get_whandle(channels, NUM_CHANNELS, 6);
	if(!ch2) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch3 = comm_get_whandle(channels, NUM_CHANNELS, 7);
	if(!ch3) {
		HOST(25) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
if ((idctshift_IntCheckOutput == -1)){ 
      
idctshiftSchedule:

    if (((comm_level(ch37) >= 1) && ((comm_level(ch38) >= 1) && ((comm_level(ch39) >= 1) && (comm_level(ch40) >= 1))))){ 
                        
idctshift_Action_0:

          if (((comm_space(ch0) >= 1) && ((comm_space(ch1) >= 1) && ((comm_space(ch2) >= 1) && (comm_space(ch3) >= 1))))){ 
                          idctshift_untag_action_0();
              goto idctshiftSchedule;
}
          else {
                          idctshift_IntCheckOutput = 0;
              return(0);
}


}

    idctshift_IntCheckOutput = -1;
}
else {
      
 switch (idctshift_IntCheckOutput) {
   case 0:
           idctshift_IntCheckOutput = -1;
      goto idctshift_Action_0;
}

}
goto idctshiftSchedule;
}
