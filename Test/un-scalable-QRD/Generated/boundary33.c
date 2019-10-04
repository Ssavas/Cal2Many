//code from boundary.cal, instance boundary33
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(18, 3, 8, 0, 32),
	COMM_CHANNEL(8, 1, 24, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch19;
//OutputPorts
 comm_handle_t ch3;
static float acc__SquareRoot_ret;
static float r;
static int boundary33_IntCheckOutput = -1;
static void acc__SquareRoot (int ns);
();;;;;;;;();;;;;()();;;;;;comm_write(ch3, &c, 4); // send 4 bytes 
comm_write(ch3, &s, 4); // send 4 bytes 
int while () {
;;}
;
int int_state_vars_boundary33 = 1;
void initStateVarsboundary33() {
acc__SquareRoot_ret = 0.0;
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch19 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch19) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch3 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch3) {
		HOST(8) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_boundary33==1){
        int_state_vars_boundary33 = 0;
        initStateVarsboundary33();
	}
if ((boundary33_IntCheckOutput == -1)){ 
		
boundary33Schedule:

		if ((comm_level(ch19) >= 1)){ 
									
boundary33_Action_0:

					if ((comm_space(ch3) >= 1)){ 
							boundary33___acc__();
							goto boundary33Schedule;
					}
					else {
							boundary33_IntCheckOutput = 0;
							return(0);
					}


		}

		boundary33_IntCheckOutput = -1;
}
else {
		
 switch (boundary33_IntCheckOutput) {
   case 0:
     			boundary33_IntCheckOutput = -1;
			goto boundary33_Action_0;
}

}
goto boundary33Schedule;
}
