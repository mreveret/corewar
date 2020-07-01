/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:21:40 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/24 16:32:14 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_ldi(t_list *list, t_vm *x, int sum)
{
	(void)x;
	printf("P %4d | ldi %d %d r%d\n", ((t_process *)list->content)->id, ((t_process *)list->content)->arg[0],
			((t_process *)list->content)->arg[1], ((t_process *)list->content)->arg[2] + 1);
	printf("       | -> load from %d + %d = %d (with pc and mod ",
			((t_process *)list->content)->arg[0], ((t_process *)list->content)->arg[1],
			((t_process *)list->content)->arg[0] + ((t_process *)list->content)->arg[1]);
	if (((t_process *)list->content)->pc - 1 + sum >= 0)
		printf("%d)\n", move_pc(((t_process *)list->content)->pc - 1, sum));
	else
		printf("%d)\n", move_pc(((t_process *)list->content)->pc - 1, sum) - MEM_SIZE);
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
	if (((t_process *)list->content)->arg[2] >= REG_NUMBER || ((t_process *)list->content)->arg[2] < 0)
		return ;
	convert_arg(((t_process *)list->content)->arg, 1, list, x);
	sum = ((t_process *)list->content)->arg[0] + ((t_process *)list->content)->arg[1];
	sum = indx_mod(&sum);
	if (x->log & LOG_OP)
		log_ldi(list, x, sum);
	((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]] =
	ft_convert3(x, 4, move_pc(((t_process *)list->content)->pc - 1, sum));
	((t_process *)list->content)->carry = (((t_process *)list->content)->reg[((t_process *)list->content)->arg[2]] == 0 ? 1 : 0);
}
