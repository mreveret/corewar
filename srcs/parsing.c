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
					memcpy(b,x->arene + PROCESS->pc,2);
					PROCESS->arg[i] = ft_convert(b,2); //
					PROCESS->pc = (PROCESS->pc + 2) % MEM_SIZE;
				}//
					printf("arg: %d\n",PROCESS->arg[i]);
		}

			printf("pc after arg dir: %d\n",PROCESS->pc);
		
		else if (PROCESS->t_arg[i] == IND_CODE)
		{
				memcpy(b,x->arene + PROCESS->pc,2);
				PROCESS->arg[i] = ft_convert(b,2);//
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
}

