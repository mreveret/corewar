/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:21 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/17 16:46:14 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	op_live(t_list *list, t_vm *x)
{
//	printf("arg: %d\n",PROCESS->arg[0]);
	PROCESS->alive = 1;
	PROCESS->last_live_cycle = x->nb_c;
	x->nbr_live++;
	if (PROCESS->arg[0] > (-1 * x->nbp) && PROCESS->arg[0] < 0)
	{
		x->winner = PROCESS->arg[0] * -1;
		printf("winner: %d\n", x->winner);
		if (x->log & LOG_LIVE)
			printf("Player %s is said to be alive.\n",
				x->p[x->winner].header.prog_name);
	}
//	printf("ALIVE player %d\n",x->winner);
}
