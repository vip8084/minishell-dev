#include "minishel.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:56:20 by hmiso             #+#    #+#             */
/*   Updated: 2020/10/29 17:10:09 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void		ft_pipe(char **comand)
{
	int 	pipefd[2];
	int		i;
	int		k;
	int		j;
	pid_t	pid;
	pid_t	pid2;
	char	**argv1;
	char	**argv2;
	int 	status;
	i = 0;
	j = 0;
	while(ft_strncmp(comand[i], "|", 1) != 0)
	{
		i++;
	}
	argv1 = malloc(sizeof(char *) * (i + 1));
	while(j < i)
	{
		argv1[j] = ft_strdup(comand[j]);
		j++;
	}
	argv1[j] = NULL;
	j = i;
	while(comand[i] != NULL)
	{
		i++;
	}
	k = i - j;
	j = 0;
	argv2 = malloc(sizeof(char *) * (k));
	while(k < i)
	{
		argv2[j] = ft_strdup(comand[k]);
		j++;
		k++;
	}
	argv2[j] = NULL;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[PIPE_READ]);
		dup2(pipefd[PIPE_WRITE], 1);
		close(pipefd[PIPE_WRITE]);
		if ((status = execve(ft_strjoin("/bin/", argv1[0]), argv1, NULL)) == -1)
			exit(WEXITSTATUS(status));
		exit(status);	
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		//pid2 = fork();
		// if (pid2 == 0)
		// {
		// 	dup2(pipefd[PIPE_WRITE], 1);
		// 	close(pipefd[PIPE_READ]);			
		// 	if ((status = execve(ft_strjoin("/bin/", argv1[0]), argv1, NULL)) == -1)
		// 		exit(WEXITSTATUS(status));
		// 	close(pipefd[PIPE_WRITE]);			
		//}
		close(pipefd[PIPE_WRITE]);
		dup2(pipefd[PIPE_READ], 0);
		close(pipefd[PIPE_READ]);		
		waitpid(pid, &status, WUNTRACED);
		g_exit_code = WEXITSTATUS(status);
	}
	pid = fork();
	if (pid == 0)
	{
		if ((status = execve(ft_strjoin("/bin/", argv2[0]), argv2, NULL)) == -1)
			exit(WEXITSTATUS(status));
		exit(status);	
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		//pid2 = fork();
		// if (pid2 == 0)
		// {
		// 	dup2(pipefd[PIPE_WRITE], 1);
		// 	close(pipefd[PIPE_READ]);			
		// 	if ((status = execve(ft_strjoin("/bin/", argv1[0]), argv1, NULL)) == -1)
		// 		exit(WEXITSTATUS(status));
		// 	close(pipefd[PIPE_WRITE]);			
		//}		
		waitpid(pid, &status, WUNTRACED);
		g_exit_code = WEXITSTATUS(status);
	}	
}

char		*init_patch(t_vars *vars, char *arg) // возвращает значение переменной env
{
	char **ptr;
	int i;
	int len_arg;
	char *value;

	i = 0;
	len_arg = ft_strlen(arg);
	value = ft_strdup("");
	while (vars->envp_copy[i] != NULL)
	{
		ptr = ft_split(vars->envp_copy[i], '=');
		if (ft_strncmp(ptr[0], arg, len_arg) == 0)
		{
			free(value);
			value = ft_strdup(ptr[1]);
		}
		free(ptr[0]);
		free(ptr[1]);
		free(ptr);
		ptr = NULL;
		i++;
	}
	return (value);
}

void		free_two_dimensional_array(char **arr)//освобождение памяти в двухмерном масиве
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void		envp_copy(char **envp, t_vars *vars)//создание копии переменных среды
{
	int i;

	i = 0;
	while(envp[i] != NULL)
	{
		i++;
	}
	vars->envp_copy = malloc(sizeof(char*) * (i + 1));
	i = 0;
	while(envp[i] != NULL)
	{
		vars->envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	vars->envp_copy[i] = NULL;
	vars->count_envp = i - 1;
}

int			system_funk(char *path, char *line, t_vars *vars)//вызов системных функций
{
	char **argv;
	int count;
	int status;
	pid_t pid;
	int i = 0;
	int j = 0;
	argv = ft_split(line, ' ');
	char *ptr;
	ptr = ft_strjoin(path, "/");
	ptr = ft_strjoin(ptr, argv[0]);
	pid = fork();
	if (pid == 0)
	{
		if ((status = execve(ptr, argv, vars->envp_copy)) == -1)
			exit(WEXITSTATUS(status));
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		g_exit_code = WEXITSTATUS(status);
	}
	count = ft_strlen(argv[0]);
	if(argv[1] != NULL)
	{
		count+=ft_strlen(argv[1]);
	}
	free(ptr);
	free_two_dimensional_array(argv);
	return count;
}

int			check_system_funk(t_vars *vars, char *str) // проверяет наличие испалняеомего файла по путям PATH
{
	DIR *dir;
    struct dirent *st;
	char **path;
	char **arg;
	int i = 0;
	int flag = 0;

	path = ft_split(init_patch(vars, "PATH"), ':');
	arg = ft_split(str, ' ');
	char **argv = ft_split(str, ' ');
	while(path[i] != NULL)
	{
		dir = opendir(path[i]);
		while((st = readdir(dir)) != NULL)
		{
			if (ft_strlen(st->d_name) == ft_strlen(argv[0]))
			{
				if ((ft_strncmp(st->d_name, str, ft_strlen(argv[0]))) == 0)
				{
					system_funk(path[i], str, vars);
					flag = 1;
				}
			}
		}
		i++;
	}
	return flag;
}

void		ft_pars_argument(char *line, t_vars *vars)
{
	char **comand_mas = ft_split(line, ' ');
	int i = 0;
	// while(comand_mas[i] != NULL)
	// {
	// 	check_system_funk(vars, &line[i]);
	// 	i++;
	// }
	ft_pipe(comand_mas);
	dup2(vars->save_std_in, 0);
	dup2(vars->save_std_out, 1);
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char *ptr;
	char *line = NULL;
	struct dirent *dir;
	vars.save_std_in = dup(0);
	vars.save_std_out = dup(1);
	envp_copy(envp, &vars);
	ft_putstr_fd("minishell>", 1);
	while(get_next_line(0, &line))
	{
		ft_pars_argument(line, &vars);
		free(line);
		line = NULL;
		ft_putstr_fd("minishell>", 1);
	}
	dup2(vars.save_std_in, 0);
	dup2(vars.save_std_out, 1);	
	return 0;
}