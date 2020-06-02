/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:18:00 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:18:02 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "corewar.h"
#include <stdio.h>

int		parse_typecode(t_list *list,t_vm *x)
{
	if (PROCESS->op != 1 && PROCESS->op != 9 && PROCESS->op != 12
			&& PROCESS->op != 15)
	{
		PROCESS->encoded = (int)(x->arene[move_pc(PROCESS->pc, x->add)]);
		PROCESS->t_arg[0] = (PROCESS->encoded >> 6) & 0b11 ;
	//	printf("typecode: %d\n",PROCESS->t_arg[0]);
		PROCESS->t_arg[1] = (PROCESS->encoded >> 4) & 0b11 ;
	//	printf("typecode: %d\n",PROCESS->t_arg[1]);
		PROCESS->t_arg[2] = (PROCESS->encoded >> 2) & 0b11 ;
	//	printf("typecode: %d\n",PROCESS->t_arg[2]);
		x->add += 1;
	}
	else
	{
		PROCESS->t_arg[0] = DIR_CODE;
	}
	if (!(PROCESS->t_arg[0] & op_tab[PROCESS->op-1].type_arg[0]))
		return (0);
	if (op_tab[PROCESS->op - 1].nb_arg > 1 &&
	(!(PROCESS->t_arg[1] & op_tab[PROCESS->op - 1].type_arg[1])))
		return (0);
	if (op_tab[PROCESS->op - 1].nb_arg > 2 &&
	(!(PROCESS->t_arg[2] & op_tab[PROCESS->op - 1].type_arg[2])))
		return (0);
	return (1);
}

int		parse_arg(t_list *list, t_vm *x)
{
	int i;
	char b[4];
	int ret;

	x->add = 0;
	i = -1;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
		PROCESS->arg[i] = 0;
	ret = parse_typecode(list, x);
//	if (ret == 0)
//		return (ret);
	i = -1;
//	//printf("nb arg: %d\n",op_tab[PROCESS->op - 1].nb_arg);
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == DIR_CODE)
		{
			if (PROCESS->op < 9 || PROCESS->op == 13 || PROCESS->op == 16)
			{
				memcpy(b,x->arene + PROCESS->pc + x->add,4);
				PROCESS->arg[i] = ft_convert(b,4);
				x->add +=4;
			}
			else
			{
				memcpy(b,x->arene + PROCESS->pc + x->add,2);
				PROCESS->arg[i] = (short)ft_convert(b,2);
				x->add+= 2;
			}
//			//printf("arg: %d\n",PROCESS->arg[i]);
		}
		else if (PROCESS->t_arg[i] == IND_CODE)
		{
			memcpy(b,x->arene + PROCESS->pc + x->add,2);
			PROCESS->arg[i] = (short)ft_convert(b,2);
			x->add += 2;
	//		//printf("arg: %d\n",PROCESS->arg[i]);
		}
		else if (PROCESS->t_arg[i] == REG_CODE)
		{

			if (i == op_tab[PROCESS->op - 1].nb_arg - 1)
			{
				memcpy(b,x->arene + PROCESS->pc + x->add,1);
				PROCESS->arg[i] = (char)ft_convert(b,1) - 1;
			}
			else
			{
				memcpy(b,x->arene + PROCESS->pc + x->add,1);
				if (ft_convert(b,1) <= 0 || ft_convert(b,1) > REG_NUMBER)
					ret = 0;
				else
					PROCESS->arg[i] = PROCESS->reg[ft_convert(b,1) - 1];
			}
	//		//printf("arg: %d\n",PROCESS->arg[i]);
			x->add += 1;
			}
		bzero(b,4);
	}
//	printf("ret %d\n",ret);
	return (ret);
}


void	convert_arg(int *arg,int mod,t_list *list,t_vm *x)
{
	int	i;
	i = -1;
	(void)arg;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == IND_CODE /*||
				(PROCESS->t_arg[i] == DIR_CODE && 
				 PROCESS->op >= 9 && PROCESS->op != 13 && PROCESS->op != 16)*/)
		{
			if (mod == 1)
			{
				PROCESS->arg[i]= ft_convert(x->arene + move_pc(PROCESS->pc -1, (indx_mod(&PROCESS->arg[i]))),4);
			}
			else
				PROCESS->arg[i]= ft_convert(x->arene + move_pc(PROCESS->pc -1, PROCESS->arg[i]),4);
		}
	}
}
