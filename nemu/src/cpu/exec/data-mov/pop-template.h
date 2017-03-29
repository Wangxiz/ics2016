#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute() {
	if(DATA_BYTE == 4) {
		uint32_t val = MEM_R(cpu.esp);
		OPERAND_W(op_src, val);
		cpu.esp += 4;
	}
	print_asm_template1();
}

make_instr_helper(r)

#include "cpu/exec/template-end.h"