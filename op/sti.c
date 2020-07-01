/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:27:53 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/01 17:31:11 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_sti(t_list *list, int pc)
{
	if (PROCESS->t_arg[2] != REG_CODE)
	{
		printf("P %4d | sti r%d %d %d\n%s %d %c %d %c %d %s ", PROCESS->id,
				PROCESS->reg_num[0], PROCESS->arg[1], PROCESS->arg[2],
				"       | -> store to", PROCESS->arg[1], '+', PROCESS->arg[2],
				'=', PROCESS->arg[1] + PROCESS->arg[2], "(with pc and mod");
		if (PROCESS->pc - 1 + (PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD < 0)
			printf("%d)\n", pc - MEM_SIZE);
		else
			printf("%d)\n", pc);
	}
	else
	{
		printf("P %4d | sti r%d %d %d\n%s %d %c %d %c %d %s ", PROCESS->id,
				PROCESS->reg_num[0], PROCESS->arg[1],
				PROCESS->reg[PROCESS->arg[2]], "       | -> store to",
				PROCESS->arg[1], '+', PROCESS->reg[PROCESS->arg[2]],
				'=', PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]],
				"(with pc and mod");
		if (PROCESS->pc - 1 + (PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]])
				% IDX_MOD >= 0)
			printf("%d)\n", pc);
		else
			printf("%d)\n", pc - MEM_SIZE);
	}
}

void	write_sti(int oct, int tmp_pc, t_vm *x, t_list *list)
{
	while (oct)
	{
		tmp_pc = move_pc(tmp_pc, -1);
		x->arene[tmp_pc] = PROCESS->arg[0] >> (8 * (4 - oct));
		oct--;
	}
}

void	op_sti(t_list *list, t_vm *x)
{
	unsigned	oct;
	int			tmp_pc;

	oct = 4;
	tmp_pc = 0;
	if (PROCESS->t_arg[0] != REG_CODE)
		return ;
	convert_arg(PROCESS->arg, 0, list, x);
	if (PROCESS->t_arg[2] != REG_CODE)
		tmp_pc = move_pc(PROCESS->pc - 1,
				(PROCESS->arg[1] + PROCESS->arg[2]) % IDX_MOD);
	else
	{
		if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
			return ;
		tmp_pc = move_pc(PROCESS->pc - 1,
				(PROCESS->arg[1] + PROCESS->reg[PROCESS->arg[2]]) % IDX_MOD);
	}
	if (x->log & LOG_OP)
		log_sti(list, tmp_pc);
	tmp_pc = move_pc(tmp_pc, oct);
	write_sti(oct, tmp_pc, x, list);
}
