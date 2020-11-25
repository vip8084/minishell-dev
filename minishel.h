/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:17:01 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 15:58:25 by hmiso            ###   ########.fr       */
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
#include <string.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#define PIPE_READ 0
#define PIPE_WRITE 1

int g_error;
int g_signal;

typedef struct s_vars{

char		**envp_copy;
int			count_envp;
char        *path;
int			save_std_in;
int			save_std_out;
int			count_pipe;
int			count_comand;
int			index_pipe;
int 		g_exit_code;
int			count_redirect;
int			count_call_pipe;
int         flag_redirect;
int         err_flag;
int         cd_flag;
int			*mas_flags;
}				t_vars;

void        set_g_error(int err);
void        show_g_error();
void        command_error(char *cmd, t_vars *vars);
void        cd_error(char *cmd, char *arg, char *err);
int         check_valid_id(char *str);



void		envp_copy(char **envp, t_vars *vars);
void		update_envp(char **str, t_vars *vars);
void		export_out(t_vars *vars, char **line);
void		ft_unset(t_vars *vars, char *str);
void		free_two_dimensional_array(char **arr);
void		ft_echo(char **line, t_vars *vars);
void		ft_echo_n(char **line, t_vars *vars);
void		ft_env(t_vars *vars);
int			ft_ls(char *line, t_vars *vars);
void		ft_pars_argument(char *line, t_vars *vars);
char		*init_patch(t_vars *vars, char *arg);
void		ft_cd(char **comand_line, t_vars *vars);
void		ft_pwd(void);
char		**check_duplicate(char **argv);
char		*init_patch(t_vars *vars, char *arg);
void		ft_exit(char **comand_line);
void		system_funk(char *path, char **argv, t_vars *vars);
char 		*check_system_funk(t_vars *vars, char *str);
void		ft_pipe(char *path, char **comand, t_vars *vars);
void		check_pipe(char **comand_mas, t_vars *vars);
int			checking_recoded_functions(char **comand_line, t_vars *vars);
void		ft_conveyor(char *line, char **comand_line, t_vars *vars);
void		check_redirect(char **comand_mas, t_vars *vars);
void		ft_conveyor_test(char *line, char **comand_line, t_vars *vars);
void		ft_redirects(char *path, char **comand, char **mas_redirektion, t_vars *vars);
void		ft_redirects_revers(char *path, char **comand, char **mas_redirektion, t_vars *vars);
char	    **move_arguments(char **comand_line, t_vars *vars);
void		ft_redirects_pipe(char *path, char **comand, char **mas_redirektion, t_vars *vars);
void		ft_redirects_redirect(char *path, char **comand, char **mas_redirektion, char **mas_redirektion2, t_vars *vars);
void		ft_signals(int signal);
void		ft_signal(int signal);
void		ptr_free(char **ptr);
char		**semicolon(char *line);
char 		*check_space(char *line_old);
char		*delete_quotes(char *line);
char		**environment_variable_substitution(char **comand_line, t_vars *vars);
char		**count_comands(char *line);
char		**ft_pars(char *line, t_vars *vars);
char		**verification_of_tokens(char **comand_line, t_vars *vars);
void		execute_command(char *line, t_vars *vars);
#endif