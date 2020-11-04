/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/04 18:53:24 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_cd(char **comand_line, t_vars *vars)
{
	char *path;
	
	path = NULL;
	if(comand_line[0 + 1] != NULL)
	{
		path = comand_line[1];  
		chdir(path);
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
// течь может init_patch и нужно зафришить возрат этой функции
