/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 08:17:17 by student           #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nam, size_t size)
{
	void	*ptr;

	ptr = (void*)malloc(size * nam);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size * nam);
	return (ptr);
}
