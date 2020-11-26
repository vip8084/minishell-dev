/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:27:08 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 19:30:28 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	ft_conveyor(char *line, char **comand_line, t_vars *vars)
{
	char **line_pipe;
	char *comand_path;
	char **com_whis_flags;
	char **mas_redirektion;
	char **mas_redirektion2;
	int i;
	int j;
	int k;
	int fd;

	j = 1;
	i = 0;
	k = 0;
	int t = 0;
	int flag = 0;
	int flag_pipe = 0;

	create_file(comand_line, vars->mas_flags);
	i = 0;
	while(comand_line[i] != NULL)
	{
		if (i != 0 && ((ft_strncmp(comand_line[i], "|", 2) == 0) && vars->flag_redirect == 1)  && vars->mas_flags[i] != 1)
		{		
			ft_pipe_eof();
			create_file(&comand_line[i], &vars->mas_flags[i]);
			vars->flag_redirect = 0;
			flag_pipe = 1;
			i++;
		}
		if ((ft_strncmp(comand_line[i], "|", 2) == 0) && vars->flag_redirect == 0 && vars->mas_flags[i] != 1)
		{
			create_file(&comand_line[i], &vars->mas_flags[i]);
			com_whis_flags = make_comand_mas_start(comand_line, i, (j - 1));
			comand_path = ft_join_path(vars, com_whis_flags);
			ft_pipe(comand_path, com_whis_flags, vars);	
			j = 0;
			vars->flag_redirect = 0;
			flag_pipe = 1;
			free_two_dimensional_array(com_whis_flags);
			free(comand_path);
		}
		else if (((ft_strncmp(comand_line[i], ">", 2) == 0) || (ft_strncmp(comand_line[i], ">>", 3) == 0)) && vars->mas_flags[i] != 1)
		{
			com_whis_flags = make_comand_mas_start(comand_line, i, (j - 1));
			if (com_whis_flags[0] != NULL)
			{
				comand_path = ft_join_path(vars, com_whis_flags);
				while(comand_line[i + 1] != NULL)
				{
					if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
					{
						break;
					}
					i++;
					k++;
				}
				mas_redirektion = make_list_rederection(comand_line, i, k, vars);
				ft_redirects(comand_path, com_whis_flags, mas_redirektion, vars);
				j = 0;
				k = 0;
				vars->flag_redirect = 1;
				flag_pipe = 0;			
				if(mas_redirektion[0] != NULL)
					i--;
				free_two_dimensional_array(com_whis_flags);
				ptr_free(&comand_path);
				free_two_dimensional_array(mas_redirektion);
			}
			else
			{
				while(comand_line[i + 1] != NULL)
				{
					if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
					{
						break;
					}
					i++;
					k++;
				}
				k = 0;
				vars->flag_redirect = 1;
				flag_pipe = 0;
				i--;
			}
		}
		else if ((ft_strncmp(comand_line[i], "<", 2) == 0) && vars->mas_flags[i] != 1)
		{
			com_whis_flags = make_comand_mas_start(comand_line, i, (j - 1));
			if(com_whis_flags[0] != NULL)
			{
				comand_path = ft_join_path(vars, com_whis_flags);
				while(comand_line[i + 1] != NULL)
				{
					if ((ft_strncmp(comand_line[i], "|", 2) == 0 || ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] != 1)
					{
						if ((ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] == 0)
							flag = 2;
						else 
							flag = 1;
						break;
					}
					i++;
					k++;
				}
				mas_redirektion = make_list_rederection_revers(comand_line, i, k, vars);
				if (flag == 0)
				{
					ft_redirects_revers(comand_path, com_whis_flags, mas_redirektion, vars);
					flag_pipe = 1;
				}
				if (flag == 1)
				{
					ft_redirects_pipe(comand_path, com_whis_flags, mas_redirektion, vars);
					flag_pipe = 1;
				}
				if (flag == 2)
				{
					j = 0;
					k = 0;
					while(comand_line[i + 1] != NULL)
					{
						if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
						{
							break;
						}
						i++;
						k++;
					}
					mas_redirektion2 = make_list_rederection(comand_line, i, j, vars);
					ft_redirects_redirect(comand_path, com_whis_flags, mas_redirektion, mas_redirektion2, vars);
					//i++;
					flag_pipe = 0;
					free_two_dimensional_array(mas_redirektion2);
				}	
				j = 0;
				k = 0;
				flag = 0;
				free_two_dimensional_array(com_whis_flags);
				ptr_free(&comand_path);
				free_two_dimensional_array(mas_redirektion);
			}
			else
			{
				while(comand_line[i + 1] != NULL)
				{
					if ((ft_strncmp(comand_line[i], "|", 2) == 0 || ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] != 1)
					{
						if ((ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] == 0)
							flag = 2;
						else 
							flag = 1;
						break;
					}
					i++;
					k++;
				}
				mas_redirektion = make_list_rederection_revers(comand_line, i, k, vars);
				if (flag == 0)
				{
					flag_pipe = 1;
				}
				if (flag == 1)
				{
					flag_pipe = 1;
				}
				if (flag == 2)
				{
					j = 0;
					k = 0;
					while(comand_line[i + 1] != NULL)
					{
						if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
						{
							break;
						}
						i++;
						k++;
					}
					mas_redirektion2 = make_list_rederection(comand_line, i, j, vars);
					flag_pipe = 0;
					free_two_dimensional_array(mas_redirektion2);
				}	
				j = 0;
				k = 0;
				flag = 0;
				free_two_dimensional_array(mas_redirektion);
			}
		}
		else if (comand_line[i + 1] == NULL && flag_pipe == 1)
		{
			com_whis_flags = make_comand_mas_start(comand_line, i + 1, j);
			comand_path = ft_join_path(vars, com_whis_flags);
			system_funk(comand_path, com_whis_flags, vars);
			j = 0;
			vars->flag_redirect = 0;
			free_two_dimensional_array(com_whis_flags);
			ptr_free(&comand_path);			
		}
		j++;
		i++;
	}
	vars->count_pipe = 0;
	vars->count_redirect = 0;
	vars->flag_redirect = 0;
	dup2(vars->save_std_in, 0);
	dup2(vars->save_std_out, 1);
}