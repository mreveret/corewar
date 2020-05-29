
#include "corewar.h"

void	op_sub(t_list *list, t_vm *x)
{
	(void)x;
		if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
			return;
		//printf("arg0 = %d\n",PROCESS->arg[0]);
		//printf("arg1 = %d\n",PROCESS->arg[1]);
		//printf("arg2 = %d\n",PROCESS->arg[2]);
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] - PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
