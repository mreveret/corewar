/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:24:04 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/06 18:42:40 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_struct	t;
	va_list		ap;

	va_start(ap, format);
	t.ret = 0;
	t.i = 0;
	t.m = 0;
	while (format[t.i])
	{
		if (format[t.i] == '%')
		{
			if (!format[t.i + 1])
				break ;
			t.i++;
			findtyp(format, ap, &t);
			if (!format[t.i] || !format[t.i + 1])
				break ;
			t.i++;
		}
		if (format[t.i] && format[t.i] != '%')
			buffer(&t, format[t.i++], 1);
	}
	t.b[t.ret] = '\0';
	write(1, t.b, t.ret);
	return (t.ret + (BUFF_S * t.m));
}
