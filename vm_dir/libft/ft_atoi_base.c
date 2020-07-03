/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:10:04 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/15 12:50:11 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			length_base(char *base)
{
	int i;
	int j;

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

static int			get_nb(char c, char *base)
{
	int i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

static int			check_error(const char *str, char *base)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && (str[i] < 33 || str[i] == 127))
		i++;
	while (str[i])
	{
		j = 0;
		while (base[j] && base[j] != str[i])
			++j;
		if (base[j] != str[i] && (str[i] != '-' && str[i] != '+'))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int					ft_atoi_base(const char *str, char *base)
{
	int		i;
	int		res;
	int		neg;
	int		length;

	i = 0;
	res = 0;
	neg = 1;
	if (!(length = length_base(base)) || !check_error(str, base))
		return (0);
	while (str[i] && (str[i] < 33 || str[i] == 127))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] && str[i] != '+' && str[i] != '-')
		res = (res * length) + (get_nb(str[i++], base));
	return (res * neg);
}
