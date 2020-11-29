/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:32:57 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/29 20:28:29 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		init_semic(t_semik *semik)
{
	semik->i = 0;
	semik->flag = 0;
	semik->count = 0;
}

static void		semicolon_res(char *line, t_semik *semik)
{
	while (line[semik->i] != '\0')
	{
		if ((line[semik->i] == '\'' || line[semik->i] == '"')
		&& semik->flag == 0 && line[semik->i + 1] != '\0')
		{
			semik->flag = 1;
			semik->i++;
		}
		else if ((line[semik->i] == '\'' || line[semik->i] == '"')
		&& semik->flag == 1 && line[semik->i + 1] != '\0')
		{
			semik->flag = 0;
			semik->i++;
		}
		else if (semik->flag == 0 && line[semik->i] == ';')
		{
			semik->count++;
			semik->i++;
		}
		else
			semik->i++;
	}
}

static void		semicolon_res_2(char *line, t_semik *semik)
{
	while (line[semik->i] != '\0')
	{
		if ((line[semik->i] == '\'' || line[semik->i] == '"')
		&& semik->flag == 0)
			semik->flag = 1;
		else if ((line[semik->i] == '\'' || line[semik->i] == '"')
		&& semik->flag == 1)
			semik->flag = 0;
		if (semik->flag == 0 && line[semik->i] == ';')
		{
			semik->argv[semik->count] = ft_substr(line, 0, semik->i);
			line = &line[semik->i + 1];
			semik->count++;
			semik->i = 0;
			continue ;
		}
		if (line[semik->i] != '\0' && line[semik->i + 1] == '\0')
		{
			semik->argv[semik->count] = ft_substr(line, 0, semik->i + 1);
			semik->count++;
		}
		semik->i++;
	}
}

char			**semicolon(char *line)
{
	t_semik semik;

	init_semic(&semik);
	semicolon_res(line, &semik);
	semik.argv = malloc(sizeof(char*) * (semik.count + 2));
	semik.i = 0;
	semik.count = 0;
	semik.flag = 0;
	semicolon_res_2(line, &semik);
	semik.argv[semik.count] = NULL;
	semik.count = 0;
	return (semik.argv);
}
