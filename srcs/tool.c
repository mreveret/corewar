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
	proc->alive = 1000;
	if (pc > 0)
		proc->alive = 500;
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

void		parse_arg(t_list *list,t_vm *x)
{
	int i;
	PROCESS->encoded = (int)(x->arene[PROCESS->pc]);
	PROCESS->t_arg[0] = (PROCESS->encoded >> 6) & 0b11 ;
	printf("typecode: %d\n",PROCESS->t_arg[0]);
	PROCESS->t_arg[1] = (PROCESS->encoded >> 4) & 0b11 ;
	printf("typecode: %d\n",PROCESS->t_arg[1]);
	PROCESS->t_arg[2] = (PROCESS->encoded >> 2) & 0b11 ;
	printf("typecode: %d\n",PROCESS->t_arg[2]);
	i = -1;
	PROCESS->pc++;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == DIR_CODE)
		{
			PROCESS->arg[i] = ft_convert(ft_strsub(x->arene,PROCESS->pc,4));
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc+= 4;
		}
		else if (PROCESS->t_arg[i] == IND_CODE)
		{
			PROCESS->arg[i] = ft_convert(ft_strsub(x->arene,PROCESS->pc,2));
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc += 2;
		}
		else if (PROCESS->t_arg[i] == REG_CODE)
		{
			PROCESS->arg[i] = ft_convert(ft_strsub(x->arene,PROCESS->pc,1));
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc += 1;
		}
	}
}

void		load_vm(t_vm *x)
{
	t_list	*list;

	list = x->first_proc;
	if (x->nb_c == 0)
		printf("Cycle numero %d\n",x->nb_c);
	while (list != NULL)
	{
		if (PROCESS->wait == 0)
		{
			if (PROCESS->op != 0)
				parse_arg(list,x);
			PROCESS->op = (int)(x->arene[PROCESS->pc]);
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
//	if (before check == 0)
//	{
//	check_process();
//	}
	x->nb_c++;
	printf("Cycle numero %d\n",x->nb_c);
	return ;
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
	x->nbr_live = NBR_LIVE;
	x->max_check = MAX_CHECKS;
	x->nb_c = 0;
	printf("test\n");
	//while (x->lst_process->next)
	i = 0;
	while (++i < 8)
		load_vm(x);
	return ;
}
