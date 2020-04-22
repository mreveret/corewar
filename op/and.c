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
	(void)x;
	PROCESS->reg[PROCESS->arg[2]] = PROCESS->reg[PROCESS->arg[0]] & PROCESS->reg[PROCESS->arg[1]];
	PROCESS->carry = 1;
}
