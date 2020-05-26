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
	int sum;
	char b[4];
	sum = 0;
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return;
	convert_arg(PROCESS->arg,0,list,x);
		sum = PROCESS->arg[0] + PROCESS->arg[1];
		sum = indx_mod(&sum);
		printf("sum %d\n",sum);
	
	PROCESS->reg[PROCESS->arg[2]] = ft_convert(memcpy(x->arene + move_pc(PROCESS->pc -1,sum),b,4),4);
	bzero(b,4);
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
