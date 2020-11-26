/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_rederection_revers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:26:46 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 19:27:24 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**make_list_rederection_revers(char **comand_line, int i, int j, t_vars *vars)
{
	int count;
	int k;
	char **mas;

	count = 0;
	k = i - j;
	while(k <= i && (ft_strncmp(comand_line[k], "|", 2) != 0 || vars->mas_flags[k] == 1) && (ft_strncmp(comand_line[k], ">", 2) != 0 || vars->mas_flags[k] == 1) && ((ft_strncmp(comand_line[k], ">>", 3) != 0) || vars->mas_flags[k] == 1))
	{
		if ((ft_strncmp(comand_line[k], "<", 2) == 0) && vars->mas_flags[k] == 0)
		{
			if ((ft_strncmp(comand_line[k - 1], "<", 2) != 0 && vars->mas_flags[k - 1] == 0))
			{
				k++;
				continue;
			}
		}
		k++;
		count++;
	}
	mas = malloc(sizeof(char *) * (count + 1));
	k = i - j;
	count = 0;
	while(k <= i&& (ft_strncmp(comand_line[k], "|", 2) != 0 || vars->mas_flags[k] == 1) && (ft_strncmp(comand_line[k], ">", 2) != 0 || vars->mas_flags[k] == 1) && ((ft_strncmp(comand_line[k], ">>", 3) != 0) || vars->mas_flags[k] == 1))
	{
		if ((ft_strncmp(comand_line[k], "<", 2) == 0) && vars->mas_flags[k] == 0)
		{
			if ((ft_strncmp(comand_line[k - 1], "<", 2) != 0 ) && vars->mas_flags[k - 1] == 0)
			{
				k++;
				continue;
			}
		}
		mas[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	mas[count] = NULL;
	return mas;
}