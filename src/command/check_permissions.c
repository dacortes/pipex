/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:35:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/05 12:02:45 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

int	check_perissions(t_f_com *parse)
{
	if (!parse->f_ok)
		return (FALSE);
	if (access(parse->path, X_OK) == ERROR)
	{
		perror(E_PERM);
		exit (ERROR);
	}
	return (TRUE);
}
