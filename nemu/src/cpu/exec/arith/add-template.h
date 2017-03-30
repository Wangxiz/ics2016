#include "cpu/exec/template-start.h"

#define instr add

static void do_execute () {
	DATA_TYPE val = op_dest->val + op_src->val;
	MEM_W(op_dest->val, val);
	print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"