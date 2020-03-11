/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:01:25 by machoffa          #+#    #+#             */
/*   Updated: 2020/03/11 18:16:56 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_dump(t_vm *x)
{
	int i;
	int j;
	char	***xnb;
	char	**ncolonne;

	if (!(ncolonne = (char**)malloc(sizeof(char*) * (MEM_SIZE / 64) + 1)))
		return ;
	if (!(xnb = (char***)malloc(sizeof(char**) * (MEM_SIZE / 64) + 1)))
		return ;
	i = -1;
	while (++i < MEM_SIZE / 64)
	{
		if (!(xnb[i] = (char**)malloc(sizeof(char*) * 64 + 1)))
			return ;
		if (!(ncolonne[i] = (char *)malloc(sizeof(char) * 10)))
			return ;
		ncolonne[i] = ft_itoa_base(i * 64, 16);
	}
	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			j++;
		xnb[j][i % 64] = ft_itoa_base2(x->arene[i], 16);
	}
	i = -1;
	while (++i < MEM_SIZE / 64)
	{
		ft_putstr(ncolonne[i]);
		j = -1;
		while (++j < 64)
		{
			ft_putstr(xnb[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	return ;
}