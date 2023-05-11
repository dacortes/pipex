/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:09:04 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/11 12:16:05 by dacortes         ###   ########.fr       */
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

/*com.i = 0;
while (com.argv[com.i])
	ft_printf("The argument is:%s%s%s\n", B, com.argv[com.i++], E);*/

void	init_struc(t_f_com *path)
{
	path->split = NULL;
	path->path = NULL;
	path->add = NULL;
	path->join = NULL;
	path->i = 0;
	path->axu_i = 0;
	path->f_ok = FALSE;

}

void	parse_command(char *command, char **env)
{
	t_parse	com;
	t_f_com path;

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
	if (!(check_quotes(com.command) && check_quuotes_argv(com.argv)))
	{
		ft_printf("%s%s%s\n", R, E_INVC, E);
		free(com.argv);
		free_split(com.split);
		exit (ERROR);
	}
	if (find_command(com.command, env, &path) == TRUE)
		ft_printf("%sOK\n%s", G, E);
	else
		ft_printf("%sKO\n%s", R, E);
	free(com.argv);
	free_split(com.split);
}

int	main (int ac,  char **av, char **env)
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
	parse_command(com1, env);
	return (SUCCESS);
}