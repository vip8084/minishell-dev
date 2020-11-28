/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:19:31 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 19:27:03 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static int		create_file_res(char **comand_line, int *mas_flags,
int fd, int i)
{
	if (ft_strncmp(comand_line[i], ">", 2) == 0
	&& comand_line[i + 1] != NULL && mas_flags[i] == 0)
	{
		fd = open(comand_line[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd == -1)
		{
			ft_putstr_fd(comand_line[i + 1], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (1);
		}
		close(fd);
	}
	return (0);
}

static int		create_file_res_2(char **comand_line, int *mas_flags,
int fd, int i)
{
	if (ft_strncmp(comand_line[i], "<", 2) == 0
	&& comand_line[i + 1] != NULL && mas_flags[i] == 0)
	{
		fd = open(comand_line[i + 1], O_RDONLY);
		if (fd == -1)
		{
			return (1);
		}
		close(fd);
	}
	return (0);
}

void			create_file(char **comand_line, int *mas_flags)
{
	int		i;
	int		fd;

	fd = 0;
	i = 0;
	while (comand_line[i] != NULL)
	{
		if (create_file_res(comand_line, mas_flags, fd, i) == 1)
			break ;
		if (create_file_res_2(comand_line, mas_flags, fd, i) == 1)
			break ;
		if (ft_strncmp(comand_line[i], ">>", 3) == 0
		&& comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd == -1)
			{
				ft_putstr_fd(comand_line[i + 1], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				break ;
			}
			close(fd);
		}
		i++;
	}
}
