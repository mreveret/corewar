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

/*unsigned char *uc2c(unsigned char *c)
{
	int i = 0;
	while (i++ < 4)
	{
		c[i] = c[i] - 255 - 1 - 255 - 1;
	printf("test\n");
	}
	return (c);
}
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
}*/

int		ft_convert(unsigned char *test, int size)
{
	int res;
	int i;
	i =  -1;

	res = 0;
	while (++i < size)
	{
		res <<= 8;
		res |= 0x000000FF & test[i];
	}
	return (res);
	}
/*	int res;
	int i;

	i = 0;
	i = size;//strlen(test);
	res = 0;
	res = (unsigned int)test[i - 1];
	while (--i > 0)
	{
	res = ft_pow(res,test[i-1]);
	}
//	if (res < -128)
//	{
//	printf("res = %d\n",res);
//	return (ft_convert(uc2c(test),size));
//	}
//	else
		return (res); }*/
