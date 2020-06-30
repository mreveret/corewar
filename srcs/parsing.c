/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:18:00 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/30 16:07:57 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

static void		parse_arg3(int i, t_list *list, t_vm *x)
{
	if (PROCESS->op < 9 || PROCESS->op == 13 || PROCESS->op == 16)
	{
		PROCESS->arg[i] = ft_convert(x, list, 4);
		x->add += 4;
	}
	else
	{
		PROCESS->arg[i] = (short)ft_convert(x, list, 2);
		x->add += 2;
	}
}

static int		parse_arg2(int i, int ret, t_list *list, t_vm *x)
{
	if (PROCESS->t_arg[i] == DIR_CODE)
		parse_arg3(i, list, x);
	else if (PROCESS->t_arg[i] == T_IND)
	{
		PROCESS->arg[i] = (short)ft_convert(x, list, 2);
		x->add += 2;
	}
	else if (PROCESS->t_arg[i] == REG_CODE)
	{
		if (i == op_tab[PROCESS->op - 1].nb_arg - 1)
		{
			PROCESS->arg[i] = (char)ft_convert(x, list, 1) - 1;
		}
		else
		{
			if (ft_convert(x, list, 1) <= 0
					|| ft_convert(x, list, 1) > REG_NUMBER)
				ret = 0;
			else
				PROCESS->arg[i] = PROCESS->reg[ft_convert(x, list, 1) - 1];
		}
		PROCESS->reg_num[i] = (char)ft_convert(x, list, 1);
		x->add += 1;
	}
	return (ret);
}

int				parse_arg(t_list *list, t_vm *x)
{
	int i;
	int ret;

	x->add = 0;
	i = -1;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
		PROCESS->arg[i] = 0;
	ret = parse_typecode(list, x);
	i = -1;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		ret = parse_arg2(i, ret, list, x);
	}
	return (ret);
}

int				ft_convert2(t_vm *x, int size, t_list *list, int j)
{
	int res;
	int i;

	i = -1;
	res = 0;
	while (++i < size)
	{
		res <<= 8;
		res |= 0x000000FF &
			x->arene[move_pc(PROCESS->pc - 1, PROCESS->arg[j] + i)];
	}
	return (res);
}

void			convert_arg(int *arg, int mod, t_list *list, t_vm *x)
{
	int	i;

	i = -1;
	(void)arg;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == T_IND)
		{
			if (mod == 1)
			{
				PROCESS->arg[i] = indx_mod(&PROCESS->arg[i]);
				PROCESS->arg[i] = ft_convert2(x, 4, list, i);
			}
			else
				PROCESS->arg[i] = ft_convert2(x, 4, list, i);
		}
	}
}
