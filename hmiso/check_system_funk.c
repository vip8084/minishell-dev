/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_system_funk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:41:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/24 21:03:07 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char 			*check_system_funk(t_vars *vars, char *str) // проверяет наличие испалняеомего файла по путям PATH
{
	DIR *dir;
    struct dirent *st;
	char **path;

	char *ptr;
	int i = 0;
	int flag = 0;

	ptr = init_patch(vars, "PATH");
	path = ft_split(ptr, ':');
	free(ptr);

	while(str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	i = 0;
	while(path[i] != NULL)
	{
		if ((dir = opendir(path[i])) == NULL)
		{
			i++;
			continue;
		}
		while((st = readdir(dir)) != NULL)
		{
			if (ft_strlen(st->d_name) == ft_strlen(str))
			{
				if ((ft_strncmp(st->d_name, str, ft_strlen(str))) == 0)
				{
					ptr = ft_strdup(path[i]);
					free_two_dimensional_array(path);
					closedir(dir);
					return(ptr);
				}
			}
		}
		closedir(dir);
		i++;
	}
	free_two_dimensional_array(path);
	return (NULL);
}