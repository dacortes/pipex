/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:08 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/10 09:00:56 by dacortes         ###   ########.fr       */
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
