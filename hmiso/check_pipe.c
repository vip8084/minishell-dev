/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:39:42 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/17 17:52:39 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	check_pipe(char **comand_mas, t_vars *vars)
{
	int i = 0;
	vars->count_pipe = 0;
	
	while(comand_mas[i] != NULL)
	{
		if(ft_strncmp(comand_mas[i], "|", 2) == 0)
		{
			vars->count_pipe++;
		}
		i++;
	}
}