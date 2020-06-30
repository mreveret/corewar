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
	if (PROCESS->op != 1 && PROCESS->op != 9 && PROCESS->op != 12
			&& PROCESS->op != 15)
	{
		PROCESS->encoded = (int)(x->arene[move_pc(PROCESS->pc, x->add)]);
		PROCESS->t_arg[0] = (((PROCESS->encoded >> 6) & 0b11)
				== 3 ? 4 : (PROCESS->encoded >> 6) & 0b11);
		PROCESS->t_arg[1] = (((PROCESS->encoded >> 4) & 0b11)
				== 3 ? 4 : (PROCESS->encoded >> 4) & 0b11);
		PROCESS->t_arg[2] = (((PROCESS->encoded >> 2) & 0b11)
				== 3 ? 4 : (PROCESS->encoded >> 2) & 0b11);
		x->add += 1;
	}
	else
		PROCESS->t_arg[0] = DIR_CODE;
	if (!(PROCESS->t_arg[0] & op_tab[PROCESS->op - 1].type_arg[0]))
		return (0);
	if (op_tab[PROCESS->op - 1].nb_arg > 1 &&
			(!(PROCESS->t_arg[1] & op_tab[PROCESS->op - 1].type_arg[1])))
		return (0);
	if (op_tab[PROCESS->op - 1].nb_arg > 2 &&
			(!(PROCESS->t_arg[2] & op_tab[PROCESS->op - 1].type_arg[2])))
		return (0);
	return (1);
}

int			ft_end_turn(t_vm *x)
{
	x->nb_c++;
	x->before_check--;
	if (x->before_check == 0)
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
	printf("ADV %u (0x%.4x -> 0x%.4x)", move + 1, pc, new_pc);
	while (pc != new_pc)
	{
		printf(" %02hhx", arene[pc]);
		pc = move_pc(pc, 1);
	}
	printf(" \n");
}

void		kill_process2(t_vm *x)
{
	t_list *list;

	list = x->lst_process;
	x->max_check += 1;
	while (list != NULL)
	{
		if (PROCESS->alive == 0)
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
		if (PROCESS->wait > 0)
			PROCESS->wait--;
		if (PROCESS->wait == 0)
		{
			if (PROCESS->op != 0 && PROCESS->op > 0 && PROCESS->op < 17)
			{
				if (parse_arg(list, x) == 1)
					do_op(list, x, PROCESS->op - 1);
				if (x->log & LOG_PC && x->add)
					log_pc(x->arene, x->add, PROCESS->pc);
				PROCESS->pc = move_pc(PROCESS->pc, x->add);
				PROCESS->op = 0;
				list = list->next;
				continue;
			}
			else
				PROCESS->op = (int)(x->arene[PROCESS->pc]);
			if (PROCESS->op > 0 && PROCESS->op < 17)
				PROCESS->wait = op_tab[PROCESS->op - 1].wait - 1;
			PROCESS->pc = move_pc(PROCESS->pc, 1);
		}
		list = list->next;
	}
}
