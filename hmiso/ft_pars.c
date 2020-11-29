/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:05:28 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 19:48:03 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		init_pars(t_pars *pars, char *line)
{
	pars->count = 0;
	pars->i = 0;
	pars->j = 0;
	pars->flag = 0;
	pars->comand_line = count_comands(line);
}

static void		ft_pars_res(char *line, t_pars *pars)
{
	if (line[pars->i] != ' ')
	{
		pars->j = pars->i;
		while ((line[pars->i] != ' ' || pars->flag == 1
		|| pars->flag == 2) && line[pars->i] != '\0')
		{
			if (line[pars->i] == '"' || line[pars->i] == '\'')
			{
				if (pars->flag == 0 && line[pars->i] == '"')
					pars->flag = 1;
				else if (pars->flag == 1 && line[pars->i] == '"')
					pars->flag = 0;
				else if (pars->flag == 0 && line[pars->i] == '\'')
					pars->flag = 2;
				else if (pars->flag == 2 && line[pars->i] == '\'')
					pars->flag = 0;
			}
			pars->i++;
		}
		pars->comand_line[pars->count] = ft_substr(line,
		pars->j, pars->i - pars->j);
		pars->count++;
	}
	else
		pars->i++;
}

char			**ft_pars(char *line, t_vars *vars)
{
	t_pars	pars;

	init_pars(&pars, line);
	while (line[pars.i] != '\0')
	{
		ft_pars_res(line, &pars);
	}
	pars.comand_line[pars.count] = NULL;
	environment_variable_substitution(pars.comand_line, vars);
	return (pars.comand_line);
}
