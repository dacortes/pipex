/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:55:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/06 19:12:31 by dacortes         ###   ########.fr       */
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
	e == E_CNF && fd_printf(2, R"Error"E": Command not found\n");
	if (e == E_PRR)
		perror(R"bash"E);
	return (exit_);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	if (split)
		free(split);
}

void	free_get(t_get *get, int type)
{
	if (type == IN && get->paht)
		free_split(get->paht);
	if (get->split)
		free_split(get->split);
	if (get->arg)
		free(get->arg);
	if (get->cmmd)
		free(get->cmmd);
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

int 	close_exit(int error, int exit_, char *cmd, t_pipex *pipex)
{
	close(pipex->tube[0]) && close(pipex->tube[1]);
	return (msg_error(error, exit_, cmd));
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
		else if  (str[i] == delimiter && del % 2 == 0)
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

void	axu_get_path(char *tmp, char *cmmd, t_pipex *pipex, t_get *get)
{
	while (get->paht[get->i])
	{
		tmp = ft_addend_char(get->paht[get->i], '/');
		if (!tmp)
			exit(close_exit(E_MEM, 1, NULL, pipex));
		cmmd = ft_strjoin(tmp, get->cmmd);
		if (!cmmd)
		{
			free(tmp);
			exit(close_exit(E_MEM, 1, NULL, pipex));
		}
		if (access(cmmd, 0) == SUCCESS)
		{
			free(tmp);
			free(get->cmmd);
			get->cmmd = cmmd;
			get->i = 0;
			break ;
		}
		free(cmmd);
		free(tmp);
		get->i++;
	}
	get->i = 0;
}

void	get_path(t_pipex *pipex, t_get *get)
{
	char	*tmp;
	char	*cmmd;

	tmp = NULL;
	cmmd = NULL;
	get->paht = ft_split(pipex->path, ':');
	if (!get->paht)
	{
		free_split(get->split);
		exit (close_exit(E_MEM, 1, NULL, pipex));
	}
	axu_get_path(tmp, cmmd, pipex, get);
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
		exit (msg_error(E_PNF, 1, NULL));
	if (pipe(pipex->tube) < 0)
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

void	axu_get_arg_len(int *len, char **split)
{
	int	i;
	int	j;
	int	OK_;

	i = 0;
	j = 0;
	(*len) = 0;
	OK_ = FALSE;
	while (split[i])
	{
		j = 0;
		OK_ = FALSE;
		while (split[i][j])
		{
			if (split[i][j] != ' ')
			{
				OK_ = TRUE;
				break ;
			}
			j++;
		}
		if (OK_ == TRUE)
			(*len)++;
		i++;
	}
}

void	axu_get_arg(t_get *g)
{
	int	OK_;

	g->i = 0;
	g->len = 0;
	OK_ = FALSE;
	while (g->split[g->i])
	{
		g->j = 0;
		OK_ = FALSE;
		while (g->split[g->i][g->j])
		{
			if (g->split[g->i][g->j] != ' ' )
			{
				OK_ = TRUE;
				break ;
			}
			g->j++;
		}
		if (OK_ == TRUE && g->split[g->i])
			g->arg[g->len++] = g->split[g->i];
		g->i++;
	}
}

void	get_arg(char *cmd, char *nd, t_pipex *pipex, t_get *g)
{
	g->n_arg = ft_strnstr(cmd, nd, ft_strlen(cmd));
	g->n_arg = &g->n_arg[ft_strlen(nd)];
	g->del = ' ';
	if (ft_strchr(g->n_arg, D_QUOTES))
		g->del = D_QUOTES;
	g->split = ft_split(g->n_arg, g->del);
	if (!g->split)
		exit (close_exit(E_MEM, 1, NULL, pipex));
	axu_get_arg_len(&g->len, g->split);
	g->arg = ft_calloc(g->len + 1, sizeof(char *));
	if (!g->arg)
	{
		free_split(g->split);
		exit(close_exit(E_MEM, 1, NULL, pipex));
	}
	axu_get_arg(g);
	g->i = 0;
}

void	parse_cmmd(char *cmd, t_pipex *pipex, t_get *get, int type)
{
	if (!close_del(cmd, D_QUOTES) || !close_del(cmd, QUOTES))
		exit (close_exit(E_CNF, 127, NULL, pipex));
	get_cmmd(cmd, pipex, get);
	if (ft_strchr(get->cmmd, '/') && (access(get->cmmd, F_OK) == ERROR
		|| access(get->cmmd, X_OK) == ERROR))
		exit (close_exit(E_CNF, 127, NULL, pipex));
	get_arg(cmd, get->cmmd, pipex, get);
	if (type == IN)
		get_path(pipex, get);
}

// void	first_child(t_pipex *pipex, t_get *get, char **env)
// {
	
// }

// void	second_child(t_pipex *pipex, t_get *get, char **env)
// {

// }

int		main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	t_get get_f;
	t_get get_s;

	if (ac != 5)
		return (msg_error(E_ARG, 1, NULL));
	init_pipex(&pipex, ac, av, env);
	parse_cmmd(pipex.cmmd1, &pipex, &get_f, IN);
	parse_cmmd(pipex.cmmd2, &pipex, &get_s, OUT);
	free_get(&get_f, IN);
	free_get(&get_s, OUT);
	return (SUCCESS);
}

/*int		main(int ac, char **av, char **env)
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
}*/