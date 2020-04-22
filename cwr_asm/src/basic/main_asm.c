/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:54:29 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/17 18:44:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

int		main(int ac, char **av)
{
	int				ret;
	t_cwr			cwr;
	t_line			line;
	t_file			champ_file;

	if (ac != 2)
		return (0);
	ret = init_structs(&cwr, &line, &champ_file, av[1]);
	if (ret == EXIT_SUCCESS)
		ret = parse_header(&cwr);
	if (ret == EXIT_SUCCESS)
		ret = parse_prog(&cwr);
	if (ret == EXIT_SUCCESS)
		ret = check_remaining_refs(&cwr);
	if (ret == EXIT_SUCCESS)
		ret = create_output_file(&cwr);
	exit_cwr(&cwr);
	return (EXIT_SUCCESS);
}
