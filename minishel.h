/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:55:07 by hmiso             #+#    #+#             */
/*   Updated: 2020/10/31 17:58:31 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHEL_H
# define MINISHEL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#define PIPE_READ 0
#define PIPE_WRITE 1

int g_exit_code = 0;

typedef struct s_vars{

char		**envp_copy;
int			count_envp;
char        *path;
int			save_std_in;
int			save_std_out;
int			count_pipe;
int			count_comand;
int			index_pipe;
}				t_vars;

void		free_two_dimensional_array(char **arr);
void		envp_copy(char **envp, t_vars *vars);
void		update_envp(char **str, t_vars *vars);
int			export_out(t_vars *vars, char **line);
int			ft_unset(t_vars *vars, char *str);
void		free_two_dimensional_array(char **arr);
int			ft_echo(char **line, t_vars *vars);
int			ft_echo_n(char **line, t_vars *vars);
int			ft_env(t_vars *vars);
int			ft_ls(char *line, t_vars *vars);
void		ft_pars_argument(char *line, t_vars *vars);
char		*init_patch(t_vars *vars, char *arg);

#endif