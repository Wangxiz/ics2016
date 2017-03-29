#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + DATA_BYTE + 1);
	if(DATA_BYTE == 4) {
		cpu.eip += op_src->val;
	}
	print_asm_template1();
}

//#if DATA_BYPE == 1 || DATA_BYPE == 4
make_instr_helper(si)
//#endif

#include "cpu/exec/template-end.h"
