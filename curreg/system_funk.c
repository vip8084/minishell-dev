/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:42:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 16:45:56 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void			system_funk(char *path, char **argv, t_vars *vars)//вызов системных функций
{
	int count;
	int status;
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		if ((status = execve(path, argv, vars->envp_copy)) == -1)
			exit(WEXITSTATUS(status));
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		vars->g_exit_code = WEXITSTATUS(status);
	}
}
//нужно разобраться с установкой ошибок