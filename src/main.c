/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/16 12:53:33 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

void	parse_file(char *file, int *fd, int type)
{
	if (type == IN)
	{
		if ((access(file, F_OK) == ERROR 
			|| access(file, X_OK) == ERROR))
			exit (printf_error(E_NSF, -2));
		(*fd) =  open(file, O_RDONLY);
		if ((*fd) < 0)
			exit(printf_error(E_OPN, 1));
	}
	else if (type == OUT)
	{
		(*fd) = open(file, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if ((*fd) < 0)
			exit(printf_error(E_OPN, 1));
	}
}
void	first_child(t_pipex *p, t_parse *com1, char **env)
{
	dup2(p->tube[1], 1);
	close(p->tube[0]);
	dup2(p->fd_in, 0);
	if (!com1->command)
	{
		free(com1->command);
		free(com1->argv);
		free_split(com1->split);
		return ;
	}
	ft_printf(Y"%s\n"E,com1->command);
	if (execve(com1->command, com1->argv, env) == ERROR)
		exit(printf_error(E_EXC, 1));
}

void	second_child(t_pipex *p, t_parse *com2, char **env)
{
	dup2(p->tube[1], 1);
	close(p->tube[0]);
	dup2(p->fd_out, 0);
	if (!com2->command)
	{
		free(com2->command);
		free(com2->argv);
		free_split(com2->split);
		return ;
	}
	if (execve(com2->command, com2->argv, env) == ERROR)
		exit(printf_error(E_EXC, 1));
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	t_parse	com1;
	t_parse	com2;

	if (ac != 5)
		exit(printf_error(E_ARG, 1));
	p.in_file = av[1];
	p.com1 = av[2];
	p.com2 = av[3];
	p.out_file = av[4];
	parse_file(p.in_file, &p.fd_in, IN);
	parse_file(p.out_file, &p.fd_out, OUT);
	parse_command(p.com1, env, &com1);
	parse_command(p.com2, env, &com2);
	if (pipe(p.tube) < 0)
		exit(printf_error(E_PIP, 1));
	p.pid1 = fork();
	if (p.pid1 < 0)
		exit(printf_error(E_FRK, 1));
	else if (!p.pid1)
		first_child(&p, &com1, env);
	p.pid2 = fork();
	if (p.pid2 < 0)
		exit(printf_error(E_FRK, 1));
	else if (!p.pid2)
		second_child(&p, &com2, env);
	close(p.tube[0]);
	close(p.tube[1]);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
	close(p.fd_in);
	close(p.fd_out);
	free(com1.command);
	free(com1.argv);
	free_split(com1.split);
	free(com2.command);
	free(com2.argv);
	free_split(com2.split);
	return (SUCCESS);
}