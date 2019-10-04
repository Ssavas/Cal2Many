//code from inner.cal, instance inner13
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(16, 1, 17, 0, 32),
	COMM_CHANNEL(11, 2, 17, 1, 32),
	COMM_CHANNEL(17, 2, 24, 2, 32),
	COMM_CHANNEL(17, 3, 18, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch7, ch16;
//OutputPorts
 comm_handle_t ch8, ch18;
static float r;
static int inner13_IntCheckOutput = -1;

static void  inner13_untag_action_0 () { 
	float x_out;
	int c;
	int s;
	int x_in;
		comm_read(ch7, &c, 4); // read 4 bytes 
comm_read(ch7, &s, 4); // read 4 bytes 

		comm_read(ch16, &x_in, 4); // read 4 bytes 

		x_out = c * x_in - s * r;
		r = s * x_in + c * r;
		comm_write(ch8, &c, 4); // send 4 bytes 
comm_write(ch8, &s, 4); // send 4 bytes 

		comm_write(ch18, &x_out, 4); // send 4 bytes 

  }
int int_state_vars_inner13 = 1;
void initStateVarsinner13() {
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch7 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch7) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch16 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch16) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch8 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch8) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch18 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch18) {
		HOST(17) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_inner13==1){
        int_state_vars_inner13 = 0;
        initStateVarsinner13();
	}
if ((inner13_IntCheckOutput == -1)){ 
		
inner13Schedule:

		if (((comm_level(ch7) >= 1) && (comm_level(ch16) >= 1))){ 
									
inner13_Action_0:

					if (((comm_space(ch8) >= 1) && (comm_space(ch18) >= 1))){ 
							inner13_untag_action_0();
							goto inner13Schedule;
					}
					else {
							inner13_IntCheckOutput = 0;
							return(0);
					}


		}

		inner13_IntCheckOutput = -1;
}
else {
		
 switch (inner13_IntCheckOutput) {
   case 0:
     			inner13_IntCheckOutput = -1;
			goto inner13_Action_0;
}

}
goto inner13Schedule;
}
