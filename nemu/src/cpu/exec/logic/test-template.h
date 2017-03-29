#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	// if(DATA_BYTE == 4) {
	// 	cpu.esp -= 4;
	// 	MEM_W(cpu.esp, op_src->val);
	// }
	DATA_TYPE val = op_src->val & op_dest->val;
	cpu.CF = 0;
	cpu.OF = 0;
	PF(val);
	ZF(val);
	SF(val);
	print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"