/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:53:09 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/02 18:22:59 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_pipe(char *path, char **comand, t_vars *vars)
{
    pid_t pid;
    int mas[2];
    int status;
    int i;
    pipe(mas);
    pid = fork();
    if (pid == 0)
    {
        close(mas[0]);
        dup2(mas[1], 1);
        close(mas[1]);
		if(checking_recoded_functions(comand, vars))
		{
			exit (0);// забирать значение эрно из внутренних функций и передавать сюда
		}
		else if ((status = execve(path, comand, vars->envp_copy)) == -1)
			exit(WEXITSTATUS(status));
    }
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
    {
        close(mas[1]);
        dup2(mas[0], 0);
        close(mas[0]);
        waitpid(pid, &status, WUNTRACED);
		vars->g_exit_code = WEXITSTATUS(status);
    }
}
// менеджмент ошибок