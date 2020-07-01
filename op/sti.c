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
	if (((t_process *)list->content)->t_arg[2] != REG_CODE)
	{
		printf("P %4d | sti r%d %d %d\n%s %d %c %d %c %d %s ", ((t_process *)list->content)->id,
				((t_process *)list->content)->reg_num[0], ((t_process *)list->content)->arg[1], ((t_process *)list->content)->arg[2],
				"       | -> store to", ((t_process *)list->content)->arg[1], '+', ((t_process *)list->content)->arg[2],
				'=', ((t_process *)list->content)->arg[1] + ((t_process *)list->content)->arg[2], "(with pc and mod");
		if (((t_process *)list->content)->pc - 1 + (((t_process *)list->content)->arg[1] + ((t_process *)list->content)->arg[2]) % IDX_MOD < 0)
			printf("%d)\n", pc - MEM_SIZE);
		else
			printf("%d)\n", pc);
	}
	else
	{
		printf("P %4d | sti r%d %d %d\n%s %d %c %d %c %d %s ", ((t_process *)list->content)->id,
				((t_process *)list->content)->reg_num[0], ((t_process *)list->content)->arg[1],
				((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]], "       | -> store to",
				((t_process *)list->content)->arg[1], '+', ((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]],
				'=', ((t_process *)list->content)->arg[1] + ((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]],
				"(with pc and mod");
		if (((t_process *)list->content)->pc - 1 + (((t_process *)list->content)->arg[1] + ((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]])
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
		x->arene[tmp_pc] = ((t_process *)list->content)->arg[0] >> (8 * (4 - oct));
		oct--;
	}
}

void	op_sti(t_list *list, t_vm *x)
{
	unsigned	oct;
	int			tmp_pc;

	oct = 4;
	tmp_pc = 0;
	if (((t_process *)list->content)->t_arg[0] != REG_CODE)
		return ;
	convert_arg(((t_process *)list->content)->arg, 0, list, x);
	if (((t_process *)list->content)->t_arg[2] != REG_CODE)
		tmp_pc = move_pc(((t_process *)list->content)->pc - 1,
				(((t_process *)list->content)->arg[1] + ((t_process *)list->content)->arg[2]) % IDX_MOD);
	else
	{
		if (((t_process *)list->content)->arg[2] >= REG_NUMBER || ((t_process *)list->content)->arg[2] < 0)
			return ;
		tmp_pc = move_pc(((t_process *)list->content)->pc - 1,
				(((t_process *)list->content)->arg[1] + ((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]]) % IDX_MOD);
	}
	if (x->log & LOG_OP)
		log_sti(list, tmp_pc);
	tmp_pc = move_pc(tmp_pc, oct);
	write_sti(oct, tmp_pc, x, list);
}
