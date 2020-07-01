/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:01:25 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/02 00:05:33 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** thus function msut free all malloc'ed dump elements
*/

int		exit_dump(char **ncolonne, char ***xnb, int i)
{
	(void)ncolonne;
	(void)xnb;
	(void)i;
	return (0);
}

void	fill_it(t_vm *x, char ***xnb, char **ncolonne)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		if (i % 32 == 0 && i != 0)
			j++;
		xnb[j][i % 32] = ft_itoa_base2(x->arene[i], 16);
	}
	i = -1;
	while (++i < MEM_SIZE / 32)
	{
		ft_putstr(ncolonne[i]);
		j = -1;
		while (++j < 32)
		{
			ft_putstr(xnb[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

int		ft_dump(t_vm *x)
{
	int		i;
	char	***xnb;
	char	**ncolonne;

	if (!(ncolonne = (char**)malloc(sizeof(char*) * (MEM_SIZE / 32) + 1)))
		return (0);
	if (!(xnb = (char***)malloc(sizeof(char**) * (MEM_SIZE / 32) + 1)))
		return (exit_dump(ncolonne, NULL, 0));
	i = -1;
	while (++i < MEM_SIZE / 32)
	{
		if (!(xnb[i] = (char**)malloc(sizeof(char*) * 32 + 1)))
			return (exit_dump(ncolonne, xnb, i));
		if (!(ncolonne[i] = (char *)malloc(sizeof(char) * 10)))
			return (exit_dump(ncolonne, xnb, i));
		ncolonne[i] = ft_itoa_base(i * 32, 16);
	}
	fill_it(x, xnb, ncolonne);
	return (exit_dump(ncolonne, xnb, i));
}
