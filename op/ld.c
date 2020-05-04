/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:51 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 18:31:29 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ld(t_list *list, t_vm *x)
{
	(void)x;
	convert_arg(PROCESS->arg,1,list,x);
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);
	}
/*	if (PROCESS->t_arg[1] != 1)
	return;
	if (PROCESS->t_arg[0] == 2)
	{
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);
	}
	else if (PROCESS->t_arg[0] == 3)
	{
	PROCESS->reg[PROCESS->arg[1]] = x->arene[PROCESS->pc + indx_mod(&PROCESS->arg[0])];
	PROCESS->carry = (x->arene[PROCESS->pc + indx_mod(&PROCESS->arg[0])] == 0 ? 1 : 0);
	}
	else
		return;
}*/
