/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:15:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/08 16:55:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include"../libft/libft.h"
# include"../libft/ft_printf.h"
# include"../libft/get_next_line.h"

// ================================= MACROS ================================= //

/* Utils */
# define D_QUOTES	34
# define S_QUOTES	39
/* Outputs */
# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1

/* Errors */
# define E_MEMO "Memory allocation error"
# define E_PATH "Path not found"
# define E_COMN "Command not found"
# define E_PERM "Permissions denied"
# define E_NARC "number of invalid arguments"

// ================================= COLORS ================================= //

# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue

// ================================= STRUCTURES ============================= //

/* structure find */

typedef struct s_f_com
{
	char	**split;
	char	*path;
	char	*add;
	char	*join;
	int		i;
	int		axu_i;
	int		f_ok;
}	t_f_com;

/* structure main */

typedef struct s_pipex
{
	char	**n_com;
	char	*in_file;
	char	*out_file;
	char	**split;
}	t_pipex;



// ================================= FUNCTIONS ============================== //

/* command/check_permissions.c */
int		check_perissions(t_f_com *parse);
/* command/find_command.c */
char	*find_path(char **env);
int		find_command(char *command, char **env, t_f_com *parse);
/* scr/utils.c */
void	free_split(char **split);
#endif