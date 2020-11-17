/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_system_funk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:41:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/17 11:41:39 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char 			*check_system_funk(t_vars *vars, char **str) // проверяет наличие испалняеомего файла по путям PATH
{
	DIR *dir;
    struct dirent *st;
	char **path;
	char **arg;
	int i = 0;
	int flag = 0;

	path = ft_split(init_patch(vars, "PATH"), ':');
	arg = str;
	char **argv = str;
	while(str[0][i] != '\0')
	{
		str[0][i] = ft_tolower(str[0][i]);
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
			if (ft_strlen(st->d_name) == ft_strlen(argv[0]))
			{
				if ((ft_strncmp(st->d_name, str[0], ft_strlen(argv[0]))) == 0)
				{
					char **str2= str;
					return(path[i]);
					flag = 1;
				}
			}
		}
		i++;
	}
	return (NULL);
}