/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:14:12 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	sym;
	size_t			i;

	ptr = (char *)s;
	sym = c;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == sym)
			return (&ptr[i]);
		i++;
	}
	if (sym == '\0')
		return (&ptr[i]);
	return (NULL);
}
