/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:40 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:20:42 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_lld(t_list *list, t_vm *x)
{
	convert_arg(PROCESS->arg,0,list,x);
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);
}
