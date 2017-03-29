#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute() {
	uint32_t addr = MEM_R(cpu.esp);

#ifdef DEBUG_MY
	printf("RET ADDRESS:0x%08x\n", addr);
#endif
	
	cpu.esp += 4 + op_src->val;
	cpu.eip = addr;
	if(op_src->val == 0) {
		print_asm("ret");
	}
	else {
		cpu.eip -= 2;
		print_asm_template1();
	}
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"