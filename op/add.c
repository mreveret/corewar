/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:59 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 18:16:57 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_add(t_list *list, t_vm *x)
{
	(void)x;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]]
	+ PROCESS->reg[PROCESS->arg[1]];
	PROCESS->carry = 1;
}
