
#include "corewar.h"

void	op_sti(t_list *list, t_vm *x)
{
	x->arene[PROCESS->arg[1] + PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]];
}

