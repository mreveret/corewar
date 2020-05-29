/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:21 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 18:24:39 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	op_live(t_list *list, t_vm *x)
{
	if (PROCESS->arg[0] > x->nbp || PROCESS->arg[0] <= 0)
	{
	PROCESS->alive = 1;
	x->nbr_live++;
	return;
	}
	else
	x->p[PROCESS->arg[0]].alive = 1;
	PROCESS->alive = 1;
	x->last_alive = PROCESS->arg[0];
	//printf("ALIVE player %d\n",x->last_alive);
	x->nbr_live++;
}
