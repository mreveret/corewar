/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:55 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:22:57 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_and(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg,1,list,x);
	if (PROCESS->arg[2] >= REG_NUMBER || PROCESS->arg[2] < 0)
		return;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->arg[0] & PROCESS->arg[1];
	PROCESS->carry = (PROCESS->reg[PROCESS->arg[2]] == 0 ? 1 : 0);
}
