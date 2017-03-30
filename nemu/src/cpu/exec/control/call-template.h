#include "cpu/exec/template-start.h"

#define instr call

/* len: defined in cpu/helper.h */
extern int len;
// tested
static void do_execute() {
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + len);
	
#ifdef DEBUG_MY
	printf("call: eip:0x%08x\n, len: %d\n", cpu.eip, len);
	printf("ESP:%x\n", MEM_R(cpu.esp));
#endif

	if(DATA_BYTE == 4) {
		cpu.eip += op_src->val;
	}
	print_asm(str(instr) str(SUFFIX) " 0x%x", cpu.eip + len + 1);
}

make_instr_helper(si)

#include "cpu/exec/template-end.h"