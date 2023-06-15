/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:55:58 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/10 17:44:43 by dacortes         ###   ########.fr       */
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

void	free_get(t_get *get)
{
	if (get->paht)
		free_split(get->paht);
	if (get->split)
		free_split(get->split);
	if (get->arg)
		free(get->arg);
	if (get->cmmd)
		free(get->cmmd);
}

int	close_del(char *str, char delimiter)
{
	int	del;
	int	i;

	del = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
			del++;
		else if (str[i] == delimiter && del % 2 == 0)
		{
			while (str[i])
			{
				i++;
				if (str[i] == delimiter)
				{
					del++;
					break ;
				}
			}
		}
		i++;
	}
	return (del % 2 == 0);
}

int	msg_error(int e, int exit_, char *cm)
{
	e == E_ARG && fd_printf(2, "bash: Invalid number of arguments\n");
	e == E_MEM && fd_printf(2, "bash: error trying to allocate memory\n", cm);
	e == E_NSF && fd_printf(2, "pipex: %s: No such file or directory\n", cm);
	e == E_PRM && fd_printf(2, "pipex: %s: permissions denied\n", cm);
	e == E_CNF && fd_printf(2, "pipex: %s: command not found\n", cm);
	if (e == E_PRR)
		perror("bash");
	return (exit_);
}

int	close_exit(int error, int exit_, char *cmd, t_pipex *pipex)
{
	close(pipex->infd);
	close(pipex->outfd);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	return (msg_error(error, exit_, cmd));
}
