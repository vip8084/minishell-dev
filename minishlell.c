/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishlell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:03 by hmiso             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/11/06 16:23:14 by hmiso            ###   ########.fr       */
=======
/*   Updated: 2020/11/07 18:31:41 by curreg           ###   ########.fr       */
>>>>>>> test
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	ft_pars_argument(char *line, t_vars *vars)
{
		char **comand_line;
		char **line_pipe;
		char *comand_path;
		char **argv;
		char *ptr;
		int mas[2];
		int count = 0;
		int	i = 0;
		int t = 0;

		comand_line = ft_split(line, ' ');
		check_pipe(comand_line, vars);
		check_redirect(comand_line, vars);
		if (vars->count_pipe == 0 && vars->count_redirect == 0)
		{
			if(!(checking_recoded_functions(comand_line, vars)))
			{
				comand_path = check_system_funk(vars, comand_line);
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, comand_line[0]);			
				system_funk(comand_path, comand_line, vars);
			}
		}
		else
		{
			ft_conveyor(line, comand_line, vars);
			dup2(vars->save_std_in, 0);
			dup2(vars->save_std_out, 1);
		}
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char *ptr;
	char *line = NULL;
	int i = 0;
	struct dirent *dir;
<<<<<<< HEAD
	vars.count_call_pipe = 0;
	vars.flag_redirect = 0;
=======

	errno = 0;
	g_error = 0;
	vars.err_flag = 0;
>>>>>>> test
	vars.save_std_in = dup(0);
	vars.save_std_out = dup(1);
	envp_copy(envp, &vars);
	vars.path = init_patch(&vars, "PATH");
	ft_putstr_fd("minishell>", 1);
	while((i = get_next_line(0, &line)) > 0)
	{
		ft_pars_argument(line, &vars);
		free(line);
		line = NULL;
		ft_putstr_fd("minishell>", 1);
		vars.count_call_pipe = 0;
	}
	return 0;
}