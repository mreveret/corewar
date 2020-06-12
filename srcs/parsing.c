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
		PROCESS->t_arg[0] = (((PROCESS->encoded >> 6) & 0b11) == 3 ? 4:(PROCESS->encoded >> 6) & 0b11) ;
	//	printf("typecode: %d\n",PROCESS->t_arg[0]);
	//	printf("arg1:%d\n",(PROCESS->encoded >> 6) & 0b11);
		PROCESS->t_arg[1] = (((PROCESS->encoded >> 4) & 0b11) == 3 ? 4:(PROCESS->encoded >> 4) & 0b11) ;
	//	printf("arg2:%d\n",(PROCESS->encoded >> 4) & 0b11);
	//	printf("typecode: %d\n",PROCESS->t_arg[1]);
		PROCESS->t_arg[2] = (((PROCESS->encoded >> 2) & 0b11) == 3 ? 4:(PROCESS->encoded >> 2) & 0b11) ;
	//	printf("arg3:%d\n",(PROCESS->encoded >> 2) & 0b11);
	//	printf("typecode: %d\n",PROCESS->t_arg[2]);
		x->add += 1;
	}
	else
	{
		PROCESS->t_arg[0] = DIR_CODE;
	}
	if (!(PROCESS->t_arg[0] & op_tab[PROCESS->op-1].type_arg[0]))
	{
		//printf("FAUX");
		return (0);
	}
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
	//char b[4];
	int ret;

	x->add = 0;
	i = -1;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
		PROCESS->arg[i] = 0;
	ret = parse_typecode(list, x);
	//	printf("ret %d\n",ret);
	if (ret == 0)
	{
	//	printf("ret %d\n",ret);
		return (ret);
	}
	i = -1;
//	//printf("nb arg: %d\n",op_tab[PROCESS->op - 1].nb_arg);
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == DIR_CODE)
		{
			if (PROCESS->op < 9 || PROCESS->op == 13 || PROCESS->op == 16)
			{
			//	memcpy(b,x->arene + PROCESS->pc + x->add,4);
				PROCESS->arg[i] = ft_convert(x,list,4);
				x->add +=4;
			}
			else
			{
			//	memcpy(b,x->arene + PROCESS->pc + x->add,2);
				PROCESS->arg[i] = (short)ft_convert(x,list,2);
				x->add+= 2;
			}
//			//printf("arg: %d\n",PROCESS->arg[i]);
		}
		else if (PROCESS->t_arg[i] == T_IND)
		{
		//	memcpy(b,x->arene + PROCESS->pc + x->add,2);
			PROCESS->arg[i] = (short)ft_convert(x,list,2);
			x->add += 2;
	//		//printf("arg: %d\n",PROCESS->arg[i]);
		}
		else if (PROCESS->t_arg[i] == REG_CODE)
		{

			if (i == op_tab[PROCESS->op - 1].nb_arg - 1)
			{
			//	memcpy(b,x->arene + PROCESS->pc + x->add,1);
				PROCESS->arg[i] = (char)ft_convert(x,list,1) - 1;
			}
			else
			{
				//memcpy(b,x->arene + PROCESS->pc + x->add,1);
				if (ft_convert(x,list,1) <= 0 || ft_convert(x,list,1) > REG_NUMBER)
					ret = 0;
				else
					PROCESS->arg[i] = PROCESS->reg[ft_convert(x,list,1) - 1];
			}
	//		//printf("arg: %d\n",PROCESS->arg[i]);
			x->add += 1;
			}
	//	bzero(b,4);
	}
//	printf("ret %d\n",ret);
	return (ret);
}

int		ft_convert2(t_vm *x, int size,t_list *list,int j)
{
	int res;
	int i;
//	int idx;
//	idx = indx_mod(PROCESS->arg[j]);
	i =  -1;

	res = 0;
	while (++i < size)
	{
		res <<= 8;
		res |= 0x000000FF & x->arene[move_pc(PROCESS->pc -1,PROCESS->arg[j] + i)];
	}
	return (res);
	}
void	convert_arg(int *arg,int mod,t_list *list,t_vm *x)
{
	int	i;
	i = -1;
	(void)arg;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == T_IND /*||
				(PROCESS->t_arg[i] == DIR_CODE && 
				 PROCESS->op >= 9 && PROCESS->op != 13 && PROCESS->op != 16)*/)
		{
			if (mod == 1)
			{
				PROCESS->arg[i] = indx_mod(&PROCESS->arg[i]);
				PROCESS->arg[i]= ft_convert2(x,4,list,i);
			}
			else
				PROCESS->arg[i]= ft_convert2(x,4,list,i);
		}
	}
}
