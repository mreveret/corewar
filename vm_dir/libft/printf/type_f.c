/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:57:53 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 15:16:03 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		t_f3(t_struct *t, int j, int tmp, int i)
{
	j = ft_strlenp(t->fl) - 1;
	if ((int)t->type_f > 4)
	{
		if (t->fl[j] == '9' && j - 1 > 0 && t->fl[j - 1] != '9')
		{
			t->fl[j] = '0';
			t->fl[j - 1] = t->fl[j - 1] + 1;
			j = -5;
		}
		if (j != -5)
		{
			t->fl[j] = t->fl[j] == '9' ? '0' : t->fl[j] + 1;
			j--;
			tmp = j;
			while (j > 0 && t->fl[j + 1] == '0' && t->fl[j] == '9')
			{
				t->fl[j] = '0';
				j--;
			}
			if (j < tmp)
				t->fl[j] = t->fl[j] == '9' ? '0' : t->fl[j] + 1;
		}
	}
	printfloat(t, j, i);
}

static void		t_f2(t_struct *t, int i)
{
	int		tmp;
	int		j;

	t->type_ud = (unsigned long long)t->type_f;
	j = -1;
	t->type_f = t->type_f - t->type_ud;
	t->type_f *= 10;
	while (j++ < i - 1)
	{
		tmp = (int)t->type_f;
		if (t->type_f == 0)
		{
			t->fl[j] = '0';
			continue ;
		}
		t->fl[j] = tmp + 48;
		t->type_f = (t->type_f - tmp) * 10;
	}
	t->fl[j] = '\0';
	t_f3(t, j, tmp, i);
}

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
	if (t->type_f < 0 && (t->type_f = t->type_f * -1))
		buffer(t, '-', 1);
	t_f2(t, i);
}

static void		t_d2(t_struct *t, int i, int j)
{
	if (t->moins == 1)
	{
		t->zero = 0;
		if (t->spaces == 1 && (j = j - 1))
			buffer(t, ' ', 1);
		if (t->plus == 1 && j--)
			buffer(t, '+', 1);
		if (t->type_f < 0 && (t->type_f = t->type_f * -1))
			buffer(t, '-', 1);
		t_f2(t, i);
		while (j-- > 0)
			buffer(t, ' ', 1);
	}
	if (t->zero == 1)
	{
		if (t->spaces == 1 && (j = j - 1))
			buffer(t, ' ', 1);
		if (t->plus == 1 && (j = j - 1))
			buffer(t, '+', 1);
		if (t->type_f < 0 && (t->type_f = t->type_f * -1))
			buffer(t, '-', 1);
		while (j-- > 0)
			buffer(t, '0', 1);
		t_f2(t, i);
	}
}

void			type_f(t_struct *t, va_list ap)
{
	int		i;
	int		j;

	t->type_f = t->cast == 5 ?
	va_arg(ap, long double) : (double)va_arg(ap, double);
	if (t->type_f < 0)
		t->plus = 0;
	if (t->type_f < 0 || t->plus == 1)
		t->spaces = 0;
	t->len = lennbr((int)t->type_f);
	i = t->point > 0 ? t->point : 6;
	if (t->tp == 1)
		i = 0;
	j = t->champ - i - t->len;
	if (i > 0 && j > 0)
		j--;
	t_d2(t, i, j);
	if (t->zero == 0 && t->moins == 0)
		t_d4(t, i, j);
}
