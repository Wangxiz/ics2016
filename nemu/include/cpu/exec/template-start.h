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

#define MEM_R_DWORD(addr) swaddr_read((addr), 4)
#define MEM_R_WORD(addr) swaddr_read((addr), 2)
#define MEM_R_BYTE(addr) swaddr_read((addr), 1)

#define MEM_W_DWORD(addr, data) swaddr_write((addr), 4, (data))
#define MEM_W_WORD(addr, data) swaddr_write((addr), 2, (data))
#define MEM_W_BYTE(addr, data) swaddr_write((addr), 1, (data))

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

#define PUSH_DWORD(data) ({ cpu.esp -= 4; MEM_W_DWORD(cpu.esp, (data)); })
#define PUSH_WORD(data) ({ cpu.esp -= 2; MEM_W_WORD(cpu.esp, (data) & 0xffff); })
#define PUSH_BYTE(data) ({ cpu.esp -= 4; MEM_W_DWORD(cpu.esp, (unsigned) (int) (signed char) ((data) & 0xff)); }) // push BTYE is just push DWORD (sign-extended)

#define POP_DWORD() ({ uint32_t ret = MEM_R_DWORD(cpu.esp); cpu.esp += 4; ret; })
#define POP_WORD() ({ uint32_t ret = MEM_R_WORD(cpu.esp); cpu.esp += 2; ret; })