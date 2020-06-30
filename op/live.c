/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:21 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/19 10:02:41 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_live(t_list *list)
{
	printf("P %4d | live %d\n", PROCESS->id, PROCESS->arg[0]);
}

void	op_live(t_list *list, t_vm *x)
{
	PROCESS->alive = 1;
	PROCESS->last_live_cycle = x->nb_c;
	x->nbr_live++;
	if (x->log & LOG_OP)
		log_live(list);
	if (PROCESS->arg[0] >= (-1 * x->nbp) && PROCESS->arg[0] < 0)
	{
		x->winner = PROCESS->arg[0] * -1;
		if (x->log & LOG_LIVE)
			printf("Player %d (%s) is said to be alive\n",x->winner,
					x->p[x->winner - 1].header.prog_name);
	}
}
