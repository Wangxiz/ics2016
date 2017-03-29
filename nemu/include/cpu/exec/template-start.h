#include "cpu/exec/helper.h"

#if DATA_BYTE == 1

#define SUFFIX b
#define DATA_TYPE uint8_t
#define DATA_TYPE_S int8_t

#elif DATA_BYTE == 2

#define SUFFIX w
#define DATA_TYPE uint16_t
#define DATA_TYPE_S int16_t

#elif DATA_BYTE == 4

#define SUFFIX l
#define DATA_TYPE uint32_t
#define DATA_TYPE_S int32_t

#else

#error unknown DATA_BYTE

#endif

#define REG(index) concat(reg_, SUFFIX) (index)
#define REG_NAME(index) concat(regs, SUFFIX) [index]

#define MEM_R(addr) swaddr_read(addr, DATA_BYTE)
#define MEM_W(addr, data) swaddr_write(addr, DATA_BYTE, data)

#define OPERAND_W(op, src) concat(write_operand_, SUFFIX) (op, src)

#define MSB(n) ((DATA_TYPE)(n) >> ((DATA_BYTE << 3) - 1))

#define UPDATE_EFLAGS_PF(val) \
	int i; \
	cpu.PF = 1; \
	for(i = 0; i < 8; ++i) cpu.PF ^= (val & (1 << i)) >> i;
#define UPDATE_EFLAGS_SF(val) cpu.SF = MSB(val)
#define UPDATE_EFLAGS_ZF(val) cpu.ZF = (val == 0)

#define SUB_CF(n, m) ((n < m) ? (cpu.CF = 1) : (cpu.CF = 0))
#define SUB_OF(n, m, t) (((MSB(t) ^ MSB(n)) && (MSB(n) ^ MSB(m))) ? (cpu.OF = 1) : (cpu.OF = 0))

#define SET_EFLAGS_CF(val) cpu.CF = val
#define SET_EFLAGS_OF(val) cpu.OF = val