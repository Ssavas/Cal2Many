//code from Combine.cal, instance idctidctColcombine
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(16, 0, 17, 0, 32),
	COMM_CHANNEL(16, 1, 17, 1, 32),
	COMM_CHANNEL(16, 2, 17, 2, 32),
	COMM_CHANNEL(16, 3, 17, 3, 32),
	COMM_CHANNEL(17, 4, 18, 0, 32),
	COMM_CHANNEL(17, 5, 18, 1, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch19, ch20, ch21, ch22;
//OutputPorts
 comm_handle_t ch23, ch24;
static int count = 0;
static int idctidctColcombine_IntCheckOutput = -1;

static void  idctidctColcombine_untag_action_0 () { 
	int s;
	int o;
	int y0;
	int y1;
	int y0out;
	int y1out;
	int a;
	int b;
	int c;
	int d;
	  comm_read(ch19, &a, 4); // read 4 bytes 

	  comm_read(ch20, &b, 4); // read 4 bytes 

	  comm_read(ch21, &c, 4); // read 4 bytes 

	  comm_read(ch22, &d, 4); // read 4 bytes 

	  s = (count == 0);
	  o = (row ? (s ? 128 : 0) : (s ? 65536 : 4));
	  y0 = ((a + d) + o);
	  y1 = ((b - c) + o);
	  y0out = (row ? y0 : (y0 >> 3));
	  y1out = (row ? y1 : (y1 >> 3));
	  count = ((count + 1) & 3);
	  comm_write(ch23, &y0out, 4); // send 4 bytes 

	  comm_write(ch24, &y1out, 4); // send 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch19 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch19) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch20 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch20) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch21 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch21) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch22 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch22) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch23 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch23) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch24 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch24) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
if ((idctidctColcombine_IntCheckOutput == -1)){ 
      
idctidctColcombineSchedule:

    if (((comm_level(ch19) >= 1) && ((comm_level(ch20) >= 1) && ((comm_level(ch21) >= 1) && (comm_level(ch22) >= 1))))){ 
                        
idctidctColcombine_Action_0:

          if (((comm_space(ch23) >= 1) && (comm_space(ch24) >= 1))){ 
                          idctidctColcombine_untag_action_0();
              goto idctidctColcombineSchedule;
}
          else {
                          idctidctColcombine_IntCheckOutput = 0;
              return(0);
}


}

    idctidctColcombine_IntCheckOutput = -1;
}
else {
      
 switch (idctidctColcombine_IntCheckOutput) {
   case 0:
           idctidctColcombine_IntCheckOutput = -1;
      goto idctidctColcombine_Action_0;
}

}
goto idctidctColcombineSchedule;
}
