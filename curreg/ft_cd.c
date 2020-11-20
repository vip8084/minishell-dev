/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/20 18:23:42 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

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
			vars->cd_flag = 1;
			vars->err_flag = 0;
			cd_error(comand_line[0], comand_line[1], strerror(errno));
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
