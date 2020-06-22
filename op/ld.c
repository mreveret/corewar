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
	printf("P %4d | ld %d r%d\n", PROCESS->id, PROCESS->arg[0],
		PROCESS->reg_num[1]);
}

void	op_ld(t_list *list, t_vm *x)
{
	(void)x;
//	printf("arg0 = %d\n",PROCESS->arg[0]);
//	printf("arg1 = %d\n",PROCESS->arg[1]);
//	printf("------\n");
	convert_arg(PROCESS->arg,1,list,x);
	if (x->log & LOG_OP)
		log_ld(list);
	if (PROCESS->arg[1] >= REG_NUMBER || PROCESS->arg[1] < 0)
		return ;
//	printf("arg0 = %d\n",PROCESS->arg[0]);
//	printf("arg1 = %d\n",PROCESS->arg[1]);
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);
	}
