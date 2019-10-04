//code from TestPrint.cal, instance print

#include "print.h"
#include <stdint.h>

#include <e-lib.h>
#include "../shared.h"
#include "../commlib.h"

#include <stdio.h>
COMM_TABLE channels[] = {
	COMM_CHANNEL(15, 1, 16, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts 
 comm_handle_t ch33;
#define fd (createFile("C:/testcomp/IDCT2D/outout.txt")) 

static void  print_untag_action_0 () { 
  int b;
    comm_read(ch33, &b, 1);

    printf("%d\n",b);
    writeByte(fd, b);
  }
int main(void)
{
  
	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch33 = comm_get_rhandle(channels, NUM_CHANNELS, 33);

printSchedule:
if ((comm_level(ch33) >= 1)){ 
            print_untag_action_0();
      goto printSchedule;

}
goto printSchedule;
}
