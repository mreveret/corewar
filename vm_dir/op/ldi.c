/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:21:40 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 19:02:55 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_ldi(t_list *list, t_vm *x, int sum)
{
	(void)x;
	ft_printf("P %4d | ldi %d %d r%d\n", ((t_p *)list->content)->id,
			((t_p *)list->content)->arg[0], ((t_p *)list->content)->arg[1],
			((t_p *)list->content)->arg[2] + 1);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod ",
			((t_p *)list->content)->arg[0], ((t_p *)list->content)->arg[1],
			((t_p *)list->content)->arg[0] + ((t_p *)list->content)->arg[1]);
	if (((t_p *)list->content)->pc - 1 + sum >= 0)
		ft_printf("%d)\n", move_pc(((t_p *)list->content)->pc - 1, sum));
	else
		ft_printf("%d)\n", move_pc(((t_p *)list->content)->pc - 1, sum)
				- MEM_SIZE);
}

int		ft_convert3(t_vm *x, int size, int pos)
{
	int res;
	int i;

	i = -1;
	res = 0;
	while (++i < size)
	{
		res <<= 8;
		res |= 0x000000FF & x->arene[move_pc(pos, i)];
	}
	return (res);
}

void	op_ldi(t_list *list, t_vm *x)
{
	int sum;

	sum = 0;
	if (((t_p *)list->content)->arg[2] >= REG_NUMBER ||
			((t_p *)list->content)->arg[2] < 0)
		return ;
	convert_arg(((t_p *)list->content)->arg, 1, list, x);
	sum = ((t_p *)list->content)->arg[0] + ((t_p *)list->content)->arg[1];
	sum = indx_mod(&sum);
	if (x->log & LOG_OP)
		log_ldi(list, x, sum);
	((t_p *)list->content)->reg[((t_p *)list->content)->arg[2]] =
	ft_convert3(x, 4, move_pc(((t_p *)list->content)->pc - 1, sum));
	((t_p *)list->content)->carry =
		(((t_p *)list->content)->reg[((t_p *)list->content)->arg[2]] ==
		0 ? 1 : 0);
}
