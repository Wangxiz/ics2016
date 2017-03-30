#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	DATA_TYPE val = op_src->val & ((1ll << (op_src->size * 8)) - 1);
	OPERAND_W(op_dest, val);
	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(rm_b2r)
#endif

#if DATA_BYTE == 4
make_instr_helper(rm_w2r)
#endif

#include "cpu/exec/template-end.h"