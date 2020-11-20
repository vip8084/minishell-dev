/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:42:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/20 12:50:23 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void			system_funk(char *path, char **argv, t_vars *vars)//вызов системных функций
{
	int count;
	int status;
	pid_t pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if ((status = execve(path, argv, vars->envp_copy)) == -1)
			exit(errno);
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (status==2)
			g_signal=1;
		if (WIFEXITED(status))
		{
			if(WEXITSTATUS(status))
			{
				set_g_error(WEXITSTATUS(status));
				if(status != 256)
					command_error(argv[0], vars);	
			}
			else
			{
				vars->err_flag = 0;
				vars->cd_flag = 0;
				g_error = 0;
			}
		}
		vars->g_exit_code = WEXITSTATUS(status);        /////
	}
}
