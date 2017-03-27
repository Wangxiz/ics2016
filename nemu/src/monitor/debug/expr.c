#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256,

	/* TODO: Add more token types */
	DEC, HEX, EQ, NE, LE, GE, LT, GT, AND, OR, NOT, REG, NS, DR
};

static struct rule {
	char *regex;
	int token_type;
	int op_level;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 * 数值越大，优先级越低
	 */

	{" +",	NOTYPE, 0},					// spaces			->
	{"\\+", '+', 5},					// plus				->
	{"-", '-', 5},						// minus			->
	{"\\*", '*', 4},					// multiplication	->
	{"/", '/', 4},						// division			->
	{"\\(", '(', 1},					// left par			->
	{"\\)", ')', 1},					// right par		->
	{"0[xX][0-9a-fA-F]+", HEX, 1},		// hex numbers		->
	{"[0-9]+", DEC, 1},					// dec numbers		->
	{"==", EQ, 7},						// equal			->
	{"!=", NE, 7},						// not equal		->
	{"<=", LE, 6},						// less or equal	->
	{">=", GE, 6},						// greater or equal	->
	{"<", LT, 6},						// less				->
	{">", GT, 6},						// greater			->
	{"&&", AND, 11},					// and				->
	{"\\|\\|", OR, 12},					// or				->
	{"!", NOT, 2},						// not				<-
	{"\\$eax|\\$edx|\\$ecx|\\$ebx|\\$ebp|\\$esi|\\$edi|\\$esp|\\$ax|\\$dx|\\$cx|\\$bx|\\$bp|\\$si|\\$di|\\$sp|\\$ah|\\$dh|\\$ch|\\$bh|\\$al|\\$dl|\\$cl|\\$bl|\\$eip", REG, 1},		// registers	->
	{"-", NS, 2},						// negative sign	<-
	{"\\*", DR, 2}						// dereference		<-
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	int op_level;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */
				
				tokens[nr_token].type = rules[i].token_type;
				tokens[nr_token].op_level = rules[i].op_level;

				switch(rules[i].token_type) {
					case '+': case '/': case AND: case OR: case NOT:
					case EQ: case NE: case LE: case GE: case LT: case GT: case '(': case ')': break;
					case '-':
						if(nr_token == 0 || !(tokens[nr_token - 1].type == ')' || tokens[nr_token - 1].type == DEC || tokens[nr_token - 1].type == HEX || tokens[nr_token - 1].type == REG)) {
							tokens[nr_token].type = NS;
							tokens[nr_token].op_level = 2;
						}
						break;
					case '*':
						if(nr_token == 0 || !(tokens[nr_token - 1].type == ')' || tokens[nr_token - 1].type == DEC || tokens[nr_token - 1].type == HEX || tokens[nr_token - 1].type == REG)) {
							tokens[nr_token].type = DR;
							tokens[nr_token].op_level = 2;
						}
						break;
					case DEC: case HEX: case REG:
						strncpy(tokens[nr_token].str, substr_start, substr_len);
						tokens[nr_token].str[substr_len] = '\0';
						break;
					case NOTYPE:
						nr_token--;
						break;
					default: panic("please implement me");
				}
				nr_token++;
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int p, int q) {
	if(tokens[p].type != '(' || tokens[q].type != ')') return false;	// 检查表达式是否被括号包围
	int count = 0, i;
	for(i = p + 1; i < q; ++i) {	// 检查最外围的括号中间的表达式是否括号匹配
		if(tokens[i].type == ')') count--;
		if(tokens[i].type == '(') count++;
		if(count < 0) return false;
	}
	return count == 0;
}

uint32_t get_dominantop(int p, int q) {
	int in_par = 0, i;
	int max_level = 1;
	for(i = p; i <= q; ++i) {
		if(tokens[i].type == '(') in_par++;
		if(tokens[i].type == ')') in_par--;
		if(in_par) continue;
		if(tokens[i].op_level > max_level) max_level = tokens[i].op_level;
	}
	for(i = q; i >= p; --i) {
		if(tokens[i].type == '(') in_par++;
		if(tokens[i].type == ')') in_par--;
		if(in_par) continue;
		if(tokens[i].op_level == max_level) {
			if(max_level == 2) {
				while(i > p && tokens[i - 1].op_level == max_level) {
					i--;
				}
			}
			return i;
		}
	}
	return 0;
}

uint32_t my_atoi(char *arg) {
	uint32_t val = 0, i;
	for(i = 0; i < strlen(arg); ++i) {
		val = val * 10 + arg[i] - '0';
	}
	return val;
}

uint32_t my_htoi(char *arg) {
	uint32_t val = 0, i;
	for(i = 0; i < strlen(arg); ++i) {
		if(arg[i] >= '0' && arg[i] <= 9)
			val = val * 16 + arg[i] - '0';
		else if(arg[i] >= 'a' && arg[i] <= 'f')
			val = val * 16 + arg[i] - 'a';
		else if(arg[i] >= 'A' && arg[i] <= 'F')
			val = val * 16 + arg[i] - 'A';
	}
	return val;
}

uint32_t eval(int p, int q) {
	if(p > q) {
		/* Bad expression */
//		printf("Bad expression.\n");
//		assert(0);
		return 0;
	}
	else if(p == q) { 
		/* Single token.
		 * For now this token should be a number. 
		 * Return the value of the number.
		 */
		uint32_t val = 0;
		if(tokens[p].type == REG) {
			char *reg = tokens[p].str + 1;
//			printf("%s\n", reg);
			if(strcmp(reg, "eip") == 0) {
//				printf("eip:%d\n",cpu.eip);
				return cpu.eip;
			}
			else {
				int i;
				for(i = 0; i < 8; ++i) {
					if(strcmp(regsl[i], reg) == 0) {
						return cpu.gpr[i]._32;
					}
				}
				if(i == 8) return 0;
			}
		}
		else if(tokens[p].type == DEC) {
			return my_atoi(tokens[p].str);
		}
		else if(tokens[p].type == HEX) {
			printf("%s\n", tokens[p].str);
			return my_htoi(tokens[p].str + 2);
		}
		return val;
	}
	else if(check_parentheses(p, q) == true) {
		/* The expression is surrounded by a matched pair of parentheses. 
		 * If that is the case, just throw away the parentheses.
		 */
		return eval(p + 1, q - 1); 
	}
	else {
		// op = the position of dominant operator in the token expression;
		uint32_t op = get_dominantop(p, q);
		printf("op:%d\n",op);
		uint32_t val1 = 0, val2 = 0;
		if(tokens[op].type == NOT || tokens[op].type == NS || tokens[op].type == DR) {
			val1 = eval(op + 1, q);
		}
		else {
			val1 = eval(p, op - 1);
			val2 = eval(op + 1, q);
		}
		switch(tokens[op].type) {
			case '+': return val1 + val2;
			case '-': return val1 - val2;
			case '*': return val1 * val2;
			case '/': return val1 / val2;
			case EQ: return val1 == val2;
			case NE: return val1 != val2;
			case LE: return val1 <= val2;
			case GE: return val1 >= val2;
			case LT: return val1 < val2;
			case GT: return val1 > val2;
			case AND: return val1 && val2;
			case OR: return val1 || val2;
			case NOT: return !val1;
			case NS: return -val1;
			case DR: return swaddr_read(val1, 4);
			default: assert(0);
		}
	}
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	/* TODO: Insert codes to evaluate the expression. */
	*success = true;
	return eval(0, nr_token - 1);
	panic("please implement me");
	return 1024;
}

