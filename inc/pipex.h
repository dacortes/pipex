/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:15:07 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/07 14:57:18 by dacortes         ###   ########.fr       */
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
# define E_ARG 1
# define E_MEM 2
# define E_NSF 3
# define E_PRR 4
# define E_PNF 5
# define E_PRM 126
# define E_CNF 127
/* Type file */
# define IN	1
# define OUT 2

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
	pid_t	pid1;
	pid_t	pid2;
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
	char	**paht;
	char	**arg;
	char	*cmmd;
	char	*n_arg;
	char	del;
	int		len;
	int		i;
	int		j;
}	t_get;

// ================================= FUNCTIONS ============================== //

/* utils.c */
void	free_get(t_get *get);
void	free_split(char **split);
int		close_del(char *str, char delimiter);
int		msg_error(int e, int exit_, char *cm);
int		close_exit(int error, int exit_, char *cmd, t_pipex *pipex);
/* get.c */
void	axu_get_arg(t_get *g);
void	axu_get_arg_len(int *len, char **split);
void	get_arg(char *cmd, char *nd, t_pipex *pipex, t_get *g);
void	get_path(t_pipex *pipex, t_get *get);
void	axu_get_path(char *tmp, char *cmmd, t_pipex *pipex, t_get *get);
/* init.c */
void	parse_file(t_pipex *pipex, int type);
void	init_pipex(t_pipex *pipex, int ac, char **av, char **env);
char	*find_path(char **env);
int		ignore(char *str, char a, char b, char c);
void	get_cmmd(char *cmd, t_pipex *pipex, t_get *g);
#endif