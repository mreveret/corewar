/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:59 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/18 17:58:38 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_add(t_list *list, t_vm *x)
{
	(void)x;
	printf("P % 4d | add r%d r%d r%d\n",PROCESS->id, PROCESS->arg[0] , PROCESS->arg[1],
		PROCESS->arg[2] + 1);
}

void	op_add(t_list *list, t_vm *x)
{
	(void)x;
	if (x->log & LOG_OP)
		log_add(list, x);
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return;
//		//printf("arg0:%d\n",PROCESS->arg[0]);
//		//printf("arg1:%d\n",PROCESS->arg[1]);
//		//printf("arg2:%d\n",PROCESS->arg[2]);
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] + PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
