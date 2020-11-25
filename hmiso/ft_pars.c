/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:05:28 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 13:05:49 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**ft_pars(char *line, t_vars *vars)
{
	int i;
	int j;
	int count;
	char **comand_line;
	int flag = 0;

	count = 0;
	i = 0;
	j = 0;
	comand_line = count_comands(line);
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			j = i;
			while((line[i] != ' ' || flag == 1 || flag == 2) && line[i] != '\0')
			{
				if(line[i] == '"' || line[i] == '\'')
				{
					if (flag == 0 && line[i] == '"')
						flag = 1;
					else if (flag == 1 && line[i] == '"')
						flag = 0;
					else if (flag == 0 && line[i] == '\'')
						flag = 2;
					else if (flag == 2 && line[i] == '\'')
						flag = 0;		
				}
				i++;
			}
			comand_line[count] = ft_substr(line, j, i - j);
			count++;
		}
		else
			i++;
	}
	comand_line[count] = NULL;
	environment_variable_substitution(comand_line, vars);
	return (comand_line);
}
