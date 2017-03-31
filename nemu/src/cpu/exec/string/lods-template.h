#include "cpu/exec/template-start.h"

#define instr lods

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_src->reg = R_ESI; op_dest->reg = R_EDI;

	snprintf(op_src->str, 11, "%%ds:(%%esi)");
	DATA_TYPE val = swaddr_read(cpu.esi, DATA_BYTE);
	if(DATA_BYTE == 1) {
		swaddr_write(cpu.gpr[0]._8[0], DATA_BYTE, val);
		snprintf(op_src->str, 14, "%%ds:(%%esi),%%al");
	}
	else if(DATA_BYTE == 2) {
		swaddr_write(cpu.gpr[0]._16, DATA_BYTE, val);
		snprintf(op_src->str, 14, "%%ds:(%%esi),%%ax");
	}
	else {
		swaddr_write(cpu.gpr[0]._32, DATA_BYTE, val);
		snprintf(op_src->str, 15, "%%ds:(%%esi),%%eax");			
	}

	cpu.esi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"