/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/05 08:53:49 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_printf(B"%s\n"E, find_command("/lkkkk", env));
	if (find_command("/xxxx", env))
		ft_printf(G"OK\n"E);
	return (SUCCESS);
}
