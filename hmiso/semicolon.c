/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:32:57 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/26 14:06:32 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char **semicolon(char *line)
{
	int i;
	int flag;
	int j;
	int count;
	char **argv;
	char *ptr_free;
	
	i = 0;
	j = 0;
	flag = 0;
	count = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0 && line[i + 1] != '\0')
		{
			flag = 1;
			i++;
		}
		else if ((line[i] == '\'' || line[i] == '"') && flag == 1 && line[i + 1] != '\0')
		{
			flag = 0;
			i++;
		}		
		else if (flag == 0 && line[i] == ';')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	argv = malloc(sizeof(char*) * (count + 2));
	i = 0;
	count = 0;
	flag = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0)
		{
			flag = 1;
		}
		else if((line[i] == '\'' || line[i] == '"') && flag == 1)
		{
			flag = 0;
		}
		if (flag == 0 && line[i] == ';')
		{
			argv[count] = ft_substr(line, 0, i);
			line = &line[i + 1];
			count++;
			i = 0;
			continue;
		}
		if (line[i] != '\0' && line[i + 1] == '\0')
		{
			argv[count] = ft_substr(line, 0, i + 1);
			count++;
		}
		i++;
	}
	argv[count] = NULL;
	count = 0;
	return(argv);
}