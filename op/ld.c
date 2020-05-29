/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:51 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/12 18:31:29 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	op_ld(t_list *list, t_vm *x)
{
	(void)x;
//	printf("arg0 = %d\n",PROCESS->arg[0]);
//	printf("arg1 = %d\n",PROCESS->arg[1]);
	convert_arg(PROCESS->arg,1,list,x);
//	printf("arg0 = %d\n",PROCESS->arg[0]);
//	printf("arg1 = %d\n",PROCESS->arg[1]);
	PROCESS->reg[PROCESS->arg[1]] = PROCESS->arg[0];
	PROCESS->carry = (PROCESS->arg[0] == 0 ? 1 : 0);
	}
