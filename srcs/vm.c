/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:18:17 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/12 16:18:18 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	convert_arg(int *arg,int mod,t_list *list,t_vm *x)
{
	int	i;
	i = -1;
	while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == IND_CODE ||
		(PROCESS->t_arg[i] == DIR_CODE && 
		PROCESS->op >= 9 && PROCESS->op != 13 && PROCESS->op != 16))
		{
			if (mod == 1)
				PROCESS->arg[i]= PROCESS->pc + (indx_mod(&PROCESS->arg[i]));
			else
				PROCESS->arg[i]= x->arene[PROCESS->pc + PROCESS->arg[i]];
		}
		else
			PROCESS->arg[i] = PROCESS->arg[i];
	}
}
/*
	if (PROCESS->t_arg[i])
}
while (++i < op_tab[PROCESS->op - 1].nb_arg)
	{
		if (PROCESS->t_arg[i] == DIR_CODE)
		{
			if (PROCESS->op < 9 || PROCESS->op == 13 || PROCESS->op == 16)
			{
			memcpy(b,x->arene + PROCESS->pc,4);
			PROCESS->arg[i] = ft_convert(b,4);
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = (PROCESS->pc + 4);
			}
			else
				{
					if (PROCESS->op >= 10 && PROCESS->op <= 12) //
					{ //
					memcpy(b,x->arene + PROCESS->pc,2);

					add = ft_convert(b,2); //
					PROCESS->arg[i] = x->arene[PROCESS->pc + indx_mod(&add)]; //
					}
					else //
					{
						memcpy(b,x->arene + PROCESS->pc,2);
						PROCESS->arg[i] = x->arene[PROCESS->pc + ft_convert(b,2)]; //
					}//
					//	PROCESS->arg[i] = ft_convert(memcpy(b,x->arene + PROCESS->pc,2),2);
					printf("arg: %d\n",PROCESS->arg[i]);
					PROCESS->pc = (PROCESS->pc + 2) % MEM_SIZE;
				}

			printf("pc after arg dir: %d\n",PROCESS->pc);
		}
		else if (PROCESS->t_arg[i] == IND_CODE)
		{
			if (PROCESS->op == 13 || PROCESS->op == 14)//
			{
				memcpy(b,x->arene + PROCESS->pc,2);
				PROCESS->arg[i] = x->arene[PROCESS->pc + ft_convert(b,2)];//
			}
			else//
			{//
					memcpy(b,x->arene + PROCESS->pc,2);
					add = ft_convert(b,2);//
					PROCESS->arg[i] = x->arene[PROCESS->pc + indx_mod(&add)];//
			}//
			//		PROCESS->arg[i] = ft_convert(memcpy(b,x->arene + PROCESS->pc,2),2);
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = (PROCESS->pc + 2) % MEM_SIZE;
		}
		else if (PROCESS->t_arg[i] == REG_CODE)
		{
			
			if (i == op_tab[PROCESS->op - 1].nb_arg - 1)//
			{
				memcpy(b,x->arene + PROCESS->pc,1);
				PROCESS->arg[i] = ft_convert(b,1);
			}
			else//
			{
				memcpy(b,x->arene + PROCESS->pc,1);
				PROCESS->arg[i] = PROCESS->reg[ft_convert(b,1)];//
			}
			printf("arg: %d\n",PROCESS->arg[i]);
			PROCESS->pc = (PROCESS->pc + 1);
			printf("pc after arg reg: %d\n",PROCESS->pc);
		}
	bzero(b,4);
	}
}*/

