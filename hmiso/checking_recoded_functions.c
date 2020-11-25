/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_recoded_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:31:40 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/24 18:35:15 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int		checking_recoded_functions(char **comand_line, t_vars *vars)
{
	char **argv;
	int count;

	count = 0;
	if (ft_strncmp(comand_line[0], "cd", 3) == 0)
	{
		ft_cd(comand_line, vars);
		vars->err_flag = 0;
		g_error = 1; //////
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "pwd", 4) == 0)
	{
		ft_pwd();
		vars->err_flag = 0;
		g_error = 0;
		return (1);		
	}
	else if ((ft_strncmp(comand_line[0], "echo", 5) == 0) && (comand_line[1] != NULL) && (ft_strncmp(comand_line[1], "-n", 3)) == 0)
	{
		ft_echo_n(&comand_line[0], vars);
		vars->err_flag = 0;
		g_error = 0;
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "echo", 5) == 0)
	{
		ft_echo(&comand_line[0], vars);
		vars->err_flag = 0;
		g_error = 0;
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "env", 4) == 0)
	{
		if (comand_line[1] != NULL)
		{
			ft_putstr_fd("minishell>env: ", 1);
			ft_putstr_fd(comand_line[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_error = 127;
		}
		else
		{
			ft_env(vars);
			vars->err_flag = 0;
			g_error = 0;
		}
			return (1);
	}
	else if (ft_strncmp(comand_line[0], "export", 7) == 0)
	{
		export_out(vars, &comand_line[0]);
		vars->err_flag = 0;
		if (!vars->err_flag_export)
			g_error = 0;
		vars->err_flag_export = 0;
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "exit", 6) == 0)
	{
		ft_exit(comand_line);
		vars->err_flag = 0;
		g_error = 0;
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "unset", 6) == 0)
	{
		argv = &comand_line[0];
		while(argv[count] != NULL)
		{
			ft_unset(vars, argv[count]);
			count++;
		}
		vars->err_flag = 0;
		g_error = 0;
		return (1);
	}
	return (0);
}