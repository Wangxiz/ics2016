#include "cpu/exec/template-start.h"

#define instr stos

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_dest->reg = R_EDI;

	snprintf(op_dest->str, 11, "%%es:(%%edi)");

	if (DATA_BYTE == 1) {
		op_src->reg = R_AL; 
		cpu.edi = REG(R_AL);
		snprintf(op_src->str, 4, "%%al");
	}
	else if(DATA_BYTE == 2) {
		op_src->reg = R_AX; 
		cpu.edi = REG(R_AX);
		snprintf(op_src->str, 4, "%%ax");
	}
	else {
		op_src->reg = R_EAX; 
		cpu.edi = REG(R_EAX);
		snprintf(op_src->str, 5, "%%eax");
	}
	uint32_t val = swaddr_read(cpu.esi, DATA_BYTE);
	swaddr_write(cpu.edi, DATA_BYTE, val);

	cpu.esi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);
	cpu.edi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);

	print_asm_template2();
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"