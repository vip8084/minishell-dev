/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:59:20 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 13:14:06 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char		**check_duplicate(char **argv) // проверка на наличие добавляемой переменной в переменных среды
{
	int i = 0;
	int j = 1;
	int count = 0;
	int count_2 = 0;
	int count_3 = 0;
	char **new_argv;
	while(argv[count_3] != NULL)
	{
		count_3++;
	}
	if (count_2 == 1)
		return argv;
	i = 0;
	count_2 = 0;
	while(argv[i] != NULL)
	{
		while(j < count_3)
		{
			if(argv[i] != NULL && argv[j] != NULL &&ft_strlen(argv[i]) == ft_strlen(argv[j]))
			{
				if(ft_strncmp(argv[i], argv[j], ft_strlen(argv[i])) == 0)
				{
					count++;
				}
			}
			j++;
		}
		if(count > 1)
		{
			argv[i] = NULL;
			count_2++;
		}
		count=0;
		i++;
		j = 0;
	}
	new_argv = malloc(sizeof(char*) *(i - count_2 + 1));
	count = 0;
	j = 0;
	while(count < i)
	{
		if(argv[count] != NULL)
		{
			new_argv[j] = ft_strdup(argv[count]);
			free(argv[count]);
			j++;
		}
		count++;
	}
	new_argv[j] = NULL;
	return new_argv; // если есть дубли то она возвращает массив без них
}

// не корректно работает в кейсе export a=b a a a
// возможно течет
