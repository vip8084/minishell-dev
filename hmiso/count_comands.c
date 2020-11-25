/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_comands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:03:47 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 13:03:59 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char **count_comands(char *line)
{
	int i;
	int count;
	char **comand_line;
	int flag = 0;

	comand_line = NULL;
	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			count++;
			while((line[i] != ' ' || flag == 1 || flag == 2) && line[i] != '\0')
			{
				if(line[i] == '"' || line[i] == '\'')
				{
					if (flag == 0 && line[i] == '"')
						flag = 1;
					else if (flag == 1 && line[i] == '"')
						flag = 0;
					else if (flag == 0 && line[i] == '\'')
						flag = 2;
					else if (flag == 2 && line[i] == '\'')
						flag = 0;		
				}
				i++;
			}
		}
		else
		{
			i++;
		}	
	}
	comand_line = malloc(sizeof(char *) * (count + 1));
	return (comand_line);
}