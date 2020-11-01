/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 17:39:51 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;
	size_t			count;
	size_t			m;

	ptr1 = (unsigned char*)dst;
	ptr2 = (unsigned char*)src;
	i = 0;
	count = 0;
	m = ft_strlen(dst) + ft_strlen(src);
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (ptr1[i] != '\0' && i < (size - 1))
		i++;
	while (ptr2[count] != '\0' && i < (size - 1))
	{
		ptr1[i] = ptr2[count];
		i++;
		count++;
	}
	dst[i] = '\0';
	return (m);
}
