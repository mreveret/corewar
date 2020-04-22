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
	if (PROCESS->t_arg[1] == 3)
	
		x->arene[PROCESS->arg[1] % IDX_MOD] = PROCESS->reg[PROCESS->arg[0]];
else if (PROCESS->t_arg[1] == 1)
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->reg[PROCESS->arg[0]];
	
}
