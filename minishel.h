/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:17:01 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 15:34:29 by hmiso            ###   ########.fr       */
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
int         err_flag_export;
int         cd_flag;
int			*mas_flags;
}				t_vars;

typedef struct s_upd{

	int		i;
	int		j;
	char	**new_envp;
	char	**ar_1;
	char	**ar_2;
	int		count;
	int		flag;
	char	*ptr;
	char	**new_str;
}				t_upd;

typedef struct s_space{

	int		i;
	int		flag;
	char	*ptr;
	char	*ptr_for_free;
	char	*line;
}				t_space;

typedef struct s_sys_funk{

	DIR				*dir;
	struct dirent	*st;
	char			**path;
	char			*ptr;
	int				i;
	int				flag;
}				t_sys_funk;

typedef struct s_conveyor{

	char		**line_pipe;
	char		*comand_path;
	char		**com_whis_flags;
	char		**mas_redirektion;
	char		**mas_redirektion2;
	int			i;
	int			j;
	int			k;
	int			flag;
	int			flag_pipe;
}				t_conveyor;

typedef struct s_quotes{

	int			i;
	int			flag;
	int			count;
	char		*line_dubl;
}				t_quotes;

void        set_g_error(int err);
void        show_g_error();
void        command_error(char *cmd, t_vars *vars);
void		syntax_error(char *cmd);
void        cd_error(char *cmd, char *arg, char *err);
int         check_valid_id(char *str);
void        id_error(char *cmd, t_vars *vars);
void		set_pwd(char *var, t_vars *vars);
void		envp_copy(char **envp, t_vars *vars);
void		update_envp(char **str, t_vars *vars);
void		export_out(t_vars *vars, char **line);
void		ft_unset(t_vars *vars, char **str);
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
void		init_conveyor(t_conveyor *conveyor);
void		conveyor_res(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_2(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_3(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_4(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_5(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_6(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_7(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_8(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_9(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_10(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_11(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_12(char **comand_line, t_vars *vars, t_conveyor *conveyor);
void		conveyor_res_13(char **comand_line, t_vars *vars, t_conveyor *conveyor);
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
void		create_file(char **comand_line,int *mas_flags);
void		ft_pipe_eof(void);
char		*ft_join_path(t_vars *vars, char **com_whis_flags);
char		**make_list_rederection_revers(char **comand_line, int i, int j, t_vars *vars);
char		**make_list_rederection(char **comand_line, int i, int j, t_vars *vars);
char		**make_comand_mas_start(char **comand_line, int i, int j);
void		check_space_res_4(t_space *space);
#endif