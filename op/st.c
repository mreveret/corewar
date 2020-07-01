/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:33:28 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 19:03:58 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_st(t_list *list)
{
	printf("P %4d | st r%d %s%d\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->reg_num[0],
			(((t_p *)list->content)->t_arg[1] == T_IND ? "" : "r"),
			(((t_p *)list->content)->t_arg[1] == T_IND ?
			((t_p *)list->content)->arg[1]
			: ((t_p *)list->content)->reg_num[1]));
}

void	op_st(t_list *list, t_vm *x)
{
	unsigned	oct;
	int			tmp_pc;

	oct = 5;
	tmp_pc = 0;
	if (x->log & LOG_OP)
		log_st(list);
	if (((t_p *)list->content)->t_arg[1] == T_IND)
	{
		tmp_pc = move_pc(((t_p *)list->content)->pc - 1,
				((t_p *)list->content)->arg[1] % IDX_MOD);
		tmp_pc = move_pc(tmp_pc, oct - 1);
		while (--oct)
		{
			tmp_pc = move_pc(tmp_pc, -1);
			x->arene[tmp_pc] =
				((t_p *)list->content)->arg[0] >> (8 * (4 - oct));
		}
	}
	else if (((t_p *)list->content)->t_arg[1] == REG_CODE)
	{
		if (((t_p *)list->content)->arg[1] >=
				REG_NUMBER || ((t_p *)list->content)->arg[1] < 0)
			return ;
		((t_p *)list->content)->reg[((t_p *)list->content)->arg[1]] =
			((t_p *)list->content)->arg[0];
	}
	else
		return ;
}
