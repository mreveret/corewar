
#include "corewar.h"

void		op_zjmp(t_list *list, t_vm *x)
{
	(void)x;
	if (PROCESS->carry == 1)
		PROCESS->pc = PROCESS->arg[0] % MEM_SIZE;
	else 
	PROCESS->pc = PROCESS->pc;
}
