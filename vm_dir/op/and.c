/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:55 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 19:02:44 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_and(t_list *list)
{
	printf("P %4d | and %d %d r%d\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->arg[0], ((t_p *)list->content)->arg[1],
			((t_p *)list->content)->reg_num[2]);
}

void	op_and(t_list *list, t_vm *x)
{
	convert_arg(((t_p *)list->content)->arg, 1, list, x);
	if (x->log & LOG_OP)
		log_and(list);
	if (((t_p *)list->content)->arg[2] >= REG_NUMBER ||
			((t_p *)list->content)->arg[2] < 0)
		return ;
	((t_p *)list->content)->reg[((t_p *)list->content)->arg[2]] =
		((t_p *)list->content)->arg[0] & ((t_p *)list->content)->arg[1];
	((t_p *)list->content)->carry =
		(((t_p *)list->content)->reg[((t_p *)list->content)->arg[2]] ==
		0 ? 1 : 0);
}
