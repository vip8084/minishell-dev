/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:54:48 by hmiso             #+#    #+#             */
/*   Updated: 2020/10/30 16:20:36 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

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

char		**check_duplicate(char **argv) // проверка на наличие добавляемой переменной в переменных среды
{
	int i = 0;
	int j = 1;
	int count = 0;
	int count_2 = 0;
	int count_3 = 0;
	char **new_argv;
	while(argv[count_3] != NULL)
	{
		count_3++;
	}
	if (count_2 == 1)
		return argv;
	i = 0;
	count_2 = 0;
	while(argv[i] != NULL)
	{
		while(j < count_3)
		{
			if(argv[i] != NULL && argv[j] != NULL &&ft_strlen(argv[i]) == ft_strlen(argv[j]))
			{
				if(ft_strncmp(argv[i], argv[j], ft_strlen(argv[i])) == 0)
				{
					count++;
				}
			}
			j++;
		}
		if(count > 1)
		{
			argv[i] = NULL;
			count_2++;
		}
		count=0;
		i++;
		j = 0;
	}
	new_argv = malloc(sizeof(char*) *(i - count_2 + 1));
	count = 0;
	j = 0;
	while(count < i)
	{
		if(argv[count] != NULL)
		{
			new_argv[j] = ft_strdup(argv[count]);
			free(argv[count]);
			j++;
		}
		count++;
	}
	new_argv[j] = NULL;
	return new_argv;
}

int		ft_unset(t_vars *vars, char *str)//удаление переменной из переменных окружения команда unset 
{
	int count = 0;
	int count_env = 0;
	char **env_new;
	char **argv;
	int	 i = 0;
	int j = 0;
	int	 flag= 0;
	while(vars->envp_copy[count_env] != NULL)
		count_env++;
	while (vars->envp_copy[count] != NULL)
	{
		argv = ft_split(vars->envp_copy[count], '=');
		if(ft_strlen(argv[0]) == ft_strlen(str))
		{
			if(ft_strncmp(argv[0], str, ft_strlen(argv[0])) == 0)
			{
				free(vars->envp_copy[count]);
				vars->envp_copy[count]=NULL;
				flag++;
			}
		}
		count++;
	}
	count = 0;
	i = 0;
	if(flag > 0)
	{
		env_new = malloc(sizeof(char**) * count_env);
		while(i < count_env)
		{
			if(vars->envp_copy[i] != NULL)
			{
				env_new[j] = ft_strdup(vars->envp_copy[i]);
				j++;
			}
			i++;
		}
		vars->envp_copy = env_new;
	}
	return ft_strlen(str);
}

void	update_envp(char **str, t_vars *vars)//добаавление новой переменной в переменные окружения
{
	int i = 0;
	int j = 0;
	char **new_envp;
	char **ar_1;
	char **ar_2;
	int count = 0;
	int flag = 0;
	char *ptr;
	while(str[i] != NULL)
	{
		i++;
	}
	while(j < i)
	{
		ar_2 = ft_split(str[j], '=');
		while (vars->envp_copy[count] != NULL)
		{
			ar_1 = ft_split(vars->envp_copy[count], '=');
			if(ft_strlen(ar_1[0])  == ft_strlen(ar_2[0]))
			{
				if(ft_strncmp(ar_1[0],ar_2[0], ft_strlen(ar_1[0])) == 0)
				{
					if(ar_2[1] != NULL)
					{
						free(vars->envp_copy[count]);
						vars->envp_copy[count]=ft_strjoin(ar_2[0], "=");
						ptr = vars->envp_copy[count];
						vars->envp_copy[count]=ft_strjoin(vars->envp_copy[count], ar_2[1]);
						free(ptr);
					}
					free(str[j]);
					str[j] = NULL;
				}
			}
			free_two_dimensional_array(ar_1);
			count++;
		}
		free_two_dimensional_array(ar_2);
		count = 0;
		j++;
	}
	count = i;
	i = 0;
	while (flag < count)
	{
		if(str[flag] != NULL)
			i++;
		flag++;
	}
	j = 0;
	while(vars->envp_copy[j] != NULL)
	{
		j++;
	}
	new_envp = malloc(sizeof(char *) *(j + i + 1));
	j = 0;
	i = 0;
	while(vars->envp_copy[i] != NULL)
	{
		new_envp[i] = vars->envp_copy[i];
		i++;
	}
	while(j < count)
	{
		if(str[j] != NULL)
		{
			new_envp[i] = str[j];
			i++;
		}
		j++;
	}
	new_envp[i] = NULL;
	free(vars->envp_copy);
	envp_copy(new_envp, vars);
	free_two_dimensional_array(new_envp);
}

int		export_out(t_vars *vars, char **line)//команда export добавление + вывод
{
	int i;
	int count = 0;
	char **argv;

	i = 1;
	if(line[i] != '\0')
	{
		argv = &line[i];
		argv = check_duplicate(argv);
		update_envp(argv, vars);
		while(line[i] != NULL)
			i++;
		return(i);	
	}
	else
	{
		i = 0;
		while(vars->envp_copy[i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			argv = ft_split(vars->envp_copy[i], '=');
			ft_putstr_fd(argv[0], 1);
			if(argv[1] != NULL)
			{
				ft_putchar_fd('=', 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(argv[1], 1);
				ft_putchar_fd('"', 1);				
			}
			ft_putchar_fd('\n', 1);
			free_two_dimensional_array(argv);
			i++;
		}
		return 1;	
	}
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

int			ft_echo(char **line, t_vars *vars)//команда echo 
{
	int i;
	i = 1;
	while(line[i] != NULL)
	{
		if (line[i][0] == '$')
		{
			ft_putstr_fd(init_patch(vars, &line[i][1]), 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);				
		}
		else
		{
			ft_putstr_fd(line[i], 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);			
		}
	}
	write(1, "\n", 1);
	return (i);
}
int			ft_echo_n(char **line, t_vars *vars)//вывод без переноса строки
{
	int i;

	i = 2;
	while(line[i] != NULL)
	{
		if (line[i][0] == '$')
		{
			ft_putstr_fd(init_patch(vars, &line[i][1]), 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);			
		}
		else
		{
			ft_putstr_fd(line[i], 1);
			i++;
			if(line[i] != NULL)
				write(1, " ", 1);			
		}
	}
	return (i);
}

int			ft_env(t_vars *vars)//вывод env команда env
{
	int i = 0;
	char **argv;
	while(vars->envp_copy[i] != NULL)
	{
		argv=ft_split(vars->envp_copy[i], '=');
		if(argv[1] != NULL)
		{
			ft_putstr_fd(argv[0], 1);
			ft_putchar_fd('=',1);
			ft_putendl_fd(argv[1], 1);			
		}
		i++;
		free_two_dimensional_array(argv);
	}
	return 1;
}

int			ft_ls(char *line, t_vars *vars)
{
	char **argv;
	int count;
	int status;
	pid_t pid;
	int i = 0;
	int j = 0;
	argv = ft_split(line, ' ');
	char *ptr2= "/bin/";
	char *ptr = ft_strjoin(ptr2, argv[0]);
	check_system_funk(vars, argv[0]);
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

// void		ft_pars_argument(char *line,  t_vars *vars) // здесь должен появится парсер)
// {
// 	int i = 0;
// 	char *ptr = NULL;
// 	char **argv;
// 	int count = 1;
// 	char **comand_mas;

// 	comand_mas = ft_split(line, ' ');
// 	while(comand_mas[i] != NULL)
// 	{
// 		if (ft_strncmp(&line[i], "cd", 2) == 0)
// 		{
// 			if(line[i + 2] == ' ')
// 				i++;
// 			i +=2;	
// 			chdir(&line[i]);	
// 		}
// 		else if (ft_strncmp(&line[i], "pwd", 3) == 0)
// 		{
// 			ft_putstr_fd((ptr = getcwd(NULL,0)), 1);
// 			write(1, "\n",1);
// 			i += 3;
// 			free(ptr);
// 			ptr = NULL;
// 		}
// 		else if (ft_strncmp(&line[i], "echo -n", 7) == 0)
// 		{
// 			i+= ft_echo_n(&line[i]);
// 		}		
// 		else if (ft_strncmp(&line[i], "echo", 4) == 0)
// 		{
// 			i+= ft_echo(&line[i], vars);
// 		}	
// 		else if (ft_strncmp(&line[i], "ls", 2) == 0)
// 		{
// 			i += check_system_funk(vars, &line[i]);
// 		}
// 		else if (ft_strncmp(&line[i], "env", 3) == 0)
// 		{
// 			i += ft_env(vars);
// 		}
// 		else if (ft_strncmp(&line[i], "export", 6) == 0)
// 		{
// 			i += export_out(vars, &line[i]);
// 		}
// 		else if (ft_strncmp(&line[i], "exit", 5) == 0)
// 		{
// 			exit(0);
// 		}		
// 		else if (ft_strncmp(&line[i], "unset", 5) == 0)
// 		{
// 			argv=ft_split(&line[i], ' ');
// 			while(argv[count] != NULL)
// 			{
// 				i += ft_unset(vars, argv[count]);
// 				count++;
// 			}
// 			count = 1;
// 			free_two_dimensional_array(argv);
// 		}
// 		else
// 			i++;
// 	}
// }

void		ft_pars_argument(char *line,  t_vars *vars) // здесь должен появится парсер)
{
	int i = 0;
	char *ptr = NULL;
	char **argv;
	int count = 1;
	char **comand_mas;

	comand_mas = ft_split(line, ' ');
	while(comand_mas[i] != NULL)
	{
		if (ft_strncmp(comand_mas[i], "cd", 2) == 0)
		{				
			if(comand_mas[i + 1] != NULL)
			{
				chdir(comand_mas[i + 1]);
				i += 2;
			}
			else
			{
				chdir(init_patch(vars, "HOME"));
				i++;
			}
		}
		else if (ft_strncmp(comand_mas[i], "pwd", 3) == 0)
		{
			ft_putstr_fd((ptr = getcwd(NULL,0)), 1);
			write(1, "\n",1);
			i++;
			free(ptr);
			ptr = NULL;
		}
		else if ((ft_strncmp(comand_mas[i], "echo", 4) == 0) && (comand_mas[i + 1] != NULL) && (ft_strncmp(comand_mas[i + 1], "-n", 2)) == 0)
		{
			i+= ft_echo_n(&comand_mas[i], vars);
		}
		else if (ft_strncmp(comand_mas[i], "echo", 4) == 0)
		{
			i+= ft_echo(&comand_mas[i], vars);
		}	
		else if (ft_strncmp(comand_mas[i], "env", 3) == 0)
		{
			i += ft_env(vars);
		}
		else if (ft_strncmp(comand_mas[i], "export", 6) == 0)
		{
			i += export_out(vars, &comand_mas[i]);
		}
		else if (ft_strncmp(comand_mas[i], "exit", 5) == 0)
		{
			exit(0);
		}
		else if (ft_strncmp(comand_mas[i], "unset", 5) == 0)
		{
			argv = &comand_mas[i];
			while(argv[count] != NULL)
			{
				i += ft_unset(vars, argv[count]);
				count++;
			}
			count = 1;
			free_two_dimensional_array(argv);
		}	
		else
		{
			if(check_system_funk(vars, &line[i]) == 0)
				ft_putstr_fd("Comand not found\n", 1);
			i++;
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