/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:06:28 by machoffa          #+#    #+#             */
/*   Updated: 2020/06/30 16:07:11 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "corewar.h"

int		parse_typecode(t_list *list, t_vm *x)
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

