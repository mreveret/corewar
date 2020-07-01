/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:40 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:20:42 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_lld(t_list *list)
{
	printf("P %4d | lld %d r%d\n", ((t_process *)list->content)->id, ((t_process *)list->content)->arg[0],
			((t_process *)list->content)->reg_num[1]);
}

void	op_lld(t_list *list, t_vm *x)
{
	convert_arg(((t_process *)list->content)->arg, 0, list, x);
	if (x->log & LOG_OP)
		log_lld(list);
	((t_process *)list->content)->reg[((t_process *)list->content)->arg[1]] = ((t_process *)list->content)->arg[0];
	((t_process *)list->content)->carry = (((t_process *)list->content)->arg[0] == 0 ? 1 : 0);
}
