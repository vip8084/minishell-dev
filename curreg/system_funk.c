/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:42:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/09 20:59:15 by curreg           ###   ########.fr       */
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
			exit(127);

		// if ((status = execve(path, argv, vars->envp_copy)) == -1)
		// {
		// 	set_g_error(errno);
		// 	command_error(argv[0], vars);
		//	exit(WEXITSTATUS(status));
		// }
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		// if ((status = execve(path, argv, vars->envp_copy)) == -1)
		// {
		// 	set_g_error(errno);
		// 	command_error(argv[0], vars);
		// }
			
		waitpid(pid, &status, WUNTRACED);               //////
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);

		printf("\n");
		printf("%d\n", g_error);
		printf("\n");
		vars->g_exit_code = WEXITSTATUS(status);        /////


		// if(!(pid=fork()))
		// {
		// 	exit(1);
		// }
		// waitpid(pid,&status,0);
		// if (WIFEXITED(status)) {
		// 	printf("%d", WEXITSTATUS(status));
		// }
	}
}
//нужно разобраться с установкой ошибок