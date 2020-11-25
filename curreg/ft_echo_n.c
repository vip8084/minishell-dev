/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:38:12 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 20:33:58 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_echo_n(char **line, t_vars *vars)//вывод без переноса строки
{
	int i;
	char *path;

	i = 2;
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
		if (ft_strncmp(line[i], "-n", 3) !=0)
		{
			ft_putstr_fd(line[i], 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);
		}
		else
		{
			i++;
		}
					
		// }
	}
	//free_two_dimensional_array(line);
}
// такая же хрень что и с эхо