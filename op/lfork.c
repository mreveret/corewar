/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:19:48 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:19:49 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_lfork(t_list *list, t_vm *x)
{
	t_process *proc;
	t_list *tmp;
	(void)x;

//	proc = create_process(PROCESS->reg[0],PROCESS->arg[0]);
	if (!(proc = (t_process*)malloc(sizeof(t_process))))
		return ;
	memcpy(proc, PROCESS,sizeof(t_process));
	proc->pc = move_pc(proc->pc - 1,PROCESS->arg[0]);
	proc->op = 0;
	tmp = ft_lstnew(proc, sizeof(t_process));
//	free(proc);
//	proc = NULL;
	ft_lstadd(&x->lst_process,tmp);
	tmp->next = x->first_proc;
	x->first_proc = tmp;
}
