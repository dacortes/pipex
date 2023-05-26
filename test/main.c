/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:33:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/26 15:52:06 by dacortes         ###   ########.fr       */
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

int	close_and_exit(int error, int exit_, t_test *pipex)
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

// void get_command(t_test *pipex)
// {
// 	if  (!is_del_close(pipex->cmmd1, D_QUOTES)
// 		|| !is_del_close(pipex->cmmd1, QUOTES))
// 		{
// 			close(pipex->tube[0]);
// 			close(pipex->tube[1]);
// 			exit (msg_error(E_CNF, 126));
// 		}
// 	int i = 0;
// 	int j = 0;
// 	int		space = 0;
// 	while (pipex->cmmd1[i] && (pipex->cmmd1[i] == D_QUOTES
// 		|| pipex->cmmd1[i] == QUOTES))
// 		i++;
// 	if (pipex->cmmd1[i] == ' ')
// 		exit (msg_error(E_CNF, 126));
// 	while (pipex->cmmd1[i])
// 	{
// 		if  (pipex->cmmd1[i] == ' ')
// 				space++;
// 		if (pipex->cmmd1[i] &&  pipex->cmmd1[i] != ' '
// 		&& (pipex->cmmd1[i] != D_QUOTES && pipex->cmmd1[i] != QUOTES))
// 			j++;
// 		if (pipex->cmmd1[i] && (pipex->cmmd1[i] == D_QUOTES
// 		|| pipex->cmmd1[i] == QUOTES))
// 			break ;
// 		i++;
// 	}
// 	char	*command;
// 	char	*arg;

// 	command = ft_calloc(j + 1, sizeof(char));
// 	if (!command)
// 	{
// 		close(pipex->tube[0]);
// 		close(pipex->tube[1]);
// 		exit (msg_error(E_MEM, 1));
// 	}
// 	if (space)
//     	i = i - j - space;
// 	else
// 		i = i - j;
// 	j = 0;
// 	while (pipex->cmmd1[i] && (pipex->cmmd1[i] != D_QUOTES
// 		&& pipex->cmmd1[i] != QUOTES) && pipex->cmmd1[i] != ' ')
// 		command[j++] = pipex->cmmd1[i++];
// 	ft_printf("el  comand:%s<----\n", command);
// 	free(command);
// 	i = i + (pipex->cmmd1[i + 1] == D_QUOTES || pipex->cmmd1[i + 1] == QUOTES);
// 	while (pipex->cmmd1[i] && pipex->cmmd1[i] == ' ')
// 		i++;
// 	arg = &pipex->cmmd1[i];
// 	ft_printf("los argumentos:%s<----\n", arg);
// 	i = 0;
// 	int comas = 0;
// 	int espacios = 0;
// 	int comas_s = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == D_QUOTES)
// 			comas++;
// 		if (arg[i] == QUOTES)
// 			comas_s++;
// 		if (arg[i] == ' ')
// 			espacios++;
// 		i++;
// 	}
// 	ft_printf("doble comas:%d espacioes%d comas simples%d\n", comas, espacios, comas_s);
// 	char **split = ft_split(arg, D_QUOTES);
// 	ft_printf(Y"%s-"E, split[1]);
// 	free_split(split);
// 	ft_printf(R"\nEl size es :%d<----\n"E, ft_strlen(command));
// }

int	ignore(char *str, char a, char b, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == a || str[i] == b || str[i] == c))
		i++;
	return (i);
}
char	*get_command(char *command, t_test *pipex)
{
	int		i;
	int		len;
	char	*tmp_comd;

	len = 0;
	i = ignore(command, ' ', QUOTES, D_QUOTES);
	while (command[i])
	{
		if (command[i] && command[i] != ' ' && command[i] != QUOTES
			&& command[i] != D_QUOTES)
			len++;
		if (command[i] && (command[i] == ' ' || command[i] == QUOTES
			|| command[i] == D_QUOTES))
			break ;
		i++;
	}
	tmp_comd = ft_calloc(len +  1, (sizeof(char)));
	if (!tmp_comd)
		exit (close_and_exit(E_MEM, 1, pipex));
	i = ignore(command, ' ', QUOTES, D_QUOTES);
	len = 0;
	while (command[i] && command[i] != ' ' && command[i] != QUOTES
			&& command[i] != D_QUOTES)
		tmp_comd[len++] = command[i++];
	free(tmp_comd);
	return (tmp_comd);
}

char	*get_arg(char *command, char *need, t_test *pipex)
{
	char	*arg;
	char	**split;
	char	**get;
	char	del;
	(void)pipex;
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
	while (get[len])
		ft_printf(G"Se paso el  str %s<-\n"E, get[len++]);
	free_split(split);
	free(get);
	return (&arg[ft_strlen(need)]);
}

void	parse_command(char *command, t_test *pipex)
{
	if  (!is_del_close(command, D_QUOTES)
		|| !is_del_close(command, QUOTES))
			exit (close_and_exit(E_CNF, 126, pipex));
	get_command(command, pipex);
	get_arg(command, get_command(command, pipex), pipex);
	ft_printf("%s\n", get_command(command, pipex));
	ft_printf(B"%s\n"E, get_arg(command, get_command(command, pipex), pipex));
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
	parse_command(pipex.cmmd1, &pipex);
	return (SUCCESS);
}