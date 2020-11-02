/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:07:05 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 11:18:06 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_cd(char **comand_line, t_vars *vars)
{
	if(comand_line[0 + 1] != NULL)
	{
		chdir(comand_line[1]);
	}
	else
	{
		chdir(init_patch(vars, "HOME"));
	}
}

//избавиться от утечек
//настроить возврат сообщения о не правильной директории
//корректно установить код ошибки
//проверить возрат баша на папку к которой нет прав в том числе код ошибки
//проверка кода возврата в баше echo $?
// течь может init_patch и нужно зафришить возрат этой функции