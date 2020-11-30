/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:49:25 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/30 12:24:13 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void	redirects_pipe(char **mas_redirektion, int *fd)
{
	int count_redirects;

	count_redirects = 0;
	while (mas_redirektion[count_redirects + 1] != NULL)
	{
		*fd = open(mas_redirektion[count_redirects], O_RDONLY);
		if (*fd < 0)
		{
			ft_putstr_fd(mas_redirektion[count_redirects], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			break ;
		}
		count_redirects++;
		close(*fd);
	}
	*fd = open(mas_redirektion[count_redirects], O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd(mas_redirektion[count_redirects], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

static void	redirects_pipe_res(int *mas, int status, pid_t pid, int fd)
{
	close(mas[1]);
	dup2(fd, 0);
	dup2(mas[0], 0);
	close(mas[0]);
	waitpid(pid, &status, WUNTRACED);
	close(fd);
}

static void	redirects_pipe_res_2(int *mas, int fd, char **comand, t_vars *vars)
{
	close(mas[0]);
	dup2(fd, 0);
	dup2(mas[1], 1);
	close(mas[1]);
	if (checking_recoded_functions(comand, vars))
		exit(0);
}

void		ft_redirects_pipe(char *path, char **comand,
char **mas_redirektion, t_vars *vars)
{
	pid_t	pid;
	int		mas[2];
	int		status;
	int		fd;

	status = 0;
	redirects_pipe(mas_redirektion, &fd);
	if (fd > 0)
	{
		pipe(mas);
		pid = fork();
		if (pid == 0)
		{
			redirects_pipe_res_2(mas, fd, comand, vars);
			if ((status = execve(path, comand, vars->envp_copy)) == -1)
				exit(WEXITSTATUS(status));
		}
		else if (pid < 0)
			ft_putendl_fd("error", 2);
		else
			redirects_pipe_res(mas, status, pid, fd);
	}
	else
		ft_pipe_eof();
}
