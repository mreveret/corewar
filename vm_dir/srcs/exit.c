/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:12:45 by skpn              #+#    #+#             */
/*   Updated: 2020/07/12 23:49:15 by machoffa         ###   ########.fr       */
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
	{
		ft_putstr("Usage : ./corewar -d N | -n N | -v N path/file.cor\n");
		ft_putstr("Verbose -v N:\n1 - Show Lives\n2 - Show Cycle\n");
		ft_putstr("4 - Show Op\n8 - Show Death\n16 - Show PC movement\n");
	}
	if (i == 1)
		ft_putstr("Wrong option\n");
	if (i == 2)
		ft_putstr("Wrong number of champion\n");
	return ;
}
