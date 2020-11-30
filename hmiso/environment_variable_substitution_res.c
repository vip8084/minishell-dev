/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_substitution_res.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:22:28 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/30 12:22:16 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		env_var_res(char **comand_line, t_envir *envir)
{
	if (comand_line[envir->i][envir->j] == '"')
	{
		if (envir->flag == 0 && comand_line[envir->i][envir->j] == '"')
			envir->flag = 2;
		else if (envir->flag == 2 && comand_line[envir->i][envir->j] == '"')
			envir->flag = 0;
	}
	if (comand_line[envir->i][envir->j] == '\'' && envir->flag != 2)
	{
		if (envir->flag == 0 && comand_line[envir->i][envir->j] == '\'')
			envir->flag = 1;
		else if (envir->flag == 1 && comand_line[envir->i][envir->j] == '\'')
			envir->flag = 0;
	}
}

void		env_var_res_2(char **comand_line, t_envir *envir)
{
	envir->k = envir->j;
	while ((comand_line[envir->i][envir->j + 1] != ' ')
	&& comand_line[envir->i][envir->j] != '\0'
	&& (ft_isalpha(comand_line[envir->i][envir->j + 1])
	|| ft_isdigit(comand_line[envir->i][envir->j + 1])
	|| comand_line[envir->i][envir->j + 1] == '_'))
	{
		envir->j++;
	}
	if (comand_line[envir->i][envir->j + 1] == '?'
	&& comand_line[envir->i][envir->j] != '\0')
	{
		envir->j++;
	}
}

void		env_var_res_3(char **comand_line, t_envir *envir)
{
	envir->ptr = ft_substr(comand_line[envir->i], 0, envir->k);
	envir->env_var = ft_substr(comand_line[envir->i],
	envir->k + 1, envir->j - envir->k);
	envir->ptr2 = ft_substr(comand_line[envir->i], envir->j, 100);
	envir->ptr_for_free = envir->ptr;
}

void		env_var_res_4(t_vars *vars, t_envir *envir)
{
	if (ft_strncmp(envir->env_var, "?", 2) == 0)
	{
		envir->ptr_for_free2 = ft_itoa(g_error);
		envir->ptr = ft_strjoin(envir->ptr, envir->ptr_for_free2);
		ptr_free(&envir->ptr_for_free2);
	}
	else
	{
		envir->ptr_for_free2 = init_patch(vars, envir->env_var);
		envir->ptr = ft_strjoin(envir->ptr, envir->ptr_for_free2);
		ptr_free(&envir->ptr_for_free2);
	}
}

void		env_var_res_5(char **comand_line, t_envir *envir)
{
	ptr_free(&envir->ptr_for_free);
	envir->ptr_for_free = envir->ptr;
	envir->ptr = ft_strjoin(envir->ptr, &envir->ptr2[1]);
	ptr_free(&envir->ptr_for_free);
	ptr_free(&comand_line[envir->i]);
	comand_line[envir->i] = envir->ptr;
	ptr_free(&envir->env_var);
	ptr_free(&envir->ptr2);
	envir->i = 0;
	envir->j = 0;
}
