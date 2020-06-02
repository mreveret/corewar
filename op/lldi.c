/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:45 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:22:46 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_lldi(t_list *list, t_vm *x)
{
	//char b[4];
	int sum;
	sum = 0;
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return;
	convert_arg(PROCESS->arg,0,list,x);
	sum = PROCESS->arg[0] + PROCESS->arg[1];
	//PROCESS->reg[PROCESS->arg[2]] = ft_convert(x->arene + move_pc(PROCESS->pc -1,sum),4);
	PROCESS->reg[PROCESS->arg[2]] = ft_convert3(x,4,move_pc(PROCESS->pc -1,sum));
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
