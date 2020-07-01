/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:59 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/19 10:01:02 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_add(t_list *list)
{
	printf("P %4d | add r%d r%d r%d\n", ((t_process *)list->content)->id, ((t_process *)list->content)->reg_num[0],
			((t_process *)list->content)->reg_num[1], ((t_process *)list->content)->reg_num[2]);
}

void	op_add(t_list *list, t_vm *x)
{
	(void)x;
	if (x->log & LOG_OP)
		log_add(list);
	if (((t_process *)list->content)->arg[2] >= REG_NUMBER || ((t_process *)list->content)->arg[2] < 0)
		return ;
	((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]] = ((t_process *)list->content)->arg[0] + ((t_process *)list->content)->arg[1];
	((t_process *)list->content)->carry = (((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]] == 0 ? 1 : 0);
}
