/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:05:33 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/21 19:37:39 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	check_redirect(char **comand_mas, t_vars *vars)
{
	int i = 0;
	
	while(comand_mas[i] != NULL)
	{
		if((ft_strncmp(comand_mas[i], ">", 2) == 0 || ft_strncmp(comand_mas[i], "<", 2) == 0 || ft_strncmp(comand_mas[i], ">>", 3) == 0) && vars->mas_flags[i] == 0) 
		{
			vars->count_redirect++;
		}
		i++;
	}
}