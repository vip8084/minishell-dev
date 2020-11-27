/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_comand_mas_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:28:22 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 19:28:24 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**make_comand_mas_start(char **comand_line, int i, int j)
{
	int k;
	int count = 0;
	char **comand_whis_flags;

	k = i - j; //смещение до пайпа или редиректа
	comand_whis_flags = malloc(sizeof(char *) * (j + 1));
	while (k < i)
	{
		comand_whis_flags[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	comand_whis_flags[count] = NULL;	
	return comand_whis_flags;
}