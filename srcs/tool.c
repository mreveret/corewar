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

int		move_pc(int pc,int pcadd)
{
	pc += pcadd;
//	printf("pc movepc: %d\n",pc);
	if (pc < 0)
		pc = MEM_SIZE - -pc;;
	if (pc > MEM_SIZE)
		pc = pc % MEM_SIZE;
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
	proc->pc = pc;
	proc->alive = 0;
	proc->wait = 0;
	while (++i < REG_NUMBER)
	{
		if (i == 0)
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
} //typedef dans le .h , tab de pointeur de fonction dans la vm ;

void		kill_process(t_list *list, t_vm *x)
{
	t_list *previous;
	previous = x->first_proc;
	if (previous == NULL)
		return ;
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
