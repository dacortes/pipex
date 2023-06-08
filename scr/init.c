/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:48:24 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/08 12:35:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

void	parse_file(t_pipex *pipex, int type)
{
	if (type == IN)
	{
		if (access(pipex->infile, F_OK) == ERROR)
			exit (msg_error(E_NSF, 0, pipex->infile));
		if (access(pipex->infile, R_OK) == ERROR)
			exit (msg_error(E_PRM, 126, pipex->infile));
		pipex->infd = open (pipex->infile, O_RDONLY);
		if (pipex->infd < 0)
			exit (msg_error(E_PRR, 11, NULL));
	}
	if (type == OUT)
	{
		pipex->outfd = open(pipex->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (pipex->outfd < 0 && !close(pipex->infd))
			exit (msg_error(E_PRR, 1, NULL));
	}
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->infile = av[1];
	parse_file(pipex, IN);
	pipex->outfile = av[ac - 1];
	parse_file(pipex, OUT);
	pipex->cmmd1 = av[2];
	pipex->cmmd2 = av[3];
	pipex->path = find_path(env);
	if (!pipex->path)
		exit (msg_error(E_PNF, 0, NULL));
	if (pipe(pipex->tube) < 0)
		exit (msg_error(E_PRR, 1, NULL));
}

char	*find_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			path = &env[i][+5];
		i++;
	}
	if (!path)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin");
	return (path);
}

int	ignore(char *str, char a, char b, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == a || str[i] == b || str[i] == c))
		i++;
	return (i);
}

void	get_cmmd(char *cmd, t_pipex *pipex, t_get *g)
{
	g->len = 0;
	g->i = ignore(cmd, ' ', D_QUOTES, QUOTES);
	while (cmd[g->i])
	{
		if (cmd[g->i] && cmd[g->i] != ' ' && cmd[g->i] != QUOTES
			&& cmd[g->i] != D_QUOTES)
			g->len++;
		if (cmd[g->i] && cmd[g->i] == ' ' && cmd[g->i] == QUOTES
			&& cmd[g->i] == D_QUOTES)
			break ;
		g->i++;
	}
	g->cmmd = ft_calloc(g->len + 1, sizeof(char));
	if (!g->cmmd)
		exit (close_exit(E_MEM, 1, NULL, pipex));
	g->i = ignore(cmd, ' ', D_QUOTES, QUOTES);
	g->len = 0;
	while (cmd[g->i] && cmd[g->i] != ' ' && cmd[g->i] != QUOTES
		&& cmd[g->i] != D_QUOTES)
		g->cmmd[g->len++] = cmd[g->i++];
}
