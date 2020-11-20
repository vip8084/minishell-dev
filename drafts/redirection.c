/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:07:14 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/20 18:49:47 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_redirects(char *path, char **comand, char **mas_redirektion, t_vars *vars)
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
		count_redirects++;
	}
	fd = open(mas_redirektion[count_redirects - 1], O_WRONLY | O_APPEND, 0666);
	if (fd > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd, 1);
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

			/////////////////////
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
					// printf("\nERRNO = %i\n", errno);
					// printf("STATUS = %d\n", status);
					// printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
					// printf("G_ERROR = %d\n", g_error);
					// printf("after that g_error = %d\n\n", g_error);
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
			/////////////////
			
			vars->g_exit_code = WEXITSTATUS(status);
			close(fd);
		}
	}
}

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
			ft_putstr_fd(mas_redirektion[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
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

			/////////////////////
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
					// printf("\nERRNO = %i\n", errno);
					// printf("STATUS = %d\n", status);
					// printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
					// printf("G_ERROR = %d\n", g_error);
					// printf("after that g_error = %d\n\n", g_error);
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
			/////////////////

			vars->g_exit_code = WEXITSTATUS(status);
			close(fd);
		}	
	}
}

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
			vars->g_exit_code = WEXITSTATUS(status);
			close(fd);
		}		
	}	
}

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
			vars->g_exit_code = WEXITSTATUS(status);
			close(fd);
			close(fd2);
		}		
	}
}

// менеджмент ошибок

// void	ft_conveyor_test(char *line, char **comand_line, t_vars *vars)
// {
// 	char **line_pipe;
// 	char *comand_path;
// 	int i;

// 	i = 0;
// 	line_pipe = ft_split(line, '>');
// 	if (vars->count_redirect - i > 0)
// 	{
// 		comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
// 		comand_line = ft_split(line_pipe[i], ' ');
// 		comand_path = ft_strjoin(comand_path, "/");
// 		comand_path = ft_strjoin(comand_path, comand_line[0]);
// 		ft_redirects(comand_path, line_pipe, vars);
// 		vars->count_redirect = 0;
// 	}
// 	else
// 	{
// 		if(!(checking_recoded_functions(&line_pipe[i], vars)))			
// 		{
// 			comand_line = ft_split(line_pipe[i], ' ');
// 			comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
// 			comand_path = ft_strjoin(comand_path, "/");
// 			comand_path = ft_strjoin(comand_path, comand_line[0]);
// 			system_funk(comand_path, comand_line, vars);
// 		}
// 	}
// 	dup2(vars->save_std_in, 0);
// 	dup2(vars->save_std_out, 1);	
// }

// void	ft_pars_argument_test(char *line, t_vars *vars)
// {
// 		char **comand_line;
// 		char **line_pipe;
// 		char *comand_path;
// 		char **argv;
// 		char *ptr;
// 		int mas[2];
// 		int count = 0;
// 		int	i = 0;
// 		int t = 0;

// 		comand_line = ft_split(line, ' ');
// 		check_redirect(comand_line, vars);
// 		if (vars->count_redirect == 0)
// 		{
// 			if(!(checking_recoded_functions(comand_line, vars)))
// 			{
// 				comand_path = check_system_funk(vars, comand_line);
// 				comand_path = ft_strjoin(comand_path, "/");
// 				comand_path = ft_strjoin(comand_path, comand_line[0]);			
// 				system_funk(comand_path, comand_line, vars);
// 			}
// 		}
// 		else
// 		{
// 			ft_conveyor_test(line, comand_line, vars);
// 			dup2(vars->save_std_in, 0);
// 			dup2(vars->save_std_out, 1);
// 		}
// }

// int main(int argc, char **argv, char **envp)
// {
// 	t_vars	vars;
// 	char *ptr;
// 	char *line = NULL;
// 	int i = 0;
// 	struct dirent *dir;
// 	vars.save_std_in = dup(0);
// 	vars.save_std_out = dup(1);
// 	envp_copy(envp, &vars);
// 	vars.count_redirect = 0;
// 	vars.path = init_patch(&vars, "PATH");
// 	ft_putstr_fd("minishell>", 1);
// 	while((i = get_next_line(0, &line)) > 0)
// 	{
// 		ft_pars_argument_test(line, &vars);
// 		free(line);
// 		line = NULL;
// 		ft_putstr_fd("minishell>", 1);
// 	}
// 	return 0;
// }