
#include "corewar.h"
#include <stdio.h>

void	op_sti(t_list *list, t_vm *x)
{
	int *ptr;

	if (PROCESS->t_arg[2] != REG_CODE)
	{

		ptr = (int*)(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
		printf("move_pc : %d\n",move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
		*ptr = PROCESS->arg[0];
		rev_str(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD),4);
	}
	else
	{
		if (PROCESS->arg[2] > REG_NUMBER || PROCESS->arg[2] < 0)
			return;
		ptr = (int*)x->arene + move_pc(PROCESS->pc -1, PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) ;//
		rev_str(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) % IDX_MOD),4);
		*ptr = PROCESS->arg[0];
	}
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 :0);
}

