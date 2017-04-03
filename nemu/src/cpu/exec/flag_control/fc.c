#include "cpu/exec/helper.h"

make_helper(cld) {
	print_asm("cld");
	cpu.DF = 0;
	return 1;
}

make_helper(std) {
	print_asm("std");
	cpu.DF = 1;
	return 1;
}

make_helper(clc) {
	print_asm("clc");
	cpu.CF = 0;
	return 1;
}

make_helper(stc) {
	print_asm("stc");
	cpu.CF = 1;
	return 1;
}

make_helper(cmc) {
	print_asm("cmc");
	cpu.CF = ~cpu.CF;
	return 1;
}

make_helper(cli) {
	print_asm("cli");
	cpu.IF = 0;
	return 1;
}

make_helper(sti) {
	print_asm("sti");
	cpu.IF = 1;
	return 1;
}
