/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:22:14 by mreveret          #+#    #+#             */
/*   Updated: 2020/07/01 18:50:07 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_aff(char c)
{
	ft_printf("Aff: %c\n", c);
}

void	op_aff(t_list *list, t_vm *x)
{
	char	c;

	(void)x;
	c = ((t_p *)list->content)->reg[((t_p *)list->content)->arg[0]] % 256;
	if (x->log & LOG_OP)
		log_aff(c);
	ft_putchar(c);
}
