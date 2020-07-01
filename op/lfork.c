/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:19:48 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/25 15:56:34 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_lfork(t_list *list, int pc)
{
	printf("P %4d | lfork %d (%d)\n", ((t_p *)list->content)->id, ((t_p *)list->content)->arg[0],
			(((t_p *)list->content)->pc - 1 + ((t_p *)list->content)->arg[0] >= 0 ?
			pc : ((t_p *)list->content)->pc - 1 + ((t_p *)list->content)->arg[0]));
}

void	op_lfork(t_list *list, t_vm *x)
{
	t_process	*proc;
	t_list		*tmp;

	tmp = ft_lstnew(((t_p *)list->content), sizeof(t_process));
	proc = tmp->content;
	proc->pc = move_pc(proc->pc - 1, ((t_p *)list->content)->arg[0]);
	if (x->log & LOG_OP)
		log_lfork(list, proc->pc);
	proc->wait = 0;
	proc->op = 0;
	proc->id = ++x->current_proc_id;
	ft_lstadd(&x->lst_process, tmp);
}
