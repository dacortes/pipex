/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/05 17:02:37 by dacortes         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_f_com parse;
	char	**num_com;
	char	*infile;
	char	*outfile;
	char	*command;
	int		i;

	if (ac == 1)
	{
		perror(E_NARC);
		exit (ERROR);
	}
	num_com = ft_calloc(sizeof(char *), ac);
	if (!num_com)
	{
		perror(E_MEMO);
		return (ERROR);
	}
	ft_printf(B"PATH=%s\n"E, parse.path);
	i = 0;
	while (av[i++])
		num_com[i] = av[i];
	infile = num_com[1];
	outfile = num_com[ac - 1];
	i = -1;
	while (num_com[i++] && i < (ac - 2))
	{
		command = ft_strjoin("/", num_com[i]);
		if (!command)
		{
			perror(E_MEMO);
			exit (ERROR);
		}
		if (!find_command(command, env, &parse) && !check_perissions(&parse))
		{
			free(command);
			perror(E_PATH);
			return (ERROR);
		}
		free(command);
	}
	ft_printf(B"infile :%s\n"E, infile);
	ft_printf(B"outfile :%s\n"E, outfile);
	free(num_com);
	return (SUCCESS);
}