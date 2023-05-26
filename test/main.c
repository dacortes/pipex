/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:33:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/26 19:19:43 by dacortes         ###   ########.fr       */
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

int	close_and_exit(int error, int exit_, t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	return (msg_error(error, exit_));
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

void	parse_file(t_pipex *pipex, int type)
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

int	ignore(char *str, char a, char b, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == a || str[i] == b || str[i] == c))
		i++;
	return (i);
}

char	*get_command(char *command, t_pipex *pipex)
{
	t_get	get;

	get.len = 0;
	get.i = ignore(command, ' ', D_QUOTES, QUOTES);
	while (command[get.i])
	{
		if (command[get.i] && command[get.i] != ' ' && command[get.i] != QUOTES
			&& command[get.i] != D_QUOTES)
			get.len++;
		if (command[get.i] && (command[get.i] == ' ' || command[get.i] == QUOTES
			|| command[get.i] == D_QUOTES))
			break ;
		get.i++;
	}
	get.cmmd = ft_calloc(get.len + 1, (sizeof(char)));
	if (!get.cmmd)
		exit (close_and_exit(E_MEM, 1, pipex));
	get.i = ignore(command, ' ', D_QUOTES, QUOTES);
	get.len = 0;
	while (command[get.i] && command[get.i] != ' ' && command[get.i] != QUOTES
		&& command[get.i] != D_QUOTES)
		get.cmmd[get.len++] = command[get.i++];
	free(get.cmmd);
	return (get.cmmd);
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

void	axu_get_arg(t_get *get)
{
	int	OK_;

	get->i = 0;
	get->len = 0;
	OK_ = FALSE;
	while (get->split[get->i])
	{
		get->j = 0;
		OK_ = FALSE;
		while (get->split[get->i][get->j])
		{
			if (get->split[get->i][get->j] != ' ')
			{
				OK_ = TRUE;
				break ;
			}
			get->j++;
		}
		if (OK_ == TRUE && get->split[get->i])
			get->arg[get->len++] = get->split[get->i];
		get->i++;
	}
}

// char	*get_arg(char *command, char *need, t_pipex *pipex)
// {
// 	t_get	get;

// 	get.n_arg = ft_strnstr(command, need, ft_strlen(command));
// 	get.n_arg = &get.n_arg[ft_strlen(need) +\
// 		(!is_del_close(&get.n_arg[ft_strlen(need)], D_QUOTES
// 		|| !is_del_close(&get.n_arg[ft_strlen(need)], QUOTES)))];
// 	get.del = ' ';
// 	if (ft_strchr(&get.n_arg[ft_strlen(need)], D_QUOTES))
// 		get.del = D_QUOTES;
// 	get.split = ft_split(&get.n_arg[ft_strlen(need) - 1], get.del);
// 	if (!get.split)
// 		exit (close_and_exit(E_MEM, 1, pipex));
// 	axu_get_arg_len(&get.len, get.split);
// 	get.arg = ft_calloc(get.len + 1, sizeof(char *));
// 	if(!get.arg)
// 		exit (close_and_exit(E_MEM, 1, pipex));
// 	axu_get_arg(&get);
// 	get.i = 0;
// 	ft_printf(G"%s<-\n"E, get.split[0]);
// 	while (get.arg[get.i])
// 		ft_printf(G"%s\n"E, get.arg[get.i++]);
// 	free_split(get.split);
// 	free(get.arg);
// 	return ("hola");
// }

char	*get_arg(char *command, char *need, t_pipex *pipex)
{
	char	*arg;
	char	**split;
	char	**get;
	char	del;

	arg = ft_strnstr(command, need, ft_strlen(command));
	arg = &arg[ft_strlen(need) + (!is_del_close(&arg[ft_strlen(need)], D_QUOTES
		|| !is_del_close(&arg[ft_strlen(need)], QUOTES)))];
	del = ' ';
	if (ft_strchr(&arg[ft_strlen(need)], D_QUOTES))
		del = D_QUOTES;
	split = ft_split(&arg[ft_strlen(need) - 1], del);
	if (!split)
		exit (close_and_exit(E_MEM, 1, pipex));
	int i =  0;
	int j = 0;
	int len = 0;
	int	OK_ = FALSE;
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
			len++;
		ft_printf(Y"Se puede pasar?= %d el len es->%d esto: %s<-\n"E, OK_, len, split[i++]);
	}
	get = ft_calloc(len + 1, sizeof(char*));
	if (!get)
		exit (close_and_exit(E_MEM, 1, pipex));
	i =  0;
	j = 0;
	len = 0;
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
		if (OK_ == TRUE && split[i])
			get[len++] = split[i];
		i++;
	}
	len = 0;
	free_split(split);
	free(get);
	return (&arg[ft_strlen(need)]);
}

void	parse_command(char *command, t_pipex *pipex)
{
	if  (!is_del_close(command, D_QUOTES)
		|| !is_del_close(command, QUOTES))
			exit (close_and_exit(E_CNF, 126, pipex));
	get_command(command, pipex);
	get_arg(command, get_command(command, pipex), pipex);
	ft_printf("%s\n", get_command(command, pipex));
	ft_printf(B"%s\n"E, get_arg(command, get_command(command, pipex), pipex));
}

void	init_pipex(t_pipex	*pipex, int ac, char **av, char **env)
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
	t_pipex	pipex;
	if (ac != 5)
		exit(msg_error(E_ARG, 1));
	init_pipex(&pipex, ac, av, env);
	parse_command(pipex.cmmd1, &pipex);
	return (SUCCESS);
}