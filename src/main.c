/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/05 10:20:30 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_f_com parse;

	ft_printf(B"%s\n"E, find_command("/ls", env, &parse));
	ft_printf(B"The error status:%d\n"E, parse.error);
	if (find_command("/echo", env, &parse))
		ft_printf(G"OK\n"E);
	return (SUCCESS);
}
