/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:33:10 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/18 17:13:37 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

int		parsingplayer(int fd, t_vm *x)
{
	t_player	*p;

	if (x->nbp >= 4)
		return (-1);
	if (!(p = (t_player *)malloc(sizeof(t_player))))
		return (-1);
//	read(fd, p->header->prog_name, PROG_NAME_LENGTH);
	read(fd, p->header->prog_name, 5);
//	read(fd, p->header->comment, COMMENT_LENGTH);
	read(fd, p->header->comment, 5);
//	p->header->prog_name[PROG_NAME_LENGTH] = '\0';
	p->header->prog_name[5] = '\0';
//	p->header->comment[COMMENT_LENGTH] = '\0';
	p->header->comment[5] = '\0';
	printf("name -- %s\n", p->header->prog_name);
	printf("comment -- %s\n",p->header->comment);

	return (0);
}

int		main(int ac, char **av)
{
	int			fd;
	int			i;
	t_vm		*x;

	i = 0;
	if (!(x = (t_vm *)malloc(sizeof(t_vm))))
		return (-1);
	x->nbp = 0;
	while (++i < ac)
	{
//		if (ft_strcmp(av[i], ".cor") == 0)
//		{
			fd = open(av[i], O_RDONLY);
			parsingplayer(fd, x);
			x->nbp++;
//		}
	//	else
	//		parsingoption(av[i]);
	}

	return 1;
}
