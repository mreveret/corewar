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
	(void)x;;

//	tmp = (t_list*)malloc(sizeof(t_list));
	PROCESS->arg[0] = 123;
	proc = create_process(PROCESS->reg[1],PROCESS->arg[0]);
	ft_memcpy(proc, PROCESS,sizeof(t_process*));
	proc->pc = PROCESS->arg[0];
//	printf("pc fork: %d\n",proc->pc);
	tmp = ft_lstnew(proc, sizeof(proc));
	while (list->next != NULL)
	list = list->next;
	list->next = tmp;
}
