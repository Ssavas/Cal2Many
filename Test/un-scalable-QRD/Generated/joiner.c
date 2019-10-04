//code from joiner.cal, instance joiner
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(8, 0, 24, 0, 32),
	COMM_CHANNEL(11, 1, 24, 1, 32),
	COMM_CHANNEL(17, 2, 24, 2, 32),
	COMM_CHANNEL(18, 3, 24, 3, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch6, ch8, ch9, ch3;
//OutputPorts
 comm_handle_t   output;
static int joiner_IntCheckOutput = -1;

static void  joiner_untag_action_0 () { 
	int data1;
	int data2;
	int data3;
	int data4;
		comm_read(ch6, &data1, 4); // read 4 bytes 

		comm_read(ch8, &data2, 4); // read 4 bytes 

		comm_read(ch9, &data3, 4); // read 4 bytes 

		comm_read(ch3, &data4, 4); // read 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch6 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch6) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch8 = comm_get_rhandle(channels, NUM_CHANNELS, 1);
	if(!ch8) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch9 = comm_get_rhandle(channels, NUM_CHANNELS, 2);
	if(!ch9) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch3 = comm_get_rhandle(channels, NUM_CHANNELS, 3);
	if(!ch3) {
		HOST(24) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
if ((joiner_IntCheckOutput == -1)){ 
		
joinerSchedule:

		if (((comm_level(ch6) >= 1) && ((comm_level(ch8) >= 1) && ((comm_level(ch9) >= 1) && (comm_level(ch3) >= 1))))){ 
									joiner_untag_action_0();
					goto joinerSchedule;

		}

		joiner_IntCheckOutput = -1;
}
else {
		
 switch (joiner_IntCheckOutput) {
}

}
goto joinerSchedule;
}
