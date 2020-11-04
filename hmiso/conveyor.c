/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:27:08 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/04 18:57:21 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**make_comand_mas_start(char **comand_line, int i, int j)
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

char	**make_list_rederection(char **comand_line, int i, int j)
{
	int count;
	int k;
	char **mas;

	count = 0;
	k = i - j;
	while(k <= i)
	{
		if((ft_strncmp(comand_line[k], ">", 1) == 0 )|| (ft_strncmp(comand_line[k - 1], ">", 1) != 0 ))
		{
			k++;
			continue;
		}
		k++;
		count++;
	}
	mas = malloc(sizeof(char *) * (count + 1));
	k = i - j;
	count = 0;
	while(k <= i)
	{
		if((ft_strncmp(comand_line[k], ">", 1) == 0 )|| (ft_strncmp(comand_line[k - 1], ">", 1) != 0 ))
		{
			k++;
			continue;
		}
		mas[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	return mas;
}

char	**make_comand_mas_end(char **comand_line, int i, int j)
{
	int k;
	int count = 0;
	char **comand_whis_flags;

	k = i - j; //смещение до пайпа или редиректа
	comand_whis_flags = malloc(sizeof(char *) * (j + 1));
	while (k < i)
	{
		comand_whis_flags[count] = ft_strdup(comand_line[k + 1]);
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
	char **com_whis_flags;
	char **mas_redirektion;
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	//line_pipe = ft_split(line, '|');

	while (comand_line[i] != NULL)
	{
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
			k = i - 1;
			if (ft_strncmp(comand_line[i], "|", 1) == 0)
			{
				while((i - j) != 0)
				{
					if ((ft_strncmp(comand_line[k - j], "|", 1) == 0) || (ft_strncmp(comand_line[k - j], ">", 1) == 0))
						break; 
					j++;
				}
				com_whis_flags = make_comand_mas_end(comand_line, k, j);
				comand_path = check_system_funk(vars, &com_whis_flags[0]);
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
				ft_pipe(comand_path, com_whis_flags, vars);
				j = 0;
			}
			else if(ft_strncmp(comand_line[i], ">", 1) == 0)
			{
				while((i - j) != 0)
				{
					if ((ft_strncmp(comand_line[k - j], "|", 1) == 0) || (ft_strncmp(comand_line[k - j], ">", 1) == 0))
						break;
					j++;
				}
				com_whis_flags = make_comand_mas_end(comand_line, k, j);
				j = 0;
				while(comand_line[i + 1] != NULL || (ft_strncmp(comand_line[i], "|", 1) == 0))
				{
					i++;
					j++;
				}
				mas_redirektion = make_list_rederection(comand_line, i, j);
				comand_path = check_system_funk(vars, &com_whis_flags[0]);
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
				ft_redirects(comand_path, com_whis_flags, mas_redirektion, vars);
			}
			else
			{
				while(i - j != 0)
				{
					if ((ft_strncmp(comand_line[i - j], "|", 1) == 0) || (ft_strncmp(comand_line[i - j], ">", 1) == 0))
						break;
					j++;
				}				
				com_whis_flags = make_comand_mas_end(comand_line, i, j);
				if(!(checking_recoded_functions(&com_whis_flags[0], vars)))			
				{
					comand_path = check_system_funk(vars,  &com_whis_flags[0]);
					comand_path = ft_strjoin(comand_path, "/");
					comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
					system_funk(comand_path, com_whis_flags, vars);
				}
				j = 0;
			}
		}
		i++;
	}
	dup2(vars->save_std_in, 0);
	dup2(vars->save_std_out, 1);	
}