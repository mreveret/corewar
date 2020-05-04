
#include "corewar.h"

void	op_or(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg,1,list,x);
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]] | PROCESS->reg[PROCESS->arg[1]];
	PROCESS->carry = 1;
}
