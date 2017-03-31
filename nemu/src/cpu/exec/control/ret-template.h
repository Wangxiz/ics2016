#include "cpu/exec/template-start.h"

#define instr ret
// tested
static void do_execute() {
	cpu.eip = POP_DWORD();

#ifdef DEBUG_MY
	printf("RET ADDRESS:0x%08x\n", cpu.eip);
#endif

	//cpu.esp += op_src->val;

	if(op_src->val == 0) {
		print_asm("ret");
	}
	else {
		//op_src->val = (int32_t)((int16_t)op_src->val);
		cpu.esp += op_src->val;
		print_asm_template1();
	}
	// else {
	// 	cpu.eip -= 2;
	// 	print_asm_template1();
	// }
}

make_instr_helper(n)
make_instr_helper(i)

#include "cpu/exec/template-end.h"