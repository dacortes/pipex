/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:08 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/03 15:44:00 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

void	free_split(char **split)
{
	int	i;
	
	i = 0;
	while (split[i])
		free(split[i++]);
	if (split)
		free(split);
}

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

int	find_command(char *command, char **env)
{
	(void)command;
	char	*path;
	char	**split;

	path = find_path(env);
	if (!path)
		return (FALSE);
	split = ft_split(path, ':');
	if (!split)
	{
		perror(E_MEMO);
		return (ERROR);
	}
	ft_printf(R"%s\n"E, split[0]);
	free_split(split);
	return (TRUE);
}