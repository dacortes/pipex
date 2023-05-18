/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:33:30 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/16 17:09:51 by dacortes         ###   ########.fr       */
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

void	parse_command(char *command, char **env, t_parse *com,  t_f_com *path)
{
	// t_parse	com;
	// t_f_com	path;

	com->split = ft_split(command, ' ');
	com->argv = ft_calloc(double_ptr_len((void *)com->split) + 1, sizeof(char *));
	if (!com->argv)
		exit (printf_error(E_MEM, 1));
	com->command = com->split[0];
	com->i = 0;
	while (com->split[com->i++])
		com->argv[com->i - 1] = com->split[com->i];
	if (!(check_quotes(com->command) && check_quotes_argv(com->argv)))
	{
		free(com->argv);
		free_split(com->split);
		exit (printf_error(E_CNF, 127));
	}
	com->command = find_slash(com->command);
	com->command = ft_addstart_char(com->command, '/');
	find_command(com->command, env, path);
	// ft_printf("%s\n", path.join);
	// free(com->command);
	// free(com->argv);
	// free_split(com->split);
}