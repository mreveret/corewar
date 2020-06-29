/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:09:30 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/29 18:32:51 by machoffa         ###   ########.fr       */
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

static char				*fill_it(char *res, int *nb, int n, int base)
{
	if (nb[0] < 2)
		res[0] = '0';
	else
		nb[0] = 0;
	while (n > 0)
	{
		if (nb[1] / n > 9)
			res[nb[0]] = nb[1] / n + 'a' - 10;
		else
			res[nb[0]] = nb[1] / n + '0';
		nb[1] = nb[1] % n;
		n = n / base;
		nb[0]++;
	}
	res[nb[0]] = '\0';
	return (res);
}

char					*ft_itoa_base2(int n, int base)
{
	char	*res;
	int		nb[2];

	if (!(res = (char *)malloc(sizeof(char) * 3)))
		return (NULL);
	if (n < 0)
		n = 256 + n;
	nb[1] = n;
	nb[0] = 1;
	while (n >= base)
	{
		n = n / base;
		nb[0]++;
	}
	n = count(nb[1], base);
	res = fill_it(res, nb, n, base);
	return (res);
}
