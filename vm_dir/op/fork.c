/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:19:36 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 18:52:13 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_fork(t_list *list, int pc)
{
	ft_printf("P %4d | fork %d (%d)\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->arg[0], (((t_p *)list->content)->pc - 1 +
				((t_p *)list->content)->arg[0] >= 0 ?
			pc : ((t_p *)list->content)->pc - 1 +
			((t_p *)list->content)->arg[0]));
}

void	op_fork(t_list *list, t_vm *x)
{
	t_p			*proc;
	t_list		*tmp;

	if (!(tmp = ft_lstnew(((t_p *)list->content), sizeof(t_p))))
		return ;
	proc = tmp->content;
	proc->pc = move_pc(proc->pc - 1, indx_mod(&((t_p *)list->content)->arg[0]));
	if (x->log & LOG_OP)
		log_fork(list, proc->pc);
	proc->wait = 0;
	proc->op = 0;
	proc->id = ++x->current_proc_id;
	ft_lstadd(&x->lst_process, tmp);
}
