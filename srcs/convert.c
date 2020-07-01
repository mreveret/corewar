/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:02:24 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 18:47:40 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "corewar.h"

int		ft_convert(t_vm *x, t_list *list, int size)
{
	int res;
	int i;

	i = -1;
	res = 0;
	while (++i < size)
	{
		res <<= 8;
		res |= 0x000000FF &
			x->arene[move_pc(((t_p *)list->content)->pc, x->add + i)];
	}
	return (res);
}
