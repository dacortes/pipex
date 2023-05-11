/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:59:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/11 12:00:54 by dacortes         ###   ########.fr       */
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
	{
		ft_printf("%s%s%s", R, E_PATH, E);
		return (NULL);
	}
	return (path);
}

void	execute_permission(t_f_com *parse)
{
	if (access(parse->join, X_OK) != ERROR)
	{
		free(parse->join);
		parse->f_ok = TRUE;
	}
	else
	{
		parse->f_ok = FALSE;
		free(parse->add);
	}
}

int	parse_path(char *command, t_f_com *parse)
{
	parse->split = ft_split(parse->add, ':');
	if (!parse->split)
	{
		perror(E_MEMO);
		exit (ERROR);
	}
	parse->i = 0;
	while (parse->split[parse->i])
	{
		parse->join = ft_strjoin(parse->split[parse->i++], command);
		if (!parse->add)
		{
			perror(E_MEMO);
			exit (ERROR);
		}
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
	{
		perror(E_MEMO);
		exit (ERROR);
	}
	parse->axu_i = 0;
	while (parse->path[parse->i++])
		parse->add[parse->axu_i++] = parse->path[parse->i];
	parse_path(command, parse);
	if (!parse->f_ok)
		return (FALSE);
	free(parse->add);
	return (TRUE);
}