/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:46:29 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 16:49:31 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void			ft_echo(char **line, t_vars *vars)//команда echo 
{
	int i;
	char *path;
	
	i = 1;
	path = NULL;
	while(line[i] != NULL)
	{
		ft_putstr_fd(line[i], 1);
		i++;
		if(line[i] != NULL)
			write(1, " ", 1);			
	}
	write(1, "\n", 1);
	g_error = 0;
}
