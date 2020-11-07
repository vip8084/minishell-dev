/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/07 17:12:24 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void show_cd_err(char *cmd, char* arg, int err)
{
	ft_putstr_fd("minishell>", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(arg, 1);
	if (err == 2)
		ft_putstr_fd(": No such file or directory\n", 1);
	else if (err == 20)
		ft_putstr_fd(": Not a directory\n", 1);
}

void		ft_cd(char **comand_line, t_vars *vars)
{
	int		status;
	char	*path;
	
	path = NULL;
	errno = 0;
	if(comand_line[0 + 1] != NULL)
	{
		path = comand_line[1];
		if (chdir(path) == -1)
		{
			set_g_error(errno);
			show_cd_err(comand_line[0], comand_line[1], errno);
		}
		free_two_dimensional_array(comand_line);
		path = NULL;      
	}
	else
	{
		path = init_patch(vars, "HOME");
		chdir(path);
		free_two_dimensional_array(comand_line);
		free(path);
		path = NULL;
	}
}

//проверить возрат баша на папку к которой нет прав в том числе код ошибки
