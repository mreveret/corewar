/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:01:25 by machoffa          #+#    #+#             */
/*   Updated: 2020/07/06 17:21:40 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** thus function msut free all malloc'ed dump elements
*/

int		exit_dump(char **ncolonne, char ***xnb, int k)
{
	int i;

	i = -1;
	while (++i < k)
	{
		free(xnb[i]);
		free(ncolonne[i]);
	}
	free(xnb);
	free(ncolonne);
	return (0);
}

void	freedump(char ***xnb, char **ncolonne, int dump_line_len)
{
	int i;
	int j;

	i = -1;
	while (++i < MEM_SIZE / dump_line_len)
	{
		j = -1;
		while (++j < dump_line_len)
			free(xnb[i][j]);
		free(xnb[i]);
		free(ncolonne[i]);
	}
	free(xnb);
	free(ncolonne);
}

void	fill_it(t_vm *x, char ***xnb, char **ncolonne)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		if (i % x->dump_line_len == 0 && i != 0)
			j++;
		xnb[j][i % x->dump_line_len] = ft_itoa_base2(x->arene[i], 16);
	}
	i = -1;
	while (++i < MEM_SIZE / x->dump_line_len)
	{
		ft_putstr(ncolonne[i]);
		j = -1;
		while (++j < x->dump_line_len)
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

	if (!(ncolonne = (char**)malloc(sizeof(char*) *
		(MEM_SIZE / x->dump_line_len) + 1)))
		return (0);
	if (!(xnb = (char***)malloc(sizeof(char**)
		* (MEM_SIZE / x->dump_line_len) + 1)))
		return (exit_dump(ncolonne, NULL, 0));
	i = -1;
	while (++i < MEM_SIZE / x->dump_line_len)
	{
		if (!(xnb[i] = (char**)malloc(sizeof(char*) *
			x->dump_line_len + 1)))
			return (exit_dump(ncolonne, xnb, i));
		if (!(ncolonne[i] = (char *)malloc(sizeof(char) * 10)))
			return (exit_dump(ncolonne, xnb, i));
		ncolonne[i] = ft_itoa_base(i * x->dump_line_len, 16);
	}
	fill_it(x, xnb, ncolonne);
	freedump(xnb, ncolonne, x->dump_line_len);
	return (1);
}
