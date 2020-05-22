
#include "corewar.h"
#include <stdio.h>

void	op_sti(t_list *list, t_vm *x)
{
//	int ptr[4];
//	int i = 0;
//	int k = 0;
	int *ptr;

//	convert_arg(PROCESS->arg,1,list,x);
//	printf("arg0 = %d\n",PROCESS->arg[0]);
//	printf("arg1 = %d\n",PROCESS->arg[1]);
//	printf("arg2 = %d\n",PROCESS->arg[2]);
//	while (i < 4)
//	{
//		ptr[i] = PROCESS->arg[0];
//		PROCESS->arg[0] = PROCESS->arg[0] >> 8;
//		i++;
//	}//	POS;
//	while (1);
	if (PROCESS->t_arg[2] != REG_CODE)
	{

//	while (--i >= 0)//
//	{//
//		x->arene[move_pc(k,PROCESS->pc  - 1 + (PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD)] = ptr[i];//
//		k++;//
//	}//
//	printf("pc: %d\n",move_pc(PROCESS->pc - 1,PROCESS->arg[1] + PROCESS->arg[2]));
		ptr = (int*)(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
		printf("move_pc : %d\n",move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
//		printf(" arene : %p\n",x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD));
		*ptr = PROCESS->arg[0];
//		printf("*ptr : %d\n",*ptr);
		rev_str(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD),4);
//		*ptr = -1;
//		x->arene[move_pc(PROCESS->pc + 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD)] = *ptr;
	}
//		ptr = (int*)x->arene + PROCESS->arg[1] + PROCESS->arg[2];
	else
	{
		if (PROCESS->arg[2] > REG_NUMBER || PROCESS->arg[2] < 0)
			return;
		ptr = (int*)x->arene + move_pc(PROCESS->pc -1, PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) ;//
		rev_str(x->arene + move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) % IDX_MOD),4);
		*ptr = PROCESS->arg[0];
	//	k = 0;//
	//	i = 4;//
	//	while (--i >= 0)//
	//	{//
	//	x->arene[move_pc(k,PROCESS->pc -1 + PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]])] = ptr[i];//
	//	k++;//
	//	}//
	}
	//*ptr = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 :0);
}

