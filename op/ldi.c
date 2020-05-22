/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:21:40 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:21:41 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	op_ldi(t_list *list, t_vm *x)
{
	(void)x;
	int sum;
	char b[4];
	sum = 0;
	int i = -1;
	while (++i< 2)
//	convert_arg(PROCESS->arg,1,list,x);
//	if (PROCESS->t_arg[0] == REG_CODE)
//		sum = ft_convert(&x->arene[move_pc(PROCESS->pc + PROCESS->arg[0], PROCESS->arg[1])],3);
//	else
		sum = PROCESS->arg[0] + PROCESS->arg[1];
		printf("sum %d\n",sum);
		printf("movepc %d\n",move_pc(PROCESS->pc - 1,sum));
	//PROCESS->reg[PROCESS->arg[2]] = sum;
	PROCESS->reg[PROCESS->arg[2]] = ft_convert(memcpy(x->arene + move_pc(PROCESS->pc -1,sum),b,4),4);
	PROCESS->carry = (sum == 0 ? 1 : 0);
}
