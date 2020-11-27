/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:36:32 by curreg            #+#    #+#             */
/*   Updated: 2020/11/27 17:45:55 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

int	check_valid_id(char *str)
{
	int i;
	int not_only_name;
	
	not_only_name = 0;
	if (str[0] == '=')
		return (0);
	i = 1;
	while(str[i] != '\0')
	{
		if (str[i] == '=')
		{
			not_only_name = 1;
			break;
		}
		i++;
	}
	i = 0;	
	if (not_only_name)
	{
		while (str[i] != '=')
		{
			if (i == 0)
			{
				if (!(str[i] == '_' || 
					(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
					return (0);
				i++;
			}
			else
			{
				if (!(str[i] == '_' || str[i] == '=' || str[i] == '"' ||
					(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || 
					(str[i] >= '0' && str[i] <= '9')))
					return (0);
				i++;
			}
		}
	}
	else
	{
		while (str[i] != '\0')
		{
			if (i == 0)
			{
				if (!(str[i] == '_' || 
					(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
					return (0);
				i++;
			}
			else
			{
				if (!(str[i] == '_' || str[i] == '=' || str[i] == '"' ||
					(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || 
					(str[i] >= '0' && str[i] <= '9')))
					return (0);
				i++;
			}
		}	
	}
	return (1);
}