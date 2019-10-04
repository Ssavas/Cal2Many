//code from boundary.cal, instance boundary00
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(19, 0, 1, 0, 32),
	COMM_CHANNEL(1, 1, 9, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch10;
//OutputPorts
 comm_handle_t ch0;
static float acc__SquareRoot_ret;
static float r;
static int boundary00_IntCheckOutput = -1;
static void acc__SquareRoot (int ns);
();;;;;;;;();;;;;()();;;;;;comm_write(ch0, &c, 4); // send 4 bytes 
comm_write(ch0, &s, 4); // send 4 bytes 
int while () {
;;}
;
int int_state_vars_boundary00 = 1;
void initStateVarsboundary00() {
acc__SquareRoot_ret = 0.0;
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch10 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch10) {
		HOST(1) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch0 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch0) {
		HOST(1) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_boundary00==1){
        int_state_vars_boundary00 = 0;
        initStateVarsboundary00();
	}
if ((boundary00_IntCheckOutput == -1)){ 
		
boundary00Schedule:

		if ((comm_level(ch10) >= 1)){ 
									
boundary00_Action_0:

					if ((comm_space(ch0) >= 1)){ 
							boundary00___acc__();
							goto boundary00Schedule;
					}
					else {
							boundary00_IntCheckOutput = 0;
							return(0);
					}


		}

		boundary00_IntCheckOutput = -1;
}
else {
		
 switch (boundary00_IntCheckOutput) {
   case 0:
     			boundary00_IntCheckOutput = -1;
			goto boundary00_Action_0;
}

}
goto boundary00Schedule;
}
