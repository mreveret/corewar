
#include "corewar.h"

void	op_sub(t_list *list, t_vm *x)
{
	(void)x;
	int i;
	i = -1;
	while (++i < 3)
	{
		if (PROCESS->arg[i] > REG_NUMBER || PROCESS->arg[i] < 0)
			return;
	}
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]]
	- PROCESS->reg[PROCESS->arg[1]];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] = 0 ? 1 : 0);
}

//	(void)x;
//	PROCESS->reg[PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]] - PROCESS->reg[PROCESS->arg[1]];
//	PROCESS->carry = 1;ii
//}
