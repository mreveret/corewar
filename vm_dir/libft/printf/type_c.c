/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:07:27 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 15:17:23 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printfloat(t_struct *t, int j, int i)
{
	if (t->tp == 0)
	{
		if (j == 0 && (int)t->type_f > 4 && t->fl[0] == '0')
			t->type_f = t->type_ud + 1;
		else
			t->type_f = t->type_ud;
		itoabuf(t, 10, "0123456789", 2);
	}
	if (t->tp == 1)
	{
		if ((int)t->type_f < 5)
		{
			t->type_f = t->type_ud;
			itoabuf(t, 10, "0123456789", 2);
		}
		else
		{
			t->type_f = t->type_ud + 1;
			itoabuf(t, 10, "0123456789", 2);
		}
	}
	if (i != 0 || (i == 0 && t->ox == 1))
		buffer(t, '.', 1);
	bufferstr(t, t->fl, 0);
}

void		type_c(t_struct *t, va_list ap)
{
	int		j;

	t->type_c = va_arg(ap, int);
	t->len = 1;
	j = t->champ - t->len;
	if (t->moins == 1)
	{
		buffer(t, t->type_c, 1);
		while (j > 0)
		{
			buffer(t, ' ', 1);
			j--;
		}
	}
	if (t->moins == 0)
	{
		while (j > 0)
		{
			buffer(t, ' ', 1);
			j--;
		}
		buffer(t, t->type_c, 1);
	}
}
