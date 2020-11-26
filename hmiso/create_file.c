/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:19:31 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 19:19:58 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	create_file(char **comand_line,int *mas_flags)
{
	int i;
	int fd;

	fd = 0;
	i = 0;
	while (comand_line[i] != NULL)
	{
		if (ft_strncmp(comand_line[i], ">", 2) == 0 && comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (fd == -1)
			{
				ft_putstr_fd(comand_line[i + 1], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				break;
			}
			close(fd);
		}
		if (ft_strncmp(comand_line[i], "<", 2) == 0 && comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd(comand_line[i + 1], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				break;
			}
			close(fd);
		}		
		if (ft_strncmp(comand_line[i], ">>", 3) == 0 && comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd == -1)
			{
				ft_putstr_fd(comand_line[i + 1], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				break;
			}			
			close(fd);
		}
		i++;
	}
}