/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_recoded_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:31:40 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/03 15:08:42 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int		checking_recoded_functions(char **comand_line, t_vars *vars)
{
	char **argv;
	int count;

	count = 0;
	if (ft_strncmp(comand_line[0], "cd", 2) == 0)
	{
		ft_cd(comand_line, vars);
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "pwd", 3) == 0)
	{
		ft_pwd();
		return (1);		
	}
	else if ((ft_strncmp(comand_line[0], "echo", 4) == 0) && (comand_line[1] != NULL) && (ft_strncmp(comand_line[1], "-n", 2)) == 0)
	{
		ft_echo_n(&comand_line[0], vars);
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "echo", 4) == 0)
	{
		ft_echo(&comand_line[0], vars);
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "env", 3) == 0)
	{
		ft_env(vars);
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "export", 6) == 0)
	{
		export_out(vars, &comand_line[0]);
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "exit", 5) == 0)
	{
		ft_exit(comand_line);
		return (1);
	}
	else if (ft_strncmp(comand_line[0], "unset", 5) == 0)
	{
		argv = &comand_line[0];
		while(argv[count] != NULL)
		{
			ft_unset(vars, argv[count]);
			count++;
		}
		return (1);
	}
	return (0);
}