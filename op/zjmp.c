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
	printf("P %4d | zjmp %d %s\n", PROCESS->id, PROCESS->arg[0],
			(PROCESS->carry ? "OK" : "FAILED"));
}

void	op_zjmp(t_list *list, t_vm *x)
{
	(void)x;
	if (x->log & LOG_OP)
		log_zjmp(list);
	if (PROCESS->carry == 1)
	{
		PROCESS->pc = move_pc(PROCESS->pc - 1, PROCESS->arg[0] % IDX_MOD);
		x->add = 0;
	}
	else
		return ;
}
