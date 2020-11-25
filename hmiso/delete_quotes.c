/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:36:43 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 12:36:58 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*delete_quotes(char *line)
{
	int i;
	int flag;
	
	i = 0;
	int count = 0;
	flag = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '"' && flag == 0)
		{
			line[i] = 10;
			flag = 1;
			i++;
		}
		else if(line[i] == '\'' && flag == 0)
		{
			line[i] = 10;
			flag = 2;
			i++;
		}
		else if(line[i] == '\'' && flag == 2)
		{
			line[i] = 10;
			flag = 0;
			i++;
		}		
		else if(line[i] == ' ' && flag == 0)
		{
			line[i] = 12;
			i++;
		}
		else if(line[i] == '"' && flag == 1)
		{
			line[i] = 10;
			flag = 0;
			i++;
		}
		else
			i++;
	}
	char *line_dubl;
	line_dubl = ft_calloc((i + 1), sizeof(char));
	i = 0;
	flag = 0;
	count = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"' ) && flag == 0)
		{
			flag = 1;
			line_dubl[count] = line[i];
			count++;
			i++;
		}
		else if ((line[i] == '\'' || line[i] == '"') && flag == 1)
		{
			flag = 0;
			line_dubl[count] = line[i];
			count++;
			i++;			
		}
		else
		{	
			if(flag != 1 || line[i] != 12)
			{
				if (line[i] != 10)
				{				
					line_dubl[count] = line[i];
					count++;
				}
			}
			i++;
		}
	}
	return line_dubl;
}