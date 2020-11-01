/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishlell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:03 by hmiso             #+#    #+#             */
/*   Updated: 2020/10/31 20:57:09 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void    ft_pipe(char *path, char **comand, t_vars *vars)
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
		if ((status = execve(path, comand, vars->envp_copy)) == -1)
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

int			system_funk(char *path, char **argv, t_vars *vars)//вызов системных функций
{
	int count;
	int status;
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		if ((status = execve(path, argv, vars->envp_copy)) == -1)
			exit(WEXITSTATUS(status));
	}
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		g_exit_code = WEXITSTATUS(status);
	}
	return 0;
}

char 			*check_system_funk(t_vars *vars, char **str) // проверяет наличие испалняеомего файла по путям PATH
{
	DIR *dir;
    struct dirent *st;
	char **path;
	char **arg;
	int i = 0;
	int flag = 0;

	path = ft_split(init_patch(vars, "PATH"), ':');
	arg = str;
	char **argv = str;
	while(path[i] != NULL)
	{
		dir = opendir(path[i]);
		while((st = readdir(dir)) != NULL)
		{
			if (ft_strlen(st->d_name) == ft_strlen(argv[0]))
			{
				if ((ft_strncmp(st->d_name, str[0], ft_strlen(argv[0]))) == 0)
				{
					char **str2= str;
					//system_funk(path[i], str2, vars);
					return(path[i]);
					flag = 1;
				}
			}
		}
		i++;
	}
	return 0;
}

void	check_pipe(char **comand_mas, t_vars *vars)
{
	int i = 0;
	vars->count_pipe = 0;
	
	while(comand_mas[i] != NULL)
	{
		if(ft_strncmp(comand_mas[i], "|", 1) == 0)
		{
			vars->count_pipe++;
		}
		i++;
	}
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

void	ft_pars_argument(char *line, t_vars *vars)
{
		char **comand_line;
		char **line_pipe;
		char *comand_path;
		int	i = 0;
		int t = 0;

		comand_line = ft_split(line, ' ');
		check_pipe(comand_line, vars);
		if (vars->count_pipe == 0)
		{
			comand_path = check_system_funk(vars, comand_line);
			comand_path = ft_strjoin(comand_path, "/");
			comand_path = ft_strjoin(comand_path, comand_line[0]);			
			system_funk(comand_path, comand_line, vars);
		}
		else
		{
			line_pipe = ft_split(line, '|');
			while (line_pipe[i] != NULL)
			{
				if (vars->count_pipe - i > 0)
				{
					comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
					comand_line = ft_split(line_pipe[i], ' ');
					comand_path = ft_strjoin(comand_path, "/");
					comand_path = ft_strjoin(comand_path, comand_line[0]);
					ft_pipe(comand_path, comand_line, vars);
					i++;
				}
				else
				{
					comand_line = ft_split(line_pipe[i], ' ');
					comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
					comand_path = ft_strjoin(comand_path, "/");
					comand_path = ft_strjoin(comand_path, comand_line[0]);
					system_funk(comand_path, comand_line, vars);
					i++;
				}
			}
			dup2(vars->save_std_in, 0);
			dup2(vars->save_std_out, 1);
		}
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char *ptr;
	char *line = NULL;
	int i = 0;
	struct dirent *dir;
		vars.save_std_in = dup(0);
	vars.save_std_out = dup(1);
	envp_copy(envp, &vars);
	vars.path = init_patch(&vars, "PATH");
	ft_putstr_fd("minishell>", 1);
	while((i = get_next_line(0, &line)) > 0)
	{
		ft_pars_argument(line, &vars);
		free(line);
		line = NULL;
		ft_putstr_fd("minishell>", 1);
	}
	return 0;
}