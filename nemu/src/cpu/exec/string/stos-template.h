#include "cpu/exec/template-start.h"

#define instr stos

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_dest->reg = R_EDI;

	snprintf(op_dest->str, 11, "%%es:(%%edi)");

	if (DATA_BYTE == 1) {
		op_src->reg = R_AL;
		MEM_W(cpu.edi, REG(R_AL));
		// swaddr_write();
		// cpu.edi = REG(R_AL);
		snprintf(op_src->str, 4, "%%al");
	}
	else if(DATA_BYTE == 2) {
		op_src->reg = R_AX; 
		MEM_W(cpu.edi, REG(R_AX));
		// cpu.edi = REG(R_AX);
		snprintf(op_src->str, 4, "%%ax");
	}
	else {
		op_src->reg = R_EAX; 
		MEM_W(cpu.edi, REG(R_EAX));
		// cpu.edi = REG(R_EAX);
		snprintf(op_src->str, 5, "%%eax");
	}

	cpu.edi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);

	print_asm_template2();
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"