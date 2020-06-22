/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:33:28 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/19 10:55:54 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	log_st(t_list *list)
{
	printf("P %4d | st r%d %s%d\n", PROCESS->id, PROCESS->reg_num[0],
		(PROCESS->t_arg[1] == T_IND ? "" : "r"), (PROCESS->t_arg[1] == T_IND ? PROCESS->arg[1]: PROCESS->reg_num[1]));
}

void	op_st(t_list *list, t_vm *x)
{
	unsigned    oct;
	int			tmp_pc;
	oct = 4;
	tmp_pc = 0;
	if (x->log & LOG_OP)
		log_st(list);
	// convert_arg(PROCESS->arg,0,list,x);
	if (PROCESS->t_arg[1] == T_IND)
	{
		tmp_pc = move_pc(PROCESS->pc - 1,PROCESS->arg[1] % IDX_MOD);
		tmp_pc = move_pc(tmp_pc,oct);
		while (oct)
		{
			tmp_pc = move_pc(tmp_pc, -1);
			x->arene[tmp_pc] = PROCESS->arg[0] >> (8 * (4 - oct));
			oct--;
		}
	}
	else if (PROCESS->t_arg[1] == REG_CODE)
	{
		if (PROCESS->arg[1] >= REG_NUMBER || PROCESS->arg[1] < 0)
			return;
		PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	}
	else
		return ;

}
/*	int *ptr;
//	convert_arg(PROCESS->arg,0,list,x);
//	ptr = NULL;
if (PROCESS->t_arg[1] == T_IND)
{
//		//printf("mvpc_st:%d\n",move_pc(0,PROCESS->arg[1]));
//	PROCESS->arg[1] = indx_mod(&PROCESS->arg[1]);
ptr = (int*)(x->arene + move_pc(PROCESS->pc - 1, PROCESS->arg[1] % IDX_MOD));
 *ptr = PROCESS->arg[0];
 rev_str(x->arene + move_pc(PROCESS->pc - 1,PROCESS->arg[1] % IDX_MOD),4);
 }
 else if (PROCESS->t_arg[1] == REG_CODE)
 {
 if (PROCESS->arg[1] >= REG_NUMBER || PROCESS->arg[1] < 0)
 return;
 PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
 }
 else
 return ;
//printf("arg0 = %d\n",PROCESS->arg[0]);
//printf("arg1 = %d\n",PROCESS->arg[1]);
//printf("arg2 = %d\n",PROCESS->arg[2]);
PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);

}*/
