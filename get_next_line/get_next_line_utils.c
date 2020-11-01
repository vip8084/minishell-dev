/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 16:47:56 by hmiso             #+#    #+#             */
/*   Updated: 2020/06/24 15:03:42 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

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

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_strlen(s1);
	ptr = (char*)malloc(sizeof(*ptr) * ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	while (i < count)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char*)malloc(sizeof(*ptr) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
