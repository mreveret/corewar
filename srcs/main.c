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

void		print_arena(uint8_t *arena, int print_mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%.4d : ", i);
		j = 0;
		while (j < print_mode)
		{
			printf("%.2x ", arena[i + j]);
			j++;
		}
		printf("\n");
		i += print_mode;
	}
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
		x->p[i].pcstart = x->pos_next_player;
//		printf("p[%d] pcstart : %d\n ",i,x->p[i].pcstart);
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
//	printf("name -- %s\n", p->header->prog_name);
//	printf("comment -- %s\n",p->header->comment);
	rev_str((char*)&p->header->magic,sizeof(p->header->magic));
	rev_str((char*)&p->header->prog_size,sizeof(p->header->prog_size));
	
//printf("prog_size -- %d\n",p->header->prog_size);
	ret = read(x->fd,p->content,CHAMP_MAX_SIZE + 1);
	if (ret != (int)p->header->prog_size)
	{
		return (-1);
		}
		x->p[x->nbp - 1] = *p;
		free(p);
//		load_arena(x,&p[0]);
	return (0);
}



int		create_player(t_vm *x)
{
	if(x->nbp > 4)
	return (-1);
	t_player	*p;
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
	//		printf("i:%d\n",i);
			if (parsingoption(av,i,x) == 0)
			{
				x->opt[0] = -1;
				i++;
			}
			else
				return (0);
		}
	}
	if (x->nbp > 4)
	{
		ft_error(0);
		return (0);
	}
	x->pos_add = MEM_SIZE / x->nbp;
	load_arena(x);
	init_vm(x);
	print_arena((uint8_t*)x->arene,64);
	ft_putstr("Le joueur ");
	ft_putstr(ft_itoa(x->last_alive));
	ft_putstr("(");
	ft_putstr(x->p[x->last_alive - 1].header->prog_name);
	ft_putstr(") a gagne\n");
	i = -1;
	printf("cycle to die final : %d\n",x->cycle_to_die);
	printf("cycle: %d\n",x->nb_c);
	return 1;
	}
/*	while (++i < x->nbp)
	{
	free(x->p[i].header);
	free(x->p[i].content);
	}
//	free(x->p);
	x->lst_process = x->first_proc;
	t_list *node;
	while(x->lst_process != NULL)
	{
		node = x->lst_process->next;
		free(x->lst_process);
		x->lst_process = node;

	}
	free(x);
	return 1;
}*/
/*void			rev_str(char *nb, unsigned int size)
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
	i = 0;
	//i = ft_strlen(p->content);
	x->pos_next_player = 0;
	while (++i < MEM_SIZE)
	x->arene[i] = 0;
	i = -1;
	while (++i < x->nbp)
	{
		x->p[i].pcstart = x->pos_next_player;
		printf("p[%d] pcstart : %d\n ",i,x->p[i].pcstart);
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
	rev_str((char*)&p->header->magic,sizeof(p->header->magic));
	rev_str((char*)&p->header->prog_size,sizeof(p->header->prog_size));

//printf("prog_size -- %d\n",p->header->prog_size);
	ret = read(x->fd,p->content,CHAMP_MAX_SIZE + 1);
	if (ret != (int)p->header->prog_size)
	{
		return (-1);
		}
		x->p[x->nbp - 1] = *p;
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
	t_vm		*x;
	char		*test;

	i = 0;
	if (!(x = (t_vm *)malloc(sizeof(t_vm))))
		return (-1);
	x->nbp = 0;
	while (++i < ac)
	{
		if ((test = ft_strrchr(av[i], '.')) && ft_strcmp(test, ".cor") == 0)
		{
			x->fd = open(av[i], O_RDONLY);
			create_player(x);
			x->opt[0] = 0;
		}
		else
		{
			if (parsingoption(av, i, x) > 0)
				i++;
			else
				return (0);
		}
	}
	if (x->nbp > 4)
	{
		ft_error(0);
		return (0);
	}
	num_players(x);
	return (1);
	x->pos_add = MEM_SIZE / x->nbp;
	load_arena(x);
	init_vm(x);
	ft_putstr("Le joueur ");
	ft_putstr(ft_itoa(x->last_alive));
	ft_putstr("(");
	ft_putstr(x->p[x->last_alive - 1].header->prog_name);
	ft_putstr(") a gagne\n");
	i = -1;
	printf("cycle to die final : %d\n",x->cycle_to_die);
	printf("cycle: %d\n",x->nb_c);

	return 1;
}*/
