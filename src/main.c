/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/15 19:29:22 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

void	parse_file(char *file, int fd)
{
	if ((access(file, F_OK) == ERROR 
		|| access(file, X_OK) == ERROR))
		exit (printf_error(E_NSF, -2));
	fd =  open(file, O_RDONLY);
	if (fd < 0)
		exit(printf_error(E_OPN, 1));
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;

	if (ac != 5)
		exit(printf_error(E_ARG, 1));
	p.in_file = av[1];
	p.com1 = av[2];
	p.com2 = av[3];
	if (!p.com1)
		exit(printf_error(E_CNF, 127));
	if (!p.com2)
		exit(printf_error(E_CNF, 127));
	parse_file(p.in_file, p.fd_in);
	parse_command(p.com1, env);
	parse_command(p.com2, env);
	close(p.fd_in);
	return (SUCCESS);
}