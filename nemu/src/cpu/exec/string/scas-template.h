#include "cpu/exec/template-start.h"

#define instr scas

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_dest->reg = R_EDI;

	snprintf(op_src->str, 11, "%%es:(%%edi),");

	DATA_TYPE val = swaddr_read(cpu.edi, DATA_BYTE);
	DATA_TYPE val1;
	// Log("edi->val: 0x%2x\n", val);
	if(DATA_BYTE == 1) {
		op_src->reg = R_AL;
		val1 = REG(R_AL) - val;

		SUB_CF(REG(R_AL), val);
		SUB_OF(REG(R_AL), val, val1);
	
		snprintf(op_dest->str, 4, "%%al");
	}
	else if(DATA_BYTE == 2) {
		op_src->reg = R_AX;
		val1 = REG(R_AX) - val;

		SUB_CF(REG(R_AX), val);
		SUB_OF(REG(R_AX), val, val1);

		snprintf(op_dest->str, 4, "%%ax");
	}
	else {
		op_src->reg = R_EAX;
		val1 = REG(R_EAX) - val;

		SUB_CF(REG(R_EAX), val);
		SUB_OF(REG(R_EAX), val, val1);

		snprintf(op_dest->str, 5, "%%eax");
	}

	UPDATE_EFLAGS_ZF(val1);
	UPDATE_EFLAGS_SF(val1);
	UPDATE_EFLAGS_PF(val1);

	cpu.edi += ((cpu.DF == 0) ? +DATA_BYTE : -DATA_BYTE);
	print_asm_template2();
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"