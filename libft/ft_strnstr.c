/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:18:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/24 19:31:10 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	m;

	i = 0;
	j = 0;
	m = ft_strlen(needle);
	if (m == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
			while (haystack[i] == needle[j] && i < len && haystack[i] != '\0')
			{
				i++;
				j++;
				if (j == m)
					return ((char *)&haystack[i - j]);
			}
		i = i - j;
		j = 0;
		i++;
	}
	return (NULL);
}
