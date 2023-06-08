/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:55:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/08 11:40:13 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

static void	parse_cmmd(char *cmd, t_pipex *pipex, t_get *get)
{
	if (!close_del(cmd, D_QUOTES) || !close_del(cmd, QUOTES))
		exit (close_exit(E_CNF, 127, cmd, pipex));
	get_cmmd(cmd, pipex, get);
	if (ft_strchr(get->cmmd, '/') && (access(get->cmmd, F_OK) == ERROR
			|| access(get->cmmd, X_OK) == ERROR))
		exit (close_exit(E_CNF, 127, get->cmmd, pipex));
	get_arg(cmd, get->cmmd, pipex, get);
	get_path(pipex, get);
}

static void	first_child(t_pipex *pipex, t_get *g, char **env)
{
	if (pipex->pid1 == ERROR)
		exit (close_exit(E_PRR, 1, NULL, pipex));
	else if (pipex->pid1 == SUCCESS)
	{
		if (dup2(pipex->tube[1], 1) == ERROR)
			exit (close_exit(E_PRR, 1, NULL, pipex));
		close(pipex->tube[0]);
		close(pipex->tube[1]);
		if (dup2(pipex->infd, 0) == ERROR)
			exit (close_exit(E_PRR, 1, NULL, pipex));
		execve(g->cmmd, g->arg, env);
		exit (close_exit(E_CNF, 127, g->cmmd, pipex));
	}
}

static void	second_child(t_pipex *pipex, t_get *g, char **env)
{
	if (pipex->pid2 == ERROR)
		exit (close_exit(E_PRR, 1, NULL, pipex));
	else if (pipex->pid2 == SUCCESS)
	{
		if (dup2(pipex->tube[0], 0) == ERROR)
			exit (close_exit(E_PRR, 1, NULL, pipex));
		close(pipex->tube[0]);
		close(pipex->tube[1]);
		if (dup2(pipex->outfd, 1) == ERROR)
			exit (close_exit(E_PRR, 1, NULL, pipex));
		execve(g->cmmd, g->arg, env);
		exit (close_exit(E_CNF, 127, g->cmmd, pipex));
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	t_get	get_f;
	t_get	get_s;

	if (ac != 5)
		return (msg_error(E_ARG, 1, NULL));
	init_pipex(&pipex, ac, av, env);
	parse_cmmd(pipex.cmmd1, &pipex, &get_f);
	parse_cmmd(pipex.cmmd2, &pipex, &get_s);
	pipex.pid1 = fork();
	first_child(&pipex, &get_f, env);
	pipex.pid2 = fork();
	second_child(&pipex, &get_s, env);
	free_get(&get_f);
	free_get(&get_s);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	close(pipex.infd);
	close(pipex.outfd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (SUCCESS);
}
