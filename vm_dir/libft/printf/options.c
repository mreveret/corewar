/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:27:04 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/06 18:43:15 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		options2(t_struct *t, const char *format)
{
	if (format[t->i] == '+')
		t->plus = 1;
	if (format[t->i] == '-')
		t->moins = 1;
	if (format[t->i] == '0')
		t->zero = 1;
	if (format[t->i] == '#')
		t->ox = 1;
	if (format[t->i] == 'l' || format[t->i] == 'L')
	{
		if (t->cast != 0)
			t->cast = 1;
		if (t->cast == 0)
			t->cast = 2;
		if (format[t->i] == 'L')
			t->cast = 5;
	}
	if (format[t->i] == 'h')
	{
		if (t->cast == 4)
			t->cast = 3;
		if (t->cast == 0)
			t->cast = 4;
	}
}

void			options1(t_struct *t, const char *f, va_list ap)
{
	while (f[t->i])
	{
		options2(t, f);
		if (f[t->i] == ' ')
			t->spaces = 1;
		if (f[t->i] >= '1' && f[t->i] <= '9')
			bufatoi(t, f);
		if (f[t->i] == '.' && (t->tc = 1))
			bufatoi(t, f);
		if (f[t->i] == '*')
			bonus(t, f, ap);
		if (f[t->i] != ' ' && f[t->i] != '+' && f[t->i] != '-' && f[t->i] != '#'
				&& f[t->i] != 'l' && f[t->i] != 'h' && f[t->i] != '.' &&
				f[t->i] != '*' && f[t->i] != 'L'
				&& !(f[t->i] >= '0' && f[t->i] <= '9'))
			break ;
		t->i++;
	}
	while (f[t->i] && f[t->i] != 's' && f[t->i] != 'd' &&
			f[t->i] != 'c' && f[t->i] != 'i' && f[t->i] != 'o' &&
			f[t->i] != 'u' && f[t->i] != 'p' && f[t->i] != 'x' &&
			f[t->i] != 'X' && f[t->i] != '%' && f[t->i] != 'f' &&
			f[t->i] != 't' && f[t->i] != 'y' && f[t->i] != 'g' &&
			f[t->i] != 'q')
		t->i++;
}

void			bufatoi(t_struct *t, const char *format)
{
	int i;

	i = 0;
	if (t->tc == 1)
		t->i++;
	while (format[t->i] && (format[t->i] >= '0' && format[t->i] <= '9'))
	{
		t->fl[i] = format[t->i];
		t->i++;
		i++;
	}
	t->fl[i] = '\0';
	if (t->tc == 0 && t->champ == 0)
		t->champ = ft_atoip(t->fl);
	if (t->tc == 1)
	{
		t->point = ft_atoip(t->fl);
		if (t->point == 0)
			t->tp = 1;
	}
	t->i--;
}

void			buffer(t_struct *t, char c, int i)
{
	if (i == 1)
	{
		if (t->ret < BUFF_S)
			t->b[t->ret] = c;
		else
		{
			t->b[t->ret] = '\0';
			write(1, t->b, t->ret);
			t->ret = 0;
			t->m++;
			t->b[t->ret] = c;
		}
		t->ret++;
	}
}

void			bufferstr(t_struct *t, char *s, int j)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (t->ret < BUFF_S)
		{
			if (j == 0 || (j == 1 && i < t->point))
				t->b[t->ret] = s[i];
		}
		else
		{
			t->b[t->ret] = '\0';
			write(1, t->b, t->ret);
			t->ret = 0;
			t->m++;
			if (j == 0 || (j == 1 && i < t->point))
				t->b[t->ret] = s[i];
		}
		if (j == 0 || (j == 1 && i < t->point))
			t->ret++;
		i++;
	}
}
