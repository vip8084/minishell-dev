/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:27:08 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/30 12:20:09 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		conveyor_res_14(char **comand_line, t_vars *vars,
t_conveyor *conveyor)
{
	conveyor->com_whis_flags =
	make_comand_mas_start(comand_line, conveyor->i, (conveyor->j - 1));
	if (conveyor->com_whis_flags[0] != NULL)
	{
		conveyor_res_5(comand_line, vars, conveyor);
		conveyor_res_6(vars, conveyor);
		conveyor_res_7(comand_line, vars, conveyor);
		conveyor_res_8(conveyor);
	}
	else
	{
		conveyor_res_9(comand_line, vars, conveyor);
		conveyor_res_10(comand_line, vars, conveyor);
		conveyor_res_11(comand_line, vars, conveyor);
	}
}

static void		conveyor_res_15(char **comand_line, t_vars *vars,
t_conveyor *conveyor)
{
	if (((ft_strncmp(comand_line[conveyor->i], ">", 2) == 0)
	|| (ft_strncmp(comand_line[conveyor->i], ">>", 3) == 0))
	&& vars->mas_flags[conveyor->i] != 1)
	{
		conveyor->com_whis_flags =
		make_comand_mas_start(comand_line, conveyor->i, (conveyor->j - 1));
		if (conveyor->com_whis_flags[0] != NULL)
			conveyor_res_3(comand_line, vars, conveyor);
		else
			conveyor_res_4(comand_line, vars, conveyor);
	}
	else if ((ft_strncmp(comand_line[conveyor->i], "<", 2) == 0)
	&& vars->mas_flags[conveyor->i] != 1)
	{
		conveyor_res_14(comand_line, vars, conveyor);
	}
	else if (comand_line[conveyor->i + 1] == NULL && conveyor->flag_pipe == 1)
		conveyor_res_12(comand_line, vars, conveyor);
}

void			ft_conveyor(char **comand_line, t_vars *vars)
{
	t_conveyor conveyor;

	init_conveyor(&conveyor);
	create_file(comand_line, vars->mas_flags);
	while (comand_line[conveyor.i] != NULL)
	{
		if (conveyor.i != 0 &&
		((ft_strncmp(comand_line[conveyor.i], "|", 2) == 0)
		&& vars->flag_redirect == 1) && vars->mas_flags[conveyor.i] != 1)
		{
			conveyor_res(comand_line, vars, &conveyor);
		}
		if ((ft_strncmp(comand_line[conveyor.i], "|", 2) == 0)
		&& vars->flag_redirect == 0 && vars->mas_flags[conveyor.i] != 1)
		{
			conveyor_res_2(comand_line, vars, &conveyor);
		}
		else
			conveyor_res_15(comand_line, vars, &conveyor);
		conveyor.j++;
		conveyor.i++;
	}
	conveyor_res_13(vars);
}
