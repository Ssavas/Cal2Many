//code from inner.cal, instance inner23
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(3, 0, 18, 0, 32),
	COMM_CHANNEL(17, 1, 18, 1, 32),
	COMM_CHANNEL(18, 2, 24, 3, 32),
	COMM_CHANNEL(18, 3, 8, 4, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch2, ch18;
//OutputPorts
 comm_handle_t ch9, ch19;
static float r;
static int inner23_IntCheckOutput = -1;

static void  inner23_untag_action_0 () { 
	float x_out;
	int c;
	int s;
	int x_in;
		comm_read(ch2, &c, 4); // read 4 bytes 
comm_read(ch2, &s, 4); // read 4 bytes 

		comm_read(ch18, &x_in, 4); // read 4 bytes 

		x_out = c * x_in - s * r;
		r = s * x_in + c * r;
		comm_write(ch9, &c, 4); // send 4 bytes 
comm_write(ch9, &s, 4); // send 4 bytes 

		comm_write(ch19, &x_out, 4); // send 4 bytes 

  }
int int_state_vars_inner23 = 1;
void initStateVarsinner23() {
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch2 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch2) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch18 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch18) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch9 = comm_get_whandle(channels, NUM_CHANNELS, 2);
	if(!ch9) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch19 = comm_get_whandle(channels, NUM_CHANNELS, 3);
	if(!ch19) {
		HOST(18) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_inner23==1){
        int_state_vars_inner23 = 0;
        initStateVarsinner23();
	}
if ((inner23_IntCheckOutput == -1)){ 
		
inner23Schedule:

		if (((comm_level(ch2) >= 1) && (comm_level(ch18) >= 1))){ 
									
inner23_Action_0:

					if (((comm_space(ch9) >= 1) && (comm_space(ch19) >= 1))){ 
							inner23_untag_action_0();
							goto inner23Schedule;
					}
					else {
							inner23_IntCheckOutput = 0;
							return(0);
					}


		}

		inner23_IntCheckOutput = -1;
}
else {
		
 switch (inner23_IntCheckOutput) {
   case 0:
     			inner23_IntCheckOutput = -1;
			goto inner23_Action_0;
}

}
goto inner23Schedule;
}
