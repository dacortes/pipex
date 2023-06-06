/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:55:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/06 11:43:36 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int	msg_error(int e, int exit_, char *cm)
{
	e == E_ARG && fd_printf(2, R"Error"E": Invalid arguments\n");
	e == E_MEM && fd_printf(2, R"Error"E": %s Memory allocation error\n", cm);
	e == E_NSF && fd_printf(2, R"Error"E": %s No such file or directory\n", cm);
	e == E_PNF && fd_printf(2, R"Error"E": Path not found\n");
	e == E_PRM && fd_printf(2, R"Error"E": Permissions denied\n");
	e == E_CNF && fd_printf(2, E"Error"E": Command not found\n");
	if (e == E_PRR)
		perror(R"bash"E);
	return (exit_);
}

void	parse_file(t_pipex *pipex, int type)
{
	if (type == IN)
	{
		if (access(pipex->infile, F_OK) == ERROR)
			exit (msg_error(E_NSF, -2, pipex->infile));
		if (access(pipex->infile, R_OK) == ERROR)
			exit (msg_error(E_PRR, -2, pipex->infile));
		pipex->infd = open (pipex->infile, O_RDONLY);
		if (pipex->infd < 0 )
			exit (msg_error(E_PRR, pipex->infd, NULL));
	}
	if (type == OUT)
	{
		pipex->outfd = open(pipex->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (pipex->outfd < 0 && !close(pipex->infd))
			exit (msg_error(E_PRR, pipex->outfd, NULL));
	}
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
		return (path);
	return (path);
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->infile = av[1];
	parse_file(pipex, IN);
	pipex->outfile = av[ac - 1];
	parse_file(pipex, OUT);
	pipex->cmmd1 = av[2];
	pipex->cmmd1 = av[3];
	pipex->path = find_path(env);
	if (!pipex->path)
		exit (msg_error(E_PNF, 1, NULL));
	if (pipe(pipex->tube) < 0)
		exit (msg_error(E_PRR, 1, NULL));
}

int		main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	char	*argv[2] = {"ls", NULL};
	char	*argv2[2] = {"wc", NULL};

	(void)av;
	if (ac != 5)
		return (msg_error(E_ARG, 1, NULL));
	pipex.infd = open("hola.txt", O_RDONLY);
	pipex.outfd = open("outfile.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		dup2(pipex.tube[1], 1);
		close(pipex.tube[0]);
		close(pipex.tube[1]);
		dup2(pipex.infd, 0);
		execve("/bin/ls", argv, env);
		exit (msg_error(E_ARG, 1, NULL));
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		dup2(pipex.tube[0], 0);
		close(pipex.tube[0]);
		close(pipex.tube[1]);
		dup2(pipex.outfd, 1);
		execve("/usr/bin/wc", argv2, env);
		exit (msg_error(E_ARG, 1, NULL));
	}
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	close(pipex.infd);
	close(pipex.outfd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (SUCCESS);
}