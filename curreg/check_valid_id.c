/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:36:32 by curreg            #+#    #+#             */
/*   Updated: 2020/11/24 17:54:44 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

// int	check_valid_id(char *str)
// {
// 	int i;
// 	int is_first;

// 	i = 0;
// 	is_first = 1;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '=' && is_first)
// 			return (0);
// 		if (!(str[i] == '$' || str[i] == '_' || 
// 			(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
// 			return (0);
// 		is_first = 0;
// 		i++;
// 	}
// 	return (1);
// }



int	check_valid_id(char *str)
{
	int i;
	int is_first;

	i = 0;
	is_first = 1;
	while (str[i] != '\0')
	{
		if (i == 0)
		{
			if (str[i] == '=' && is_first)
				return (0);
			if (!(str[i] == '$' || str[i] == '_' || 
				(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
				return (0);
			is_first = 0;
			i++;
		}
		else
		{
			if (!(str[i] == '$' || str[i] == '_' || 
				(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || 
				(str[i] >= '0' && str[i] <= '9')))
				return (0);
			i++;
		}
	}
	return (1);
}