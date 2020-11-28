/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:49:25 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 19:30:28 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_redirects_pipe(char *path, char **comand, char **mas_redirektion, t_vars *vars)
{
    pid_t pid;
    int mas[2];
    int status;
    int i;
	int fd;
	char **comand_s;
	char *name_file;

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
	if (fd > 0)
	{
		pipe(mas);
		pid = fork();
		if (pid == 0)
		{
			close(mas[0]);
			dup2(fd, 0);
			dup2(mas[1], 1);
			close(mas[1]);
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
			close(mas[1]);
			dup2(fd, 0);
			dup2(mas[0], 0);
			close(mas[0]);
			waitpid(pid, &status, WUNTRACED);
			close(fd);
		}		
	}	
}
