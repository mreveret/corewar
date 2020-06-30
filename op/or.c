/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 10:01:40 by skpn              #+#    #+#             */
/*   Updated: 2020/06/19 10:01:41 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_or(t_list *list)
{
	printf("P %4d | or %d %d r%d\n", PROCESS->id, PROCESS->arg[0],
		PROCESS->arg[1], PROCESS->reg_num[2]);
}

void	op_or(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg, 1, list, x);
	if (x->log & LOG_OP)
		log_or(list);
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return ;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] | PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
