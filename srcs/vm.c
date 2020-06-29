/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:18:17 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/25 15:56:00 by machoffa         ###   ########.fr       */
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
	if (x->cycle_to_die < 0)
		return (0);
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

	list = x->lst_process;
	x->max_check += 1;
	while (list != NULL)
	{
		if (PROCESS->alive == 0)
		{
			kill_process(list, x);
			list = x->lst_process;
		}
		else
			list = list->next;
	}
	list = x->lst_process;
	while (list != NULL)
	{
		PROCESS->alive = 0;
		list = list->next;
	}
	if (x->nbr_live >= NBR_LIVE || x->max_check == MAX_CHECKS)
	{
		x->cycle_to_die -= CYCLE_DELTA;
		if (x->log & LOG_CYCLE)
			printf("Cycle to die is now %d\n", x->cycle_to_die);
		x->max_check = 0;
	}
	x->nbr_live = 0;
	x->before_check = x->cycle_to_die;
}

int			ft_end_turn(t_vm *x)
{
	x->nb_c++;
	x->before_check--;
	if (x->before_check == 0)
	{
		check_live(x);
		if (stop_vm(x) < 1)
			return (0);
	}
	return (1);
}

void		log_pc(char *arene, int move, int pc)
{
	int	new_pc;

	new_pc = move_pc(pc, move);
	pc = move_pc(pc, -1);
	printf("ADV %u (0x%.4x -> 0x%.4x)", move + 1, pc, new_pc);
	while (pc != new_pc)
	{
		printf(" %02hhx", arene[pc]);
		pc = move_pc(pc, 1);
	}
	printf(" \n");
}

int			load_vm(t_vm *x)
{
	t_list	*list;

	list = x->lst_process;
	if (x->log & LOG_CYCLE)
		printf("It is now cycle %d\n", x->nb_c);
	while (list != NULL)
	{
		if (PROCESS->wait > 0)
			PROCESS->wait--;
		if (PROCESS->wait == 0)
		{
			if (PROCESS->op != 0 && PROCESS->op > 0 && PROCESS->op < 17)
			{
				if (parse_arg(list, x) == 1)
					do_op(list, x, PROCESS->op - 1);
				if (x->log & LOG_PC && x->add)
					log_pc(x->arene, x->add, PROCESS->pc);
				PROCESS->pc = move_pc(PROCESS->pc, x->add);
				PROCESS->op = 0;
				list = list->next;
				continue;
			}
			else
				PROCESS->op = (int)(x->arene[PROCESS->pc]);
			if (PROCESS->op > 0 && PROCESS->op < 17)
				PROCESS->wait = op_tab[PROCESS->op - 1].wait - 1;
			PROCESS->pc = move_pc(PROCESS->pc, 1);
		}
		list = list->next;
	}
	return (ft_end_turn(x));
}

void		init_vm(t_vm *x)
{
	int			i;
	t_list		*tmp;
	t_process	*proc;

	i = 0;
	proc = create_process(x, x->p[i].num, x->p[i].pcstart);
	x->lst_process = ft_lstnew(NULL, 0);
	x->lst_process->content = proc;
	while (++i < x->nbp)
	{
		proc = create_process(x, x->p[i].num, x->p[i].pcstart);
		tmp = ft_lstnew(NULL, 0);
		tmp->content = proc;
		ft_lstadd(&x->lst_process, tmp);
	}
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
	return ;
}
