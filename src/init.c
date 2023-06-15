/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:32:12 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/15 14:49:27 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int		parse_open(t_pipex *pip, int type)
{
	if (type == IN)
	{
		if (access(pip->infile, F_OK) == ERROR)
			return (msg_error(E_NSF, -2, pip->infile));
		if (access(pip->infile, R_OK) == ERROR)
			return (msg_error(E_PRR, -2, pip->infile));
		pip->infd = open(pip->infile, O_RDONLY);
		if (pip->infd == ERROR)
			return (1);
	}
	else if (type == OUT)
	{
		if  (!access(pip->outfile, F_OK) && access(pip->outfile, W_OK))
			exit (close_exit(E_PRM, 0, pip->outfile, pip));
		pip->outfd = open(pip->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (pip->outfd == ERROR)
			return (1);
	}
	return (ERROR);
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

void	init_pipex(t_pipex *pip, int ac, char **av, char **env)
{
	pip->err = 0;
	pip->infd = 0;
	pip->outfile = 0;
	pip->infile = av[1];
	pip->cmmd1 = av[2];
	pip->cmmd2 = av[3];
	pip->outfile= av[ac - 1];
	pip->path = find_path(env);
	if (pipe(pip->tube) == ERROR)
		exit (msg_error(E_PRR, 1, NULL));
	pip->err = parse_open(pip, IN);
	if (pip->err == 1 && !close(pip->tube[0]) && !close(pip->tube[1]))
		exit (msg_error(E_PRR, 1, NULL));
	if (pip->err == -1 && pip->infd < 0 && !close(pip->tube[0])
		&& !close(pip->tube[1]) && !close(pip->infd))
		exit (msg_error(E_PRR, 1, NULL));

}

int	ignore(char *str, char a, char b, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == a || str[i] == b || str[i] == c))
		i++;
	return (i);
}

void	get_cmmd(char *cmd, t_pipex *pip, t_get *g)
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
		exit (close_exit(E_MEM, 1, NULL, pip));
	g->i = ignore(cmd, ' ', D_QUOTES, QUOTES);
	g->len = 0;
	while (cmd[g->i] && cmd[g->i] != ' ' && cmd[g->i] != QUOTES
		&& cmd[g->i] != D_QUOTES)
		g->cmmd[g->len++] = cmd[g->i++];
}
