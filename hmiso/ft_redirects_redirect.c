/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:52:17 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 19:27:02 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_redirects_redirect(char *path, char **comand, char **mas_redirektion, char **mas_redirektion2, t_vars *vars)
{
    pid_t pid;
    int mas[2];
    int status;
    int i;
	int fd;
	int fd2;

	i = 0;
	int count_redirects = 0;
	
	while(mas_redirektion[count_redirects] != NULL)
	{
		fd = open(mas_redirektion[count_redirects], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(mas_redirektion[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			break;			
		}
		count_redirects++;
	}
	count_redirects = 0;
	while(mas_redirektion2[count_redirects] != NULL)
	{
		count_redirects++;
	}
	fd2 = open(mas_redirektion2[count_redirects - 1], O_WRONLY | O_APPEND, 0666);
	if (fd > 0 && fd2 > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd, 0);
			dup2(fd2, 1);
			if(checking_recoded_functions(comand, vars))
			{
				exit (0);// забирать значение эрно из внутренних функций и передавать сюда
			}
			if ((status = execve(path, comand, vars->envp_copy)) == -1)
				exit(WEXITSTATUS(status));
		}
		else if (pid < 0)
			ft_putendl_fd("error", 2);
		else
		{
			waitpid(pid, &status, WUNTRACED);
			close(fd);
			close(fd2);
		}		
	}
}