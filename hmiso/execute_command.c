/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:10:28 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 16:36:03 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	execute_command(char *line, t_vars *vars)
{
	char **comand_line = NULL;
	char *comand_path = NULL;
	char *ptr_fre;

	line = check_space(line);
	comand_line = ft_pars(line, vars);
	int i = 0;
	if (comand_line[0] != NULL)
	{
		// comand_line = move_arguments(comand_line, vars);
		// int i = 0;
		// while(comand_line[i])
		// {
		// 	printf("%d %s\n", vars->mas_flags[i], comand_line[i]);
		// 	i++;
		// }
		if ((comand_line = verification_of_tokens(comand_line, vars)) != NULL)
		{
			// int i = 0;
			// while(comand_line[i] != NULL)
			// {
			// 	printf("%s\n", comand_line[i]);
			// 	i++;
			// }
			// exit(0);
			comand_line = move_arguments(comand_line, vars);
			check_pipe(comand_line, vars);
			check_redirect(comand_line, vars);
			if (vars->count_pipe == 0 && vars->count_redirect == 0)
			{
				if(!(checking_recoded_functions(comand_line, vars)))
				{
					comand_path = check_system_funk(vars, comand_line[0]);
					if (comand_path == NULL)
						comand_path = ft_strdup(comand_line[0]);
					else
					{
						ptr_fre = comand_path;
						comand_path = ft_strjoin(comand_path, "/");
						ptr_free(&ptr_fre);
						ptr_fre = comand_path;
						comand_path = ft_strjoin(comand_path, comand_line[0]);
						ptr_free(&ptr_fre);
					}	
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
	}
	if(comand_line != NULL)
		free_two_dimensional_array(comand_line);
	if (comand_path != NULL)
		ptr_free(&comand_path);
	ptr_free(&line);
	free(vars->mas_flags);
	vars->mas_flags = NULL;	
}
