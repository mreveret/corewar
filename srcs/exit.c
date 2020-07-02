/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:12:45 by skpn              #+#    #+#             */
/*   Updated: 2020/07/02 18:57:42 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		exit_corewar(t_vm *x, int ret)
{
	t_list	*tmp;

	while (x->lst_process)
	{
		tmp = x->lst_process;
		x->lst_process = x->lst_process->next;
		free(tmp->content);
		free(tmp);
	}
	return (ret);
}

void	ft_error(int i)
{
	if (i == 0)
		ft_putstr("Error\n");
	if (i == 1)
		ft_putstr("Wrong option\n");
	return ;
}
