/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:14 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:22:15 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_aff(t_list *list, t_vm *x)
{
	(void)x;
	char c;

	c = PROCESS->reg[PROCESS->arg[0]] % 256;
	ft_putendl(&c);
}
