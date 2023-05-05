/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:08 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/04 11:02:13 by dacortes         ###   ########.fr       */
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
