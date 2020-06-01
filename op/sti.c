
#include "corewar.h"
#include <stdio.h>

void	op_sti(t_list *list, t_vm *x)
{
	int *ptr;

		convert_arg(PROCESS->arg,0,list,x);
//		printf("move_pc : %d\n",move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
//		printf("arg1 %d\n",PROCESS->arg[1]);
//		printf("pc %d\n",PROCESS->pc);
//		printf ("idxmod %d\n",PROCESS->pc -1 +(PROCESS->arg[1] + PROCESS->arg[2] % IDX_MOD));
	if (PROCESS->t_arg[2] != REG_CODE)
	{

		ptr = (int*)(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
//		printf("move_pc : %d\n",move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
		*ptr = PROCESS->arg[0];
		rev_str(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD),4);
	}
	else
	{
		if (PROCESS->arg[2] > REG_NUMBER || PROCESS->arg[2] < 0)
			return;
		
//		printf("arg2 %d\n",PROCESS->arg[2]);
		ptr = (int*)(x->arene + move_pc(PROCESS->pc -1, (PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) % IDX_MOD)) ;//
		*ptr = PROCESS->arg[0];
		rev_str(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) % IDX_MOD),4);
	}
//	printf("arg[0]:%hd\n",(short)PROCESS->arg[0]);
//	printf("carry avant : %d\n",PROCESS->carry);
//	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 :0);
//	printf("carry apres : %d\n",PROCESS->carry);
}

