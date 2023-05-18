/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:33:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/18 16:43:51 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int	msg_error(int error, int exit_)
{
	if (error == E_ARG)
		ft_putstr_fd(R"Error:"E" Invalid arguments\n", 2);
	if (error == E_MEM)
		ft_putstr_fd(R"Error:"E" Memory allocation error\n", 2);
	if (error == E_PTH)
		ft_putstr_fd(R"Error:"E" Path not found\n", 2);
	if (error == E_NSF)
		ft_putstr_fd(R"Error:"E" No such file or directory\n", 2);
	if (error == E_OPN)
		ft_putstr_fd(R"Error:"E" In funtion open\n", 2);
	if (error == E_FRK)
		ft_putstr_fd(R"Error:"E" In funtion fork\n", 2);
	if (error == E_PIP)
		ft_putstr_fd(R"Error:"E" In funtion pipe\n", 2);
	if (error == E_EXC)
		ft_putstr_fd(R"Error:"E" In funtion execve\n", 2);
	if (error == E_PRM)
		ft_putstr_fd(R"Error:"E" Permissions denied\n", 2);
	if (error == E_CNF)
		ft_putstr_fd(R"Error:"E" Command not found\n", 2);
	return (exit_);
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
		exit(msg_error(E_PTH, -2));
	return (path);
}

void	parse_file(t_test *pipex, int type)
{
	if (type == IN)
	{
		if (access(pipex->infile, F_OK) == ERROR
			|| access(pipex->infile, X_OK) == ERROR)
			exit(msg_error(E_NSF, 1));
		pipex->infd = open(pipex->infile, O_RDONLY);
		if (pipex->infd < 0)
			exit(msg_error(E_OPN, 1));
	}
	else if (type == OUT)
	{
		pipex->outfd = open(pipex->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (pipex->outfd < 0)
		{
			close(pipex->infd);
			exit(msg_error(E_OPN, 1));
		}
	}
}

int	is_del_close(char *str, char delimiter)
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

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	if (split)
		free(split);
}

void get_command(t_test *pipex)
{
	if  (!is_del_close(pipex->cmmd1, D_QUOTES)
		|| !is_del_close(pipex->cmmd1, QUOTES))
		{
			close(pipex->tube[0]);
			close(pipex->tube[1]);
			exit (msg_error(E_CNF, 126));
		}
	if  (!is_del_close(pipex->cmmd2, D_QUOTES)
		|| !is_del_close(pipex->cmmd2, QUOTES))
		{
			close(pipex->tube[0]);
			close(pipex->tube[1]);
			exit (msg_error(E_CNF, 126));
		}
	int i = 0;
	int j = 0;
	while (pipex->cmmd1[i] && (pipex->cmmd1[i] == D_QUOTES
		|| pipex->cmmd1[i] == QUOTES))
		i++;
	if (pipex->cmmd1[i] == ' ')
		exit (msg_error(E_CNF, 126));
	while (pipex->cmmd1[i])
	{
		if (pipex->cmmd1[i] &&  pipex->cmmd1[i] != ' ' 
		&& (pipex->cmmd1[i] != D_QUOTES && pipex->cmmd1[i] != QUOTES))
			j++;
		if (pipex->cmmd1[i] && (pipex->cmmd1[i] == D_QUOTES
		|| pipex->cmmd1[i] == QUOTES))
			break ;
		i++;
	}
	char	*command;
	//char	*arg;
	ft_printf(B"%d\n"E, i);
	command = ft_calloc(j + 1, sizeof(char));
	if (!command)
	{
		close(pipex->tube[0]);
		close(pipex->tube[1]);
		exit (msg_error(E_MEM, 1));
	}
	i = i - j - 1;
	j = 0;
	while (pipex->cmmd1[i] && pipex->cmmd1[i] && (pipex->cmmd1[i] != D_QUOTES
		&& pipex->cmmd1[i] != QUOTES) && pipex->cmmd1[i] != ' ')
		command[j++] = pipex->cmmd1[i++];
	free(command);
	ft_printf("%s<----\n", command);
}

void	init_pipex(t_test	*pipex, int ac, char **av, char **env)
{
	pipex->infile = av[1];
	parse_file(pipex, IN);
	pipex->outfile = av[ac - 1];
	parse_file(pipex, OUT);
	pipex->cmmd1 = av[2];
	pipex->cmmd2 = av[3];
	pipex->path = find_path(env);
	if (!pipex->path)
		exit(msg_error(E_PTH, 1));
	if (pipe(pipex->tube) < 0)
		exit(msg_error(E_PIP, 1));
}

int main(int ac, char **av, char **env)
{
	t_test	pipex;
	if (ac != 5)
		exit(msg_error(E_ARG, 1));
	init_pipex(&pipex, ac, av, env);
	get_command(&pipex);
	return (SUCCESS);
}