/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:33:10 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 16:40:57 by mreveret         ###   ########.fr       */
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
	{
		x->p[i].num = x->opt[i + 1];		
		printf("player[%d] num: %d\n",i,x->p[i].num);
	}
}

int		create_player(t_vm *x)
{
	t_player	*p;

	if(x->nbp > 4)
	    return (-1);
	if (!(p = (t_player *)malloc(sizeof(t_player))))
		return (-1);
	if (!(p->header = (header_t *)malloc(sizeof(header_t))))
		return (-1);
	if (!(p->content = (char*)malloc(sizeof(char) * CHAMP_MAX_SIZE + 1)))
	    return (-1);
	x->nbp++;
	if (x->opt[x->nbp + 1] != 0)
		p->num = x->opt[x->nbp + 1];
	else
		p->num = x->nbp;
	parsingplayer(x, p);
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

int		parsingoption(char **av,int i, t_vm *x)
{
	if (av[i + 1] && ft_str_is_numeric(av[i + 1]) != 1)
			return (-1);
	if (ft_strcmp(av[i],"-d") == 0)
	{
			x->dumpnb = atoi(av[i + 1]);
			ft_dump(x);
			return (1);
	}
	if (ft_strcmp(av[i], "-n") == 0)
	{
		x->opt[x->nbp + 1] = 0;
		if (ft_id_player(av, i, x) == -1)
			return (-1);
		x->opt[0] = -1;
		return(2);
	}
	else
	{
		ft_error(1);
		return (-1);
	}
}
