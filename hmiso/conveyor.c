/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:27:08 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/03 21:20:33 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**make_comand_mas(char **comand_line, int i, int j)
{
	int k;
	int count = 0;
	char **comand_whis_flags;

	k = i - j; //смещение до пайпа или редиректа
	comand_whis_flags = malloc(sizeof(char *) * (j + 1));
	while (k < i)
	{
		comand_whis_flags[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	comand_whis_flags[count] = NULL;	
	return comand_whis_flags;
}

void	ft_conveyor(char *line, char **comand_line, t_vars *vars)
{
	char **line_pipe;
	char *comand_path;
	int i;
	int j;
	int k;

	j = 1;
	i = 0;
	k = 0;
	//line_pipe = ft_split(line, '|');

	while (comand_line[i] != NULL)
	{
		char **com_whis_flags;
		// if (vars->count_pipe - i > 0)
		// {
		// 	comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
		// 	comand_line = ft_split(line_pipe[i], ' ');
		// 	comand_path = ft_strjoin(comand_path, "/");
		// 	comand_path = ft_strjoin(comand_path, comand_line[0]);
		// 	ft_pipe(comand_path, comand_line, vars);
		// 	i++;
		// }
		// else if(vars->count_redirect > 0)
		// {
		// 	line = ft_strdup(line_pipe[i]);
		// 	ft_conveyor_test(line, &line_pipe[i], vars);
		// 	i++;
		// }		
		// else
		// {
		// 	if(!(checking_recoded_functions(&line_pipe[i], vars)))			
		// 	{
		// 		comand_line = ft_split(line_pipe[i], ' ');
		// 		comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
		// 		comand_path = ft_strjoin(comand_path, "/");
		// 		comand_path = ft_strjoin(comand_path, comand_line[0]);
		// 		system_funk(comand_path, comand_line, vars);
		// 	}
		// 	i++;
		// }
		if ((ft_strncmp(comand_line[i], "|", 1) == 0) || (ft_strncmp(comand_line[i], ">", 1) == 0) || comand_line[i + 1] == NULL)
		{
			if (ft_strncmp(comand_line[i], "|", 1) == 0)
			{
				while(i - j != 0)
				{
					if ((ft_strncmp(comand_line[i - j], "|", 1) == 0) || (ft_strncmp(comand_line[i - j], ">", 1) == 0))
						break;
					j++;
				}
				com_whis_flags = make_comand_mas(comand_line, i, j);
				comand_path = check_system_funk(vars, &com_whis_flags[0]);
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
				ft_pipe(comand_path, com_whis_flags, vars);
				i++;
				j = 0;
			}
			else
			{
				com_whis_flags = make_comand_mas(comand_line, i, j);
				if(!(checking_recoded_functions(&com_whis_flags[0], vars)))			
				{
					comand_path = check_system_funk(vars,  &com_whis_flags[0]);
					comand_path = ft_strjoin(comand_path, "/");
					comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
					system_funk(comand_path, comand_line, vars);
				}
			}
		}
		i++;
	}
	dup2(vars->save_std_in, 0);
	dup2(vars->save_std_out, 1);	
}