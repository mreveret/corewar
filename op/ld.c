/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:51 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/19 10:58:12 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_ld(t_list *list)
{
	printf("P %4d | ld %d r%d\n", ((t_process *)list->content)->id, ((t_process *)list->content)->arg[0],
			((t_process *)list->content)->reg_num[1]);
}

void	op_ld(t_list *list, t_vm *x)
{
	(void)x;
	convert_arg(((t_process *)list->content)->arg, 1, list, x);
	if (x->log & LOG_OP)
		log_ld(list);
	if (((t_process *)list->content)->arg[1] >= REG_NUMBER || ((t_process *)list->content)->arg[1] < 0)
		return ;
	((t_process *)list->content)->reg[((t_process *)list->content)->arg[1]] = ((t_process *)list->content)->arg[0];
	((t_process *)list->content)->carry = (((t_process *)list->content)->arg[0] == 0 ? 1 : 0);
}
