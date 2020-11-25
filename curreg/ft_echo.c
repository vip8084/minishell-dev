/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:46:29 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 20:26:44 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishel.h"

// void			ft_echo(char **line, t_vars *vars)
// {
// 	int i;
// 	char *path;
	
// 	i = 1;
// 	path = NULL;
// 	while(line[i] != NULL)
// 	{
// 		if (line[i][0] == '$')
// 		{
// 			if(line[i][1] == '?')
// 			{
// 				show_g_error();
// 				vars->err_flag = 0;
// 				vars->cd_flag = 0;
// 			}
// 			path = init_patch(vars, &line[i][1]);
// 			ft_putstr_fd(path, 1);
// 			free(path);
// 			path = NULL;
// 			i++;
// 			if(line[i] != NULL)
// 				write(1, " ", 1);
// 		}
// 		else
// 		{
// 		// if (line[i][0] == '$')
// 		// {
// 		// 	path = init_patch(vars, &line[i][1]);
// 		// 	ft_putstr_fd(path, 1);
// 		// 	free(path);
// 		// 	path = NULL;
// 		// 	i++;
// 		// 	if(line[i] != NULL)
// 		// 		write(1, " ", 1);
// 		// }
// 		// else
// 		// {
// 			ft_putstr_fd(line[i], 1);
// 			i++;
// 			if(line[i] != NULL)
// 				write(1, " ", 1);			
// 		// }
// 	}
// 	free_two_dimensional_array(line);
// 	write(1, "\n", 1);
// }

// не правильно работает с вызовом в несколько аргументов
// парсинг экранирования кавычек и всего еже с ним


void			ft_echo(char **line, t_vars *vars)//команда echo 
{
	int i;
	char *path;
	
	i = 1;
	path = NULL;
	while(line[i] != NULL)
	{
		// if (line[i][0] == '$')
		// {
		// 	path = init_patch(vars, &line[i][1]);
		// 	ft_putstr_fd(path, 1);
		// 	free(path);
		// 	path = NULL;
		// 	i++;
		// 	if(line[i] != NULL)
		// 		write(1, " ", 1);
		// }
		// else
		// {
			ft_putstr_fd(line[i], 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);			
		// }
	}
	write(1, "\n", 1);
	g_error = 0;
}

// не правильно работает с вызовом в несколько аргументов
// парсинг экранирования кавычек и всего еже с ним