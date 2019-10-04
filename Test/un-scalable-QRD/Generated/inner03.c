//code from inner.cal, instance inner03
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(10, 1, 11, 0, 32),
	COMM_CHANNEL(19, 2, 11, 1, 32),
	COMM_CHANNEL(11, 2, 24, 1, 32),
	COMM_CHANNEL(11, 3, 17, 2, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch5, ch13;
//OutputPorts
 comm_handle_t ch6, ch16;
static float r;
static int inner03_IntCheckOutput = -1;

static void  inner03_untag_action_0 () { 
	float x_out;
	int c;
	int s;
	int x_in;
		comm_read(ch5, &c, 4); // read 4 bytes 
comm_read(ch5, &s, 4); // read 4 bytes 

		comm_read(ch13, &x_in, 4); // read 4 bytes 

		x_out = c * x_in - s * r;
		r = s * x_in + c * r;
		comm_write(ch6, &c, 4); // send 4 bytes 
comm_write(ch6, &s, 4); // send 4 bytes 

		comm_write(ch16, &x_out, 4); // send 4 bytes 

  }
int int_state_vars_inner03 = 1;
void initStateVarsinner03() {
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch5 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch5) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch13 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch13) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch6 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch6) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch16 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch16) {
		HOST(11) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_inner03==1){
        int_state_vars_inner03 = 0;
        initStateVarsinner03();
	}
if ((inner03_IntCheckOutput == -1)){ 
		
inner03Schedule:

		if (((comm_level(ch5) >= 1) && (comm_level(ch13) >= 1))){ 
									
inner03_Action_0:

					if (((comm_space(ch6) >= 1) && (comm_space(ch16) >= 1))){ 
							inner03_untag_action_0();
							goto inner03Schedule;
					}
					else {
							inner03_IntCheckOutput = 0;
							return(0);
					}


		}

		inner03_IntCheckOutput = -1;
}
else {
		
 switch (inner03_IntCheckOutput) {
   case 0:
     			inner03_IntCheckOutput = -1;
			goto inner03_Action_0;
}

}
goto inner03Schedule;
}
