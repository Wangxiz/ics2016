#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + DATA_BYTE + 1);
	printf("ESP:%x\n", cpu.esp);
	if(DATA_BYTE == 4) {
		cpu.eip += op_src->val;
	}
	print_asm_template1();
}

make_instr_helper(si)

#include "cpu/exec/template-end.h"