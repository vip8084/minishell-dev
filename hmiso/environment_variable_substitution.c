/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_substitution.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:49:39 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 17:26:43 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		init_envir(t_envir *envir)
{
	envir->ptr = NULL;
	envir->env_var = NULL;
	envir->ptr2 = NULL;
	envir->ptr_for_free = NULL;
	envir->ptr_for_free2 = NULL;
	envir->i = 0;
	envir->j = 0;
	envir->flag = 0;
	envir->k = 0;
}

void			env_var_res_6(char **comand_line, t_vars *vars, t_envir *envir)
{
	envir->i = 0;
	while (comand_line[envir->i] != NULL)
		envir->i++;
	if (vars->mas_flags == NULL)
	{
		vars->mas_flags = malloc(sizeof(int) * (envir->i + 1));
		envir->i = 0;
		while (comand_line[envir->i] != NULL)
		{
			if (comand_line[envir->i][0] == '"'
			|| comand_line[envir->i][0] == '\'')
				vars->mas_flags[envir->i] = 1;
			else
				vars->mas_flags[envir->i] = 0;
			envir->ptr_for_free2 = comand_line[envir->i];
			comand_line[envir->i] = delete_quotes(comand_line[envir->i]);
			ptr_free(&envir->ptr_for_free2);
			envir->i++;
		}
		vars->mas_flags[envir->i] = 2;
	}
}

void			env_var_res_7(char **comand_line, t_vars *vars, t_envir *envir)
{
	while (comand_line[envir->i][envir->j] != '\0')
	{
		env_var_res(comand_line, vars, envir);
		if (comand_line[envir->i][envir->j] == '$' && envir->flag != 1)
		{
			env_var_res_2(comand_line, vars, envir);
			if (envir->j - envir->k >= 1)
			{
				env_var_res_3(comand_line, vars, envir);
				env_var_res_4(comand_line, vars, envir);
				env_var_res_5(comand_line, vars, envir);
			}
			else if (comand_line[envir->i][envir->j] != '\0')
				envir->j++;
		}
		else
			envir->j++;
	}
}

char			**environment_variable_substitution(char **comand_line,
t_vars *vars)
{
	t_envir	envir;

	init_envir(&envir);
	while (comand_line[envir.i] != NULL)
	{
		env_var_res_7(comand_line, vars, &envir);
		envir.i++;
		envir.j = 0;
	}
	env_var_res_6(comand_line, vars, &envir);
	return (comand_line);
}
