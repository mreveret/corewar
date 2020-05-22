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
#include <stdio.h>

void	op_st(t_list *list, t_vm *x)
{
	int *ptr;
//	convert_arg(PROCESS->arg,1,list,x);
	ptr = NULL;
	if (PROCESS->t_arg[0] != REG_CODE)
	return;
	if (PROCESS->t_arg[1] == IND_CODE)
	{
//		printf("mvpc_st:%d\n",move_pc(0,PROCESS->arg[1]));
		ptr = (int*)(x->arene + move_pc(PROCESS->pc - 1, PROCESS->arg[1]));
		*ptr = PROCESS->arg[0];
		rev_str(x->arene + move_pc(PROCESS->pc - 1,PROCESS->arg[1]),4);
	}
else if (PROCESS->t_arg[1] == REG_CODE)
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	else
		return ;
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);
	
}
