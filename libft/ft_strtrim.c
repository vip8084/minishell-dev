/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 08:45:17 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strim_start(char const *s1, char const *set)
{
	size_t		j;
	size_t		count;
	size_t		i;

	i = 0;
	j = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				count++;
			j++;
		}
		j = 0;
		if (count == 0)
			break ;
		count = 0;
		i++;
	}
	return (i);
}

static int		ft_strim_end(char const *s1, char const *set)
{
	size_t		j;
	size_t		count;
	size_t		m;

	j = 0;
	count = 0;
	m = 0;
	while (ft_strlen(s1) - m != 0)
	{
		while (set[j] != '\0')
		{
			if (s1[ft_strlen(s1) - m - 1] == set[j])
				count++;
			j++;
		}
		j = 0;
		if (count == 0)
			break ;
		count = 0;
		m++;
	}
	return (m);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	m;
	size_t	count;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = ft_strim_start(s1, set);
	m = ft_strim_end(s1, set);
	j = i;
	count = 0;
	if (ft_strlen(s1) == i || ft_strlen(s1) == m)
	{
		ptr = (char*)malloc(sizeof(*ptr) * 1);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = (char*)malloc(sizeof(*ptr) * (ft_strlen(s1) - m - i + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, &s1[j], ft_strlen(s1) - m - i);
	ptr[ft_strlen(s1) - m - i] = '\0';
	return (ptr);
}
