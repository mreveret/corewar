/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:09:30 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/11 18:22:35 by mreveret         ###   ########.fr       */
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

char	*ft_itoa_base2(int n, int base)
{
	char *res;
	int	nb2;
	int	i;

	if(!(res = (char *)malloc(sizeof(char) * 3)))
		return (NULL);
	if (n < 0)
		n = 255 + n;
	nb2 = n;
	i = 1;
	while (n >= base)
	{
		n = n / base;
		i++;
	}
	n = count(nb2, base);
	if (i < 2)
		res[0] = '0';
	else
		i = 0;
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
	res[i] = '\0';
	return (res);
}
