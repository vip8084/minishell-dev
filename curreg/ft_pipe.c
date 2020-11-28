/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:53:09 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 21:18:54 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static int	get_exit(char *path, char **comand, t_vars *vars, int *status)
{
	if (checking_recoded_functions(comand, vars))
		return (0);
	else if ((*status = execve(path, comand, vars->envp_copy)) == -1)
		return (WEXITSTATUS(*status));
	return (0);
}

void		ft_pipe(char *path, char **comand, t_vars *vars)
{
	pid_t	pid;
	int		mas[2];
	int		status;
	int		i;

	i = 0;
	status = 0;
	pipe(mas);
	pid = fork();
	if (pid == 0)
	{
		close(mas[0]);
		dup2(mas[1], 1);
		close(mas[1]);
		exit(get_exit(path, comand, vars, &status));
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		close(mas[1]);
		dup2(mas[0], 0);
		close(mas[0]);
		waitpid(pid, &status, WUNTRACED);
	}
}
