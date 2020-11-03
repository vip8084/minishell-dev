/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:46:29 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/03 19:01:44 by curreg           ###   ########.fr       */
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
		if (line[i][0] == '$')
		{
			path = init_patch(vars, &line[i][1]);
			ft_putstr_fd(path, 1);
			free(path);
			path = NULL;
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);
		}
		else
		{
			ft_putstr_fd(line[i], 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);			
		}
	}
	free_two_dimensional_array(line);
	write(1, "\n", 1);
}

// не правильно работает с вызовом в несколько аргументов
// парсинг экранирования кавычек и всего еже с ним
