/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_substitution.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:49:39 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 16:24:17 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char **environment_variable_substitution(char **comand_line, t_vars *vars)
{
	char *ptr = NULL;
	char *env_var = NULL;
	char *ptr2 = NULL;
	char *ptr_for_free = NULL;
	char *ptr_for_free2 = NULL;
	int i;
	int j;
	int flag;
	int k;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	while(comand_line[i] != NULL)
	{
		while (comand_line[i][j] != '\0')
		{
			if (comand_line[i][j] == '"')
			{
				if (flag == 0 && comand_line[i][j] == '"')
					flag = 2;
				else if (flag == 2 && comand_line[i][j] == '"')
					flag = 0;
			}
			if (comand_line[i][j] == '\'' && flag != 2)
			{
				if (flag == 0 && comand_line[i][j] == '\'')
					flag = 1;
				else if (flag == 1 && comand_line[i][j] == '\'')
					flag = 0;
			}
			if (comand_line[i][j] == '$' && flag != 1)
			{
				k = j;
				while((comand_line[i][j + 1] != ' ') && comand_line[i][j] != '\0' && (ft_isalpha(comand_line[i][j + 1]) || ft_isdigit(comand_line[i][j + 1])) == 1)
				{
					j++;
				}
				if (comand_line[i][j + 1] == '?' && comand_line[i][j] != '\0')
					j++;
				if (j - k >= 1)
				{
					ptr = ft_substr(comand_line[i], 0, k);
					env_var = ft_substr(comand_line[i], k + 1, j - k);
					ptr2 = ft_substr(comand_line[i], j, 100);
					ptr_for_free = ptr;
					if (ft_strncmp(env_var, "?", 2) == 0)
					{
						ptr_for_free2 = ft_itoa(g_error);
						ptr = ft_strjoin(ptr, ptr_for_free2);
						ptr_free(&ptr_for_free2);
					}
					else
					{	
						ptr_for_free2 = init_patch(vars, env_var);
						ptr = ft_strjoin(ptr, ptr_for_free2);
						ptr_free(&ptr_for_free2);
					}
					ptr_free(&ptr_for_free);
					ptr_for_free = ptr;	
					ptr = ft_strjoin(ptr, &ptr2[1]);
					ptr_free(&ptr_for_free);
					ptr_free(&comand_line[i]);
					comand_line[i] = ptr;
					ptr_free(&env_var);
					ptr_free(&ptr2);
					i = 0;
				}
				else
				{
					j++;
				}
			}
			else
				j++;	
		}
		i++;
		j = 0;
	}
	i = 0;
	int *mas_flags;
	while(comand_line[i] != NULL)
	{
		i++;
	}
	if (vars->mas_flags == NULL)
	{
		vars->mas_flags = malloc(sizeof(int) * (i + 1));
		i = 0;
		while (comand_line[i] != NULL)
		{
			if(comand_line[i][0] == '"' || comand_line[i][0] == '\'')
				vars->mas_flags[i] = 1;
			else
				vars->mas_flags[i] = 0;
			ptr_for_free2 = comand_line[i];	
			comand_line[i] = delete_quotes(comand_line[i]);
			ptr_free(&ptr_for_free2);
			i++;
		}
		vars->mas_flags[i] = 2;
	}
	return comand_line;
}