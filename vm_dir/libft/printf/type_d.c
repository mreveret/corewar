/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 22:57:16 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 15:15:47 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		t_d4(t_struct *t, int i, int j)
{
	if (t->spaces == 1 && (j = j - 1))
		buffer(t, ' ', 1);
	if (t->plus == 1)
		j--;
	while (j-- > 0)
		buffer(t, ' ', 1);
	if (t->plus == 1)
		buffer(t, '+', 1);
	if (t->type_d < 0 && (t->type_d = t->type_d * -1))
		buffer(t, '-', 1);
	while (i-- > 0)
		buffer(t, '0', 1);
	if (!(t->tp == 1 && t->type_d == 0))
	{
		if (t->type_d >= -9223372036854775807)
			itoabuf(t, 10, "0123456789", 0);
		else
			bufferstr(t, "9223372036854775808", 0);
	}
}

static void		t_d3(t_struct *t, int i, int j)
{
	if (t->spaces == 1 && (j = j - 1))
		buffer(t, ' ', 1);
	if (t->plus == 1)
		j--;
	if (t->point > 0)
		while (j-- > 0)
			buffer(t, ' ', 1);
	if (t->plus == 1)
		buffer(t, '+', 1);
	if (t->type_d < 0 && (t->type_d = t->type_d * -1))
		buffer(t, '-', 1);
	while (j-- > 0)
		buffer(t, '0', 1);
	while (i-- > 0)
		buffer(t, '0', 1);
	if (!(t->tp == 1 && t->type_d == 0))
	{
		if (t->type_d >= -9223372036854775807)
			itoabuf(t, 10, "0123456789", 0);
		else
			bufferstr(t, "9223372036854775808", 0);
	}
}

static void		t_d2(t_struct *t, int i, int j)
{
	t->zero = 0;
	if (t->plus == 1 && j--)
		buffer(t, '+', 1);
	if (t->spaces == 1 && (j = j - 1))
		buffer(t, ' ', 1);
	if (t->type_d < 0 && (t->type_d = t->type_d * -1))
		buffer(t, '-', 1);
	while (i-- > 0)
		buffer(t, '0', 1);
	if (!(t->tp == 1 && t->type_d == 0))
	{
		if (t->type_d >= -9223372036854775807)
			itoabuf(t, 10, "0123456789", 0);
		else
			bufferstr(t, "9223372036854775808", 0);
	}
	while (j-- > 0)
		buffer(t, ' ', 1);
}

void			type_d(t_struct *t)
{
	int		i;
	int		j;

	t->len = lennbr(t->type_d);
	if (t->type_d < 0)
		t->plus = 0;
	if (t->type_d < 0 || t->plus == 1)
		t->spaces = 0;
	i = t->point - t->len;
	j = i > 0 ? t->champ - t->point : t->champ - t->len;
	if (t->tp == 1 && j > 0 && t->point == 0 && t->type_d == 0)
		j++;
	if (t->type_d < 0 && (i > 0 || (i == 0 && t->point == t->len)))
	{
		i++;
		j--;
	}
	if (t->moins == 1)
		t_d2(t, i, j);
	if (t->zero == 1)
		t_d3(t, i, j);
	if (t->zero == 0 && t->moins == 0)
		t_d4(t, i, j);
}
