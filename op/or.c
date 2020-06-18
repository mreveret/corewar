
#include "corewar.h"

void	log_or(t_list *list, t_vm *x)
{
	printf("P % 4d | or %d %d r%d\n", PROCESS->arg[0], PROCESS->arg[1],
		PROCESS->arg[2]);
}

void	op_or(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg,1,list,x);
	if (x->log & LOG_OP)
		log_or(list, x);
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] | PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
