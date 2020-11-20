/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:51:37 by curreg            #+#    #+#             */
/*   Updated: 2020/11/20 14:23:33 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void command_error(char *cmd, t_vars *vars)
{
    ft_putstr_fd("minishell>", 1);
    if (ft_strcmp("$?", cmd) == 0)
    {
        if (vars->cd_flag == 1 && vars->err_flag == 0)
        {
            ft_putstr_fd("1", 1);
            vars->err_flag = 1;
        }
        else if (vars->err_flag == 0)
        {
            ft_putstr_fd("0", 1);
            vars->err_flag = 1;
        }
        else
            ft_putstr_fd(ft_itoa(g_error), 1);
    }
    else
    {
        vars->err_flag = 1;
        ft_putstr_fd(cmd, 1);
    }
    ft_putstr_fd(": command not found\n", 1);
}

void cd_error(char *cmd, char* arg, char *err)
{
	ft_putstr_fd("minishell>", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(arg, 1);
    ft_putstr_fd(": ", 1);
	ft_putstr_fd(err, 1);
    ft_putstr_fd("\n", 1);
}