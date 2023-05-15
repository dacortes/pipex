/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:59:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/15 15:45:39 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

char	*find_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			path = env[i];
		i++;
	}
	if (!path)
		exit(printf_error(E_PTH, -2));
	return (path);
}

void	execute_permission(t_f_com *parse)
{
	if (access(parse->join, X_OK) != ERROR)
	{
		free(parse->join);
		parse->f_ok = TRUE;
	}
	else if (access(parse->join, X_OK) == ERROR)
	{
		free(parse->add);
		parse->f_ok = FALSE;
		exit (printf_error(E_NSF, -2));
	}
}

int	parse_path(char *command, t_f_com *parse)
{
	parse->split = ft_split(parse->add, ':');
	if (!parse->split)
		exit (printf_error(E_MEM, 1));
	parse->i = 0;
	while (parse->split[parse->i])
	{
		parse->join = ft_strjoin(parse->split[parse->i++], command);
		if (!parse->add)
			exit (printf_error(E_MEM, 1));
		if (access(parse->join, F_OK) != ERROR)
			break ;
		free(parse->join);
	}
	free_split(parse->split);
	execute_permission(parse);
	return (TRUE);
}

int	find_command(char *command, char **env, t_f_com *parse)
{
	parse->path = find_path(env);
	if (!parse->path)
		return (FALSE);
	parse->i = 0;
	while (parse->path[parse->i] && parse->path[parse->i] != EQUAL)
		parse->i++;
	parse->add = ft_calloc(sizeof(char), (ft_strlen(parse->path) - parse->i) + 1);
	if (!parse->add)
		exit (printf_error(E_MEM, 1));
	parse->axu_i = 0;
	while (parse->path[parse->i++])
		parse->add[parse->axu_i++] = parse->path[parse->i];
	parse_path(command, parse);
	if (!parse->f_ok)
		return (FALSE);
	free(parse->add);
	return (TRUE);
}