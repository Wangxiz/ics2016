#include "cpu/exec/template-start.h"

#define if_exec() { OPERAND_W(op_src, 1); }

#define else_exec() { OPERAND_W(op_src, 0); }

#define all_exec() \
static void do_execute() { \
	if(SETFLAG) if_exec()\
	else else_exec();\
	print_asm_template1();\
} \
make_instr_helper(rm) 

#define instr setne 	/* also setnz */
#define SETFLAG cpu.ZF == 0
all_exec();
#undef SETFLAG
#undef instr

#define instr setnbe	/* also seta */
#define SETFLAG cpu.ZF == 0 && cpu.CF == 0
all_exec();
#undef SETFLAG
#undef instr

#define instr setae		/* also setnb | setnc */
#define SETFLAG cpu.CF == 0
all_exec();
#undef SETFLAG
#undef instr

#define instr setb 		/* also setc | setnae */
#define SETFLAG cpu.CF == 1
all_exec();
#undef SETFLAG
#undef instr

#define instr setbe 	/* also setna */
#define SETFLAG cpu.CF == 1 || cpu.ZF == 1
all_exec();
#undef SETFLAG
#undef instr

#define instr sete 		/* also setz */
#define SETFLAG cpu.ZF == 1
all_exec();
#undef SETFLAG
#undef instr

#define instr setg 	/* also setnle */
#define SETFLAG cpu.ZF == 0 && cpu.SF == cpu.OF
all_exec();
#undef SETFLAG
#undef instr

#define instr setge 	/* also setnl */
#define SETFLAG cpu.SF == cpu.OF
all_exec();
#undef SETFLAG
#undef instr

#define instr setl 		/* also setnge */
#define SETFLAG cpu.SF != cpu.OF
all_exec();
#undef SETFLAG
#undef instr

#define instr setle 	/* also setng */
#define SETFLAG cpu.ZF == 1 || cpu.SF != cpu.OF
all_exec();
#undef SETFLAG
#undef instr

#define instr setno
#define SETFLAG cpu.OF == 0
all_exec();
#undef SETFLAG
#undef instr

#define instr setnp 	/* also setpo */
#define SETFLAG cpu.PF == 0
all_exec();
#undef SETFLAG
#undef instr

#define instr setns
#define SETFLAG cpu.SF == 0
all_exec();
#undef SETFLAG
#undef instr

#define instr seto
#define SETFLAG cpu.OF == 1
all_exec();
#undef SETFLAG
#undef instr

#define instr setp 		/* also setpe */
#define SETFLAG cpu.PF == 1
all_exec();
#undef SETFLAG
#undef instr

#define instr sets
#define SETFLAG cpu.SF == 1
all_exec();
#undef SETFLAG
#undef instr

#include "cpu/exec/template-end.h"
