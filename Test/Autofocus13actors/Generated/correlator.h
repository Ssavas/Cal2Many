#ifndef _ACTORScorrelator
#define _ACTORScorrelator

// Macro for placing the data on corresponding core's memory 
#undef  SECTION 
#define SECTION(x) __attribute__((section(x))) 

int correlator( ) SECTION(".core12.text");
int correlator_checkFlag(volatile int*) SECTION(".core12.text");
static void correlator_readInputs1( ) SECTION(".core12.text");
static void correlator_readInputs2( ) SECTION(".core12.text");
static void correlator_readInputs3( ) SECTION(".core12.text");
static void correlator_readInputs4( ) SECTION(".core12.text");
static void correlator_readInputs5( ) SECTION(".core12.text");
static void correlator_readInputs6( ) SECTION(".core12.text");
static void correlator___acc__correlation( ) SECTION(".core12.text");
static void correlator_set_correlation_inputs( ) SECTION(".core12.text");
static void correlator_correlation_done1( ) SECTION(".core12.text");
static void correlator_correlation_done2( ) SECTION(".core12.text");
static void correlator_correlation_done3( ) SECTION(".core12.text");
static void correlator_correlation_done4( ) SECTION(".core12.text");
static void correlator_correlation_done5( ) SECTION(".core12.text");
static void correlator_correlation_done6( ) SECTION(".core12.text");
void initStateVarscorrelator() SECTION(".core12.text");

// Macros for inlinig code to call the accelerator 
#define STR1(x) #x 
#define STR(x) STR1(x) 
#define EXTRACT(a, size, offset) (((~(~0 << size) << offset) & a) >> offset) 
#define CUSTOMX_OPCODE(x) CUSTOM_ ## x 
#define CUSTOM_0 0b0001011 
#define CUSTOM_1 0b0101011 
#define CUSTOM_2 0b1011011 
#define CUSTOM_3 0b1111011 
#define CUSTOMX(X, rd, rs1, rs2, funct)         \
	CUSTOMX_OPCODE(X)                   |         \
	(rd                   << (7))       |         \
	(0x7                  << (7+5))     |         \
	(rs1                  << (7+5+3))   |         \
	(rs2                  << (7+5+3+5)) |         \
	(EXTRACT(funct, 7, 0) << (7+5+3+5+5)) 

// Standard macro that passes rd, rs1, and rs2 via registers 
#define ROCC_INSTRUCTION(X, rd, rs1, rs2, funct)                \
	ROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct, 10, 11, 12) 

// rd, rs1, and rs2 are data 
// rd_n, rs_1, and rs2_n are the register numbers to use 
#define ROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) { \
	register uint64_t rd_  asm ("x" # rd_n);                            \
	register uint64_t rs1_ asm ("x" # rs1_n) = (uint64_t) rs1;          \
	register uint64_t rs2_ asm ("x" # rs2_n) = (uint64_t) rs2;          \
	asm volatile (                                                      \
		".word " STR(CUSTOMX(X, rd_n, rs1_n, rs2_n, funct)) "\n\t"      \
		: "=r" (rd_)                                                    \
		: [_rs1] "r" (rs1_), [_rs2] "r" (rs2_));                        \
	rd = rd_;                                                           \
} 
#define XCUSTOM_ACC	0 
#define FUNCT_FIRE	4 
#define FUNCT_IN1	1 
#define FUNCT_IN2	2 
#define FUNCT_IN3	3 
#define FUNCT_READ 5 

// Standard macro that passes rd, rs1, and rs2 via registers and expects does not block (while waiting for the result) 
#define ROCC_INSTRUCTION_NO_BLOCK(X, rd, rs1, rs2, funct)                \
	ROCC_INSTRUCTION_NO_BLOCK_R_R_R(X, rd, rs1, rs2, funct, 10, 11, 12) 

	// rd, rs1, and rs2 are data 
	// rd_n, rs_1, and rs2_n are the register numbers to use 
#define ROCC_INSTRUCTION_NO_BLOCK_R_R_R(X, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) { \
	register uint64_t rd_  asm ("x" # rd_n);                            \
	register uint64_t rs1_ asm ("x" # rs1_n) = (uint64_t) rs1;          \
	register uint64_t rs2_ asm ("x" # rs2_n) = (uint64_t) rs2;          \
	asm volatile (                                                      \
		".word " STR(CUSTOMX_NP(X, rd_n, rs1_n, rs2_n, funct)) "\n\t"   \
		: "=r" (rd_)                                                    \
		: [_rs1] "r" (rs1_), [_rs2] "r" (rs2_));                        \
	rd = rd_;                                                           \
} 

// no requirement for return register 
#define CUSTOMX_NP(X, rd, rs1, rs2, funct)         \
	CUSTOMX_OPCODE(X)                   |         \
	(rd                   << (7))       |         \
	(0x3                  << (7+5))     |         \
	(rs1                  << (7+5+3))   |         \
	(rs2                  << (7+5+3+5)) |         \
	(EXTRACT(funct, 7, 0) << (7+5+3+5+5)) 

#define ROCC_CUBIC(rd, rs1, rs2, rs3, rs4, rs5, rs6, rs7, rs8)                \
	ROCC_CUBIC_R(rd, rs1, rs2, rs3, rs4, rs5, rs6, rs7, rs8, 4, 5, 6, 7, 8, 9, 10, 11, 12) 

#define ROCC_CUBIC_R(rd, rs1, rs2, rs3, rs4, rs5, rs6, rs7, rs8, rd_n, rs1_n, rs2_n, rs3_n, rs4_n, rs5_n, rs6_n, rs7_n, rs8_n) { \
	register uint64_t rd_  asm ("x" # rd_n);                            	\
	register uint64_t rs1_ asm ("x" # rs1_n) = (uint64_t) rs1;          	\
	register uint64_t rs2_ asm ("x" # rs2_n) = (uint64_t) rs2;          	\
	register uint64_t rs3_ asm ("x" # rs3_n) = (uint64_t) rs3;          	\
	register uint64_t rs4_ asm ("x" # rs4_n) = (uint64_t) rs4;          	\
	register uint64_t rs5_ asm ("x" # rs5_n) = (uint64_t) rs5;          	\
	register uint64_t rs6_ asm ("x" # rs6_n) = (uint64_t) rs6;          	\
	register uint64_t rs7_ asm ("x" # rs7_n) = (uint64_t) rs7;          	\
	register uint64_t rs8_ asm ("x" # rs8_n) = (uint64_t) rs8;          	\
	asm volatile (                                                     		\
		".word " STR(CUSTOMX_NP(0, rd_n, rs1_n, rs2_n, FUNCT_IN1)) "\n\t"   \
		".word " STR(CUSTOMX_NP(0, rd_n, rs3_n, rs4_n, FUNCT_IN2)) "\n\t"   \
		".word " STR(CUSTOMX_NP(0, rd_n, rs5_n, rs6_n, FUNCT_IN3)) "\n\t"   \
		".word " STR(CUSTOMX(0, rd_n, rs7_n, rs8_n, FUNCT_FIRE)) "\n\t"     \
		: "=r" (rd_)                                                    	\
		: [_rs1] "r" (rs1_), [_rs2] "r" (rs2_), [_rs3] "r" (rs3_), 			\
		[_rs4] "r" (rs4_), [_rs5] "r" (rs5_), [_rs6] "r" (rs6_), [_rs7] 	\
		"r" (rs7_), [_rs8] "r" (rs8_)) ;   			                     	\
	rd = rd_;                                                           	\
}
 
#endif
