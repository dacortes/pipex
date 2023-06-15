/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:01:24 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/13 17:41:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/pipex.h"

void	axu_get_arg(t_get *g)
{
	int	ok;

	g->i = 0;
	g->len = 0;
	ok = FALSE;
	while (g->split[g->i])
	{
		g->j = 0;
		ok = FALSE;
		while (g->split[g->i][g->j])
		{
			if (g->split[g->i][g->j] != ' ' )
			{
				ok = TRUE;
				break ;
			}
			g->j++;
		}
		if (ok == TRUE && g->split[g->i])
			g->arg[g->len++] = g->split[g->i];
		g->i++;
	}
}

void	axu_get_arg_len(int *len, char **split)
{
	int	i;
	int	j;
	int	ok;

	i = 0;
	j = 0;
	(*len) = 0;
	ok = FALSE;
	while (split[i])
	{
		j = 0;
		ok = FALSE;
		while (split[i][j])
		{
			if (split[i][j] != ' ')
			{
				ok = TRUE;
				break ;
			}
			j++;
		}
		if (ok == TRUE)
			(*len)++;
		i++;
	}
}

void	get_arg(char *cmd, char *nd, t_pipex *pipex, t_get *g)
{
	g->n_arg = ft_strnstr(cmd, nd, ft_strlen(cmd));
	g->del = ' ';
	if (ft_strchr(g->n_arg, D_QUOTES))
		g->del = D_QUOTES;
	if (ft_strchr(g->n_arg, QUOTES))
		g->del = QUOTES;
	g->split = ft_split(g->n_arg, g->del);
	if (!g->split)
		exit (close_exit(E_MEM, 1, NULL, pipex));
	axu_get_arg_len(&g->len, g->split);
	g->arg = ft_calloc(g->len + 1, sizeof(char *));
	if (!g->arg)
	{
		free_split(g->split);
		exit(close_exit(E_MEM, 1, NULL, pipex));
	}
	axu_get_arg(g);
	g->i = 0;
}

void	get_path(t_pipex *pipex, t_get *get)
{
	char	*tmp;
	char	*cmmd;

	tmp = NULL;
	cmmd = NULL;
	get->paht = ft_split(pipex->path, ':');
	axu_get_path(tmp, cmmd, pipex, get);
}

void	axu_get_path(char *tmp, char *cmmd, t_pipex *pipex, t_get *get)
{
	while (get->paht[get->i])
	{
		tmp = ft_addend_char(get->paht[get->i], '/');
		if (!tmp)
			exit(close_exit(E_MEM, 1, NULL, pipex));
		cmmd = ft_strjoin(tmp, get->cmmd);
		if (!cmmd)
		{
			free(tmp);
			exit(close_exit(E_MEM, 1, NULL, pipex));
		}
		if (access(cmmd, 0) == SUCCESS)
		{
			free(tmp);
			free(get->cmmd);
			get->cmmd = cmmd;
			get->i = 0;
			break ;
		}
		free(cmmd);
		free(tmp);
		get->i++;
	}
	get->i = 0;
}
