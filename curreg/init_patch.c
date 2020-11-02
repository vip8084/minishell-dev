/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:33:34 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 13:40:17 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char		*init_patch(t_vars *vars, char *arg) // возвращает значение переменной env
{
	char **ptr;
	int i;
	int len_arg;
	char *value;

	i = 0;
	len_arg = ft_strlen(arg);
	value = ft_strdup("");
	while (vars->envp_copy[i] != NULL)
	{
		ptr = ft_split(vars->envp_copy[i], '=');
		if (ft_strncmp(ptr[0], arg, len_arg) == 0)
		{
			free(value);
			value = ft_strdup(ptr[1]);
		}
		free(ptr[0]);
		free(ptr[1]);
		free(ptr);
		ptr = NULL;
		i++;
	}
	return (value);
}
//протести