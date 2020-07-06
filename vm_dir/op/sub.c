/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 10:01:12 by skpn              #+#    #+#             */
/*   Updated: 2020/07/01 19:04:30 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_sub(t_list *list)
{
	ft_printf("P %4d | sub r%d r%d r%d\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->reg_num[0],
			((t_p *)list->content)->reg_num[1],
			((t_p *)list->content)->reg_num[2]);
}

void	op_sub(t_list *list, t_vm *x)
{
	(void)x;
	if (x->log & LOG_OP)
		log_sub(list);
	if (((t_p *)list->content)->arg[2] >= REG_NUMBER ||
			((t_p *)list->content)->arg[2] < 0)
		return ;
	((t_p *)list->content)->reg[((t_p *)list->content)->arg[2]] =
		((t_p *)list->content)->arg[0] - ((t_p *)list->content)->arg[1];
	((t_p *)list->content)->carry =
		(((t_p *)list->content)->reg[((t_p *)list->content)->arg[2]] ==
		0 ? 1 : 0);
}
