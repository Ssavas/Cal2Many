//code from inner.cal, instance inner12
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(2, 0, 16, 0, 32),
	COMM_CHANNEL(10, 1, 16, 1, 32),
	COMM_CHANNEL(16, 2, 17, 0, 32),
	COMM_CHANNEL(16, 3, 3, 1, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch1, ch15;
//OutputPorts
 comm_handle_t ch7, ch17;
static float r;
static int inner12_IntCheckOutput = -1;

static void  inner12_untag_action_0 () { 
	float x_out;
	int c;
	int s;
	int x_in;
		comm_read(ch1, &c, 4); // read 4 bytes 
comm_read(ch1, &s, 4); // read 4 bytes 

		comm_read(ch15, &x_in, 4); // read 4 bytes 

		x_out = c * x_in - s * r;
		r = s * x_in + c * r;
		comm_write(ch7, &c, 4); // send 4 bytes 
comm_write(ch7, &s, 4); // send 4 bytes 

		comm_write(ch17, &x_out, 4); // send 4 bytes 

  }
int int_state_vars_inner12 = 1;
void initStateVarsinner12() {
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch1 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch1) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch15 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch15) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch7 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch7) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch17 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch17) {
		HOST(16) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_inner12==1){
        int_state_vars_inner12 = 0;
        initStateVarsinner12();
	}
if ((inner12_IntCheckOutput == -1)){ 
		
inner12Schedule:

		if (((comm_level(ch1) >= 1) && (comm_level(ch15) >= 1))){ 
									
inner12_Action_0:

					if (((comm_space(ch7) >= 1) && (comm_space(ch17) >= 1))){ 
							inner12_untag_action_0();
							goto inner12Schedule;
					}
					else {
							inner12_IntCheckOutput = 0;
							return(0);
					}


		}

		inner12_IntCheckOutput = -1;
}
else {
		
 switch (inner12_IntCheckOutput) {
   case 0:
     			inner12_IntCheckOutput = -1;
			goto inner12_Action_0;
}

}
goto inner12Schedule;
}
