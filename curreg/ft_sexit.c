/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:13:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 18:22:29 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_exit(char **comand_line)
{
	int i;

	if (comand_line[1] != NULL)
	{
		if (ft_isdigit(comand_line[1][0]))
		{
			i = ft_atoi(comand_line[1]);
			exit(i);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell> exit: ", 2);
			ft_putstr_fd(comand_line[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	else
	{
		exit(0);
	}
}
// менеджмент ошибок в дочерних процесссах хотя по идеее должно быть норм