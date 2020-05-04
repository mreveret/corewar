/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:33:28 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 18:35:39 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_st(t_list *list, t_vm *x)
{
	int *ptr;
	ptr = NULL;
	if (PROCESS->t_arg[0] != REG_CODE)
	return;
	if (PROCESS->t_arg[1] == 3)
	{
		ptr = (int*)x->arene + PROCESS->arg[1];
		*ptr = PROCESS->arg[0];
	}
else if (PROCESS->t_arg[1] == 1)
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	else
		return ;
	
}
