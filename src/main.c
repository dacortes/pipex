/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/05 15:11:46 by dacortes         ###   ########.fr       */
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
	// t_f_com parse;
	// char	*command;
	(void)env;
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
	if (num_com)
	{
		perror(E_MEMO);
		return (ERROR);
	}
	i = 0;
	while (av[i])
	{
		av[i]
	}
	
	free(num_com);
	return (SUCCESS);
}