/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:10:02 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/24 10:53:51 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_array(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	count_del;

	i = 0;
	count = 0;
	count_del = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count_del = 0;
		else if (count_del == 0)
		{
			count_del = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char		**free_mas(char **mas)
{
	int i;

	i = 0;
	while (mas[i] != NULL)
	{
		free(mas[i]);
		i++;
	}
	free(mas);
	return (NULL);
}

static char		**greyt_str(char const *s, char c, char **mas, size_t count)
{
	size_t	i;
	size_t	count_mas;
	size_t	count_str;

	i = 0;
	count_mas = 0;
	count_str = 0;
	while (s[i] != '\0' && count_mas < count)
	{
		while (s[i] == c)
			i++;
		while (s[i + count_str] != c && s[i + count_str] != '\0')
			count_str++;
		mas[count_mas] = (char*)malloc(sizeof(char) * (count_str + 1));
		if (!mas[count_mas])
			return (free_mas(mas));
		ft_strlcpy(mas[count_mas], &s[i], count_str + 1);
		i = i + count_str;
		count_mas++;
		count_str = 0;
	}
	return (mas);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	j;
	char	**mas;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	count = count_array(s, c);
	mas = (char**)malloc(sizeof(char*) * (count + 1));
	if (!mas)
		return (NULL);
	mas[count] = NULL;
	mas = greyt_str(s, c, mas, count);
	return (mas);
}
