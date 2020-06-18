
#include "corewar.h"
#include <stdio.h>

void	log_zjmp(t_list *list, t_vm *x)
{
	(void)x;
	printf("P % 4d | zjmp %d %s\n",PROCESS->id, PROCESS->arg[0],
		(PROCESS->carry ? "OK" : "FAIL"));
}

void		op_zjmp(t_list *list, t_vm *x)
{
	(void)x;
//	printf("carry = %d\n",PROCESS->carry);
//	printf("arg = %d\n",PROCESS->arg[0]);
	if (x->log & LOG_OP)
		log_zjmp(list, x);
	if (PROCESS->carry == 1)
	{
		PROCESS->pc = move_pc(PROCESS->pc - 1, PROCESS->arg[0]);
//		printf("pcjmp : %d\n",PROCESS->pc);
		x->add = 0;
	}
	else
		return;
}
