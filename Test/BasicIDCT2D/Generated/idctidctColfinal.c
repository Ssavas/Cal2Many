//code from Final.cal, instance idctidctColfinal
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(19, 4, 24, 0, 32),
	COMM_CHANNEL(19, 5, 24, 1, 32),
	COMM_CHANNEL(19, 6, 24, 2, 32),
	COMM_CHANNEL(19, 7, 24, 3, 32),
	COMM_CHANNEL(24, 4, 25, 4, 32),
	COMM_CHANNEL(24, 5, 25, 5, 32),
	COMM_CHANNEL(24, 6, 25, 6, 32),
	COMM_CHANNEL(24, 7, 25, 7, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch29, ch30, ch31, ch32;
//OutputPorts
 comm_handle_t ch37, ch38, ch39, ch40;
static int idctidctColfinal_IntCheckOutput = -1;

static void  idctidctColfinal_untag_action_0 () { 
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch29, &a, 4); // read 4 bytes 

	  comm_read(ch30, &b, 4); // read 4 bytes 

	  comm_read(ch31, &c, 4); // read 4 bytes 

	  comm_read(ch32, &d, 4); // read 4 bytes 

	  int tmpvar_0_Y0 = ((a + c) >> 8);
	comm_write(ch37, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = ((a - c) >> 8);
	comm_write(ch38, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = ((b + d) >> 8);
	comm_write(ch39, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = ((b - d) >> 8);
	comm_write(ch40, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch29 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch29) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch30 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch30) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch31 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch31) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch32 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch32) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch37 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch37) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch38 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch38) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch39 = comm_get_whandle(channels, NUM_CHANNELS, 6);
	if(!ch39) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch40 = comm_get_whandle(channels, NUM_CHANNELS, 7);
	if(!ch40) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
if ((idctidctColfinal_IntCheckOutput == -1)){ 
      
idctidctColfinalSchedule:

    if (((comm_level(ch29) >= 1) && ((comm_level(ch30) >= 1) && ((comm_level(ch31) >= 1) && (comm_level(ch32) >= 1))))){ 
                        
idctidctColfinal_Action_0:

          if (((comm_space(ch37) >= 1) && ((comm_space(ch38) >= 1) && ((comm_space(ch39) >= 1) && (comm_space(ch40) >= 1))))){ 
                          idctidctColfinal_untag_action_0();
              goto idctidctColfinalSchedule;
}
          else {
                          idctidctColfinal_IntCheckOutput = 0;
              return(0);
}


}

    idctidctColfinal_IntCheckOutput = -1;
}
else {
      
 switch (idctidctColfinal_IntCheckOutput) {
   case 0:
           idctidctColfinal_IntCheckOutput = -1;
      goto idctidctColfinal_Action_0;
}

}
goto idctidctColfinalSchedule;
}
