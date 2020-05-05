
#include "corewar.h"
#include <stdio.h>

void		op_zjmp(t_list *list, t_vm *x)
{
	(void)x;
	printf("carry = %d\n",PROCESS->carry);
	if (PROCESS->carry == 1)
		PROCESS->pc = move_pc(PROCESS->pc, PROCESS->arg[0]);
	else
	return;
}
