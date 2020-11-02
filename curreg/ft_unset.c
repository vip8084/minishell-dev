/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:02:21 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 13:05:45 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_unset(t_vars *vars, char *str)//удаление переменной из переменных окружения команда unset 
{
	int count = 0;
	int count_env = 0;
	char **env_new;
	char **argv;
	int	 i = 0;
	int j = 0;
	int	 flag= 0;
	while(vars->envp_copy[count_env] != NULL)
		count_env++;
	while (vars->envp_copy[count] != NULL)
	{
		argv = ft_split(vars->envp_copy[count], '=');
		if(ft_strlen(argv[0]) == ft_strlen(str))
		{
			if(ft_strncmp(argv[0], str, ft_strlen(argv[0])) == 0)
			{
				free(vars->envp_copy[count]);
				vars->envp_copy[count]=NULL;
				flag++;
			}
		}
		count++;
	}
	count = 0;
	i = 0;
	if(flag > 0)
	{
		env_new = malloc(sizeof(char**) * count_env);
		while(i < count_env)
		{
			if(vars->envp_copy[i] != NULL)
			{
				env_new[j] = ft_strdup(vars->envp_copy[i]);
				j++;
			}
			i++;
		}
		vars->envp_copy = env_new;
	}
}
// течет
// протести плиз