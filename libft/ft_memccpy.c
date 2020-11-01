/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 13:55:14 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	unsigned char	sym;
	size_t			i;

	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	sym = c;
	i = 0;
	while (n > i)
	{
		ptr1[i] = ptr2[i];
		i++;
		if (ptr1[i - 1] == sym)
		{
			return (&dst[i]);
		}
	}
	return (NULL);
}
