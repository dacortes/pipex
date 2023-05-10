/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/10 09:37:24 by dacortes         ###   ########.fr       */
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

int	check_quotes(char *str)
{
	int	quotes;
	int	i = 0;

	quotes = FALSE;
	while (str[i])
	{
		if (str[i] == D_QUOTES)
		{
			quotes = TRUE;
			i++;
			while (str[i] && str[i] != D_QUOTES )
				i++;
		}
		if (!str[i])
			return (FALSE);
		i++;
	}
	return (!quotes || (quotes && (str[i - 1] == D_QUOTES)));
}

int	check_quuotes_argv(char **agrv)
{
	int i;
	i = 0;
	while (agrv[i])
	{
		if (!check_quotes(agrv[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	parse_command(char *command)
{
	t_parse	com;

	com.split = ft_split(command, ' ');
	com.argv = ft_calloc(double_ptr_len((void *)com.split) + 1, sizeof(char *));
	if (!com.argv)
	{
		perror(E_MEMO);
		exit (ERROR);
	}
	com.command = com.split[0];
	com.i = 0;
	while (com.split[com.i++])
		com.argv[com.i - 1] = com.split[com.i];
	com.i = 0;
	while (com.argv[com.i])
		ft_printf("The argument is:%s%s%s\n", B, com.argv[com.i++], E);
	if (!(check_quotes(com.command) && check_quuotes_argv(com.argv)))
		ft_printf("%sKO\n%s", R, E);
	free(com.argv);
	free_split(com.split);
}

int	main (int ac,  char **av)
{
	if (ac != 5)
	{
		perror(E_NARC);
		return (ERROR);
	}
	// char	*i_file = av[1];
	char	*com1 = av[2];
	// char	*com2 = av[3];
	// char	*o_file = av[4];
	parse_command(com1);
	return (SUCCESS);
}