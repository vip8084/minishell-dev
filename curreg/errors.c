/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:51:37 by curreg            #+#    #+#             */
/*   Updated: 2020/11/16 16:30:22 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

// int get_exit_err()
// {
//     int error;
    
//     error = 0;
//     vars->err_flag;
//     vars->cd_flag;
//        g_error;

//     return (error);
// }


void command_error(char *cmd, t_vars *vars)
{
    

    // if(ft_strcmp("clear", cmd) == 0)
    // {
    //     vars->err_flag = 0;
    //     g_error = 0;
    // }
    // else
    // {
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
    // }
}

void cd_error(char *cmd, char* arg, int err)
{
	ft_putstr_fd("minishell>", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(arg, 1);
	if (err == 2)
		ft_putstr_fd(": No such file or directory\n", 1);
	else if (err == 20)
		ft_putstr_fd(": Not a directory\n", 1);
}