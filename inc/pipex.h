/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:15:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/05/26 18:24:36 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include"../libft/libft.h"
# include"../libft/ft_printf.h"
# include"../libft/get_next_line.h"

// ================================= MACROS ================================= //

/* Utils */
# define D_QUOTES	34
# define QUOTES		39

/* Outputs */
# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1

/* Error */
# define	E_ARG 1
# define	E_MEM 2
# define	E_PTH 3
# define	E_NSF 4
# define	E_OPN 5
# define	E_FRK 6
# define	E_PIP 7
# define	E_EXC 8
# define	E_PRM 126
# define	E_CNF 127
/* Type file */
# define	IN	1
# define	OUT 2

// ================================= COLORS ================================= //

# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue

// ================================= STRUCTURES ============================= //

/* structure find */

/* test estruc */
typedef struct s_pipex
{
	char	*path;
	char	*infile;
	char	*outfile;
	char	*cmmd1;
	char	*cmmd2;
	int		tube[2];
	int		infd;
	int		outfd;
}	t_pipex;
/* get_arg */
typedef struct s_get
{
	char	**split;
	char	**arg;
	char	*cmmd;
	char	del;
	int		len;
	int		i;
	int		j;
}	t_get;

// ================================= FUNCTIONS ============================== //

// /* command/find_command.c */
// char	*find_path(char **env);
// int		find_command(char *command, char **env, t_f_com *parse);
// /* command/parse.c */
// char	*find_slash(char *command);
// void	parse_command(char *command, char **env, t_parse *com, t_f_com *path);
// /* scr/utils.c */
// void	free_split(char **split);
// int		double_ptr_len(void **ptr);
// int		check_quotes(char *str);
// int		check_quotes_argv(char **agrv);
// int		printf_error(int error,  int exit_);
#endif