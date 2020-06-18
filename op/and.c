/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:55 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/18 17:58:31 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_and(t_list *list, t_vm *x)
{
	(void)x;
	printf("P % 4d | and %d %d r%d\n", PROCESS->id,PROCESS->arg[0], PROCESS->arg[1],
		PROCESS->arg[2] + 1);
}

void	op_and(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg,1,list,x);
	if (x->log & LOG_OP)
		log_and(list, x);
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] & PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
