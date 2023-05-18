/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:08 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/17 11:14:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	if (split)
		free(split);
}

int	check_quotes(char *str)
{
	int	quotes;
	int	i;

	i = 0;
	quotes = FALSE;
	while (str[i])
	{
		if (str[i] == D_QUOTES)
		{
			quotes = TRUE;
			i++;
			while (str[i] && str[i] != D_QUOTES)
				i++;
		}
		if (!str[i])
			return (FALSE);
		i++;
	}
	return (!quotes || (quotes && (str[i - 1] == D_QUOTES)));
}

int	check_quotes_argv(char **agrv)
{
	int	i;

	i = 0;
	while (agrv[i])
	{
		if (!check_quotes(agrv[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	printf_error(int error, int exit_)
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