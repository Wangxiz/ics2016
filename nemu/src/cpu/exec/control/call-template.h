#include "cpu/exec/template-start.h"

#define instr call

// len: defined in cpu/helper.h
extern int len;

static void do_execute() {
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + len);

#ifdef DEBUG_MY
	printf("ESP:%x\n", MEM_R(cpu.esp));
#endif

	if(DATA_BYTE == 4) {
		cpu.eip += op_src->val;
	}
	print_asm_template1();
}

make_instr_helper(si)

#include "cpu/exec/template-end.h"