/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:19:36 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:19:38 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void		op_fork(t_list *list, t_vm *x)
{
	t_process *proc;
	t_list *tmp;
	(void)x;

//	tmp = (t_list*)malloc(sizeof(t_list));
	//PROCESS->arg[0] = 123;
	printf("arg[0] 1 :%d\n",PROCESS->arg[0]);
	
	printf("process->pc :%d\n",PROCESS->pc);
	proc = create_process(PROCESS->reg[1],PROCESS->pc);
//	if (!(proc = (t_process*)malloc(sizeof(t_process))))
//		return;
	memcpy(proc, PROCESS,sizeof(t_process));

	printf("arg[0] idx :%d\n",indx_mod(&PROCESS->arg[0]));
	proc->pc = move_pc(proc->pc,indx_mod(&PROCESS->arg[0]));
//	proc->pc = (proc->pc % MEM_SIZE);
	proc->wait = 0;
	proc->op = 0;
	printf("pc fork: %d\n",proc->pc);
	tmp = ft_lstnew(proc, sizeof(t_process));
//	while (list->next != NULL)
//	list = list->next;
//	list->next = tmp;
	ft_lstadd(&x->lst_process,tmp);
	tmp->next = x->first_proc;
	x->first_proc = tmp;
printf("wwaaait: %d\n",((t_process*)x->first_proc->content)->wait);
printf("pcccc: %d\n",((t_process*)x->first_proc->content)->pc);
printf("PROCESSf: %p\n", (t_process*)x->first_proc->content);
}
