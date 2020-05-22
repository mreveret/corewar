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
	int sum;
	sum = 0;
	convert_arg(PROCESS->arg,0,list,x);
//	if (PROCESS->t_arg[0] == REG_CODE)
//		sum = ft_convert(&x->arene[move_pc(PROCESS->arg[0], PROCESS->arg[1])],3);
//	else
	sum = ft_convert(x->arene + move_pc(PROCESS->arg[0], PROCESS->arg[1]),4);
	PROCESS->reg[PROCESS->arg[2]] = sum;
	PROCESS->carry = (sum == 0 ? 1 : 0);
}
