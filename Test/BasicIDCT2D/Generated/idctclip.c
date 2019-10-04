//code from Clip.cal, instance idctclip
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(26, 4, 27, 0, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t ch4,   SIGNED;
//OutputPorts
 comm_handle_t   O;
static int count = -1;
static int sflag;
static int idctclip_IntCheckOutput = -1;

static void  idctclip_read_signed () { 
	int s;
	  comm_read(  SIGNED, &s, 4); // read 4 bytes 

	  sflag = s;
	  count = 63;
  }
static void  idctclip_limit_max () { 
	int i;
	  comm_read(ch4, &i, 4); // read 4 bytes 

	  count = (count - 1);
	  int tmpvar_0_O = 255;
	comm_write(  O, &tmpvar_0_O, 4); // send 4 bytes 

  }
static void  idctclip_limit_zero () { 
	int i;
	  comm_read(ch4, &i, 4); // read 4 bytes 

	  count = (count - 1);
	  comm_write(  O, &i, 4); // send 4 bytes 

  }
static void  idctclip_limit_min () { 
	int i;
	  comm_read(ch4, &i, 4); // read 4 bytes 

	  count = (count - 1);
	  int tmpvar_2_O = -255;
	comm_write(  O, &tmpvar_2_O, 4); // send 4 bytes 

  }
static void  idctclip_limit_none () { 
	int i;
	  comm_read(ch4, &i, 4); // read 4 bytes 

	  count = (count - 1);
	  comm_write(  O, &i, 4); // send 4 bytes 

  }
int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 	ch4 = comm_get_rhandle(channels, NUM_CHANNELS, 0);
	if(!ch4) {
		HOST(27) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}

	//OutputPorts
int i_ac1;
int i_ac2;
int i_ac3;
if ((idctclip_IntCheckOutput == -1)){ 
      
idctclipSchedule:

    if ((comm_level(  SIGNED) >= 1)){ 
              if ((count < 0)){ 
                      idctclip_read_signed();
            goto idctclipSchedule;
}

}

    if ((comm_level(ch4) >= 1)){ 
              comm_peek(ch4, &i_ac1, 1);

        if ((i_ac1 > 255)){ 
                      
idctclip_Action_0:

            if ((comm_space(  O) >= 1)){ 
                              idctclip_limit_max();
                goto idctclipSchedule;
}
            else {
                              idctclip_IntCheckOutput = 0;
                return(0);
}

}

}

    if ((comm_level(ch4) >= 1)){ 
              comm_peek(ch4, &i_ac2, 1);

        if (((! sflag) && (i_ac2 < 0))){ 
                      
idctclip_Action_1:

            if ((comm_space(  O) >= 1)){ 
                              idctclip_limit_zero();
                goto idctclipSchedule;
}
            else {
                              idctclip_IntCheckOutput = 1;
                return(0);
}

}

}

    if ((comm_level(ch4) >= 1)){ 
              comm_peek(ch4, &i_ac3, 1);

        if ((i_ac3 < -255)){ 
                      
idctclip_Action_2:

            if ((comm_space(  O) >= 1)){ 
                              idctclip_limit_min();
                goto idctclipSchedule;
}
            else {
                              idctclip_IntCheckOutput = 2;
                return(0);
}

}

}

    if ((comm_level(ch4) >= 1)){ 
                        
idctclip_Action_3:

          if ((comm_space(  O) >= 1)){ 
                          idctclip_limit_none();
              goto idctclipSchedule;
}
          else {
                          idctclip_IntCheckOutput = 3;
              return(0);
}


}

    idctclip_IntCheckOutput = -1;
}
else {
      
 switch (idctclip_IntCheckOutput) {
   case 0:
           idctclip_IntCheckOutput = -1;
      goto idctclip_Action_0;
   case 1:
           idctclip_IntCheckOutput = -1;
      goto idctclip_Action_1;
   case 2:
           idctclip_IntCheckOutput = -1;
      goto idctclip_Action_2;
   case 3:
           idctclip_IntCheckOutput = -1;
      goto idctclip_Action_3;
}

}
goto idctclipSchedule;
}
