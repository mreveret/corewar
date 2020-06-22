/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:19:48 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/17 17:26:35 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_lfork(t_list *list, int pc)
{
	printf("P % 4d | lfork %d (%d)\n", PROCESS->id, PROCESS->arg[0],(PROCESS->pc -1 + PROCESS->arg[0] >= 0 ? pc: PROCESS->pc -1 + PROCESS->arg[0]));
}

void	op_lfork(t_list *list, t_vm *x)
{
	t_process *proc;
	t_list *tmp;

	tmp = ft_lstnew(PROCESS, sizeof(t_process));//
	proc = tmp->content;
	proc->pc = move_pc(proc->pc - 1, PROCESS->arg[0]);
	if (x->log & LOG_OP)
		log_lfork(list, proc->pc);
	proc->wait = 0;
	proc->op = 0;
	proc->id = ++x->current_proc_id;
	ft_lstadd(&x->lst_process,tmp);
	ft_lstadd(&x->first_proc,tmp);

}
