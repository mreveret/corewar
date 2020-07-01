/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 10:01:18 by skpn              #+#    #+#             */
/*   Updated: 2020/06/19 10:01:29 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_xor(t_list *list)
{
	printf("P %4d | xor %d %d r%d\n", ((t_process *)list->content)->id, ((t_process *)list->content)->arg[0],
			((t_process *)list->content)->arg[1], ((t_process *)list->content)->reg_num[2]);
}

void	op_xor(t_list *list, t_vm *x)
{
	convert_arg(((t_process *)list->content)->arg, 1, list, x);
	if (x->log & LOG_OP)
		log_xor(list);
	if (((t_process *)list->content)->arg[2] >= REG_NUMBER || ((t_process *)list->content)->arg[2] < 0)
		return ;
	((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]] = ((t_process *)list->content)->arg[0] ^ ((t_process *)list->content)->arg[1];
	((t_process *)list->content)->carry = (((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]] == 0 ? 1 : 0);
}
