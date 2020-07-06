/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:56:33 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/18 16:06:28 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		lennbr(long long n)
{
	unsigned long long	neg;
	unsigned long long	nb;
	unsigned long long	i;

	i = 1;
	neg = 0;
	nb = n;
	if (n < 0 && (nb = -n))
		neg = 1;
	while (nb >= 10 && i++)
		nb = nb / 10;
	return (i + neg);
}

size_t	ft_strlenp(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
		i++;
	return (i);
}

int		ft_atoip(const char *str)
{
	int		res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int		lnbrbase(unsigned long long n, unsigned long long base)
{
	int		i;

	i = 1;
	while (n >= base)
	{
		n = n / base;
		i++;
	}
	return (i);
}

void	itoabuf(t_struct *t, int base, char *cbase, int j)
{
	unsigned long long	i;
	unsigned long long	nb;
	unsigned long long	nb2;

	if (j == 0)
		nb = t->type_d;
	else if (j == 2)
		nb = t->type_f;
	else
		nb = t->type_ud;
	nb2 = nb;
	i = 1;
	while (nb2 >= (unsigned long long)base)
	{
		nb2 = nb2 / base;
		i = i * base;
	}
	while (i > 0)
	{
		buffer(t, cbase[nb / i], 1);
		nb = nb % i;
		i = i / base;
	}
}
