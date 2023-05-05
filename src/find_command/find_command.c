/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:59:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/05 11:03:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

char	*find_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			path = env[i];
		i++;
	}
	if (!path)
	{
		perror(E_PATH);
		exit (ERROR);
	}
	return (path);
}
int	axu_find_com(char *command, t_f_com *parse)
{
	parse->i = 0;
	while (parse->split[parse->i])
	{
		parse->join = ft_strjoin(parse->split[parse->i++], command);
		if (!parse->join)
			return (ERROR);
		if (access(parse->join, F_OK) != ERROR)
			break ;
		free(parse->join);
	}
	parse->path = parse->join;
	free_split(parse->split);
	if (access(parse->join, F_OK) != ERROR)
	{
		free(parse->join);
		parse->error = TRUE;
	}
	else
	{
		parse->path = NULL;
		parse->error = FALSE;
	}
	free(parse->add);
	return (SUCCESS);
}
// char	*find_command(char *command, char **env, t_f_com *parse)
// {
// 	parse->path = find_path(env);
// 	if (!parse->path)
// 		return (NULL);
// 	parse->i = 0;
// 	while (parse->path[parse->i])
// 	{
// 		parse->i++;
// 		if (parse->path[parse->i] == ':')
// 			break ;
// 	}
// 	parse->i++;
// 	parse->add = ft_calloc(sizeof(char), (ft_strlen(parse->path) - parse->i) + 1);
// 	if (!parse->add)
// 		return (NULL);
// 	parse->axu_i = 0;
// 	while (parse->path[parse->i])
// 		parse->add[parse->axu_i++] = parse->path[parse->i++];
// 	parse->split = ft_split(parse->add, ':');
// 	if (!parse->split)
// 		return (NULL);
// 	parse->i = 0;
// 	while (parse->split[parse->i])
// 	{
// 		parse->join = ft_strjoin(parse->split[parse->i++], command);
// 		if (!parse->join)
// 			return (NULL);
// 		if (access(parse->join, F_OK) != ERROR)
// 			break ;
// 		free(parse->join);
// 	}
// 	parse->path = parse->join;
// 	free_split(parse->split);
// 	if (access(parse->join, F_OK) != ERROR)
// 	{
// 		free(parse->join);
// 		parse->error = TRUE;
// 	}
// 	else
// 	{
// 		parse->path = NULL;
// 		parse->error = FALSE;
// 	}
// 	free(parse->add);
// 	return (parse->path);
// }
int	find_command(char *command, char **env, t_f_com *parse)
{
	parse->path = find_path(env);
	if (!parse->path)
		return (ERROR);
	parse->i = 0;
	while (parse->path[parse->i])
	{
		parse->i++;
		if (parse->path[parse->i] == ':')
			break ;
	}
	parse->i++;
	parse->add = ft_calloc(sizeof(char), (ft_strlen(parse->path) - parse->i) + 1);
	if (!parse->add)
		return (ERROR);
	parse->axu_i = 0;
	while (parse->path[parse->i])
		parse->add[parse->axu_i++] = parse->path[parse->i++];
	parse->split = ft_split(parse->add, ':');
	if (!parse->split)
		return (ERROR);
	if (axu_find_com(command, parse) == ERROR)
		return (ERROR);
	return (SUCCESS);
}