/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:21:27 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/15 14:43:45 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		count(unsigned int nb)
{
	unsigned int	count;

	count = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		count = count * 10;
	}
	return (count);
}

static unsigned int		size(int nb)
{
	unsigned int i;

	i = 0;
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

char					*ft_itoa(int n)
{
	unsigned int	nb;
	int				neg;
	char			*res;

	nb = n;
	neg = 0;
	if (n < 0)
	{
		nb = -n;
		neg = 1;
	}
	if (!(res = ft_memalloc(size(nb) + neg + 1)))
		return (NULL);
	if (neg == 1)
		res[0] = '-';
	n = count(nb);
	while (n > 0)
	{
		res[neg] = nb / n + '0';
		nb = nb % n;
		n = n / 10;
		neg++;
	}
	res[neg + 1] = '\0';
	return (res);
}
