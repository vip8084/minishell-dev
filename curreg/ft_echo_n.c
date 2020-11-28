/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:38:12 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 19:05:59 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_echo_n(char **line, t_vars *vars)
{
	int		i;
	char	*path;

	i = 2;
	path = NULL;
	while (line[i] != NULL)
	{
		if (ft_strncmp(line[i], "-n", 3) != 0)
		{
			ft_putstr_fd(line[i], 1);
			i++;
			if (line[i] != NULL)
				write(1, " ", 1);
		}
		else
			i++;
	}
}
