/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:21 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 18:56:49 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_live(t_list *list)
{
	printf("P %4d | live %d\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->arg[0]);
}

void	op_live(t_list *list, t_vm *x)
{
	((t_p *)list->content)->alive = 1;
	((t_p *)list->content)->last_live_cycle = x->nb_c;
	x->nbr_live++;
	if (x->log & LOG_OP)
		log_live(list);
	if (((t_p *)list->content)->arg[0] >= (-1 * x->nbp) &&
			((t_p *)list->content)->arg[0] < 0)
	{
		x->winner = ((t_p *)list->content)->arg[0] * -1;
		if (x->log & LOG_LIVE)
			printf("Player %d (%s) is said to be alive\n", x->winner,
					x->p[x->winner - 1].header.prog_name);
	}
}
