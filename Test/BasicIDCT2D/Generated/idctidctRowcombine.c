//code from Combine.cal, instance idctidctRowcombine
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(2, 0, 3, 0, 32),
	COMM_CHANNEL(2, 1, 3, 1, 32),
	COMM_CHANNEL(2, 2, 3, 2, 32),
	COMM_CHANNEL(2, 3, 3, 3, 32),
	COMM_CHANNEL(3, 4, 8, 0, 32),
	COMM_CHANNEL(3, 5, 8, 1, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch5, ch6, ch7, ch8;
//OutputPorts
 comm_handle_t ch9, ch10;
static int count = 0;
static int idctidctRowcombine_IntCheckOutput = -1;

static void  idctidctRowcombine_untag_action_0 () { 
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
	  comm_read(ch5, &a, 4); // read 4 bytes 

	  comm_read(ch6, &b, 4); // read 4 bytes 

	  comm_read(ch7, &c, 4); // read 4 bytes 

	  comm_read(ch8, &d, 4); // read 4 bytes 

	  s = (count == 0);
	  o = (row ? (s ? 128 : 0) : (s ? 65536 : 4));
	  y0 = ((a + d) + o);
	  y1 = ((b - c) + o);
	  y0out = (row ? y0 : (y0 >> 3));
	  y1out = (row ? y1 : (y1 >> 3));
	  count = ((count + 1) & 3);
	  comm_write(ch9, &y0out, 4); // send 4 bytes 

	  comm_write(ch10, &y1out, 4); // send 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch5 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch5) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch6 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch6) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch7 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch7) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch8 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch8) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch9 = comm_get_whandle(channels, NUM_CHANNELS, 4);
	if(!ch9) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch10 = comm_get_whandle(channels, NUM_CHANNELS, 5);
	if(!ch10) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
if ((idctidctRowcombine_IntCheckOutput == -1)){ 
      
idctidctRowcombineSchedule:

    if (((comm_level(ch5) >= 1) && ((comm_level(ch6) >= 1) && ((comm_level(ch7) >= 1) && (comm_level(ch8) >= 1))))){ 
                        
idctidctRowcombine_Action_0:

          if (((comm_space(ch9) >= 1) && (comm_space(ch10) >= 1))){ 
                          idctidctRowcombine_untag_action_0();
              goto idctidctRowcombineSchedule;
}
          else {
                          idctidctRowcombine_IntCheckOutput = 0;
              return(0);
}


}

    idctidctRowcombine_IntCheckOutput = -1;
}
else {
      
 switch (idctidctRowcombine_IntCheckOutput) {
   case 0:
           idctidctRowcombine_IntCheckOutput = -1;
      goto idctidctRowcombine_Action_0;
}

}
goto idctidctRowcombineSchedule;
}
