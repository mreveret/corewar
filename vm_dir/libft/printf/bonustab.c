/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words_tables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:49:01 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/19 12:22:54 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	bonustab(t_struct *t, va_list ap, const char *f)
{
	int i;

	if (f[t->i] == 't' || f[t->i] == 'y')
		t->tab = va_arg(ap, char **);
	if (f[t->i] == 'g' || f[t->i] == 'q')
		t->tabi = va_arg(ap, int *);
	if ((f[t->i] == 'y' || f[t->i] == 'q'))
		i = va_arg(ap, int) - 1;
	if ((f[t->i] == 'g' || f[t->i] == 't') && (t->len = -1))
		i = -1;
	t->len += va_arg(ap, int);
	while (++i <= t->len)
	{
		if (f[t->i] == 't' || f[t->i] == 'y')
			bufferstr(t, t->tab[i], 0);
		if (f[t->i] == 'g' || f[t->i] == 'q')
		{
			if (t->tabi[i] < 0 && (t->type_d = -t->tabi[i]))
				buffer(t, '-', 1);
			else
				t->type_d = t->tabi[i];
			itoabuf(t, 10, "0123456789", 0);
		}
		buffer(t, '\n', 1);
	}
}
