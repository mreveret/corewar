
#include "corewar.h"

void	op_xor(t_list *list, t_vm *x)
{
	(void)x;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]] ^ PROCESS->reg[PROCESS->arg[1]];
	PROCESS->carry = 1;
}
