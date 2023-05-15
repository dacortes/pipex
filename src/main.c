/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/15 16:04:34 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

char	*find_slash(char *command)
{
	if (command[0] == '/')
	{
		if (access(command, F_OK) == ERROR || access(command, X_OK) == ERROR)
			exit (printf_error(E_NSF, -2));
		return (command);
	}
	else
		return (command);
}

void	parse_command(char *command, char **env)
{
	t_parse	com;
	t_f_com	path;

	com.split = ft_split(command, ' ');
	com.argv = ft_calloc(double_ptr_len((void *)com.split) + 1, sizeof(char *));
	if (!com.argv)
		exit (printf_error(E_MEM, 1));
	com.command = com.split[0];
	com.i = 0;
	while (com.split[com.i++])
		com.argv[com.i - 1] = com.split[com.i];
	if (!(check_quotes(com.command) && check_quotes_argv(com.argv)))
	{
		free(com.argv);
		free_split(com.split);
		exit (printf_error(E_CNF, 127));
	}
	com.command = find_slash(com.command);
	com.command = ft_addstart_char(com.command, '/');
	find_command(com.command, env, &path);
	free(com.command);
	free(com.argv);
	free_split(com.split);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		exit(printf_error(E_ARG, 1));
	// char	*i_file = av[1];
	char	*com1 = av[2];
	// char	*com2 = av[3];
	// char	*o_file = av[4];
	parse_command(com1, env);
	return (SUCCESS);
}