#include "cpu/exec/template-start.h"

#define instr lods

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_src->reg = R_ESI;

	snprintf(op_src->str, 13, "%%ds:(%%esi)");
	DATA_TYPE val = swaddr_read(cpu.esi, DATA_BYTE);

	if(DATA_BYTE == 1) {
		op_dest->reg = R_AL;
		cpu.gpr[0]._8[0]= val;
		snprintf(op_dest->str, 4, "%%al");
	}
	else if(DATA_BYTE == 2) {
		op_dest->reg = R_AX;
		cpu.gpr[0]._16 = val;
		snprintf(op_dest->str, 4, "%%ax");
	}
	else {
		op_dest->reg = R_EAX;
		cpu.gpr[0]._32 = val;
		snprintf(op_dest->str, 5, "%%eax");			
	}

	cpu.esi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);
	print_asm_template2();
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"