/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two_dimensional_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:55:07 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/24 20:40:34 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		free_two_dimensional_array(char **arr)//освобождение памяти в двухмерном масиве
{
	int i;

	i = 0;
	if (arr != NULL)
	{
		while(arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr=NULL;
	}
}

//вроде норм добавить проверку на NULL дабы не сегала если хрень придет