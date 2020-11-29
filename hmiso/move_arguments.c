/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:06:46 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/29 19:15:22 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void		init_move(t_move *move)
{
	move->ptr = NULL;
	move->ptr2 = NULL;
	move->flag2 = 0;
	move->count = 0;
	move->flag = 0;
	move->i = 0;
	move->poz = 0;
}

static void		move_res(char **comand_line, t_move *move, t_vars *vars)
{
	if ((ft_strncmp(comand_line[move->i], ">", 2) == 0
	|| ft_strncmp(comand_line[move->i], ">>", 3) == 0 ||
	ft_strncmp(comand_line[move->i], "<", 2) == 0)
	&& vars->mas_flags[move->i + move->count] != 1)
	{
		if ((comand_line[move->i + 2] != NULL)
		&& (ft_strncmp(comand_line[move->i + 2], "|", 2) != 0))
		{
			if ((ft_strncmp(comand_line[move->i + 2], ">", 2) != 0
			&& ft_strncmp(comand_line[move->i + 2], ">>", 3) != 0 &&
			ft_strncmp(comand_line[move->i + 2], "<", 2) != 0))
			{
				move->ptr = comand_line[move->i];
				move->flag = vars->mas_flags[move->i + move->count];
				comand_line[move->i] = comand_line[move->i + 2];
				vars->mas_flags[move->i + move->count] =
				vars->mas_flags[move->i + 2];
				comand_line[move->i + 2] = comand_line[move->i + 1];
				vars->mas_flags[move->i + 2] = vars->mas_flags[move->i + 1];
				comand_line[move->i + 1] = move->ptr;
				vars->mas_flags[move->i + 1] = move->flag;
			}
		}
	}
	move->i++;
}

static void		move_res_2(char **comand_line, t_move *move, t_vars *vars)
{
	move->ptr = comand_line[move->i];
	move->flag = vars->mas_flags[move->i + move->count];
	move->ptr2 = comand_line[move->i + 1];
	move->flag2 = vars->mas_flags[move->i + 1];
	comand_line[move->i] = comand_line[move->i + 2];
	vars->mas_flags[move->i + move->count] = vars->mas_flags[move->i + 2];
	comand_line[move->i + 1] = comand_line[move->i + 3];
	vars->mas_flags[move->i + 1] = vars->mas_flags[move->i + 3];
	comand_line[move->i + 2] = move->ptr;
	vars->mas_flags[move->i + 2] = move->flag;
	comand_line[move->i + 3] = move->ptr2;
	vars->mas_flags[move->i + 3] = move->flag2;
}

static void		move_res_3(char **comand_line, t_move *move, t_vars *vars)
{
	while (comand_line[move->poz] != NULL)
	{
		while (comand_line[move->i] != NULL)
		{
			if ((ft_strncmp(comand_line[move->i], ">", 2) == 0
			|| ft_strncmp(comand_line[move->i], ">>", 3) == 0)
			&& vars->mas_flags[move->i + move->count] != 1)
			{
				if ((comand_line[move->i + 2] != NULL)
				&& ((ft_strncmp(comand_line[move->i + 2], "|", 2) != 0)
				&& vars->mas_flags[move->i + 2] != 1))
				{
					if ((ft_strncmp(comand_line[move->i + 2], "<", 2) == 0)
					&& vars->mas_flags[move->i + move->count] != 1)
						move_res_2(comand_line, move, vars);
				}
			}
			move->i++;
		}
		move->i = 0;
		move->poz++;
	}
}

char			**move_arguments(char **comand_line, t_vars *vars)
{
	t_move move;

	init_move(&move);
	while (comand_line[move.i] != NULL)
		move.i++;
	while (vars->mas_flags[move.count] != 2)
		move.count++;
	move.count = move.count - move.i;
	while (comand_line[move.poz] != NULL)
	{
		while (comand_line[move.i] != NULL)
			move_res(comand_line, &move, vars);
		move.i = 0;
		move.poz++;
	}
	move.i = 0;
	move.poz = 0;
	move_res_3(comand_line, &move, vars);
	return (comand_line);
}
