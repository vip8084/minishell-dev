/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:58:12 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/18 21:10:15 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		sum;
	t_list	*list;

	list = lst;
	sum = 0;
	if (lst != NULL)
	{
		while (list)
		{
			list = list->next;
			sum++;
		}
	}
	return (sum);
}
