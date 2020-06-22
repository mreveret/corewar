/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:33:10 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/19 10:11:03 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void			rev_str(char *nb, unsigned int size)
{
	unsigned int	i;
	char			tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = nb[i];
		nb[i] = nb[size - i - 1];
		nb[size - i - 1] = tmp;
		++i;
	}
}

void	load_arena(t_vm *x)
{
	int i;
	i = -1;
	//i = ft_strlen(p->content);
	x->pos_next_player = 0;
	while (++i < MEM_SIZE)
	x->arene[i] = 0;
	i = -1;
	while (++i < x->nbp)
	{
		x->p[i].pcstart = x->pos_next_player;
		memcpy(x->arene + x->pos_next_player, x->p[i].content,
			x->p[i].header.prog_size);
	//	while(1);
//	while (1);
		x->pos_next_player += x->pos_add;
	}
//	while (1);
//	ft_dump(x);
}

int		parsingplayer(t_vm *x, t_player *p)
{
	int			ret;
	header_t	*header;

	header = &p->header;
	ret = read(x->fd, header, sizeof(header_t));
	if (ret != (int)sizeof(header_t))
		return (-1);
	//printf("name -- %s\n", header->prog_name);
	//printf("comment -- %s\n",header->comment);
	rev_str((char*)&header->magic, sizeof(header->magic));
	rev_str((char*)&header->prog_size, sizeof(header->prog_size));

////printf("prog_size -- %d\n",header->prog_size);
	ret = read(x->fd, &p->content,CHAMP_MAX_SIZE + 1);
	if (ret != (int)header->prog_size || header->prog_size > CHAMP_MAX_SIZE)
	{
		return (-1);
		}
	x->p[x->nbp] = *p;
//		load_arena(x,&p[0]);
	return (0);
}

void	ft_error(int i)
{
	if (i == 0)
		ft_putstr("Error\n");
	if (i == 1)
		ft_putstr("Wrong option\n");
	return ;
}

int		main(int ac, char **av)
{
	int			i;
	t_vm		ouzeyiflbkn_apres_tout_hein;
	t_vm		*x;
	char		*test;

	i = 0;
	x = &ouzeyiflbkn_apres_tout_hein;
	ft_memset(x, 0, sizeof(ouzeyiflbkn_apres_tout_hein));
	x->nbp = 0;
	while (++i < ac)
	{
		if ((test = ft_strrchr(av[i], '.')) && ft_strcmp(test, ".cor") == 0)
		{
			if ((x->fd = open(av[i], O_RDONLY)) == -1)
				return (exit_corewar(x, -1));
			if (create_player(x) == -1)
				return (exit_corewar(x, -1));
			x->opt[0] = 0;
		}
		else
		{
			if (parsingoption(av, i, x) > 0)
				i++;
			else
				return (exit_corewar(x, 0));
		}
	}
	if (x->nbp > 4 || x->nbp < 1)
	{
		ft_error(0);
		return (exit_corewar(x, 0));
	}
	num_players(x);
	x->pos_add = MEM_SIZE / x->nbp;
	load_arena(x);
	init_vm(x);
	//ft_putstr("Le joueur ");
	//ft_putstr(ft_itoa(x->winner));
	//ft_putstr("(");
	//ft_putstr(x->p[x->winner - 1].header->prog_name);
	//ft_putstr(") a gagne\n");
	//i = -1;
//	printf("cycle to die final : %d\n",x->cycle_to_die);
//	printf("cycle: %d\n",x->nb_c);

	return (exit_corewar(x, 1));
}
