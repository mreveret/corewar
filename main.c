/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:33:10 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/04 17:28:18 by mreveret         ###   ########.fr       */
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
void	ft_dump(t_vm *x)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			printf(" \n");
		if (i % 64 == 0 && i != (MEM_SIZE - 1))
			printf("0x%04x :",i);
		if (i % 1 == 0)
			printf(" ");
		printf("%0.2hhx",x->arene[i]);
		i++;
	}
	//printf("arene --\n%s\n",x->arene);
	return ;
}
void	load_arena(t_vm *x)
{
	int i;
	i = 0;
	//i = ft_strlen(p->content);
	x->pos_next_player = 0;
	while (++i < MEM_SIZE)
	x->arene[i] = 0;
	i = -1;
	while (++i < x->nbp)
	{
		memcpy(x->arene + x->pos_next_player ,x->p[i].content,x->p[i].header->prog_size);
		x->pos_next_player += x->pos_add;
	}
	ft_dump(x);
}

int		parsingplayer(t_vm *x, t_player *p)
{
	int	ret;

	ret = read(x->fd,p->header, sizeof(header_t));
	if (ret != (int)sizeof(header_t))
		return (-1);
	printf("name -- %s\n", p->header->prog_name);
	printf("comment -- %s\n",p->header->comment);
	rev_str((char*)&p->header->prog_size,sizeof(p->header->prog_size));
	
printf("prog_size -- %d\n",p->header->prog_size);
	ret = read(x->fd,p->content,CHAMP_MAX_SIZE + 1);
	if (ret != (int)p->header->prog_size)
	{
		return (-1);
		}
		x->p[x->nbp - 1] = *p;
//		load_arena(x,&p[0]);
	return (0);
}



int		create_player(t_vm *x)
{
	t_player	*p;
	if (x->nbp >= 4)
		return (-1);
	if (!(p = (t_player *)malloc(sizeof(t_player))))
		return (-1);
	if (!(p->header = (header_t *)malloc(sizeof(header_t))))
		return (-1);
	if (!(p->content = (char*)malloc(sizeof(char) * CHAMP_MAX_SIZE + 1)))
	return (-1);
			x->nbp++;
	
	p->num = x->nbp;
	if(x->opt[0] >= 0)
	parsingplayer(x,p);
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

int		ft_id_player(char **av, int i, t_vm *x)
{
	int id;

	if (av[i + 1])
	{
		if ((id = ft_atoi(av[i + 1])) > 4 || id < 0)
			return (-1);
		x->opt[0] = id;
	}
	else
	return (-1);
	return (0);
}



int		parsingoption(char **av,int i, t_vm *x)
{
	if (ft_strcmp(av[i],"-dump") == 0)
	{
		ft_dump(x);
		return (1);
	}
	if (ft_strcmp(av[i], "-n") == 0)
	{
		create_player(x);
		if (ft_id_player(av,i,x) == -1)
			return (-1);
			return(1);
	}
	else
	{
		ft_error(1);
		return (-1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	int			i;
	t_vm		*x;
	char		*test;

	i = 0;
	if (!(x = (t_vm *)malloc(sizeof(t_vm))))
		return (-1);
	x->nbp = 0;
	while (++i < ac)
	{
		if ((test = ft_strrchr(av[i],'.')) && ft_strcmp(test,".cor") == 0)
		{
			x->fd = open(av[i], O_RDONLY);
			if (x->opt[0] != -1)
			create_player(x);
			x->opt[0] = 0;
		}
		else
		{
			printf("i:%d\n",i);
			if (parsingoption(av,i,x) == 0)
			{
				x->opt[0] = -1;
				i++;
			}
			else
				return (0);
		}
	}
	x->pos_add = MEM_SIZE / x->nbp;
	load_arena(x);
	return 1;
}
