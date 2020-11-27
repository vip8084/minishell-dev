/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/27 20:25:50 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_cd(char **comand_line, t_vars *vars)
{
	int		status;
	char	*path;
	// char	*pwd[2];
	// char	*ptr;

	path = NULL;
	errno = 0;
	// pwd[0] = "OLDPWD=";
	// ptr = getcwd(NULL,0);
	// pwd[0] = ft_strjoin(pwd[0], ptr);
	// pwd[1] = NULL;
	// free(ptr);
	if(comand_line[0 + 1] != NULL)
	{
		//update_envp(pwd, vars);
		set_pwd("OLDPWD", vars);
		path = comand_line[1];
		if (chdir(path) == -1)
		{
			set_g_error(errno);
			vars->cd_flag = 1;
			vars->err_flag = 0;
			cd_error(comand_line[0], comand_line[1], strerror(errno));
		}
		path = NULL;
	}
	else
	{
		path = init_patch(vars, "HOME");
		chdir(path);
		free(path);
		path = NULL;
	}
}
