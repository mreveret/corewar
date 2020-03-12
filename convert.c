/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:02:24 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 16:06:52 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
static int		ft_pow(int res,char c)
{
	int res2;
	int pow;
	int	ten;
	pow = 0;
	res2 = res;
	while (res2 > 0)
	{
		res2 /= 10;
		pow++;
	}
	ten = (int)c;
	while (pow > 0)
	{
		ten *= 10;
		pow--;
	}
	res2 = ten + res;
	return (res2);
}

int		ft_convert(char *test)
{
	int res;
	int i;

	i = 0;
	i = strlen(test);
	res = 0;
	res = (int)test[i - 1];
	while (--i > 0)
	{
	res = ft_pow(res,test[i-1]);
	}
	return (res);
}
