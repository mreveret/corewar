/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:11:00 by machoffa          #+#    #+#             */
/*   Updated: 2020/06/29 18:26:49 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static unsigned int		count(int nb, int base)
{
	int	count;

	count = 1;
	while (nb >= base)
	{
		nb = nb / base;
		count = count * base;
	}
	return (count);
}

static char				*fill_it(int *nb, char *res, int n, int base)
{
	while (nb[1] > 0)
	{
		res[nb[0]] = '0';
		nb[0]++;
		nb[1]--;
	}
	while (n > 0)
	{
		if (nb[2] / n > 9)
			res[nb[0]] = nb[2] / n + 'a' - 10;
		else
			res[nb[0]] = nb[2] / n + '0';
		nb[2] = nb[2] % n;
		n = n / base;
		nb[0]++;
	}
	res[nb[0]] = ' ';
	res[nb[0] + 1] = ':';
	res[nb[0] + 2] = ' ';
	res[nb[0] + 3] = '\0';
	return (res);
}

char					*ft_itoa_base(int n, int base)
{
	char	*res;
	int		nb[3];

	if (!(res = (char *)malloc(sizeof(char) * 10)))
		return (NULL);
	nb[2] = n;
	nb[0] = 1;
	while (n >= base)
	{
		n = n / base;
		nb[0]++;
	}
	n = count(nb[2], base);
	res[0] = '0';
	res[1] = 'x';
	nb[1] = 4 - nb[0];
	nb[0] = 2;
	res = fill_it(nb, res, n, base);
	return (res);
}
