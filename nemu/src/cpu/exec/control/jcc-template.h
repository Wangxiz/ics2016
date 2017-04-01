#include "cpu/exec/template-start.h"

/* len: defined in cpu/helper.h */
extern int len;
// tested
#define if_exec() {\
	cpu.eip += op_src->val;\
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + len + 1);\
}

#define else_exec() \
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + op_src->val + len + 1)

#define all_exec() \
static void do_execute() { \
	if(JMPFLAG) if_exec()\
	else else_exec();\
	print_asm_template1();\
} \
make_instr_helper(si) 

#define instr je	/* also jz */
#define JMPFLAG cpu.ZF == 1
all_exec();
#undef JMPFLAG
#undef instr

#define instr jbe	/* also jna */
#define JMPFLAG cpu.ZF == 1 || cpu.CF == 1
all_exec();
#undef JMPFLAG
#undef instr

#define instr jne	/* also jnz */
#define JMPFLAG cpu.ZF == 0
all_exec();
#undef JMPFLAG
#undef instr

#define instr jle	/* also jng */
#define JMPFLAG cpu.ZF == 1 || cpu.SF != cpu.OF
all_exec();
#undef JMPFLAG
#undef instr

#define instr jl	/* also jnge */
#define JMPFLAG cpu.SF != cpu.OF
all_exec();
#undef JMPFLAG
#undef instr

#define instr jge	/* also jnl */
#define JMPFLAG cpu.SF == cpu.OF
all_exec();
#undef JMPFLAG
#undef instr

#define instr jg	/* also jnle */
#define JMPFLAG cpu.ZF == 0 && cpu.SF == cpu.OF
all_exec();
#undef JMPFLAG
#undef instr

#define instr ja	/* also jnbe */
#define JMPFLAG cpu.ZF == 0 && cpu.CF == 0
all_exec();
#undef JMPFLAG
#undef instr

#define instr js
#define JMPFLAG cpu.SF == 1
all_exec();
#undef JMPFLAG
#undef instr

#define instr jns
#define JMPFLAG cpu.SF == 0
all_exec();
#undef JMPFLAG
#undef instr

#include "cpu/exec/template-end.h"