#include "cpu/exec/template-start.h"

#define instr scas

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_dest->reg = R_EDI;

	snprintf(op_src->str, 11, "%%ds:(%%esi)");
	DATA_TYPE val = swaddr_read(cpu.esi, DATA_BYTE);
	DATA_TYPE val1;

	if(DATA_BYTE == 1) {
		op_src->reg = R_AL;
		val1 = REG(R_AL) - val;

		SUB_CF(val, REG(R_AL));
		SUB_OF(val, REG(R_AL), val1);

		snprintf(op_src->str, 14, "%%es:(%%edi),%%al");
		print_asm("%%es:(%%edi),%%al");
	}
	else if(DATA_BYTE == 2) {
		op_src->reg = R_AX;
		val1 = REG(R_AX) - val;

		SUB_CF(val, REG(R_AX));
		SUB_OF(val, REG(R_AX), val1);

		snprintf(op_src->str, 14, "%%es:(%%edi),%%ax");
		print_asm("%%es:(%%edi),%%ax");
	}
	else {
		op_src->reg = R_EAX;
		val1 = REG(R_EAX) - val;

		SUB_CF(val, REG(R_EAX));
		SUB_OF(val, REG(R_EAX), val1);

		snprintf(op_src->str, 15, "%%es:(%%edi),%%eax");
		print_asm("%%es:(%%edi),%%eax");
	}

	UPDATE_EFLAGS_ZF(val1);
	UPDATE_EFLAGS_SF(val1);
	UPDATE_EFLAGS_PF(val1);

	cpu.edi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"