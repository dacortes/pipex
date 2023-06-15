/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:29:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/15 17:15:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int	is_bin(char *cmd, t_get *g)
{
	if (ft_strnstr(cmd, "./", ft_strlen(cmd)) && !close_del(cmd, ' '))
	{
		if ((!close_del(cmd, D_QUOTES) || !close_del(cmd, QUOTES)))
			exit (msg_error(E_CNF, 127, g->cmmd));
		return (msg_error(E_CNF, E_SPC, g->cmmd));
	}
	else
	{
		if ((!close_del(cmd, D_QUOTES) || !close_del(cmd, QUOTES)))
			return (msg_error(E_CNF, -2, g->cmmd));
		else if (ft_strchr(cmd, '/') && access(g->cmmd, F_OK))
			return (msg_error(E_CNF, 127, g->cmmd));
		else if (ft_strchr(cmd, '/') && access(g->cmmd, X_OK))
			return (msg_error(E_PRM, 126, g->cmmd));
	}
	return (SUCCESS);
}

int	parse_cmd(char *cmd, t_pipex *pip, t_get *g, int type)
{
	get_cmmd(cmd, pip, g);
	get_arg(cmd, g->cmmd, pip, g);
	get_path(pip, g);
	if (type == IN)
		g->err = is_bin(cmd, g);
	else if (type == OUT)
	{
		if (!close_del(cmd, D_QUOTES) || !close_del(cmd, QUOTES))
			exit (close_exit(E_CNF, 127, cmd, pip));
		else if (ft_strchr(cmd, '/') && access(g->cmmd, F_OK))
			exit (close_exit(E_CNF, 127, cmd, pip));
		else if (ft_strchr(cmd, '/') && access(g->cmmd, X_OK))
			exit (close_exit(E_PRM, 126, cmd, pip));
	}
	return (SUCCESS);
}

void	first_child(t_pipex *pipex, t_get *g, char **env)
{
	if (pipex->pid1 == ERROR)
		exit (close_exit(E_PRR, 1, NULL, pipex));
	else if (pipex->pid1 == SUCCESS)
	{
		if (pipex->err == -2 || g->err == -2)
			close(pipex->infd);
		else
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
}

void	second_child(t_pipex *pip, t_get *g, char **env)
{
	pip->err = parse_open(pip, OUT);
	if (pip->err == 1 && !close(pip->tube[0]) && !close(pip->tube[1]))
		exit (msg_error(E_PRR, 1, NULL));
	if (pip->err == -1 && pip->outfd < 0 && !close(pip->tube[0])
		&& !close(pip->tube[1]))
		exit (msg_error(E_PRR, 1, NULL));
	if (pip->pid2 == ERROR)
		exit (close_exit(E_PRR, 1, NULL, pip));
	else if (pip->pid2 == SUCCESS)
	{
		if (dup2(pip->tube[0], 0) == ERROR)
			exit (close_exit(E_PRR, 1, NULL, pip));
		close(pip->tube[0]);
		close(pip->tube[1]);
		if (dup2(pip->outfd, 1) == ERROR)
			exit (close_exit(E_PRR, 1, NULL, pip));
		execve(g->cmmd, g->arg, env);
		exit (close_exit(E_CNF, 127, g->cmmd, pip));
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pip;
	t_get	first;
	t_get	second;

	if (ac != 5)
		return (msg_error(E_ARG, 1, NULL));
	init_pipex(&pip, ac, av, env);
	parse_cmd(pip.cmmd1, &pip, &first, IN);
	parse_cmd(pip.cmmd2, &pip, &second, OUT);
	pip.pid1 = fork();
	first_child(&pip, &first, env);
	pip.pid2 = fork();
	second_child(&pip, &second, env);
	free_get(&first);
	free_get(&second);
	close(pip.tube[0]);
	close(pip.tube[1]);
	close(pip.infd);
	close(pip.outfd);
	waitpid(pip.pid1, &first.stt, 0);
	waitpid(pip.pid2, &second.stt, 0);
	return (WEXITSTATUS(second.stt));
}
