
#include "corewar.h"

void	op_xor(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg,1,list,x);
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return ;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] ^ PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}