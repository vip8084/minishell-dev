/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:11:27 by hmiso             #+#    #+#             */
/*   Updated: 2020/05/16 15:15:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_negativ(char *ptr, int i, int n)
{
	ptr[0] = '-';
	while (n != 0)
	{
		i--;
		ptr[i] = n % 10 * (-1) + '0';
		n = n / 10;
	}
	return (ptr);
}

static char		*ft_itoa_pozitiv(char *ptr, int i, int n)
{
	while (n != 0)
	{
		i--;
		ptr[i] = n % 10 + '0';
		n = n / 10;
	}
	return (ptr);
}

char			*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		m;

	i = 0;
	m = n;
	while (m != 0)
	{
		m = m / 10;
		i++;
	}
	if (n <= 0)
		i++;
	ptr = (char*)malloc(sizeof(char) * i + 1);
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	if (n < 0)
		ptr = ft_itoa_negativ(ptr, i, n);
	else if (n == 0)
		ptr[0] = '0';
	else
		ptr = ft_itoa_pozitiv(ptr, i, n);
	return (ptr);
}
