#include "cpu/exec/template-start.h"

#define instr cwtl

static void do_execute() {
	if(DATA_BYTE == 2) {
		int8_t al = reg_b(R_AL);
		reg_w(R_AX) = (int16_t)al;
		print_asm("cwtlw");	
	}
	else {
		int16_t ax = reg_w(R_AX);
		reg_l(R_EAX) = (int32_t)ax;
		print_asm("cwtll");	
	} 
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"