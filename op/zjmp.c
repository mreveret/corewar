/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:31:45 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/01 17:32:09 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_zjmp(t_list *list)
{
	printf("P %4d | zjmp %d %s\n", ((t_process *)list->content)->id, ((t_process *)list->content)->arg[0],
			(((t_process *)list->content)->carry ? "OK" : "FAILED"));
}

void	op_zjmp(t_list *list, t_vm *x)
{
	(void)x;
	if (x->log & LOG_OP)
		log_zjmp(list);
	if (((t_process *)list->content)->carry == 1)
	{
		((t_process *)list->content)->pc = move_pc(((t_process *)list->content)->pc - 1, ((t_process *)list->content)->arg[0] % IDX_MOD);
		x->add = 0;
	}
	else
		return ;
}
