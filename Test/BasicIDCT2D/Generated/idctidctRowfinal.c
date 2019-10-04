//code from Final.cal, instance idctidctRowfinal
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(9, 4, 10, 0, 32),
	COMM_CHANNEL(9, 5, 10, 1, 32),
	COMM_CHANNEL(9, 6, 10, 2, 32),
	COMM_CHANNEL(9, 7, 10, 3, 32),
	COMM_CHANNEL(10, 4, 11, 0, 32),
	COMM_CHANNEL(10, 5, 11, 1, 32),
	COMM_CHANNEL(10, 6, 11, 2, 32),
	COMM_CHANNEL(10, 7, 11, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch15, ch16, ch17, ch18;
//OutputPorts
 comm_handle_t ch33, ch34, ch35, ch36;
static int idctidctRowfinal_IntCheckOutput = -1;

static void  idctidctRowfinal_untag_action_0 () { 
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch15, &a, 4); // read 4 bytes 

	  comm_read(ch16, &b, 4); // read 4 bytes 

	  comm_read(ch17, &c, 4); // read 4 bytes 

	  comm_read(ch18, &d, 4); // read 4 bytes 

	  int tmpvar_0_Y0 = ((a + c) >> 8);
	comm_write(ch33, &tmpvar_0_Y0, 4); // send 4 bytes 

	  int tmpvar_1_Y1 = ((a - c) >> 8);
	comm_write(ch34, &tmpvar_1_Y1, 4); // send 4 bytes 

	  int tmpvar_2_Y2 = ((b + d) >> 8);
	comm_write(ch35, &tmpvar_2_Y2, 4); // send 4 bytes 

	  int tmpvar_3_Y3 = ((b - d) >> 8);
	comm_write(ch36, &tmpvar_3_Y3, 4); // send 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch15 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch15) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch16 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch16) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch17 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch17) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch18 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch18) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch33 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch33) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch34 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch34) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch35 = comm_get_whandle(channels, NUM_CHANNELS, 6);
	if(!ch35) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch36 = comm_get_whandle(channels, NUM_CHANNELS, 7);
	if(!ch36) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
if ((idctidctRowfinal_IntCheckOutput == -1)){ 
      
idctidctRowfinalSchedule:

    if (((comm_level(ch15) >= 1) && ((comm_level(ch16) >= 1) && ((comm_level(ch17) >= 1) && (comm_level(ch18) >= 1))))){ 
                        
idctidctRowfinal_Action_0:

          if (((comm_space(ch33) >= 1) && ((comm_space(ch34) >= 1) && ((comm_space(ch35) >= 1) && (comm_space(ch36) >= 1))))){ 
                          idctidctRowfinal_untag_action_0();
              goto idctidctRowfinalSchedule;
}
          else {
                          idctidctRowfinal_IntCheckOutput = 0;
              return(0);
}


}

    idctidctRowfinal_IntCheckOutput = -1;
}
else {
      
 switch (idctidctRowfinal_IntCheckOutput) {
   case 0:
           idctidctRowfinal_IntCheckOutput = -1;
      goto idctidctRowfinal_Action_0;
}

}
goto idctidctRowfinalSchedule;
}
