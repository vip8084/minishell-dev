/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_revers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:48:28 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 19:27:06 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_redirects_revers(char *path, char **comand, char **mas_redirektion, t_vars *vars)
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
			ft_putstr_fd("minishell>", 2);
			ft_putstr_fd(mas_redirektion[i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			break;			
		}
		count_redirects++;
	}
	if (fd > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd, 0);
			if(checking_recoded_functions(comand, vars))
			{
				exit (0);
			}
			if ((status = execve(path, comand, vars->envp_copy)) == -1)
				exit(WEXITSTATUS(status));
		}
		else if (pid < 0)
			ft_putendl_fd("error", 2);
		else
		{
			waitpid(pid, &status, WUNTRACED);
			if (status == 2)
			{
				g_signal = 1;
				g_error = 130;
			}
			if (status == 3)
			{
				ft_putstr_fd("^\\Quit: 3\n", 1);
				g_error = 131;
			}
			if (WIFEXITED(status))
			{
				if(WEXITSTATUS(status))
				{
					if (status == 256 || errno == 13 || errno == 2)
					{
						vars->err_flag = 1;
						g_error = 1;
						errno = 0;
					}
					if (status != 256 && status != 16384)
						command_error(comand[0], vars);	
				}
				else
				{
					vars->err_flag = 0;
					vars->cd_flag = 0;
					g_error = 0;
				}
			}
			close(fd);
		}	
	}
}
