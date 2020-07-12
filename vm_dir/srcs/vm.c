/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:18:17 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/30 16:45:22 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

int			stop_vm(t_vm *x)
{
	int		nb_alive_p;
	t_list	*list;

	list = x->lst_process;
	nb_alive_p = 0;
	while (list != NULL)
	{
		list = list->next;
		nb_alive_p++;
	}
	return (nb_alive_p);
}

void		check_live(t_vm *x)
{
	t_list *list;

	kill_process2(x);
	list = x->lst_process;
	while (list != NULL)
	{
		((t_p *)list->content)->alive = 0;
		list = list->next;
	}
	if (x->nbr_live >= NBR_LIVE || x->max_check == MAX_CHECKS)
	{
		x->cycle_to_die -= CYCLE_DELTA;
		if (x->log & LOG_CYCLE)
			ft_printf("Cycle to die is now %d\n", x->cycle_to_die);
		x->max_check = 0;
	}
	x->nbr_live = 0;
	x->before_check = x->cycle_to_die;
}

int			load_vm(t_vm *x)
{
	t_list	*list;

	list = x->lst_process;
	if (x->log & LOG_CYCLE)
		ft_printf("It is now cycle %d\n", x->nb_c);
	run_vm(x, list);
	return (ft_end_turn(x));
}

void		dump_vm(t_vm *x)
{
	x->cycle_to_die = CYCLE_TO_DIE;
	x->cycle_delta = CYCLE_DELTA;
	x->nbr_live = 0;
	x->max_check = 0;
	x->before_check = CYCLE_TO_DIE;
	x->nb_c = 1;
	while (load_vm(x) == 1)
		if (x->dumpnb != 0 && x->nb_c - 1 == x->dumpnb)
			break ;
	if (x->dumpnb != 0 && x->nb_c - 1 == x->dumpnb)
		ft_dump(x);
}

void		init_vm(t_vm *x)
{
	int			i;
	t_list		*tmp;
	t_p			*proc;

	i = 0;
	if (!(proc = create_process(x, x->p[i].num, x->p[i].pcstart)))
		return ;
	if (!(x->lst_process = ft_lstnew(NULL, 0)))
		return ;
	x->lst_process->content = proc;
	while (++i < x->nbp)
	{
		if (!(proc = create_process(x, x->p[i].num, x->p[i].pcstart)))
			return ;
		if (!(tmp = ft_lstnew(NULL, 0)))
			return ;
		tmp->content = proc;
		ft_lstadd(&x->lst_process, tmp);
	}
	dump_vm(x);
}
