/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/09 11:13:44 by dacortes         ###   ########.fr       */
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

void	are_there_quotes(char *command, int *d_quotes, int *s_quotes)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (command[i] == D_QUOTES)
		{
			(*d_quotes)++;
		}
		else if (command[i] == S_QUOTES)
		{
			(*s_quotes)++;
		}
		i++;
	}
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
	
	/* parseo */
	int		space = 0;
	int		word = 0;
	int		d_quotes = 0;
	int		s_quotes = 0;
	ft_printf("%s%s%s%s\n", "in file: ", B, i_file, E);
	ft_printf("%s%s%s%s\n", "command1: ", B, com1, E);
	ft_printf("%s%s%s%s\n", "command2: ", B, com2, E);
	ft_printf("%s%s%s%s\n", "out file: ", B, o_file, E);
	/* find  quotes */
	are_there_quotes(com1, &d_quotes, &s_quotes);
	ft_printf("%sdouble quotes:%s %d\n", Y, E, d_quotes);
	ft_printf("%ssingle quotes:%s %d\n", Y, E, s_quotes);
	d_quotes = 0;
	s_quotes = 0;
	are_there_quotes(com2, &d_quotes, &s_quotes);
	ft_printf("%sdouble quotes:%s %d\n", Y, E, d_quotes);
	ft_printf("%ssingle quotes:%s %d\n", Y, E, s_quotes);
	/* word count */
	word_count(&space, &word, com1);
	if (space)
		ft_printf("%sTRUE%s\n", B, E);
	else
		ft_printf("%sFALSE%s\n", B, E);
	ft_printf("%scount words:%s %d\n", Y, E, word);
	return (SUCCESS);
}