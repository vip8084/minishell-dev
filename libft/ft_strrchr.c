/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:15:55 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	sym;
	size_t			i;

	ptr = (char *)s;
	sym = c;
	i = ft_strlen(s);
	if (sym == '\0')
		return (&ptr[i]);
	while (i != 0)
	{
		if (ptr[i - 1] == sym)
			return (&ptr[i - 1]);
		i--;
	}
	return (NULL);
}
