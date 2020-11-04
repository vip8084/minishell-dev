/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/04 19:47:41 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void show_dir_err(char *cmd, char* arg)
{
	ft_putstr_fd("minishell>", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
}

void		ft_cd(char **comand_line, t_vars *vars)
{
	char	*path;
	int		status;
	
	path = NULL;
	status = 0;
	if(comand_line[0 + 1] != NULL)
	{
		path = comand_line[1];  
		status = chdir(path);
		if(status == -1)
			show_dir_err(comand_line[0], comand_line[1]);
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

//настроить возврат сообщения о не правильной директории
//корректно установить код ошибки
//проверить возрат баша на папку к которой нет прав в том числе код ошибки
//проверка кода возврата в баше echo $?
