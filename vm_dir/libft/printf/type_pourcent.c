/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_pourcent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:13:26 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/16 21:07:36 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		zero(t_struct *t, int i, int j)
{
	while (t->point > 0 && j-- > 0)
		buffer(t, ' ', 1);
	while (j-- > 0)
		buffer(t, '0', 1);
	while (i-- > 0)
		buffer(t, '0', 1);
	buffer(t, '%', 1);
}

void			type_pourcent(t_struct *t)
{
	int		i;
	int		j;

	t->len = 1;
	i = t->point - t->len;
	j = i > 0 ? t->champ - t->len - i : t->champ - t->len;
	if (t->moins == 1)
	{
		t->zero = 0;
		while (i-- > 0)
			buffer(t, '0', 1);
		buffer(t, '%', 1);
		while (j-- > 0)
			buffer(t, ' ', 1);
	}
	if (t->zero == 1)
		zero(t, i, j);
	if (t->zero == 0 && t->moins == 0)
	{
		while (j-- > 0)
			buffer(t, ' ', 1);
		while (i-- > 0)
			buffer(t, '0', 1);
		buffer(t, '%', 1);
	}
}
