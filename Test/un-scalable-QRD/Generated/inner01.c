//code from inner.cal, instance inner01
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(1, 0, 9, 0, 32),
	COMM_CHANNEL(19, 1, 9, 1, 32),
	COMM_CHANNEL(9, 2, 10, 0, 32),
	COMM_CHANNEL(9, 3, 2, 1, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch0, ch11;
//OutputPorts
 comm_handle_t ch4, ch14;
static float r;
static int inner01_IntCheckOutput = -1;

static void  inner01_untag_action_0 () { 
	float x_out;
	int c;
	int s;
	int x_in;
		comm_read(ch0, &c, 4); // read 4 bytes 
comm_read(ch0, &s, 4); // read 4 bytes 

		comm_read(ch11, &x_in, 4); // read 4 bytes 

		x_out = c * x_in - s * r;
		r = s * x_in + c * r;
		comm_write(ch4, &c, 4); // send 4 bytes 
comm_write(ch4, &s, 4); // send 4 bytes 

		comm_write(ch14, &x_out, 4); // send 4 bytes 

  }
int int_state_vars_inner01 = 1;
void initStateVarsinner01() {
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch0 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch0) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch11 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch11) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch4 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch4) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch14 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch14) {
		HOST(9) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_inner01==1){
        int_state_vars_inner01 = 0;
        initStateVarsinner01();
	}
if ((inner01_IntCheckOutput == -1)){ 
		
inner01Schedule:

		if (((comm_level(ch0) >= 1) && (comm_level(ch11) >= 1))){ 
									
inner01_Action_0:

					if (((comm_space(ch4) >= 1) && (comm_space(ch14) >= 1))){ 
							inner01_untag_action_0();
							goto inner01Schedule;
					}
					else {
							inner01_IntCheckOutput = 0;
							return(0);
					}


		}

		inner01_IntCheckOutput = -1;
}
else {
		
 switch (inner01_IntCheckOutput) {
   case 0:
     			inner01_IntCheckOutput = -1;
			goto inner01_Action_0;
}

}
goto inner01Schedule;
}
