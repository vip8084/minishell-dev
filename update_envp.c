/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:38:30 by hmiso             #+#    #+#             */
/*   Updated: 2020/10/14 12:38:52 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	update_envp(char **str, t_vars *vars)
{
	int i = 0;
	int j = 0;
	char **new_envp;
	char **ar_1;
	char **ar_2;
	int count = 0;
	int flag = 0;
	char *ptr;
	while(str[i] != NULL)
	{
		i++;
	}
	while(j < i)
	{
		ar_2 = ft_split(str[j], '=');
		while (vars->envp_copy[count] != NULL)
		{
			ar_1 = ft_split(vars->envp_copy[count], '=');
			if(ft_strlen(ar_1[0])  == ft_strlen(ar_2[0]))
			{
				if(ft_strncmp(ar_1[0],ar_2[0], ft_strlen(ar_1[0])) == 0)
				{
					if(ar_2[1] != NULL)
					{
						free(vars->envp_copy[count]);
						vars->envp_copy[count]=ft_strjoin(ar_2[0], "=");
						ptr = vars->envp_copy[count];
						vars->envp_copy[count]=ft_strjoin(vars->envp_copy[count], ar_2[1]);
						free(ptr);
					}
					free(str[j]);
					str[j] = NULL;
				}
			}
			free_two_dimensional_array(ar_1);
			count++;
		}
		free_two_dimensional_array(ar_2);
		count = 0;
		j++;
	}
	count = i;
	i = 0;
	while (flag < count)
	{
		if(str[flag] != NULL)
			i++;
		flag++;
	}
	j = 0;
	while(vars->envp_copy[j] != NULL)
	{
		j++;
	}
	new_envp = malloc(sizeof(char *) *(j + i + 1));
	j = 0;
	i = 0;
	while(vars->envp_copy[i] != NULL)
	{
		new_envp[i] = vars->envp_copy[i];
		i++;
	}
	while(j < count)
	{
		if(str[j] != NULL)
		{
			new_envp[i] = str[j];
			i++;
		}
		j++;
	}
	new_envp[i] = NULL;
	free(vars->envp_copy);
	envp_copy(new_envp, vars);
	free_two_dimensional_array(new_envp);
}