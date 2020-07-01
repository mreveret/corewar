/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:47:14 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/01 18:49:30 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	run_vm2(t_vm *x, t_list *list)
{
	if (parse_arg(list, x) == 1)
		do_op(list, x, ((t_p *)list->content)->op - 1);
	if (x->log & LOG_PC && x->add)
		log_pc(x->arene, x->add, ((t_p *)list->content)->pc);
	((t_p *)list->content)->pc =
		move_pc(((t_p *)list->content)->pc, x->add);
	((t_p *)list->content)->op = 0;
}
