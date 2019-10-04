//code from RowSort.cal, instance idctrowsort
#include <stdint.h>
#include <rv32array.h>
#include "common/commlib.h"

COMM_TABLE channels[] = {
	COMM_CHANNEL(1, 0, 2, 4, 32),
	COMM_CHANNEL(1, 1, 2, 5, 32),
};
#define NUM_CHANNELS (sizeof(channels)/sizeof(channels[0]))

//InputPorts
 comm_handle_t   ROW;
//OutputPorts
 comm_handle_t ch41, ch42;
static int x0;
static int x1;
static int x2;
static int x3;
static int x5;
static int idctrowsort_State;
#define FSM_idctrowsort_s0 (0) 
#define FSM_idctrowsort_s1 (1) 
#define FSM_idctrowsort_s2 (2) 
#define FSM_idctrowsort_s3 (3) 
#define FSM_idctrowsort_s4 (4) 
#define FSM_idctrowsort_s5 (5) 
#define FSM_idctrowsort_s6 (6) 
#define FSM_idctrowsort_s7 (7) 
#define FSM_idctrowsort_s8 (8) 
static int idctrowsort_IntCheckOutput = -1;

static void  idctrowsort_a0 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  x0 = a;
  }
static void  idctrowsort_a1 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  x1 = a;
  }
static void  idctrowsort_a2 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  x2 = a;
  }
static void  idctrowsort_a3 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  x3 = a;
  }
static void  idctrowsort_a4 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  comm_write(ch41, &x0, 4); // send 4 bytes 

	  comm_write(ch42, &a, 4); // send 4 bytes 

  }
static void  idctrowsort_a5 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  x5 = a;
  }
static void  idctrowsort_a6 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  comm_write(ch41, &x2, 4); // send 4 bytes 

	  comm_write(ch42, &a, 4); // send 4 bytes 

  }
static void  idctrowsort_a7 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  comm_write(ch41, &x1, 4); // send 4 bytes 

	  comm_write(ch42, &a, 4); // send 4 bytes 

  }
static void  idctrowsort_a8 () { 
	int a;
	  comm_read(  ROW, &a, 4); // read 4 bytes 

	  x0 = a;
	  comm_write(ch41, &x5, 4); // send 4 bytes 

	  comm_write(ch42, &x3, 4); // send 4 bytes 

  }
static void  idctrowsort_a9 () { 
	  comm_write(ch41, &x5, 4); // send 4 bytes 

	  comm_write(ch42, &x3, 4); // send 4 bytes 

  }
int int_state_vars_idctrowsort = 1;
void initStateVarsidctrowsort() {
idctrowsort_State = FSM_idctrowsort_s0;

}

int main(void)
{
  	/* initialization */
	platform_init();
	comm_init(channels, NUM_CHANNELS);

	//InputPorts
 
	//OutputPorts
	ch41 = comm_get_whandle(channels, NUM_CHANNELS, 0);
	if(!ch41) {
		HOST(1) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
	ch42 = comm_get_whandle(channels, NUM_CHANNELS, 1);
	if(!ch42) {
		HOST(1) = 0xDEADC0DE;
		asm volatile(".byte 0x00, 0x00, 0x00, 0x00");
	}
    if(int_state_vars_idctrowsort==1){
        int_state_vars_idctrowsort = 0;
        initStateVarsidctrowsort();
	}
if ((idctrowsort_IntCheckOutput == -1)){ 
      
idctrowsortSchedule:

    
 switch (idctrowsort_State) {
   case FSM_idctrowsort_s0:
           if ((comm_level(  ROW) >= 1)){ 
                              idctrowsort_a0();
            idctrowsort_State = FSM_idctrowsort_s1;
            goto idctrowsortSchedule;

}

           break;

   case FSM_idctrowsort_s1:
           if ((comm_level(  ROW) >= 1)){ 
                              idctrowsort_a1();
            idctrowsort_State = FSM_idctrowsort_s2;
            goto idctrowsortSchedule;

}

           break;

   case FSM_idctrowsort_s2:
           if ((comm_level(  ROW) >= 1)){ 
                              idctrowsort_a2();
            idctrowsort_State = FSM_idctrowsort_s3;
            goto idctrowsortSchedule;

}

           break;

   case FSM_idctrowsort_s3:
           if ((comm_level(  ROW) >= 1)){ 
                              idctrowsort_a3();
            idctrowsort_State = FSM_idctrowsort_s4;
            goto idctrowsortSchedule;

}

           break;

   case FSM_idctrowsort_s4:
           if ((comm_level(  ROW) >= 1)){ 
                              
idctrowsort_Action_0:

            if (((comm_space(ch41) >= 1) && (comm_space(ch42) >= 1))){ 
                              idctrowsort_a4();
                idctrowsort_State = FSM_idctrowsort_s5;
                goto idctrowsortSchedule;
}
            else {
                              idctrowsort_IntCheckOutput = 0;
                return(0);
}


}

           break;

   case FSM_idctrowsort_s5:
           if ((comm_level(  ROW) >= 1)){ 
                              idctrowsort_a5();
            idctrowsort_State = FSM_idctrowsort_s6;
            goto idctrowsortSchedule;

}

           break;

   case FSM_idctrowsort_s6:
           if ((comm_level(  ROW) >= 1)){ 
                              
idctrowsort_Action_1:

            if (((comm_space(ch41) >= 1) && (comm_space(ch42) >= 1))){ 
                              idctrowsort_a6();
                idctrowsort_State = FSM_idctrowsort_s7;
                goto idctrowsortSchedule;
}
            else {
                              idctrowsort_IntCheckOutput = 1;
                return(0);
}


}

           break;

   case FSM_idctrowsort_s7:
           if ((comm_level(  ROW) >= 1)){ 
                              
idctrowsort_Action_2:

            if (((comm_space(ch41) >= 1) && (comm_space(ch42) >= 1))){ 
                              idctrowsort_a7();
                idctrowsort_State = FSM_idctrowsort_s8;
                goto idctrowsortSchedule;
}
            else {
                              idctrowsort_IntCheckOutput = 2;
                return(0);
}


}

           break;

   case FSM_idctrowsort_s8:
           if ((comm_level(  ROW) >= 1)){ 
                              
idctrowsort_Action_3:

            if (((comm_space(ch41) >= 1) && (comm_space(ch42) >= 1))){ 
                              idctrowsort_a8();
                idctrowsort_State = FSM_idctrowsort_s1;
                goto idctrowsortSchedule;
}
            else {
                              idctrowsort_IntCheckOutput = 3;
                return(0);
}


}

              
idctrowsort_Action_4:

        if (((comm_space(ch41) >= 1) && (comm_space(ch42) >= 1))){ 
                      idctrowsort_a9();
            idctrowsort_State = FSM_idctrowsort_s0;
            goto idctrowsortSchedule;
}
        else {
                      idctrowsort_IntCheckOutput = 4;
            return(0);
}


           break;

}

    idctrowsort_IntCheckOutput = -1;
}
else {
      
 switch (idctrowsort_IntCheckOutput) {
   case 0:
           idctrowsort_IntCheckOutput = -1;
      goto idctrowsort_Action_0;
   case 1:
           idctrowsort_IntCheckOutput = -1;
      goto idctrowsort_Action_1;
   case 2:
           idctrowsort_IntCheckOutput = -1;
      goto idctrowsort_Action_2;
   case 3:
           idctrowsort_IntCheckOutput = -1;
      goto idctrowsort_Action_3;
   case 4:
           idctrowsort_IntCheckOutput = -1;
      goto idctrowsort_Action_4;
}

}
goto idctrowsortSchedule;
}
