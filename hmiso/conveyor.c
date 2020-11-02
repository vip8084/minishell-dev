/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:27:08 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 18:38:58 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	ft_conveyor(char *line, char **comand_line, t_vars *vars)
{
	char **line_pipe;
	char *comand_path;
	int i;

	i = 0;
	line_pipe = ft_split(line, '|');
	while (line_pipe[i] != NULL)
	{
		if (vars->count_pipe - i > 0)
		{
			comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
			comand_line = ft_split(line_pipe[i], ' ');
			comand_path = ft_strjoin(comand_path, "/");
			comand_path = ft_strjoin(comand_path, comand_line[0]);
			ft_pipe(comand_path, comand_line, vars);
			i++;
		}
		else
		{
			if(!(checking_recoded_functions(&line_pipe[i], vars)))			
			{
				comand_line = ft_split(line_pipe[i], ' ');
				comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, comand_line[0]);
				system_funk(comand_path, comand_line, vars);
			}
			i++;
		}
	}
	dup2(vars->save_std_in, 0);
	dup2(vars->save_std_out, 1);	
}