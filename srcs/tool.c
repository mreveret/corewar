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


int		move_pc(int pc,long long int pcadd)
{
	pc += pcadd;
	if (pc < 0)
	pc = MEM_SIZE - pc;;
	if (pc > MEM_SIZE)
	{
	printf("tool pc 1: %d\n",pc);
	pc = pc % MEM_SIZE;
	printf("tool pc 2: %d\n",pc);
	}
	return (pc);

}
int		indx_mod(int *arg)
{
	*arg = *arg % MEM_SIZE;
	if (*arg > IDX_MOD  || *arg < -IDX_MOD)	
		*arg = *arg % IDX_MOD;
		return (*arg);
}
t_process		*create_process(int id, int pc)
{
	t_process	*proc;
	int			i;
	if (!(proc = (t_process*)malloc(sizeof(t_process))))
		return (0);
	i = -1;
	proc->id = id;
	proc->alive = 0;
	proc->pc = pc % MEM_SIZE;
	proc->wait = 0;
	while (++i < REG_NUMBER)
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
		{
			nb_alive_p++;
			x->p[i].alive = 0;
		}
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
		bzero(list,sizeof(t_list));
		free(list->content);
		free(list);
		list = NULL;
	}
	else
	{
	while (previous->next != list)
	previous = previous->next;
	previous->next = list->next;
	free(list->content);
	free(list);
	list = NULL;
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
		//	printf("process player %d killed\n",PROCESS->reg[1]);
			kill_process(list,x);
			list = x->first_proc;
		}
		else
		{
		//	printf("process player %d alive\n",PROCESS->reg[1]);
			list = list->next;
		}
	}
	list = x->first_proc;
	while (list != NULL)
	{
		printf("process player %d alive\n",PROCESS->reg[1]);
		PROCESS->alive = 0;
		list = list->next;
	}
	if (x->nbr_live == NBR_LIVE)
	x->cycle_to_die -= CYCLE_DELTA;
	else
		x->max_check +=1;
	if (x->max_check == MAX_CHECKS)
	x->cycle_to_die -= CYCLE_DELTA;
	x->before_check = x->cycle_to_die;
	ft_dump(x);
}

void		parse_typecode(t_list *list,t_vm *x)
{
			printf("pc avant arg: %d\n",PROCESS->pc);
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
	PROCESS->pc = move_pc(PROCESS->pc,1);
	}
	if (PROCESS->op == 1)
		PROCESS->t_arg[0] = 2;
	if (PROCESS->op == 9)
	{
		PROCESS->t_arg[0] = DIR_CODE;
	}
}

void		parse_arg(t_list *list, t_vm *x)
{
	int i;
	char b[4];
	int add;
	add = 0;
	i = -1;
	parse_typecode(list, x);
	printf("nb arg: %d\n",op_tab[PROCESS->op - 1].nb_arg);
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == DIR_CODE)
		{
			if (PROCESS->op < 9 || PROCESS->op == 13 || PROCESS->op == 16)
			{
			memcpy(b,x->arene + PROCESS->pc,4);
			PROCESS->arg[i] = ft_convert(b,4);
			PROCESS->pc = move_pc(PROCESS->pc,4);
			}
			else
				{
					memcpy(b,x->arene + PROCESS->pc,2);
					PROCESS->arg[i] = ft_convert(b,2); 
				PROCESS->pc = move_pc(PROCESS->pc,2);
				}
					printf("arg: %d\n",PROCESS->arg[i]);
			printf("pc after arg dir: %d\n",PROCESS->pc);
		}
		else if (PROCESS->t_arg[i] == IND_CODE)
		{
				memcpy(b,x->arene + PROCESS->pc,2);
				PROCESS->arg[i] = ft_convert(b,2);
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = move_pc(PROCESS->pc,2);
		}
		else if (PROCESS->t_arg[i] == REG_CODE)
		{
			
			if (i == op_tab[PROCESS->op - 1].nb_arg - 1)
			{
				memcpy(b,x->arene + PROCESS->pc,1);
				PROCESS->arg[i] = ft_convert(b,1);
			}
			else
			{
				memcpy(b,x->arene + PROCESS->pc,1);
				PROCESS->arg[i] = PROCESS->reg[ft_convert(b,1)];
			}
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = move_pc(PROCESS->pc,1);
			printf("pc after arg reg: %d\n",PROCESS->pc);
		}
	bzero(b,4);
	}
}


void	convert_arg(int *arg,int mod,t_list *list,t_vm *x)
{
	int	i;
	int j;
	i = -1;
	(void)arg;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == IND_CODE ||
		(PROCESS->t_arg[i] == DIR_CODE && 
		PROCESS->op >= 9 && PROCESS->op != 13 && PROCESS->op != 16))
		{
			if (mod == 1)
			{
				j = move_pc(PROCESS->pc, (indx_mod(&PROCESS->arg[i])));
				PROCESS->arg[i]= x->arene[move_pc(PROCESS->pc, (indx_mod(&PROCESS->arg[i])))];
			}
			else
				PROCESS->arg[i]= x->arene[move_pc(PROCESS->pc, PROCESS->arg[i])];
		}
	}
}

int		ft_end_turn(t_vm *x)
{
	printf("Fin liste\n");
	x->nb_c++;
	x->before_check--;
	printf("Cycle numero %d\n",x->nb_c);
	if (x->before_check == 0)
	{
		check_live(x);
	x->before_check = x->cycle_to_die;
		if (stop_vm(x) < 1)
			return (0);
	}
	return (1);
}
//	printf("list: %p\n", list); fflush(0);
//printf("list content: %p\n", list->content);
//printf("process->pc tool : %d\n",PROCESS->pc);
//printf("PROCESS: %p\n", PROCESS);
//printf("process-w: %p\n", &PROCESS->wait);
//printf("processWAIT: %d\n", PROCESS->pc);
	
int		load_vm(t_vm *x)
{
	t_list	*list;
	list = x->first_proc;
printf("PROCESS: %p\n", PROCESS);

	if (x->nb_c == 0)
		printf("Cycle numero %d\n",x->nb_c);
	while (list != NULL)
	{
//	POS;
	if (PROCESS->wait == 0)
		{
//		POS;
			if (PROCESS->op != 0 && PROCESS->op > 0 && PROCESS->op < 17)
			{
				printf("action op: %d\n",PROCESS->op);
				parse_arg(list,x);
				do_op(list, x, PROCESS->op - 1);
				PROCESS->op = 0;
				printf("pc after op : %d\n",PROCESS->pc);
				list = list->next;
				continue;
			}
			else
			PROCESS->op = (int)(x->arene[PROCESS->pc]);
		//	printf("op: %d\n",PROCESS->op);
			if (PROCESS->op > 0 && PROCESS->op < 17)
			{
				printf("op %d\n",PROCESS->op);
				printf("pc : %d\n",PROCESS->pc);
				PROCESS->wait = op_tab[PROCESS->op - 1].wait;
			}
			PROCESS->pc = move_pc(PROCESS->pc,1);
		}
		else
			PROCESS->wait--;
		printf("wait = %d\n",PROCESS->wait);
//		POS;
		list = list->next;
	}
//	POS;
	return(ft_end_turn(x));
}


void		init_vm(t_vm *x)
{
	int		i;
	t_list	*tmp;

	i = 0;
		x->lst_process = ft_lstnew(create_process(x->p[i].num,x->p[i].pcstart),sizeof(t_process));
	while (++i < x->nbp)
	{
		printf ("i : %d\n", i );
		tmp = ft_lstnew(create_process(x->p[i].num,x->p[i].pcstart),sizeof(t_process));
		ft_lstadd(&x->lst_process,tmp);
		if (i == x->nbp - 1)
			x->first_proc = x->lst_process;
		printf("pc tmp: %d\n",((t_process *)x->lst_process->content)->pc);
	}
	if (x->nbp == 1)
			x->first_proc = x->lst_process;
	x->cycle_to_die = CYCLE_TO_DIE;
	x->cycle_delta = CYCLE_DELTA;
	x->nbr_live = 0;
	x->max_check = 0;
	x->before_check = CYCLE_TO_DIE;
	x->nb_c = 0;
	printf("test\n");
	i = 0;
		while (load_vm(x) == 1);
	return ;
}
