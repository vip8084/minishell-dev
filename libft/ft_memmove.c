/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 13:57:53 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/20 08:15:21 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	i = 0;
	if (ptr1 == ptr2)
		return (dst);
	if (ptr1 > ptr2)
	{
		while (n-- > 0)
			ptr1[n] = ptr2[n];
	}
	else
	{
		while (i < n)
		{
			ptr1[i] = ptr2[i];
			i++;
		}
	}
	return (dst);
}
