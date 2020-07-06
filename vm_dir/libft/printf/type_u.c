/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:06:36 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 15:17:05 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		convert(t_struct *t)
{
	if (t->o == 1)
		itoabuf(t, 8, "01234567", 1);
	else if (t->x == 1)
		itoabuf(t, 16, "0123456789abcdef", 1);
	else if (t->xx == 1)
		itoabuf(t, 16, "0123456789ABCDEF", 1);
	else
		itoabuf(t, 10, "0123456789", 1);
}

static void		t_u4(t_struct *t, int i, int j)
{
	if (t->ox > 0 && (t->x == 1 || t->xx == 1))
		j -= 2;
	if (t->ox > 0 && t->o == 1)
	{
		if (i > 0)
			i--;
		else
			j--;
	}
	while (j-- > 0)
		buffer(t, ' ', 1);
	if (t->ox > 0)
	{
		buffer(t, '0', 1);
		if (t->x == 1)
			buffer(t, 'x', 1);
		if (t->xx == 1)
			buffer(t, 'X', 1);
	}
	while (i-- > 0)
		buffer(t, '0', 1);
	if (!(t->tp == 1 && t->type_ud == 0))
		convert(t);
}

static void		t_u3(t_struct *t, int i, int j)
{
	if (t->ox > 0 && (t->x == 1 || t->xx == 1))
		j -= 2;
	if (t->ox > 0 && t->o == 1)
	{
		if (i > 0)
			i--;
		else
			j--;
	}
	while (t->point > 0 && j-- > 0)
		buffer(t, ' ', 1);
	if (t->ox > 0)
	{
		buffer(t, '0', 1);
		if (t->x == 1)
			buffer(t, 'x', 1);
		if (t->xx == 1)
			buffer(t, 'X', 1);
	}
	while (j-- > 0)
		buffer(t, '0', 1);
	while (i-- > 0)
		buffer(t, '0', 1);
	if (!(t->tp == 1 && t->type_ud == 0))
		convert(t);
}

static void		t_u2(t_struct *t, int i, int j)
{
	t->zero = 0;
	if (t->ox > 0 && (t->x == 1 || t->xx == 1))
	{
		buffer(t, '0', 1);
		if (t->x == 1)
			buffer(t, 'x', 1);
		else
			buffer(t, 'X', 1);
		j -= 2;
	}
	if (t->ox > 0 && t->o == 1)
	{
		buffer(t, '0', 1);
		if (i > 0)
			i--;
		else
			j--;
	}
	while (i-- > 0)
		buffer(t, '0', 1);
	if (!(t->tp == 1 && t->type_ud == 0))
		convert(t);
	while (j-- > 0)
		buffer(t, ' ', 1);
}

void			type_u(t_struct *t)
{
	int		i;
	int		j;

	i = t->point - t->len;
	j = i > 0 ? t->champ - t->len - i : t->champ - t->len;
	if (t->tp == 1 && j > 0 && t->point == 0 && t->type_ud == 0)
		j++;
	if (t->type_ud == 0 && t->ox == 1)
	{
		t->ox = 0;
		if (t->o == 1 && t->tp == 1)
			t->ox = 1;
	}
	if (t->moins == 1)
		t_u2(t, i, j);
	if (t->zero == 1)
		t_u3(t, i, j);
	if (t->zero == 0 && t->moins == 0)
		t_u4(t, i, j);
}
