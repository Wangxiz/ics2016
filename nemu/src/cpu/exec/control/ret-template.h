#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute() {
	cpu.eip = POP_DWORD();

#ifdef DEBUG_MY
	printf("RET ADDRESS:0x%08x\n", cpu.eip);
#endif

	//cpu.esp += op_src->val;

	if(op_src->val == 0) {
		print_asm("ret");
	}
	// else {
	// 	cpu.eip -= 2;
	// 	print_asm_template1();
	// }
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"