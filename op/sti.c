
#include "corewar.h"
#include <stdio.h>

void	op_sti(t_list *list, t_vm *x)
{
    unsigned    oct;
	int			tmp_pc;
    oct = 4;
	tmp_pc = 0;
	convert_arg(PROCESS->arg,0,list,x);
	tmp_pc = move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD);
	tmp_pc = move_pc(tmp_pc,oct);
    while (oct)
    {
        tmp_pc = move_pc(tmp_pc, -1);
        x->arene[tmp_pc] = PROCESS->arg[0] >> (8 * (4 - oct));
        oct--;
    }
}
