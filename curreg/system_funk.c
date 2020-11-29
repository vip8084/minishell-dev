/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:42:45 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/29 15:40:31 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void	set_sf_err(int status, int err, t_vars *vars, char **argv)
{
	if (status == 256 || err == 13 || err == 2)
	{
		vars->err_flag = 1;
		g_error = 1;
		errno = 0;
	}
	if (status != 256 && status != 16384)
		command_error(argv[0], vars);
}

static void set_err(int status)
{
	if (status == 2)
	{
		g_signal = 1;
		g_error = 130;
	}
	else if (status == 3)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
		g_error = 131;
	}
}

static void set_flags(t_vars *vars)
{
	vars->err_flag = 0;
	vars->cd_flag = 0;
	g_error = 0;
}

void		system_funk(char *path, char **argv, t_vars *vars)
{
	int		count;
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if ((status = execve(path, argv, vars->envp_copy)) == -1)
			exit(errno);
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
		signal(SIGINT, &ft_signals);
		signal(SIGQUIT, &ft_signal);
		set_err(status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
				set_sf_err(status, errno, vars, argv);
			else
				set_flags(vars);
		}
	}
}
