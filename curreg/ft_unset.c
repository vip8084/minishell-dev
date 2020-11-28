/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:02:21 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 21:24:16 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_unset(t_vars *vars, char **str)
{
	int		count;
	int		count_env;
	char	**env_new;
	char	**argv;
	int		i;
	int		j;
	int		m;
	int		flag;

	count = 0;
	count_env = 0;
	i = 0;
	j = 0;
	m = 0;
	flag = 0;
	while (vars->envp_copy[count_env] != NULL)
		count_env++;
	while (str[j] != NULL)
		j++;
	while (m < j)
	{
		while (count < count_env)
		{
			argv = ft_split(vars->envp_copy[count], '=');
			if (argv != NULL && (ft_strlen(argv[0]) == ft_strlen(str[m])))
			{
				if (ft_strncmp(argv[0], str[m], ft_strlen(argv[0])) == 0)
				{
					free(vars->envp_copy[count]);
					vars->envp_copy[count] = NULL;
					flag++;
					free_two_dimensional_array(argv);
					count = 0;
					break ;
				}
			}
			free_two_dimensional_array(argv);
			count++;
		}
		m++;
		count = 0;
	}
	j = 0;
	count = 0;
	i = 0;
	if (flag > 0)
	{
		env_new = malloc(sizeof(char**) * (count_env));
		while (i < count_env)
		{
			if (vars->envp_copy[i] != NULL)
			{
				env_new[j] = ft_strdup(vars->envp_copy[i]);
				j++;
			}
			i++;
		}
		env_new[j] = NULL;
		i = 0;
		while (i < count_env)
		{
			if (vars->envp_copy[i] != NULL)
			{
				free(vars->envp_copy[i]);
			}
			i++;
		}
		free(vars->envp_copy);
		envp_copy(env_new, vars);
		free_two_dimensional_array(env_new);
	}
}
