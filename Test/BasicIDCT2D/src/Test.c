/*Network Test() ==>  : 
 
Var


Entities

TestSource source(  )
RowSort idctrowsort( sz = 13,  )
Scale idctidctRowscale( isz = 16, osz = 30, csz = 13,  )
Combine idctidctRowcombine( isz = 30, osz = 24,  = true,  )
ShuffleFly idctidctRowshufflefly( sz = 24,  )
Shuffle idctidctRowshuffle( sz = 24,  )
Final idctidctRowfinal( isz = 24, osz = 16,  )
Transpose idcttrans( sz = 16,  )
Scale idctidctColscale( isz = 16, osz = 30, csz = 13,  )
Combine idctidctColcombine( isz = 30, osz = 24,  = false,  )
ShuffleFly idctidctColshufflefly( sz = 24,  )
Shuffle idctidctColshuffle( sz = 24,  )
Final idctidctColfinal( isz = 24, osz = 16,  )
Shift idctshift( isz = 16, csz = 10,  )
Retranspose idctretrans( isz = 10, osz = 10,  )
Clip idctclip( isz = 10, osz = 9,  )
TestPrint print(  )

Struct

Shift  idctshift.Y0 --> Retranspose  idctretrans.X0
Shift  idctshift.Y1 --> Retranspose  idctretrans.X1
Shift  idctshift.Y2 --> Retranspose  idctretrans.X2
Shift  idctshift.Y3 --> Retranspose  idctretrans.X3
Retranspose  idctretrans.Y --> Clip  idctclip.I
Scale  idctidctRowscale.Y0 --> Combine  idctidctRowcombine.X0
Scale  idctidctRowscale.Y1 --> Combine  idctidctRowcombine.X1
Scale  idctidctRowscale.Y2 --> Combine  idctidctRowcombine.X2
Scale  idctidctRowscale.Y3 --> Combine  idctidctRowcombine.X3
Combine  idctidctRowcombine.Y0 --> ShuffleFly  idctidctRowshufflefly.X0
Combine  idctidctRowcombine.Y1 --> ShuffleFly  idctidctRowshufflefly.X1
ShuffleFly  idctidctRowshufflefly.Y0 --> Shuffle  idctidctRowshuffle.X0
ShuffleFly  idctidctRowshufflefly.Y1 --> Shuffle  idctidctRowshuffle.X1
ShuffleFly  idctidctRowshufflefly.Y2 --> Shuffle  idctidctRowshuffle.X2
ShuffleFly  idctidctRowshufflefly.Y3 --> Shuffle  idctidctRowshuffle.X3
Shuffle  idctidctRowshuffle.Y0 --> Final  idctidctRowfinal.X0
Shuffle  idctidctRowshuffle.Y1 --> Final  idctidctRowfinal.X1
Shuffle  idctidctRowshuffle.Y2 --> Final  idctidctRowfinal.X2
Shuffle  idctidctRowshuffle.Y3 --> Final  idctidctRowfinal.X3
Scale  idctidctColscale.Y0 --> Combine  idctidctColcombine.X0
Scale  idctidctColscale.Y1 --> Combine  idctidctColcombine.X1
Scale  idctidctColscale.Y2 --> Combine  idctidctColcombine.X2
Scale  idctidctColscale.Y3 --> Combine  idctidctColcombine.X3
Combine  idctidctColcombine.Y0 --> ShuffleFly  idctidctColshufflefly.X0
Combine  idctidctColcombine.Y1 --> ShuffleFly  idctidctColshufflefly.X1
ShuffleFly  idctidctColshufflefly.Y0 --> Shuffle  idctidctColshuffle.X0
ShuffleFly  idctidctColshufflefly.Y1 --> Shuffle  idctidctColshuffle.X1
ShuffleFly  idctidctColshufflefly.Y2 --> Shuffle  idctidctColshuffle.X2
ShuffleFly  idctidctColshufflefly.Y3 --> Shuffle  idctidctColshuffle.X3
Shuffle  idctidctColshuffle.Y0 --> Final  idctidctColfinal.X0
Shuffle  idctidctColshuffle.Y1 --> Final  idctidctColfinal.X1
Shuffle  idctidctColshuffle.Y2 --> Final  idctidctColfinal.X2
Shuffle  idctidctColshuffle.Y3 --> Final  idctidctColfinal.X3
Clip  idctclip.O --> TestPrint  print.B
TestSource  source.V --> RowSort  idctrowsort.ROW
TestSource  source.Signed --> Clip  idctclip.SIGNED
Final  idctidctRowfinal.Y0 --> Transpose  idcttrans.X0
Final  idctidctRowfinal.Y1 --> Transpose  idcttrans.X1
Final  idctidctRowfinal.Y2 --> Transpose  idcttrans.X2
Final  idctidctRowfinal.Y3 --> Transpose  idcttrans.X3
Final  idctidctColfinal.Y0 --> Shift  idctshift.X0
Final  idctidctColfinal.Y1 --> Shift  idctshift.X1
Final  idctidctColfinal.Y2 --> Shift  idctshift.X2
Final  idctidctColfinal.Y3 --> Shift  idctshift.X3
RowSort  idctrowsort.Y0 --> Scale  idctidctRowscale.X0
RowSort  idctrowsort.Y1 --> Scale  idctidctRowscale.X1
Transpose  idcttrans.Y0 --> Scale  idctidctColscale.X0
Transpose  idcttrans.Y1 --> Scale  idctidctColscale.X1
*/

// ********* Generate Code form flatten NL Test.c *********/

#include "source.h"
#include "idctrowsort.h"
#include "idctidctRowscale.h"
#include "idctidctRowcombine.h"
#include "idctidctRowshufflefly.h"
#include "idctidctRowshuffle.h"
#include "idctidctRowfinal.h"
#include "idcttrans.h"
#include "idctidctColscale.h"
#include "idctidctColcombine.h"
#include "idctidctColshufflefly.h"
#include "idctidctColshuffle.h"
#include "idctidctColfinal.h"
#include "idctshift.h"
#include "idctretrans.h"
#include "idctclip.h"
#include "print.h"
#include "include\calChannel.h"
#include <stdio.h>
//Input Ports 
//Output Ports
fifo ch0;
fifo ch1;
fifo ch2;
fifo ch3;
fifo ch4;
fifo ch5;
fifo ch6;
fifo ch7;
fifo ch8;
fifo ch9;
fifo ch10;
fifo ch11;
fifo ch12;
fifo ch13;
fifo ch14;
fifo ch15;
fifo ch16;
fifo ch17;
fifo ch18;
fifo ch19;
fifo ch20;
fifo ch21;
fifo ch22;
fifo ch23;
fifo ch24;
fifo ch25;
fifo ch26;
fifo ch27;
fifo ch28;
fifo ch29;
fifo ch30;
fifo ch31;
fifo ch32;
fifo ch33;
fifo ch34;
fifo ch35;
fifo ch36;
fifo ch37;
fifo ch38;
fifo ch39;
fifo ch40;
fifo ch41;
fifo ch42;
fifo ch43;
fifo ch44;
fifo ch45;
fifo ch46;
fifo ch47;
int main(){
   
init_fifo(&ch0); // printf("0\n");
init_fifo(&ch1); // printf("1\n");
init_fifo(&ch2); // printf("2\n");
init_fifo(&ch3); // printf("3\n");
init_fifo(&ch4); // printf("4\n");
init_fifo(&ch5); // printf("5\n");
init_fifo(&ch6); // printf("6\n");
init_fifo(&ch7); // printf("7\n");
init_fifo(&ch8); // printf("8\n");
init_fifo(&ch9); // printf("9\n");
init_fifo(&ch10); // printf("10\n");
init_fifo(&ch11); // printf("11\n");
init_fifo(&ch12); // printf("12\n");
init_fifo(&ch13); // printf("13\n");
init_fifo(&ch14); // printf("14\n");
init_fifo(&ch15); // printf("15\n");
init_fifo(&ch16); // printf("16\n");
init_fifo(&ch17); // printf("17\n");
init_fifo(&ch18); // printf("18\n");
init_fifo(&ch19); // printf("19\n");
init_fifo(&ch20); // printf("20\n");
init_fifo(&ch21); // printf("21\n");
init_fifo(&ch22); // printf("22\n");
init_fifo(&ch23); // printf("23\n");
init_fifo(&ch24); // printf("24\n");
init_fifo(&ch25); // printf("25\n");
init_fifo(&ch26); // printf("26\n");
init_fifo(&ch27); // printf("27\n");
init_fifo(&ch28); // printf("28\n");
init_fifo(&ch29); // printf("29\n");
init_fifo(&ch30); // printf("30\n");
init_fifo(&ch31); // printf("31\n");
init_fifo(&ch32); // printf("32\n");
init_fifo(&ch33); // printf("33\n");
init_fifo(&ch34); // printf("34\n");
init_fifo(&ch35); // printf("35\n");
init_fifo(&ch36); // printf("36\n");
init_fifo(&ch37); // printf("37\n");
init_fifo(&ch38); // printf("38\n");
init_fifo(&ch39); // printf("39\n");
init_fifo(&ch40); // printf("40\n");
init_fifo(&ch41); // printf("41\n");
init_fifo(&ch42); // printf("42\n");
init_fifo(&ch43); // printf("43\n");
init_fifo(&ch44); // printf("44\n");
init_fifo(&ch45); // printf("45\n");
init_fifo(&ch46); // printf("46\n");
init_fifo(&ch47); // printf("47\n");    int run=0;
    int no_run = 4096, run =0;
 	while(run <=no_run){
	    Scheduler_source();
	    Scheduler_idctrowsort();
	    Scheduler_idctidctRowscale();
	    Scheduler_idctidctRowcombine();
	    Scheduler_idctidctRowshufflefly();
	    Scheduler_idctidctRowshuffle();
	    Scheduler_idctidctRowfinal();
	    Scheduler_idcttrans();
	    Scheduler_idctidctColscale();
	    Scheduler_idctidctColcombine();
	    Scheduler_idctidctColshufflefly();
	    Scheduler_idctidctColshuffle();
	    Scheduler_idctidctColfinal();
	    Scheduler_idctshift();
	    Scheduler_idctretrans();
	    Scheduler_idctclip();
	    Scheduler_print();
	    run++;
    }
}
