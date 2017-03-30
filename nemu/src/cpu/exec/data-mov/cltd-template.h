#include "cpu/exec/template-start.h"

#define instr cltd

static void do_execute() {
	if(cpu.eax >> (DATA_BYTE * 8 - 1) != 0) {
		cpu.edx = (1ll << (DATA_BYTE * 8)) - 1;
	}
	else {
		cpu.edx = 0;
	}
	if(DATA_BYTE == 2) print_asm("cwtlw");
	else print_asm("cltdl");
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"