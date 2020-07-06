/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:06:10 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 15:16:34 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		type_s2(t_struct *t, int i)
{
	if (t->type_s != NULL && (i > 0 || t->tp == 1))
		bufferstr(t, t->type_s, 1);
	if (t->type_s != NULL && !(i > 0 || t->tp == 1))
		bufferstr(t, t->type_s, 0);
	if (t->type_s == NULL && t->tp == 0)
	{
		if (i > 0 || t->tp == 1)
			bufferstr(t, "(null)", 1);
		else
			bufferstr(t, "(null)", 0);
	}
}

void			type_s(t_struct *t, va_list ap)
{
	int		i;
	int		j;

	t->type_s = va_arg(ap, char *);
	t->len = ft_strlenp(t->type_s);
	if (t->type_s == NULL)
		t->len = 6;
	i = t->point > t->len ? t->len : t->point;
	j = i > 0 ? t->champ - i : t->champ - t->len;
	if (t->tp == 1)
		j = t->champ;
	if (t->moins == 1)
	{
		type_s2(t, i);
		while (j-- > 0)
			buffer(t, ' ', 1);
	}
	if (t->moins == 0)
	{
		while (j-- > 0)
			buffer(t, ' ', 1);
		type_s2(t, i);
	}
}
