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

void	reduce_wait(t_list *list)
{
	if (((t_p *)list->content)->wait > 0)
		((t_p *)list->content)->wait--;
}

int		check_ocp(t_list *list)
{
	if (!(((t_p *)list->content)->t_arg[0] &
	op_tab[((t_p *)list->content)->op - 1].type_arg[0]))
		return (0);
	if (op_tab[((t_p *)list->content)->op - 1].nb_arg > 1 &&
			(!(((t_p *)list->content)->t_arg[1] &
			op_tab[((t_p *)list->content)->op - 1].type_arg[1])))
		return (0);
	if (op_tab[((t_p *)list->content)->op - 1].nb_arg > 2 &&
			(!(((t_p *)list->content)->t_arg[2] &
			op_tab[((t_p *)list->content)->op - 1].type_arg[2])))
		return (0);
	return (1);
}

int		search_idx(t_vm *x)
{
	int i;

	i = -1;
	while (++i < x->nbp)
	{
		if (x->p[i].num == x->winner)
			break ;
	}
	return (i);
}
