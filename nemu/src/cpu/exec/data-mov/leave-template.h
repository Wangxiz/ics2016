#include "cpu/exec/template-start.h"

#define instr leave
// tested
static void do_execute() {
	cpu.esp = cpu.ebp;
	
	DATA_TYPE val = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	cpu.ebp = val;
	
	print_asm("leave");
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"