/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/04 21:30:08 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void show_cd_err(char *cmd, char* arg, char *type)
{
	if ((ft_strcmp(type, "dir")) == 0)
	{
		ft_putstr_fd("minishell>", 1);
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else if ((ft_strcmp(type, "file")) == 0)
	{
		ft_putstr_fd("minishell>", 1);
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(": Not a directory\n", 1);
	}

	// ft_putstr_fd("minishell>", 1);
	// ft_putstr_fd(cmd, 1);
	// ft_putstr_fd(": ", 1);
	// ft_putstr_fd(arg, 1);
	// if (ft_strcmp(type, "dir"))
	// 	ft_putstr_fd(": No such file or directory\n", 1);
	// else if (ft_strcmp(type, "file"))
	// 	ft_putstr_fd(": Not a directory\n", 1);
}

void		ft_cd(char **comand_line, t_vars *vars)
{
	int		status;
	char	*path;
	DIR 	*is_dir;
	
	status = 0;
	path = NULL;
	is_dir = NULL;
	if(comand_line[0 + 1] != NULL)
	{
		path = comand_line[1];
		is_dir = opendir(comand_line[1]); //////
		status = chdir(path);  /////////////////
		////////////////////////////////////////
		if (is_dir == NULL)
			show_cd_err(comand_line[0], comand_line[1], "file");
		else if (status == -1)
			show_cd_err(comand_line[0], comand_line[1], "dir");
		///////////////////////////////////////
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
