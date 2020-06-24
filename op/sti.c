
#include "corewar.h"
#include <stdio.h>

void	log_sti(t_list *list, int pc)
{
	if (PROCESS->t_arg[2] != REG_CODE)
	printf("P %4d | sti r%d %d %d\n%s %d %c %d %c %d %s %d%c\n", PROCESS->id, PROCESS->reg_num[0],PROCESS->arg[1],
	PROCESS->arg[2],"       | -> store to",PROCESS->arg[1], '+', PROCESS->arg[2], '=', PROCESS->arg[1] + PROCESS->arg[2], "(with pc and mod",pc,')');
	else
		printf("P %4d | sti r%d %d %d\n%s %d %c %d %c %d %s %d%c\n", PROCESS->id, PROCESS->reg_num[0],PROCESS->arg[1],
	PROCESS->reg[PROCESS->arg[2]],"       | -> store to",PROCESS->arg[1], '+', PROCESS->reg[PROCESS->arg[2]], '=', PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]], "(with pc and mod",pc,')');
	

}

void	op_sti(t_list *list, t_vm *x)
{
    unsigned    oct;
	int			tmp_pc;
    oct = 4;
	tmp_pc = 0;
//	printf("arg2: %d\n",PROCESS->t_arg[2]);
	if (PROCESS->t_arg[0] != REG_CODE)
		return;
		if (x->nb_c == 2810)
		printf("arg3 : %d\n",PROCESS->t_arg[2]);
	convert_arg(PROCESS->arg,0,list,x);
//	printf("arg2: %d\n",PROCESS->arg[2]);
	if (PROCESS->t_arg[2] != REG_CODE)
	tmp_pc = move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD);
	else
	{
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return ;
	tmp_pc = move_pc(PROCESS->pc - 1,(PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) % IDX_MOD);
	}
		if (x->log & LOG_OP)
		log_sti(list,tmp_pc);

	//if (x->nb_c > 2000)
//	printf("arg1 %d\narg2 %d\n",PROCESS->arg[1],PROCESS->arg[2]);
//	printf("idxmod : %d\n",(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD);
//	printf("pc %d\n",PROCESS->pc);
//	printf("tmp_pc1:%d\n",tmp_pc);
	tmp_pc = move_pc(tmp_pc,oct);
	//if (x->nb_c > 2000)
//	printf("tmp_pc2:%d\n",tmp_pc);
    while (oct)
    {
        tmp_pc = move_pc(tmp_pc, -1);
        x->arene[tmp_pc] = PROCESS->arg[0] >> (8 * (4 - oct));
        oct--;
    }
}
