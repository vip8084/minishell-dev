/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:10:28 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/30 12:23:32 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		init_exute(t_execute *execute)
{
	execute->comand_line = NULL;
	execute->comand_path = NULL;
	execute->ptr_fre = NULL;
}

static void		execute_command_res(t_execute *execute, t_vars *vars)
{
	if (!(checking_recoded_functions(execute->comand_line, vars)))
	{
		execute->comand_path = check_system_funk(vars, execute->comand_line[0]);
		if (execute->comand_path == NULL)
			execute->comand_path = ft_strdup(execute->comand_line[0]);
		else
		{
			execute->ptr_fre = execute->comand_path;
			execute->comand_path = ft_strjoin(execute->comand_path, "/");
			ptr_free(&execute->ptr_fre);
			execute->ptr_fre = execute->comand_path;
			execute->comand_path = ft_strjoin(execute->comand_path,
			execute->comand_line[0]);
			ptr_free(&execute->ptr_fre);
		}
		system_funk(execute->comand_path, execute->comand_line, vars);
	}
}

static void		execute_command_res_2(t_execute *execute,
t_vars *vars, char *line)
{
	if (execute->comand_line != NULL)
		free_two_dimensional_array(execute->comand_line);
	if (execute->comand_path != NULL)
		ptr_free(&execute->comand_path);
	ptr_free(&line);
	free(vars->mas_flags);
	vars->mas_flags = NULL;
}

void			execute_command(char *line, t_vars *vars)
{
	t_execute execute;

	init_exute(&execute);
	line = check_space(line);
	execute.comand_line = ft_pars(line, vars);
	if (execute.comand_line[0] != NULL)
	{
		if ((execute.comand_line = verification_of_tokens(execute.comand_line,
		vars)) != NULL)
		{
			execute.comand_line = move_arguments(execute.comand_line, vars);
			check_pipe(execute.comand_line, vars);
			check_redirect(execute.comand_line, vars);
			if (vars->count_pipe == 0 && vars->count_redirect == 0)
				execute_command_res(&execute, vars);
			else
			{
				ft_conveyor(execute.comand_line, vars);
				dup2(vars->save_std_in, 0);
				dup2(vars->save_std_out, 1);
			}
		}
	}
	execute_command_res_2(&execute, vars, line);
}
