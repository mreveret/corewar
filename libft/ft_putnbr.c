/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:21:26 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/09 17:34:57 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr(int n)
{
	unsigned int	nb;
	unsigned int	nb2;
	unsigned int	count;

	count = 1;
	nb = n;
	if (n < 0)
	{
		nb = -n;
		ft_putchar('-');
	}
	nb2 = nb;
	while (nb >= 10)
	{
		nb = nb / 10;
		count = count * 10;
	}
	while (count >= 10)
	{
		ft_putchar(nb2 / count + '0');
		nb2 = nb2 % count;
		count = count / 10;
	}
	ft_putchar(nb2 + '0');
}
