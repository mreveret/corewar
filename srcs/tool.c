/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:11:32 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/11 18:01:28 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

char			*ft_strsubzero(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	//if (!(s))
	//	return (NULL);
	if (!(dst = ft_memalloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

t_process		*create_process(int id, int pc)
{
	t_process	*proc;
	int			i;
	if (!(proc = (t_process*)malloc(sizeof(t_process))))
		return (0);
	i = -1;
	proc->id = id;
	proc->alive = 1000;
	if (pc > 0)
		proc->alive = 500;
	proc->pc = pc % MEM_SIZE;
	proc->wait = 0;
	while (++i)
	{
		if (i == 1)
			proc->reg[i] = id;
		else
			proc->reg[i] = 0;
	}
	return (proc);
}

void		wait_queue(t_process *proc)
{
	if (proc->op == 1 || proc->op == 4 || proc->op == 5 || proc->op == 13)
		proc->wait = 10;
	else if (proc->op == 2 || proc->op == 3)
		proc->wait = 5;
	else if (proc->op == 6 || proc->op == 7 || proc->op == 8)
		proc->wait = 6;
	else if (proc->op == 9)
		proc->wait = 20;
	else if (proc->op == 10 || proc->op == 11)
		proc->wait = 25;
	else if (proc->op == 12)
		proc->wait = 800;
	else if (proc->op == 14)
		proc->wait = 50;
	else if (proc->op == 15)
		proc->wait = 1000;
	else if (proc->op == 16)
		proc->wait = 2;
	//	else if (proc->op >16 || proc->op < 1)
	//	proc->wait = -1;
}

void		load_vm(t_vm *x)
{
	t_list	*list;
	int		i;

	list = x->first_proc;
	// TEST LIST //
	if (x->nb_c == 0)
		printf("Cycle numero %d\n",x->nb_c);
	while (list != NULL)
	{
		if (PROCESS->wait == 0)
		{
			if (PROCESS->op != 0)
			{
				PROCESS->encoded = (int)(x->arene[PROCESS->pc]);
				printf("encoded byte %d\n",PROCESS->encoded);
				PROCESS->enc[0] = PROCESS->encoded & 0b11000000;
				if (PROCESS->enc[0] == 128)
				{
					PROCESS->t_arg[0] = DIR_CODE;
					printf("argument 1 = DIRECT\n");
				}
				else if (PROCESS->enc[0] == 192)
				{
					PROCESS->t_arg[0] = IND_CODE;
					printf("argument 1 = INDIRECT\n");
				}
				else if (PROCESS->enc[0] == 64)
				{
					PROCESS->t_arg[0] = REG_CODE;
					printf("argument 1 = REGISTER\n");
				}
				else
				{
					PROCESS->arg[0] = 0;
					printf("error arg\n");
				}
				PROCESS->enc[1] = PROCESS->encoded & 0b00110000;
				if (PROCESS->enc[1] == 32)
				{
					PROCESS->t_arg[1] = DIR_CODE;
					printf("argument 2 = DIRECT\n");
				}
				else if (PROCESS->enc[1] == 48)
				{
					PROCESS->t_arg[1] = IND_CODE;
					printf("argument 2 = INDIRECT\n");
				}
				else if (PROCESS->enc[1] == 16)
				{
					PROCESS->t_arg[1] = REG_CODE;
					printf("argument 2 = REGISTER\n");
				}
				else
				{
					PROCESS->t_arg[1] = 0;
					printf("pas de 2e arg\n");
				}
				PROCESS->enc[2] = PROCESS->encoded & 0b00001100;
				if (PROCESS->enc[2] == 8)
				{
					PROCESS->t_arg[2] = DIR_CODE;
					printf("argument 3 = DIRECT\n");
				}
				else if (PROCESS->enc[2] == 12)
				{
					PROCESS->t_arg[2] = IND_CODE;
					printf("argument 3 = INDIRECT\n");
				}
				else if (PROCESS->enc[2] == 4)
				{
					PROCESS->t_arg[2] = REG_CODE;
					printf("argument 3 = REGISTER\n");
				}
				else
				{
					PROCESS->t_arg[2] = 0;
					printf("pas de 3e arg\n");
				}
				PROCESS->enc[3] = PROCESS->encoded & 0b00000011;
				if (PROCESS->enc[3] == 2)
				{
					PROCESS->t_arg[3] = DIR_CODE;
					printf("argument 4 = DIRECT\n");
				}
				else if (PROCESS->enc[3] == 3)
				{
					PROCESS->t_arg[3] = IND_CODE;
					printf("argument 4 = INDIRECT\n");
				}
				else if (PROCESS->enc[3] == 1)
				{
					PROCESS->t_arg[3] = REG_CODE;
					printf("argument 4 = REGISTER\n");
				}
				else
				{
					PROCESS->t_arg[3] = 0;
					printf("pas de 4e arg\n");
				}
				i = -1;
				while (++i < 4)
				{
					if (PROCESS->t_arg[i] == DIR_CODE)
					{
						PROCESS->arg[i] = ft_strsub(x->arene,PROCESS->pc,4);
						PROCESS->pc_arg += 4;
					}
					else if (PROCESS->t_arg[i] == IND_CODE)
					{
						PROCESS->arg[i] = ft_strsub(x->arene,PROCESS->pc,2);
						PROCESS->pc_arg += 2;
					}
					else if (PROCESS->t_arg[i] == REG_CODE)
					{
						PROCESS->arg[i] = ft_strsub(x->arene,PROCESS->pc,4);
						PROCESS->pc_arg += 4;
					}
				}
			}
			//	else
			//	{
			PROCESS->op = (int)(x->arene[PROCESS->pc]);

			if (PROCESS->op > 0 && PROCESS->op < 17)
			{
				printf("op %d\n",PROCESS->op);
				wait_queue(PROCESS);
			}
			PROCESS->pc = (PROCESS->pc + 1) % MEM_SIZE;
			//		printf("seg2: %d\n",PROCESS->alive);
			}
			else
			PROCESS->wait--;


			printf("wait = %d\n",PROCESS->wait);
			list = list->next;
		}
//	
	x->nb_c++;
	printf("Cycle numero %d\n",x->nb_c);
	return ;
}

void		init_vm(t_vm *x)
{
	int		i;
	t_list	*tmp;

	i = -1;
	if(!(x->lst_process = (t_list *)malloc(sizeof(t_list))))
		return ;
	if(!(tmp = (t_list *)malloc(sizeof(t_list))))
		return;
	x->lst_process = NULL;
	while (++i < x->nbp)
	{

		printf ("i : %d\n", i );
		tmp = ft_lstnew(create_process(x->p[i].num,x->p[i].pcstart),sizeof(t_process));
		//	tmp->next = NULL;
		ft_lstadd(&x->lst_process,tmp);
		//		if (i == 0)
		//		x->lst_process->next = NULL;

		if (i == x->nbp - 1)
		{
			x->first_proc = x->lst_process;
			//			x->first_proc->next = NULL;
		}
		printf("pc tmp: %d\n",((t_process *)x->lst_process->content)->pc);
		//x->lst_process = x->lst_process->next;
	}
	free(tmp);
	x->cycle_to_die = CYCLE_TO_DIE;
	x->cycle_delta = CYCLE_DELTA;
	x->nbr_live = NBR_LIVE;
	x->max_check = MAX_CHECKS;
	x->nb_c = 0;
	printf("test\n");
	//while (x->lst_process->next)
	i = 0;
	while (++i < 8)
		load_vm(x);
	return ;
}
