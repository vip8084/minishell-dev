/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:56:20 by hmiso             #+#    #+#             */
/*   Updated: 2020/10/30 19:28:27 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char	**ft_join_mas(char *str1, char *str2)
{
	char **mas;

	mas = malloc(sizeof(char *) * 3);
	mas[0] = ft_strdup(str1);
	mas[1] = ft_strdup(str2);
	mas[2] = NULL;
	return mas;
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

int			system_funk(char *path, char **argv, t_vars *vars)//вызов системных функций
{
	int count;
	int status;
	pid_t pid;
	int i = 0;
	int j = 0;
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
					char **str2= ft_split(str, ' ');
					system_funk(path[i], str2, vars);
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
	char **comand_to_pipe;
	check_pipe(comand_mas, vars);
	if (vars->count_pipe > 0)
	{
		while(comand_mas[i] != NULL)
		{
			if ((ft_strncmp(comand_mas[i], "|", 1) == 0) && (vars->count_pipe > 1))
			{
				if(comand_mas[i - 1][0] == '-')
				{
					comand_to_pipe = ft_join_mas(comand_mas[i - 2], comand_mas[i - 1]);
					ft_pipe(init_patch(vars, "PATH"), comand_to_pipe, vars);
				}
				if(comand_mas[i + 2][0] == '-')
				{
					comand_to_pipe = ft_join_mas(comand_mas[i + 1], comand_mas[i + 2]);
					ft_pipe(init_patch(vars, "PATH"), comand_to_pipe, vars);
					i+= 2;
				}
				vars->count_pipe--;
				i++;
			}
			if ((ft_strncmp(comand_mas[i], "|", 1) == 0) && (vars->count_pipe == 1))
			{
				if(comand_mas[i - 1][0] == '-')
				{
					comand_to_pipe = ft_join_mas(comand_mas[i - 2], comand_mas[i - 1]);
					ft_pipe("/bin/ls", comand_to_pipe, vars);
				}
				comand_to_pipe = ft_join_mas(comand_mas[i + 1], comand_mas[i + 2]);
				check_system_funk(vars, comand_to_pipe);
				vars->count_pipe--;
				i+= 2;
			}
			i++;		
		}
	}
	else 
	{
		while(comand_mas[i] != NULL)
		{
			if (check_system_funk(vars, &line[i]) > 0)
				i++;
			else if (ft_strncmp(comand_mas[i], "exit", 5) == 0)
			{
				exit(0);
			}
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char *ptr;
	char *line = NULL;
	struct dirent *dir;
	envp_copy(envp, &vars);
	ft_putstr_fd("minishell>", 1);
	while(get_next_line(0, &line))
	{
		ft_pars_argument(line, &vars);
		free(line);
		line = NULL;
		ft_putstr_fd("minishell>", 1);
	}
	return 0;
}