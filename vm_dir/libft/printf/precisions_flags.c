/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precisions_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 22:45:37 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/19 12:23:05 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		sig(t_struct *t, va_list ap)
{
	if (t->cast == 1)
		t->type_d = va_arg(ap, long long);
	else if (t->cast == 2)
		t->type_d = va_arg(ap, long);
	else if (t->cast == 3)
		t->type_d = (signed char)va_arg(ap, int);
	else if (t->cast == 4)
		t->type_d = (short int)va_arg(ap, int);
	else
		t->type_d = (int)va_arg(ap, int);
	type_d(t);
}

static void		unsig(t_struct *t, va_list ap, const char *format)
{
	if (format[t->i] == 'p' && (t->cast = 1))
		t->ox = 2;
	if (t->cast == 1)
		t->type_ud = va_arg(ap, unsigned long long);
	else if (t->cast == 2)
		t->type_ud = (unsigned long)va_arg(ap, unsigned long);
	else if (t->cast == 3)
		t->type_ud = (unsigned char)va_arg(ap, unsigned int);
	else if (t->cast == 4)
		t->type_ud = (unsigned short int)va_arg(ap, unsigned int);
	else
		t->type_ud = (unsigned int)va_arg(ap, unsigned int);
	if (t->o == 1)
		t->len = lnbrbase(t->type_ud, 8);
	else if (t->x == 1)
		t->len = lnbrbase(t->type_ud, 16);
	else if (t->xx == 1)
		t->len = lnbrbase(t->type_ud, 16);
	else
		t->len = lnbrbase(t->type_ud, 10);
	type_u(t);
}

static void		initvar(t_struct *t)
{
	t->ox = 0;
	t->o = 0;
	t->x = 0;
	t->xx = 0;
	t->moins = 0;
	t->plus = 0;
	t->zero = 0;
	t->point = 0;
	t->spaces = 0;
	t->point = 0;
	t->champ = 0;
	t->tp = 0;
	t->tc = 0;
	t->cast = 0;
}

void			findtyp(const char *f, va_list ap, t_struct *t)
{
	initvar(t);
	options1(t, f, ap);
	if (f[t->i] == 's')
		type_s(t, ap);
	if (f[t->i] == 'x' && (t->x = 1))
		unsig(t, ap, f);
	if (f[t->i] == 'p' && (t->x = 1))
		unsig(t, ap, f);
	if (f[t->i] == 'i' || f[t->i] == 'd')
		sig(t, ap);
	if (f[t->i] == 'o' && (t->o = 1))
		unsig(t, ap, f);
	if (f[t->i] == 'u')
		unsig(t, ap, f);
	if (f[t->i] == 'X' && (t->xx = 1))
		unsig(t, ap, f);
	if (f[t->i] == 'c')
		type_c(t, ap);
	if (f[t->i] == 't' || f[t->i] == 'g' || f[t->i] == 'y' || f[t->i] == 'q')
		bonustab(t, ap, f);
	if (f[t->i] == 'f')
		type_f(t, ap);
	if (f[t->i] == '%')
		type_pourcent(t);
}
