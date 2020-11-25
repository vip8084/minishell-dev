/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:06:46 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 13:07:09 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**move_arguments(char **comand_line, t_vars *vars)
{
	int i;
	int poz;
	char *ptr;
	char *ptr2;
	int flag;
	int flag2=0;

	flag = 0;
	i = 0;
	poz = 0;
	int count = 0;
	while(comand_line[i] != NULL)
	{
		i++;
	}
	while(vars->mas_flags[count] != 2)
	{
		count++;
	}
	count = count - i;
	while (comand_line[poz] != NULL)	
	{
		while (comand_line[i] != NULL)
		{
			if ((ft_strncmp(comand_line[i], ">", 2) == 0  || ft_strncmp(comand_line[i], ">>", 3) == 0 || ft_strncmp(comand_line[i], "<", 2) == 0) && vars->mas_flags[i + count] != 1)
			{
				if ((comand_line[i + 2] != NULL) && (ft_strncmp(comand_line[i + 2], "|", 2) != 0))
				{
					if ((ft_strncmp(comand_line[i + 2], ">", 2) != 0  && ft_strncmp(comand_line[i + 2], ">>", 3) != 0 && ft_strncmp(comand_line[i + 2], "<", 2) != 0))
					{
						ptr = comand_line[i]; // копируем символ редиректа в ячейку
						flag = vars->mas_flags[i + count];
						comand_line[i] = comand_line[i + 2]; // меняем редирект на флаг
						vars->mas_flags[i + count] = vars->mas_flags[i + 2];
						comand_line[i + 2] = comand_line[i + 1]; // меняем флаг на название файла
						vars->mas_flags[i + 2] = vars->mas_flags[i + 1];
						comand_line[i + 1] = ptr; // заменяем название файла на флаг
						vars->mas_flags[i + 1] = flag;
					}
				}
			}
			i++;
		}
		i = 0;
		poz++;
	}
	// exit(0);
	i = 0;
	poz = 0;
	// while(comand_line[i] != NULL)
	// {
	// 	printf("%s ", comand_line[i]);
	// 	printf("%d ", vars->mas_flags[i]);
	// 	i++;
	// }
	// exit(0);	
	while (comand_line[poz] != NULL)	
	{
		while (comand_line[i] != NULL)
		{
			if ((ft_strncmp(comand_line[i], ">", 2) == 0  || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i + count] != 1)
			{
				if ((comand_line[i + 2] != NULL) && ((ft_strncmp(comand_line[i + 2], "|", 2) != 0) && vars->mas_flags[i + 2] != 1))
				{
					if ((ft_strncmp(comand_line[i + 2], "<", 2) == 0) && vars->mas_flags[i + count] != 1)
					{
						ptr = comand_line[i]; // копируем редирект
						flag = vars->mas_flags[i + count];
						ptr2 = comand_line[i + 1]; // копируем название файла
						flag2 = vars->mas_flags[i + 1];
						comand_line[i] = comand_line[i + 2]; // меняем редиректы
						vars->mas_flags[i + count] = vars->mas_flags[i + 2];
						comand_line[i + 1] = comand_line[i + 3]; //меняем названия файлов
						vars->mas_flags[i + 1] = vars->mas_flags[i + 3];
						comand_line[i + 2] = ptr;
						vars->mas_flags[i + 2] = flag;
						comand_line[i + 3] = ptr2;
						vars->mas_flags[i + 3] = flag2;
					}
				}
			}
			i++;
		}
		i = 0;
		poz++;
	}
	i = 0;
	poz = 0;
	// while(comand_line[i] != NULL)
	// {
	// 	printf("%s ", comand_line[i]);
	// 	printf("%d ", vars->mas_flags[i]);
	// 	i++;
	// }
	// exit(0);
	return comand_line;
}