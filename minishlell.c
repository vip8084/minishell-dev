/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishlell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:03 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/17 17:06:05 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char *delete_quotes(char *line)
{
	int i;
	int flag;
	
	i = 0;
	int count = 0;
	flag = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '"' && flag == 0)
		{
			line[i] = 10;
			flag = 1;
			i++;
		}
		else if(line[i] == '\'' && flag == 0)
		{
			line[i] = 10;
			flag = 2;
			i++;
		}
		else if(line[i] == '\'' && flag == 2)
		{
			line[i] = 10;
			flag = 0;
			i++;
		}		
		else if(line[i] == ' ' && flag == 0)
		{
			line[i] = 12;
			i++;
		}
		else if(line[i] == '"' && flag == 1)
		{
			line[i] = 10;
			flag = 0;
			i++;
		}
		else
			i++;
	}
	char *line_dubl;
	line_dubl = ft_calloc((i + 1), sizeof(char));
	i = 0;
	flag = 0;
	count = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"' ) && flag == 0)
		{
			flag = 1;
			line_dubl[count] = line[i];
			count++;
			i++;
		}
		else if ((line[i] == '\'' || line[i] == '"') && flag == 1)
		{
			flag = 0;
			line_dubl[count] = line[i];
			count++;
			i++;			
		}
		else
		{	
			if(flag != 1 || line[i] != 12)
			{
				if (line[i] != 10)
				{				
					line_dubl[count] = line[i];
					count++;
				}
			}
			i++;
		}
	}
	return line_dubl;
}

char **environment_variable_substitution(char **comand_line, t_vars *vars)
{
	char *ptr;
	char *env_var;
	char *ptr2;
	int i;
	int j;
	int flag;
	int k;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	while(comand_line[i] != NULL)
	{
		while (comand_line[i][j] != '\0')
		{
			if (comand_line[i][j] == '"')
			{
				if (flag == 0 && comand_line[i][j] == '"')
					flag = 2;
				else if (flag == 2 && comand_line[i][j] == '"')
					flag = 0;
			}
			if (comand_line[i][j] == '\'' && flag != 2)
			{
				if (flag == 0 && comand_line[i][j] == '\'')
					flag = 1;
				else if (flag == 1 && comand_line[i][j] == '\'')
					flag = 0;
			}
			if (comand_line[i][j] == '$' && flag != 1)
			{
				k = j;
				while((comand_line[i][j + 1] != ' ') && comand_line[i][j] != '\0' && (comand_line[i][j + 1] != '"' && comand_line[i][j + 1] != '\'' && comand_line[i][j + 1] != '$'))
				{
					j++;
				}
				ptr = ft_substr(comand_line[i], 0, k);
				env_var = ft_substr(comand_line[i], k + 1, j - k);
				ptr2 = ft_substr(comand_line[i], j, 100);
				ptr = ft_strjoin(ptr, (init_patch(vars, env_var)));
				ptr = ft_strjoin(ptr, &ptr2[1]);
				// printf("%s\n", ptr);
				comand_line[i] = ptr;
			}
			else
				j++;	
		}
		i++;
		j = 0;
	}
	i = 0;
	while (comand_line[i] != NULL)
	{
		comand_line[i] = delete_quotes(comand_line[i]);	
		i++;
	}
	return comand_line;
}

char **count_comands(char *line)
{
	int i;
	int count;
	char **comand_line;
	int flag = 0;

	comand_line = NULL;
	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			count++;
			while((line[i] != ' ' || flag == 1 || flag == 2) && line[i] != '\0')
			{
				if(line[i] == '"' || line[i] == '\'')
				{
					if (flag == 0 && line[i] == '"')
						flag = 1;
					else if (flag == 1 && line[i] == '"')
						flag = 0;
					else if (flag == 0 && line[i] == '\'')
						flag = 2;
					else if (flag == 2 && line[i] == '\'')
						flag = 0;		
				}
				i++;
			}
		}
		else
		{
			i++;
		}	
	}
	comand_line = malloc(sizeof(char *) * (count + 1));
	return (comand_line);
}

char	**ft_pars(char *line, t_vars *vars)
{
	int i;
	int j;
	int count;
	char **comand_line;
	int flag = 0;

	count = 0;
	i = 0;
	j = 0;
	comand_line = count_comands(line);
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			j = i;
			while((line[i] != ' ' || flag == 1 || flag == 2) && line[i] != '\0')
			{
				if(line[i] == '"' || line[i] == '\'')
				{
					if (flag == 0 && line[i] == '"')
						flag = 1;
					else if (flag == 1 && line[i] == '"')
						flag = 0;
					else if (flag == 0 && line[i] == '\'')
						flag = 2;
					else if (flag == 2 && line[i] == '\'')
						flag = 0;		
				}
				i++;
			}
			comand_line[count] = ft_substr(line, j, i - j);
			// printf("%s\n", comand_line[count]);
			count++;
		}
		else
			i++;
	}
	
	comand_line[count] = NULL;
	// exit(0);
	environment_variable_substitution(comand_line, vars);
	return (comand_line);
}

char	**move_arguments(char **comand_line)
{
	int i;
	int poz;
	char *ptr;
	char *ptr2;
	int flag;

	flag = 0;
	i = 0;
	poz = 0;
	while (comand_line[poz] != NULL)	
	{
		while (comand_line[i] != NULL)
		{
			if (ft_strncmp(comand_line[i], ">", 2) == 0  || ft_strncmp(comand_line[i], ">>", 3) == 0 || ft_strncmp(comand_line[i], "<", 2) == 0)
			{
				if ((comand_line[i + 2] != NULL) && (ft_strncmp(comand_line[i + 2], "|", 2) != 0))
				{
					if ((ft_strncmp(comand_line[i + 2], ">", 2) != 0  && ft_strncmp(comand_line[i + 2], ">>", 3) != 0 && ft_strncmp(comand_line[i + 2], "<", 2) != 0))
					{
						ptr = comand_line[i]; // копируем символ редиректа в ячейку
						comand_line[i] = comand_line[i + 2]; // меняем редирект на флаг
						comand_line[i + 2] = comand_line[i + 1]; // меняем флаг на название файла
						comand_line[i + 1] = ptr; // заменяем название файла на флаг
					}
				}
			}
			i++;
		}
		i = 0;
		poz++;
	}
	i = 0;
	poz = 0;
	while (comand_line[poz] != NULL)	
	{
		while (comand_line[i] != NULL)
		{
			if (ft_strncmp(comand_line[i], ">", 2) == 0  || ft_strncmp(comand_line[i], ">>", 3) == 0)
			{
				if ((comand_line[i + 2] != NULL) && (ft_strncmp(comand_line[i + 2], "|", 2) != 0))
				{
					if (ft_strncmp(comand_line[i + 2], "<", 2) == 0)
					{
						ptr = comand_line[i]; // копируем редирект 
						ptr2 = comand_line[i + 1]; // копируем название файла
						comand_line[i] = comand_line[i + 2]; // меняем редиректы
						comand_line[i + 1] = comand_line[i + 3]; //меняем названия файлов
						comand_line[i + 2] = ptr;
						comand_line[i + 3] = ptr2;
					}
				}
			}
			i++;
		}
		i = 0;
		poz++;
	}
	i = 0;
	poz = 0;
	// while(comand_line[i] != NULL)
	// {
	// 	printf("%s ", comand_line[i]);
	// 	i++;
	// }
	// exit(0);
	return comand_line;
}

void	ft_pars_argument(char *line, t_vars *vars)
{
		char **comand_line;
		char **line_pipe;
		char *comand_path;
		char **argv;
		char *ptr;
		int mas[2];
		int count = 0;
		int	i = 0;
		int t = 0;
		
		// line=ft_pars(line);
		// comand_line = ft_split(line, ' ');
		comand_line = ft_pars(line, vars);
		comand_line = move_arguments(comand_line);
		check_pipe(comand_line, vars);
		check_redirect(comand_line, vars);
		if (vars->count_pipe == 0 && vars->count_redirect == 0)
		{
			if(!(checking_recoded_functions(comand_line, vars)))
			{
				comand_path = check_system_funk(vars, comand_line);
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, comand_line[0]);			
				system_funk(comand_path, comand_line, vars);
			}
		}
		else
		{
			ft_conveyor(line, comand_line, vars);
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
	vars.count_call_pipe = 0;
	vars.flag_redirect = 0;

	errno = 0;
	g_error = 0;
	vars.err_flag = 0;
	vars.cd_flag = 0;
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
		vars.count_call_pipe = 0;
	}
	return 0;
}