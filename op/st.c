/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:33:28 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 17:35:09 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_st(t_list *list)
{
	printf("P %4d | st r%d %s%d\n", PROCESS->id, PROCESS->reg_num[0],
			(PROCESS->t_arg[1] == T_IND ? "" : "r"),
			(PROCESS->t_arg[1] == T_IND ?
			PROCESS->arg[1] : PROCESS->reg_num[1]));
}

void	op_st(t_list *list, t_vm *x)
{
	unsigned	oct;
	int			tmp_pc;

	oct = 5;
	tmp_pc = 0;
	if (x->log & LOG_OP)
		log_st(list);
	if (PROCESS->t_arg[1] == T_IND)
	{
		tmp_pc = move_pc(PROCESS->pc - 1, PROCESS->arg[1] % IDX_MOD);
		tmp_pc = move_pc(tmp_pc, oct - 1);
		while (--oct)
		{
			tmp_pc = move_pc(tmp_pc, -1);
			x->arene[tmp_pc] = PROCESS->arg[0] >> (8 * (4 - oct));
		}
	}
	else if (PROCESS->t_arg[1] == REG_CODE)
	{
		if (PROCESS->arg[1] >= REG_NUMBER || PROCESS->arg[1] < 0)
			return ;
		PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	}
	else
		return ;
}
