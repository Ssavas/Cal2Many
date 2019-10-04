//code from inner.cal, instance inner02
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(9, 1, 10, 0, 32),
	COMM_CHANNEL(19, 2, 10, 1, 32),
	COMM_CHANNEL(10, 2, 11, 0, 32),
	COMM_CHANNEL(10, 3, 16, 1, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch4, ch12;
//OutputPorts
 comm_handle_t ch5, ch15;
static float r;
static int inner02_IntCheckOutput = -1;

static void  inner02_untag_action_0 () { 
	float x_out;
	int c;
	int s;
	int x_in;
		comm_read(ch4, &c, 4); // read 4 bytes 
comm_read(ch4, &s, 4); // read 4 bytes 

		comm_read(ch12, &x_in, 4); // read 4 bytes 

		x_out = c * x_in - s * r;
		r = s * x_in + c * r;
		comm_write(ch5, &c, 4); // send 4 bytes 
comm_write(ch5, &s, 4); // send 4 bytes 

		comm_write(ch15, &x_out, 4); // send 4 bytes 

  }
int int_state_vars_inner02 = 1;
void initStateVarsinner02() {
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch4 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch4) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch12 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch12) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch5 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch5) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch15 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch15) {
		HOST(10) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_inner02==1){
        int_state_vars_inner02 = 0;
        initStateVarsinner02();
	}
if ((inner02_IntCheckOutput == -1)){ 
		
inner02Schedule:

		if (((comm_level(ch4) >= 1) && (comm_level(ch12) >= 1))){ 
									
inner02_Action_0:

					if (((comm_space(ch5) >= 1) && (comm_space(ch15) >= 1))){ 
							inner02_untag_action_0();
							goto inner02Schedule;
					}
					else {
							inner02_IntCheckOutput = 0;
							return(0);
					}


		}

		inner02_IntCheckOutput = -1;
}
else {
		
 switch (inner02_IntCheckOutput) {
   case 0:
     			inner02_IntCheckOutput = -1;
			goto inner02_Action_0;
}

}
goto inner02Schedule;
}
