/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:31:24 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 15:23:48 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		bonus3(t_struct *t, int j)
{
	t->fl[j] = '\0';
	if (t->tc == 0)
	{
		t->champ = ft_atoip(t->fl);
		if (t->fl[0] == '0')
			t->zero = 1;
	}
	if (t->tc == 1 && t->crash != 2 && (t->point = ft_atoip(t->fl)))
		t->tp = t->point == 0 ? 1 : 0;
	if (t->crash == 2 && (t->tp = 0))
		t->point = -1;
	t->i--;
}

static int		bonus2(t_struct *t, int j, int nb, va_list ap)
{
	int	nb2;
	int	i;

	i = 1;
	nb = va_arg(ap, int);
	if (t->crash == 1 && nb < 0 && (t->point = nb))
	{
		t->crash = 2;
		return (j);
	}
	if (nb < 0 && t->tc == 0 && (nb = -nb))
		t->moins = 1;
	nb2 = nb;
	while (nb2 >= 10)
	{
		nb2 = nb2 / 10;
		i = i * 10;
	}
	while (i > 0)
	{
		t->fl[j++] = nb / i + 48;
		nb = nb % i;
		i = i / 10;
	}
	return (j);
}

void			bonus(t_struct *t, const char *f, va_list ap)
{
	unsigned long long	j;
	int					nb;

	j = t->i;
	nb = 0;
	if (t->i > 0 &&
			((f[t->i - 1] >= '0' && f[t->i - 1] <= '9') || f[t->i - 1] == '.'))
		t->i--;
	while (t->i > 0 && f[t->i] >= '0' && f[t->i] <= '9')
		t->i--;
	t->tc = f[t->i] == '.' ? 1 : 0;
	if (f[t->i] != '*' && !(f[t->i] >= '0' && f[t->i] <= '9'))
		t->i++;
	while (t->tc == 1 && f[j] && ((f[j] >= '0' && f[j] <= '9') || f[j] == '*'))
		j++;
	t->crash = f[j] == 's' ? 1 : 0;
	j = 0;
	while (f[t->i] && ((f[t->i] >= '0' && f[t->i] <= '9') || f[t->i] == '*'))
	{
		if (f[t->i] == '*' && t->i++)
			j = bonus2(t, j, nb, ap);
		else
			t->fl[j++] = f[t->i++];
	}
	bonus3(t, j);
}
