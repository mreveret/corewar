/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:14 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/18 18:12:55 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_aff(char c)
{
	printf("Aff: %c\n", c);
}

void	op_aff(t_list *list, t_vm *x)
{
	(void)	x;
	char	c;

	c = PROCESS->reg[PROCESS->arg[0]] % 256;
	if (x->log & LOG_OP)
		log_aff(c);
	ft_putchar(c);
}
