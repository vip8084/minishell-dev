/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor_res.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 20:57:13 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/27 21:02:52 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	init_conveyor(t_conveyor *conveyor)
{
	conveyor->j = 1;
	conveyor->i = 0;
	conveyor->k = 0;
	conveyor->flag = 0;
	conveyor->flag_pipe = 0;
	conveyor->comand_path = NULL;
	conveyor->com_whis_flags = NULL;
	conveyor->mas_redirektion = NULL;
	conveyor->mas_redirektion2 = NULL;
}

void	conveyor_res(char **comand_line, t_vars *vars, t_conveyor *conveyor)
{
	ft_pipe_eof();
	create_file(&comand_line[conveyor->i], &vars->mas_flags[conveyor->i]);
	vars->flag_redirect = 0;
	conveyor->flag_pipe = 1;
	conveyor->i++;
}

void	conveyor_res_2(char **comand_line, t_vars *vars, t_conveyor *conveyor)
{
	create_file(&comand_line[conveyor->i], &vars->mas_flags[conveyor->i]);
	conveyor->com_whis_flags = make_comand_mas_start(comand_line,
	conveyor->i, (conveyor->j - 1));
	conveyor->comand_path = ft_join_path(vars, conveyor->com_whis_flags);
	ft_pipe(conveyor->comand_path, conveyor->com_whis_flags, vars);
	conveyor->j = 0;
	vars->flag_redirect = 0;
	conveyor->flag_pipe = 1;
	free_two_dimensional_array(conveyor->com_whis_flags);
	free(conveyor->comand_path);
}

void	conveyor_res_3(char **comand_line, t_vars *vars, t_conveyor *conveyor)
{
	conveyor->comand_path = ft_join_path(vars, conveyor->com_whis_flags);
	while (comand_line[conveyor->i + 1] != NULL)
	{
		if (ft_strncmp(comand_line[conveyor->i], "|", 2) == 0
		&& vars->mas_flags[conveyor->i] == 0)
		{
			break ;
		}
		conveyor->i++;
		conveyor->k++;
	}
	conveyor->mas_redirektion = make_list_rederection(comand_line,
	conveyor->i, conveyor->k, vars);
	ft_redirects(conveyor->comand_path, conveyor->com_whis_flags,
	conveyor->mas_redirektion, vars);
	conveyor->j = 0;
	conveyor->k = 0;
	vars->flag_redirect = 1;
	conveyor->flag_pipe = 0;
	if (conveyor->mas_redirektion[0] != NULL)
		conveyor->i--;
	free_two_dimensional_array(conveyor->com_whis_flags);
	ptr_free(&conveyor->comand_path);
	free_two_dimensional_array(conveyor->mas_redirektion);
}

void	conveyor_res_4(char **comand_line, t_vars *vars, t_conveyor *conveyor)
{
	while (comand_line[conveyor->i + 1] != NULL)
	{
		if (ft_strncmp(comand_line[conveyor->i], "|", 2) == 0
		&& vars->mas_flags[conveyor->i] == 0)
		{
			break ;
		}
		conveyor->i++;
		conveyor->k++;
	}
	conveyor->k = 0;
	vars->flag_redirect = 1;
	conveyor->flag_pipe = 0;
	conveyor->i--;
}
