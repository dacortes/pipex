/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/08 20:05:39 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_f_com parse;
// 	char	*command;

// 	if (ac == 1)
// 	{
// 		perror(E_NARC);
// 		exit(ERROR);
// 	}
// 	command = ft_strjoin("/", av[1]);
// 	char *args[] = {command, NULL};
// 	ft_printf("the command is :%s\n", command);
// 	if (find_command(command, env, &parse) && check_perissions(&parse))
// 		ft_printf(B"PATH=%s\n"E, parse.path);
// 	if (execve(parse.path, args, env) == -1)
// 	{
// 		free(command);
// 		perror("Could not execve");
// 		return (ERROR);
// 	}
// 	free(command);
// 	return (SUCCESS);
// }


// int	main(int ac, char **av, char **env)
// {
// 	(void)env;
// 	char	**n_com;
// 	char	*in_file;
// 	char	*out_file;
// 	int		i;

// 	if (ac != 5)
// 	{
// 		perror(E_NARC);
// 		exit (ERROR);
// 	}
// 	n_com = ft_calloc(sizeof(char *), ac - 2);
// 	if (!n_com)
// 	{
// 		perror(E_MEMO);
// 		return (ERROR);
// 	}
// 	i = 1;
// 	while (av[i++] && i < ac - 1)
// 		n_com[i - 2] = av[i];
// 	in_file = av[1];
// 	out_file = av[ac - 1];
// 	free(n_com);
// 	return (SUCCESS);
// }

// void	init_struc(t_f_com *parse)
// {
// 	parse->split = NULL;
// 	parse->path = NULL;
// 	parse->add = NULL;
// 	parse->join = NULL;
// 	parse->i = 0;
// 	parse->axu_i = 0;
// 	parse->f_ok= 0;
// }

// int	main(int ac, char **av, char **env)
// {
// 	(void)env;
// 	t_pipex	p;
// 	t_f_com parse;
// 	int		i;

// 	if (ac != 5)
// 	{
// 		perror(E_NARC);
// 		exit (ERROR);
// 	}
// 	p.n_com = ft_calloc(sizeof(char *), ac - 2);
// 	if (!p.n_com)
// 	{
// 		perror(E_MEMO);
// 		return (ERROR);
// 	}
// 	init_struc(&parse);
// 	i = 1;
// 	while (av[i++] && i < ac -1)
// 		p.n_com[i - 2] = av[i];
// 	p.in_file = av[1];
// 	p.out_file = av[ac - 1];
// 	ft_printf("%s%s%s%s\n", "In file: ", B, p.in_file, E);
// 	ft_printf("%s%s%s%s\n", "Command1: ", B, p.out_file, E);
// 	ft_printf("%s%s%s%s\n", "Command2: ", B, p.n_com[0], E);
// 	ft_printf("%s%s%s%s\n", "Out file: ", B, p.n_com[1], E);
// 	ft_printf("%s%s%s\n", G, "Aply split", E);
// 	i = 0;
// 	int j = 0;
// 	int c = 0;
// 	char *command;
// 	while (p.n_com[i])
// 	{
// 		j = 0;
// 		while (p.n_com[i][j] && p.n_com[i][j] != D_QUOTES
// 			&& p.n_com[i][j] != ' ')
// 			j++;
// 		command = ft_calloc(sizeof(char), j + 1);
// 		if (!command)
// 		{
// 			perror(E_MEMO);
// 			return (ERROR);
// 		}
// 		j = 0;
// 		while (p.n_com[i][j] && p.n_com[i][j] != D_QUOTES
// 			&& p.n_com[i][j] != ' ')
// 			command[c] = p.n_com[i][j++];
// 		ft_printf(R"%s\n"E, command);
// 		free(command);
// 		i++;
// 	}
// 	free(p.n_com);
// 	return (SUCCESS);
// }

int	are_there_quotes(char *command)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (command[i] == D_QUOTES)
		{
			return (TRUE);
			break ;
		}
		i++;
	}
	return (FALSE);
}
void	word_count(int *space, int *word, char *command)
{
	int i;
	int	p;

	i = 0;
	p = 0;
	while (command[i])
	{
		if (command[i] != ' ' && !p)
		{
			(*word)++;
			p = 1;
		}
		else if (command[i] == ' ')
		{
			*space = TRUE;
			p = 0;
		}
		i++;
	}
	
}
int	main(int ac, char **av)
{
	if (ac != 5)
	{
		perror(E_NARC);
		return (ERROR);
	}
	char	*i_file = av[1];
	char	*com1 = av[2];
	char	*com2 = av[3];
	char	*o_file = av[4];
	
	ft_printf("%s%s%s%s\n", "in file: ", B, i_file, E);
	ft_printf("%s%s%s%s\n", "command1: ", B, com1, E);
	ft_printf("%s%s%s%s\n", "command2: ", B, com2, E);
	ft_printf("%s%s%s%s\n", "out file: ", B, o_file, E);
	if (are_there_quotes(com1))
		ft_printf("status com1: %s%s%s\n", G, "OK", E);
	else
		ft_printf("status com1: %s%s%s\n", R, "KO", E);
	if (are_there_quotes(com2))
		ft_printf("status com1: %s%s%s\n", G, "OK", E);
	else
		ft_printf("status com1: %s%s%s\n", R, "KO", E);

	return (SUCCESS);
}