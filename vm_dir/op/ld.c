/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:51 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 18:52:49 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_ld(t_list *list)
{
	ft_printf("P %4d | ld %d r%d\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->arg[0], ((t_p *)list->content)->reg_num[1]);
}

void	op_ld(t_list *list, t_vm *x)
{
	(void)x;
	convert_arg(((t_p *)list->content)->arg, 1, list, x);
	if (x->log & LOG_OP)
		log_ld(list);
	if (((t_p *)list->content)->arg[1] >= REG_NUMBER ||
			((t_p *)list->content)->arg[1] < 0)
		return ;
	((t_p *)list->content)->reg[((t_p *)list->content)->arg[1]] =
		((t_p *)list->content)->arg[0];
	((t_p *)list->content)->carry = (((t_p *)list->content)->arg[0] ==
		0 ? 1 : 0);
}
