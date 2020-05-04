
#include "corewar.h"
#include <stdio.h>

void	op_sti(t_list *list, t_vm *x)
{
	int *ptr;
	convert_arg(PROCESS->arg,1,list,x);
	POS;
//	while (1);
	if (PROCESS->t_arg[2] != REG_CODE)
		ptr = (int*)x->arene + move_pc(PROCESS->arg[1], PROCESS->arg[2]);
//		ptr = (int*)x->arene + PROCESS->arg[1] + PROCESS->arg[2];
	else
	{
		if (PROCESS->arg[2] > REG_NUMBER || PROCESS->arg[2] < 0)
			return;
		ptr = (int*)x->arene + move_pc(PROCESS->arg[1], PROCESS->reg[PROCESS->arg[2]]);
	}
	*ptr = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] ? 1 :0);
}

