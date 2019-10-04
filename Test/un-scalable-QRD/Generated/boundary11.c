//code from boundary.cal, instance boundary11
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(9, 3, 2, 0, 32),
	COMM_CHANNEL(2, 1, 16, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch14;
//OutputPorts
 comm_handle_t ch1;
static float acc__SquareRoot_ret;
static float r;
static int boundary11_IntCheckOutput = -1;
static void acc__SquareRoot (int ns);
();;;;;;;;();;;;;()();;;;;;comm_write(ch1, &c, 4); // send 4 bytes 
comm_write(ch1, &s, 4); // send 4 bytes 
int while () {
;;}
;
int int_state_vars_boundary11 = 1;
void initStateVarsboundary11() {
acc__SquareRoot_ret = 0.0;
r = 0.0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch14 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch14) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
	ch1 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch1) {
		HOST(2) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_boundary11==1){
        int_state_vars_boundary11 = 0;
        initStateVarsboundary11();
	}
if ((boundary11_IntCheckOutput == -1)){ 
		
boundary11Schedule:

		if ((comm_level(ch14) >= 1)){ 
									
boundary11_Action_0:

					if ((comm_space(ch1) >= 1)){ 
							boundary11___acc__();
							goto boundary11Schedule;
					}
					else {
							boundary11_IntCheckOutput = 0;
							return(0);
					}


		}

		boundary11_IntCheckOutput = -1;
}
else {
		
 switch (boundary11_IntCheckOutput) {
   case 0:
     			boundary11_IntCheckOutput = -1;
			goto boundary11_Action_0;
}

}
goto boundary11Schedule;
}
