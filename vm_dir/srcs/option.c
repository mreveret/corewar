/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:49:53 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/12 23:47:20 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	num_players(t_vm *x)
{
	int i;
	int j;
	int k;

	i = 0;
	while (++i < x->nbp + 1)
	{
		j = 0;
		k = 1;
		if (x->opt[i] == 0)
		{
			while (++j < x->nbp + 1)
			{
				if (x->opt[j] == k)
				{
					k++;
					j = 0;
				}
			}
			x->opt[i] = k;
		}
	}
	i = -1;
	while (++i < x->nbp)
		x->p[i].num = x->opt[i + 1];
}

int		create_player(t_vm *x)
{
	t_player	*p;

	p = &(x->p[x->nbp]);
	if (x->opt[x->nbp + 1] != 0)
		p->num = x->opt[x->nbp + 1];
	else
		p->num = x->nbp;
	if (parsingplayer(x, p) == -1)
		return (-1);
	if (++x->nbp > 4)
		return (-1);
	return (0);
}

int		ft_id_player(char **av, int i, t_vm *x)
{
	int id;

	if (av[i + 1])
	{
		if ((id = ft_atoi(av[i + 1])) > 4 || id < 0)
			return (-1);
		x->opt[x->nbp + 1] = id;
	}
	else
		return (-1);
	return (0);
}

int		parsingoption(char **av, int i, t_vm *x)
{
	if (!av[i + 1] || ft_str_is_numeric(av[i + 1]) != 1)
		return (-1);
	if (ft_strcmp(av[i], "-d") == 0 || ft_strcmp(av[i], "-dump") == 0)
	{
		x->dump_line_len = ft_strcmp(av[i], "-d") == 0 ? 64 : 32;
		x->dumpnb = atoi(av[i + 1]);
		return (1);
	}
	if (ft_strcmp(av[i], "-n") == 0)
	{
		x->opt[x->nbp + 1] = 0;
		if (ft_id_player(av, i, x) == -1)
			return (-1);
		x->opt[0] = -1;
		return (2);
	}
	if (ft_strcmp(av[i], "-v") == 0)
	{
		if (ft_str_is_numeric(av[i + 1]) == 1 && (x->log = ft_atoi(av[i + 1])))
			return (3);
		return (-1);
	}
	else
		return (-1);
}
