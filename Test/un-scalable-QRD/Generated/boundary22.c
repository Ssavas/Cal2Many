//code from boundary.cal, instance boundary22
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(16, 3, 3, 0, 32),
	COMM_CHANNEL(3, 1, 18, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch17;
//OutputPorts
 comm_handle_t ch2;
static float acc__SquareRoot_ret;
static float r;
static int boundary22_IntCheckOutput = -1;
static void acc__SquareRoot (int ns);
();;;;;;;;();;;;;()();;;;;;comm_write(ch2, &c, 4); // send 4 bytes 
comm_write(ch2, &s, 4); // send 4 bytes 
int while () {
;;}
;
int int_state_vars_boundary22 = 1;
void initStateVarsboundary22() {
acc__SquareRoot_ret = 0.0;
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch17 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch17) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch2 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch2) {
		HOST(3) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_boundary22==1){
        int_state_vars_boundary22 = 0;
        initStateVarsboundary22();
	}
if ((boundary22_IntCheckOutput == -1)){ 
		
boundary22Schedule:

		if ((comm_level(ch17) >= 1)){ 
									
boundary22_Action_0:

					if ((comm_space(ch2) >= 1)){ 
							boundary22___acc__();
							goto boundary22Schedule;
					}
					else {
							boundary22_IntCheckOutput = 0;
							return(0);
					}


		}

		boundary22_IntCheckOutput = -1;
}
else {
		
 switch (boundary22_IntCheckOutput) {
   case 0:
     			boundary22_IntCheckOutput = -1;
			goto boundary22_Action_0;
}

}
goto boundary22Schedule;
}
