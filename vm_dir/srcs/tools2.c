/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:06:28 by machoffa          #+#    #+#             */
/*   Updated: 2020/06/30 16:45:13 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "corewar.h"

int			parse_typecode(t_list *list, t_vm *x)
{
	if (((t_p *)list->content)->op != 1
	&& ((t_p *)list->content)->op != 9
	&& ((t_p *)list->content)->op != 12
			&& ((t_p *)list->content)->op != 15)
	{
		((t_p *)list->content)->encoded =
		(int)(x->arene[move_pc(((t_p *)list->content)->pc, x->add)]);
		((t_p *)list->content)->t_arg[0] =
		(((((t_p *)list->content)->encoded >> 6) & 0b11)
				== 3 ? 4 : (((t_p *)list->content)->encoded >> 6) & 0b11);
		((t_p *)list->content)->t_arg[1] =
		(((((t_p *)list->content)->encoded >> 4) & 0b11)
				== 3 ? 4 : (((t_p *)list->content)->encoded >> 4) & 0b11);
		((t_p *)list->content)->t_arg[2] =
		(((((t_p *)list->content)->encoded >> 2) & 0b11)
				== 3 ? 4 : (((t_p *)list->content)->encoded >> 2) & 0b11);
		x->add += 1;
	}
	else
		((t_p *)list->content)->t_arg[0] = DIR_CODE;
	return (check_ocp(list));
}

int			ft_end_turn(t_vm *x)
{
	x->nb_c++;
	x->before_check--;
	if (x->before_check <= 0)
	{
		check_live(x);
		if (stop_vm(x) < 1)
			return (0);
	}
	return (1);
}

void		log_pc(char *arene, int move, int pc)
{
	int	new_pc;

	new_pc = move_pc(pc, move);
	pc = move_pc(pc, -1);
	ft_printf("ADV %u (0x%.4x -> 0x%.4x)", move + 1, pc, new_pc);
	while (pc != new_pc)
	{
		ft_printf(" %02hhx", arene[pc]);
		pc = move_pc(pc, 1);
	}
	ft_printf(" \n");
}

void		kill_process2(t_vm *x)
{
	t_list *list;

	list = x->lst_process;
	x->max_check += 1;
	while (list != NULL)
	{
		if (((t_p *)list->content)->alive == 0)
		{
			kill_process(list, x);
			list = x->lst_process;
		}
		else
			list = list->next;
	}
}

void		run_vm(t_vm *x, t_list *list)
{
	while (list != NULL)
	{
		reduce_wait(list);
		if (((t_p *)list->content)->wait == 0)
		{
			if (((t_p *)list->content)->op != 0
			&& ((t_p *)list->content)->op > 0
			&& ((t_p *)list->content)->op < 17)
			{
				run_vm2(x, list);
				list = list->next;
				continue;
			}
			else
				((t_p *)list->content)->op =
				(int)(x->arene[((t_p *)list->content)->pc]);
			if (((t_p *)list->content)->op > 0
			&& ((t_p *)list->content)->op < 17)
				((t_p *)list->content)->wait =
				op_tab[((t_p *)list->content)->op - 1].wait - 1;
			((t_p *)list->content)->pc =
			move_pc(((t_p *)list->content)->pc, 1);
		}
		list = list->next;
	}
}
