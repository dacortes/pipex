/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:08 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/10 09:44:11 by dacortes         ###   ########.fr       */
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

int	double_ptr_len(void **ptr)
{
	int	len;

	len = 0;
	while (ptr[len])
		len++;
	return (len);
}

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