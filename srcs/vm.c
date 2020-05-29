/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:18:17 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:18:18 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

int			stop_vm(t_vm *x)
{
	if (x->cycle_to_die < 0)
		return (0);
	t_list *list;
	int nb_alive_p;

	nb_alive_p = 0;
	list  = x->first_proc;
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

	list = x->first_proc;
	x->max_check +=1;
	while (list != NULL)
	{
		if (PROCESS->alive == 0)
		{
			kill_process(list,x);
			list = x->first_proc;
		}
		else
			list = list->next;
	}
	list = x->first_proc;
	while (list != NULL)
	{
		PROCESS->alive = 0;
		list = list->next;
	}
	if (x->nbr_live >= NBR_LIVE || x->max_check == MAX_CHECKS)
	{
		x->cycle_to_die -= CYCLE_DELTA;
	//	if (x->nbr_live >= NBR_LIVE)
			x->nbr_live = 0;
		x->max_check = 0;
	}
	x->before_check = x->cycle_to_die;
}

int		ft_end_turn(t_vm *x)
{
	x->nb_c++;
	x->before_check--;
	//	printf("Cycle numero %d\n",x->nb_c);
	if (x->before_check == 0)
	{
		check_live(x);
		x->before_check = x->cycle_to_die;
		if (stop_vm(x) < 1)
			return (0);
	}
	return (1);
}

int		load_vm(t_vm *x)
{
	t_list	*list;

	list = x->first_proc;
	while (list != NULL)
	{
		if (PROCESS->wait > 0)
			PROCESS->wait--;
		 if (PROCESS->wait == 0)
		{
			if (PROCESS->op != 0 && PROCESS->op > 0 && PROCESS->op < 17)
			{
				printf("Cycle %d\n",x->nb_c);
				printf("action op: %d\n",PROCESS->op);
				printf("du joueur %d\n",PROCESS->reg[0]);
				if (parse_arg(list,x) == 1)
					do_op(list, x, PROCESS->op - 1);
				PROCESS->pc = move_pc(PROCESS->pc, x->add);
				printf("pc : %x\n",x->arene[PROCESS->pc]);
				PROCESS->op = 0;
				list = list->next;
				continue;
			}
			else
				PROCESS->op = (int)(x->arene[PROCESS->pc]);
			if (PROCESS->op > 0 && PROCESS->op < 17)
				PROCESS->wait = op_tab[PROCESS->op - 1].wait - 1;
				PROCESS->pc = move_pc(PROCESS->pc,1);
		}
		//else
		//	PROCESS->wait--;
	//		printf("wait = %d\n",PROCESS->wait);
		list = list->next;
	}
	return(ft_end_turn(x));
}

void		init_vm(t_vm *x)
{
	int		i;
	t_list	*tmp;
	t_process *proc;

	i = 0;
	proc = create_process(x->p[i].num,x->p[i].pcstart);
	x->lst_process = ft_lstnew(proc,sizeof(t_process));
	free(proc);
	while (++i < x->nbp)
	{
		proc = create_process(x->p[i].num,x->p[i].pcstart);
		tmp = ft_lstnew(proc, sizeof(t_process));
		free(proc);
		ft_lstadd(&x->lst_process,tmp);
		if (i == x->nbp - 1)
			x->first_proc = x->lst_process;
	}
	if (x->nbp == 1)
		x->first_proc = x->lst_process;
	x->cycle_to_die = CYCLE_TO_DIE;
	x->cycle_delta = CYCLE_DELTA;
	x->nbr_live = 0;
	x->max_check = 0;
	x->before_check = CYCLE_TO_DIE;
	x->nb_c = 1;
	i = 0;
	while(load_vm(x) == 1);
//	while (x->nb_c != 1530)
//		load_vm(x);
	ft_dump(x);
	return ;
}

