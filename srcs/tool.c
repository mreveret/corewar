/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:11:32 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 18:08:51 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

t_process		*create_process(int id, int pc)
{
	t_process	*proc;
	int			i;
	if (!(proc = (t_process*)malloc(sizeof(t_process))))
		return (0);
	i = -1;
	proc->id = id;
	proc->alive = 0;
	//if (pc > 0)
	//	proc->alive = 500;
	proc->pc = pc % MEM_SIZE;
	proc->wait = 0;
	while (++i)
	{
		if (i == 1)
			proc->reg[i] = id;
		else
			proc->reg[i] = 0;
	}
	return (proc);
}

void		do_op(t_list *list, t_vm *x, int op)
{
void	(*doop[16])(t_list*, t_vm*);
	doop[0] = &op_live;
	doop[1] = &op_ld;
	doop[2] = &op_st;
	doop[3] = &op_add;
	doop[4] = &op_sub;
	doop[5] = &op_and;
	doop[6] = &op_or;
	doop[7] = &op_xor;
	doop[8] = &op_zjmp;
	doop[9] = &op_ldi;
	doop[10] = &op_sti;
	doop[11] = &op_fork;
	doop[12] = &op_lld;
	doop[13] = &op_lldi;
	doop[14] = &op_lfork;
	doop[15] = &op_aff;
	return (doop[op](list,x));
}

int			stop_vm(t_vm *x)
{
	int i;
	int nb_alive_p;

	i = -1;
	nb_alive_p = 0;
	while (++i < 4)
	{
		if (x->p[i].alive == 1)
			nb_alive_p++;
	}
	return (nb_alive_p);
}

void		kill_process(t_list *list, t_vm *x)
{
	t_list *previous;
	previous = x->first_proc;
	if (list == previous)
	{
		x->first_proc = list->next;
		free(list);
	}
	else
	{
	while (previous->next != list)
	previous = previous->next;
	previous->next = list->next;
	free(list);
	}
}

void		check_live(t_vm *x)
{
	t_list *list;

	list = x->first_proc;
	while (list != NULL)
	{
		if (PROCESS->alive == 0)
		{
			kill_process(list,x);
			printf("process killed\n");
			list = x->first_proc;
		}
		else
		{
			printf("process alive\n");
			list = list->next;
		}
	}
	list = x->first_proc;
	while (list != NULL)
	{
		PROCESS->alive = 0;
		list = list->next;
	}
	if (x->nbr_live == NBR_LIVE)
	x->cycle_to_die -= CYCLE_DELTA;
	x->before_check = x->cycle_to_die;
}

void		parse_arg(t_list *list,t_vm *x)
{
	if (PROCESS->op != 1 && PROCESS->op != 9 && PROCESS->op != 12
	&& PROCESS->op != 15)
	{
	PROCESS->encoded = (int)(x->arene[PROCESS->pc]);
	PROCESS->t_arg[0] = (PROCESS->encoded >> 6) & 0b11 ;
	printf("typecode: %d\n",PROCESS->t_arg[0]);
	PROCESS->t_arg[1] = (PROCESS->encoded >> 4) & 0b11 ;
	printf("typecode: %d\n",PROCESS->t_arg[1]);
	PROCESS->t_arg[2] = (PROCESS->encoded >> 2) & 0b11 ;
	printf("typecode: %d\n",PROCESS->t_arg[2]);
	PROCESS->pc++;
	}
	if (PROCESS->op == 1)
		PROCESS->t_arg[0] = 2;
	if (PROCESS->op == 9)
	{
		PROCESS->t_arg[0] = 2;
		PROCESS->arg[0] = ft_convert(ft_strsub(x->arene,PROCESS->pc,2));
		printf("arg: %d\n",PROCESS->arg[0]);
		PROCESS->pc = (PROCESS->pc + 2) % MEM_SIZE;
		return;
	}

	int i;
	i = -1;
	printf("nb arg: %d\n",op_tab[PROCESS->op - 1].nb_arg);
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == DIR_CODE)
		{
			PROCESS->arg[i] = ft_convert(ft_strsub(x->arene,PROCESS->pc,4));
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = (PROCESS->pc + 4) % MEM_SIZE;
		}
		else if (PROCESS->t_arg[i] == IND_CODE)
		{
			PROCESS->arg[i] = ft_convert(ft_strsub(x->arene,PROCESS->pc,2));
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = (PROCESS->pc + 2) % MEM_SIZE;
		}
		else if (PROCESS->t_arg[i] == REG_CODE)
		{
			PROCESS->arg[i] = ft_convert(ft_strsub(x->arene,PROCESS->pc,1));
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = (PROCESS->pc + 1) % MEM_SIZE;
		}
	}
}

int		load_vm(t_vm *x)
{
	t_list	*list;

	list = x->first_proc;
//	op_fork(list,x);
//	while (list != NULL)
//{
//	printf("id : %d\n",PROCESS->id);
//	list = list->next;
//	}
	if (x->nb_c == 0)
		printf("Cycle numero %d\n",x->nb_c);
	while (list != NULL)
	{
		if (PROCESS->wait == 0)
		{
			if (PROCESS->op != 0 && PROCESS->op > 0 && PROCESS->op < 17)
			{
				printf("action op: %d\n",PROCESS->op);
				parse_arg(list,x);
				do_op(list, x, PROCESS->op - 1);
				PROCESS->op = 0;
				list = list->next;
				continue;
			}
			else
			PROCESS->op = (int)(x->arene[PROCESS->pc]);
		//		printf("op %d\n",PROCESS->op);
			if (PROCESS->op > 0 && PROCESS->op < 17)
			{
				printf("op %d\n",PROCESS->op);
				PROCESS->wait = op_tab[PROCESS->op - 1].wait;
			}
			PROCESS->pc = (PROCESS->pc + 1) % MEM_SIZE;
		}
		else
			PROCESS->wait--;
		printf("wait = %d\n",PROCESS->wait);
		list = list->next;
	}
	x->nb_c++;
	x->before_check--;
	printf("Cycle numero %d\n",x->nb_c);
	if (x->before_check == 0)
	{
//	x->before_check = x->cycle_to_die;
		check_live(x);
		if (stop_vm(x) == 1)
			return (0);
	}
	return (1);
}

void		init_vm(t_vm *x)
{
	int		i;
	t_list	*tmp;

	i = -1;
	if(!(x->lst_process = (t_list *)malloc(sizeof(t_list))))
		return ;
	if(!(tmp = (t_list *)malloc(sizeof(t_list))))
		return;
	x->lst_process = NULL;
	while (++i < x->nbp)
	{

		printf ("i : %d\n", i );
		tmp = ft_lstnew(create_process(x->p[i].num,x->p[i].pcstart),sizeof(t_process));
		//	tmp->next = NULL;
		ft_lstadd(&x->lst_process,tmp);
		//		if (i == 0)
		//		x->lst_process->next = NULL;

		if (i == x->nbp - 1)
		{
			x->first_proc = x->lst_process;
			//			x->first_proc->next = NULL;
		}
		printf("pc tmp: %d\n",((t_process *)x->lst_process->content)->pc);
		//x->lst_process = x->lst_process->next;
	}
	free(tmp);
	x->cycle_to_die = CYCLE_TO_DIE;
	x->cycle_delta = CYCLE_DELTA;
	x->nbr_live = 0;
	x->max_check = MAX_CHECKS;
	x->before_check = CYCLE_TO_DIE;
	x->nb_c = 0;
	printf("test\n");
	//while (x->lst_process->next)
	i = 0;

		while (load_vm(x) == 1);
	return ;
}
