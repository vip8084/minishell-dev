/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_system_funk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:41:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/27 14:08:13 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		init_sys_fink(t_sys_funk *sys_funk, t_vars *vars, char *str)
{
	sys_funk->path = NULL;
	sys_funk->ptr = NULL;
	sys_funk->i = 0;
	sys_funk->flag = 0;
	sys_funk->ptr = init_patch(vars, "PATH");
	sys_funk->path = ft_split(sys_funk->ptr, ':');
	free(sys_funk->ptr);
	while (str[sys_funk->i] != '\0')
	{
		str[sys_funk->i] = ft_tolower(str[sys_funk->i]);
		sys_funk->i++;
	}
	sys_funk->i = 0;
}

char			*check_system_funk(t_vars *vars, char *str)
{
	t_sys_funk sys_funk;

	init_sys_fink(&sys_funk, vars, str);
	while (sys_funk.path[sys_funk.i] != NULL)
	{
		if ((sys_funk.dir = opendir(sys_funk.path[sys_funk.i])) == NULL)
		{
			sys_funk.i++;
			continue;
		}
		while ((sys_funk.st = readdir(sys_funk.dir)) != NULL)
			if (ft_strlen(sys_funk.st->d_name) == ft_strlen(str))
				if ((ft_strncmp(sys_funk.st->d_name, str, ft_strlen(str))) == 0)
				{
					sys_funk.ptr = ft_strdup(sys_funk.path[sys_funk.i]);
					free_two_dimensional_array(sys_funk.path);
					closedir(sys_funk.dir);
					return (sys_funk.ptr);
				}
		closedir(sys_funk.dir);
		sys_funk.i++;
	}
	free_two_dimensional_array(sys_funk.path);
	return (NULL);
}
