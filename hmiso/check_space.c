/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:35:13 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/26 19:28:26 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void	check_space_res(char *ptr, char *line, int i)
{
	char *ptr_for_free;
	// char *ptr;
	// char *line;

	// ptr = *str;
	// line = *line2;
	ptr = ft_substr(line, 0, i);
	ptr_for_free = ptr;
	ptr = ft_strjoin(ptr, " ");
	ptr_free(&ptr_for_free);
	ptr_for_free = ptr;
	ptr = ft_strjoin(ptr, &line[i]);
	ptr_free(&ptr_for_free);
	ptr_free(&line);
	line = ft_strdup(ptr);
	ptr_free(&ptr);
}

char *check_space(char *line_old)
{
	int		i;
	int		flag;
	char	*ptr;
	char	*ptr_for_free = NULL;
	char	*line;
	
	ptr = NULL;
	i = 0;
	flag = 0;
	line = ft_strdup(line_old);
	ptr_for_free = NULL;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0 && line[i + 1] != '\0')
		{
			flag = 1;
			i++;
		}
		if ((line[i] == '\'' || line[i] == '"') && flag == 1 && line[i + 1] != '\0')
		{
			flag = 0;
			i++;
		}		
		if (ft_strlen(line) > 1 && (line[i] == '>' || line[i] == '|' || line[i] == '<') && flag == 0)
		{
			if (i !=0 && line[i - 1] != ' ' && i != 0 && line[i - 1] != '>')
			{
				ptr=ft_substr(line, 0, i);
				ptr_for_free = ptr;
				ptr=ft_strjoin(ptr, " ");
				ptr_free(&ptr_for_free);
				ptr_for_free = ptr;
				ptr = ft_strjoin(ptr, &line[i]);
				ptr_free(&ptr_for_free);
				ptr_free(&line);
				line = ft_strdup(ptr);
				ptr_free(&ptr);
				// check_space_res(ptr, line, i);
			}
			else if (ft_strlen(line) >= i + 1 && line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '>')
			{			
				ptr = ft_substr(line, 0 , i + 1);
				ptr_for_free = ptr;
				ptr = ft_strjoin(ptr, " ");
				ptr_free(&ptr_for_free);
				ptr_for_free = ptr;				
				ptr = ft_strjoin(ptr, &line[i + 1]);
				ptr_free(&ptr_for_free);
				ptr_free(&line);
				line = ft_strdup(ptr);
				ptr_free(&ptr);
			}
			else if (ft_strlen(line) >= i + 2 && line[i + 2] != ' ' && line[i + 2] != '\0' && line[i + 1] == '>')
			{
				ptr = ft_substr(line, 0 , i + 2);
				ptr_for_free = ptr;
				ptr = ft_strjoin(ptr, " ");
				ptr_free(&ptr_for_free);
				ptr_for_free = ptr;
				ptr = ft_strjoin(ptr, &line[i + 2]);
				ptr_free(&ptr_for_free);
				ptr_free(&line);
				line = ft_strdup(ptr);
				ptr_free(&ptr);
				i++;
			}
		}
		i++;
	}
	return (line);
}