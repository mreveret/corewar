/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:11:32 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/04 16:59:39 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

char			*ft_strsubzero(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	//if (!(s))
	//	return (NULL);
	if (!(dst = ft_memalloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

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
	while (++i)
	{
		if (i == 1)
			proc->reg[i] = id;
		else
			proc->reg[i] = 0;
	}
	return (proc);
}

void		wait_queue(t_process *proc)
{
	if (proc->op == 1 || proc->op == 4 || proc->op == 5 || proc->op == 13)
	proc->wait = 10;
	else if (proc->op == 2 || proc->op == 3)
	proc->wait = 5;
	else if (proc->op == 6 || proc->op == 7 || proc->op == 8)
	proc->wait = 6;
	else if (proc->op == 9)
	proc->wait = 20;
	else if (proc->op == 10 || proc->op == 11)
	proc->wait = 25;
	else if (proc->op == 12)
	proc->wait = 800;
	else if (proc->op == 14)
	proc->wait = 50;
	else if (proc->op == 15)
	proc->wait = 1000;
	else if (proc->op == 16)
	proc->wait = 2;
	else if (proc->op >16 || proc->op < 1)
	proc->wait = -1;
}

void		load_vm(t_vm *x)
{
	t_list	*list;
	int		i;

	list = x->first_proc;

	printf("Cycle numero %d\n",x->nb_c);
	while (list->next)
	{
	//	if (PROCESS->wait == 0)
	//	{
		PROCESS->op = (int)(x->arene[PROCESS->pc]);
		printf("op %d\n",PROCESS->op);
	//	if (PROCESS->op > 0 && PROCESS->op < 17)
		wait_queue(PROCESS);
		printf("wait = %d\n",PROCESS->wait);
		list = list->next;
	//	}
	}
	x->nb_c++;
	printf("Cycle numero %d\n",x->nb_c);
	return ;
}

void		init_vm(t_vm *x)
{
	int		i;
	t_list	*tmp;

	i = -1;
	if(!(x->lst_process = (t_list *)malloc(sizeof(t_list)* 4)))
	return;
	while (++i < x->nbp)
	{
		tmp = ft_lstnew(create_process(x->p[i].num,x->p[i].pcstart),sizeof(t_process));
		ft_lstadd(&x->lst_process,tmp);

		if (i == 0)
			x->first_proc = x->lst_process;
			printf("pc tmp: %d\n",((t_process *)x->lst_process->content)->pc);
		x->lst_process = x->lst_process->next;
	}
	x->cycle_to_die = CYCLE_TO_DIE;
	x->cycle_delta = CYCLE_DELTA;
	x->nbr_live = NBR_LIVE;
	x->max_check = MAX_CHECKS;
	x->nb_c = 0;
	printf("test\n");
	//while (x->lst_process->next)
	load_vm(x);
	return ;
}
