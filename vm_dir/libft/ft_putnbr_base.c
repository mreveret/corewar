/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:00:21 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/15 12:53:13 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_base_length(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			++j;
		}
		++i;
	}
	if (i < 2)
		return (0);
	return (i);
}

void			ft_putnbr_base(int nbr, char *base)
{
	unsigned int i;
	unsigned int nb2;

	nb2 = nbr;
	if (nbr < 0)
	{
		nb2 = -nbr;
		ft_putchar('-');
	}
	if (!(i = get_base_length(base)))
		return ;
	if (nb2 > i - 1)
		ft_putnbr_base(nb2 / i, base);
	ft_putchar(base[nb2 % i]);
}
