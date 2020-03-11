/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:11:00 by machoffa          #+#    #+#             */
/*   Updated: 2020/03/11 18:08:15 by mreveret         ###   ########.fr       */
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

char	*ft_itoa_base(int n, int base)
{
	char *res;
	int	nb2;
	int	i;
	int	j;

	if(!(res = (char *)malloc(sizeof(char) * 10)))
		return (NULL);
	nb2 = n;
	i = 1;
	while (n >= base)
	{
		n = n / base;
		i++;
	}
	n = count(nb2, base);
	res[0] = '0';
	res[1] = 'x';
	j = 4 - i;
	i = 2;
	while (j > 0)
	{
		res[i] = '0';
		i++;
		j--;
	}
	while (n > 0)
	{
		if (nb2 / n > 9)
			res[i] = nb2 / n + 'a' - 10;
		else
			res[i] = nb2 / n + '0';
		nb2 = nb2 % n;
		n = n / base;
		i++;
	}
	res[i] = ' ';
	res[i + 1] = ':';
	res[i + 2] = ' ';
	res[i + 3] = '\0';
	return (res);
}
