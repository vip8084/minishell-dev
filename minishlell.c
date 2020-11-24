/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishlell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:03 by hmiso             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/11/20 20:58:20 by hmiso            ###   ########.fr       */
=======
/*   Updated: 2020/11/24 12:24:34 by hmiso            ###   ########.fr       */
>>>>>>> hmiso_branch
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char **semicolon(char *line)
{
	int i;
	int flag;
	int j;
	int count;
	char **argv;
	
	i = 0;
	j = 0;
	flag = 0;
	count = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0 && line[i + 1] != '\0')
		{
			flag = 1;
			i++;
		}
		if ((line[i] == '\'' || line[i] == '"') && flag == 1 && line[i + 1] != '\0')
		{
			flag = 0;
			i++;
		}		
		if (flag == 0 && line[i] == ';')
		{
			count++;
		}
		i++;
	}
	argv = malloc(sizeof(char*) * (count + 2));
	i = 0;
	count = 0;
	flag = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0)
		{
			flag = 1;
		}
		else if((line[i] == '\'' || line[i] == '"') && flag == 1)
		{
			flag = 0;
		}
		if (flag == 0 && line[i] == ';')
		{
			argv[count] = ft_substr(line, 0, i);
			line = ft_strdup(&line[i + 1]);
			count++;
			i = 0;
		}
		if (line[i + 1] == '\0')
		{
			argv[count] = ft_substr(line, 0, i + 1);
			count++;
		}
		i++;
	}
	argv[count] = NULL;
	// count = 0;
	// while(argv[count] != NULL)
	// {
	// 	printf("%s\n",argv[count]);
	// 	count++;
	// }
	// exit(0);
	return(argv);
}

char *check_space(char *line)
{
	int i;
	int flag = 0;
	char *ptr;
	char *ptr_for_free = NULL;
	
	ptr = NULL;
	i = 0;
	while(line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0 && line[i + 1] != '\0')
		{
			flag = 1;
			i++;
		}
		if ((line[i] == '\'' || line[i] == '"') && flag == 1 && line[i + 1] != '\0')
		{
			flag = 0;
			i++;
		}		
		if ((line[i] == '>' || line[i] == '|' || line[i] == '<') && flag == 0)
		{
			if (line[i - 1] != ' ' && i != 0 && line[i - 1] != '>')
			{
				//if (ptr != NULL)
				//	ptr_for_free = ptr;
				ptr=ft_substr(line, 0, i);
				//if (ptr_for_free != NULL)
				//	free(ptr_for_free);
				//ptr_for_free = ptr;
				ptr=ft_strjoin(ptr, " ");
				//	free(ptr_for_free);
				//ptr_for_free = ptr;	
				ptr = ft_strjoin(ptr, &line[i]);
				//free(ptr_for_free);
				line = ptr;
			}
			else if(line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '>')
			{
				//if (ptr != NULL)
				//	ptr_for_free = ptr;				
				ptr = ft_substr(line, 0 , i + 1);
				//if (ptr_for_free != NULL)
				//	free(ptr_for_free);
				//ptr_for_free = ptr;				
				ptr = ft_strjoin(ptr, " ");
				//free(ptr_for_free);
				//ptr_for_free = ptr;				
				ptr = ft_strjoin(ptr, &line[i + 1]);
				line = ptr;
			}
			else if (line[i + 2] != ' ' && line[i + 2] != '\0' && line[i + 1] == '>')
			{
				ptr = ft_substr(line, 0 , i + 2);
				ptr = ft_strjoin(ptr, " ");
				ptr = ft_strjoin(ptr, &line[i + 2]);
				line = ptr;
				i++;
			}
		}
		i++;
	}
	// printf("%s\n", line);
	// exit(0);
	return line;
}

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

void free_ptr(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char **environment_variable_substitution(char **comand_line, t_vars *vars)
{
	char *ptr = NULL;
	char *env_var = NULL;
	char *ptr2 = NULL;
	char *ptr_for_free = NULL;
	char *ptr_for_free2 = NULL;
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
				while((comand_line[i][j + 1] != ' ') && comand_line[i][j] != '\0' && (ft_isalpha(comand_line[i][j + 1]) || ft_isdigit(comand_line[i][j + 1])) == 1)
				{
					j++;
				}
				if (comand_line[i][j + 1] == '?' && comand_line[i][j] != '\0')
					j++;
				if (j - k >= 1)
				{
					ptr = ft_substr(comand_line[i], 0, k);
					env_var = ft_substr(comand_line[i], k + 1, j - k);
					ptr2 = ft_substr(comand_line[i], j, 100);
					ptr_for_free = ptr;
					if (ft_strncmp(env_var, "?", 2) == 0)
					{
						ptr_for_free2 = ft_itoa(g_error);
						ptr = ft_strjoin(ptr, ptr_for_free2);
						free_ptr(&ptr_for_free2);
					}
					else
					{	
						ptr_for_free2 = init_patch(vars, env_var);
						ptr = ft_strjoin(ptr, ptr_for_free2);
						free_ptr(&ptr_for_free2);
					}
					free(ptr_for_free);
					ptr_for_free = ptr;	
					ptr = ft_strjoin(ptr, &ptr2[1]);
					free(ptr_for_free);
					free(comand_line[i]);
					comand_line[i] = ptr;
					free_ptr(&env_var);
					free_ptr(&ptr2);
					i = 0;
				}
				else
				{
					j++;
				}
			}
			else
				j++;	
		}
		i++;
		j = 0;
	}
	i = 0;
	// while(comand_line[i] != NULL)
	// {
	// 	printf("%s\n",comand_line[i]);
	// 	i++;
	// }
	// exit(0);
	int *mas_flags;
	while(comand_line[i] != NULL)
	{
		i++;
	}
	if (vars->mas_flags == NULL)
	{
		vars->mas_flags = malloc(sizeof(int) * i + 1);
		i = 0;
		while (comand_line[i] != NULL)
		{
			if(comand_line[i][0] == '"' || comand_line[i][0] == '\'')
				vars->mas_flags[i] = 1;
			else
				vars->mas_flags[i] = 0;
			ptr_for_free2 = comand_line[i];	
			comand_line[i] = delete_quotes(comand_line[i]);
			free_ptr(&ptr_for_free2);
			i++;
		}
		vars->mas_flags[i] = 2;
	}
	else
	{
		j = 0;
		while (vars->mas_flags[j] != 2)
		{
			j++;
		}
		mas_flags= malloc(sizeof(int) * (i + j));
		j = 0;
		while(vars->mas_flags[j] != 2)
		{
			mas_flags[j] = vars->mas_flags[j];
			j++;
		}
		i = 0;
		while (comand_line[i] != NULL)
		{
			if(comand_line[i][0] == '"' || comand_line[i][0] == '\'')
				mas_flags[j] = 1;
			else
				mas_flags[j] = 0;
			ptr_for_free2 = comand_line[i];	
			comand_line[i] = delete_quotes(comand_line[i]);
			free_ptr(&ptr_for_free2);
			i++;
			j++;
		}
		mas_flags[j] = 2;
		free(vars->mas_flags);
		vars->mas_flags = mas_flags;
		i = 0;
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
			count++;
		}
		else
			i++;
	}
	comand_line[count] = NULL;
	environment_variable_substitution(comand_line, vars);
	return (comand_line);
}

char	**move_arguments(char **comand_line, t_vars *vars)
{
	int i;
	int poz;
	char *ptr;
	char *ptr2;
	int flag;
	int flag2=0;

	flag = 0;
	i = 0;
	poz = 0;
	int count = 0;
	while(comand_line[i] != NULL)
	{
		i++;
	}
	while(vars->mas_flags[count] != 2)
	{
		count++;
	}
	count = count - i;
	while (comand_line[poz] != NULL)	
	{
		while (comand_line[i] != NULL)
		{
			if ((ft_strncmp(comand_line[i], ">", 2) == 0  || ft_strncmp(comand_line[i], ">>", 3) == 0 || ft_strncmp(comand_line[i], "<", 2) == 0) && vars->mas_flags[i + count] != 1)
			{
				if ((comand_line[i + 2] != NULL) && (ft_strncmp(comand_line[i + 2], "|", 2) != 0))
				{
					if ((ft_strncmp(comand_line[i + 2], ">", 2) != 0  && ft_strncmp(comand_line[i + 2], ">>", 3) != 0 && ft_strncmp(comand_line[i + 2], "<", 2) != 0))
					{
						ptr = comand_line[i]; // копируем символ редиректа в ячейку
						flag = vars->mas_flags[i + count];
						comand_line[i] = comand_line[i + 2]; // меняем редирект на флаг
						vars->mas_flags[i + count] = vars->mas_flags[i + 2];
						comand_line[i + 2] = comand_line[i + 1]; // меняем флаг на название файла
						vars->mas_flags[i + 2] = vars->mas_flags[i + 1];
						comand_line[i + 1] = ptr; // заменяем название файла на флаг
						vars->mas_flags[i + 1] = flag;
					}
				}
			}
			i++;
		}
		i = 0;
		poz++;
	}
	// exit(0);
	i = 0;
	poz = 0;
	// while(comand_line[i] != NULL)
	// {
	// 	printf("%s ", comand_line[i]);
	// 	printf("%d ", vars->mas_flags[i]);
	// 	i++;
	// }
	// exit(0);	
	while (comand_line[poz] != NULL)	
	{
		while (comand_line[i] != NULL)
		{
			if ((ft_strncmp(comand_line[i], ">", 2) == 0  || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i + count] != 1)
			{
				if ((comand_line[i + 2] != NULL) && ((ft_strncmp(comand_line[i + 2], "|", 2) != 0) && vars->mas_flags[i + 2] != 1))
				{
					if ((ft_strncmp(comand_line[i + 2], "<", 2) == 0) && vars->mas_flags[i + count] != 1)
					{
						ptr = comand_line[i]; // копируем редирект
						flag = vars->mas_flags[i + count];
						ptr2 = comand_line[i + 1]; // копируем название файла
						flag2 = vars->mas_flags[i + 1];
						comand_line[i] = comand_line[i + 2]; // меняем редиректы
						vars->mas_flags[i + count] = vars->mas_flags[i + 2];
						comand_line[i + 1] = comand_line[i + 3]; //меняем названия файлов
						vars->mas_flags[i + 1] = vars->mas_flags[i + 3];
						comand_line[i + 2] = ptr;
						vars->mas_flags[i + 2] = flag;
						comand_line[i + 3] = ptr2;
						vars->mas_flags[i + 3] = flag2;
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
	// 	printf("%d ", vars->mas_flags[i]);
	// 	i++;
	// }
	// exit(0);
	return comand_line;
}

<<<<<<< HEAD
=======
void sig_pipe(int signal)
{
	write(0, "", 0);
	write(0, "\n", 1);
}

char **verification_of_tokens(char **comand_line, t_vars *vars)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	char *line;
	char **new_comand_line;
	char **fre_arr;
	char **argv;
	int fd =0;
	line = NULL;
	while(comand_line[i + 1] != NULL && ft_strncmp(comand_line[i], "|", 2) !=0 && vars->mas_flags[i] == 0)
	{
		i++;
	}
	if ((i == 0 && ft_strncmp(comand_line[i], "|", 2) == 0) && vars->mas_flags[i] == 0)
	{
		ft_putstr_fd("minishell> syntax error near unexpected token `|'\n", 2);
		g_error = 258;
		return NULL;
	}
	if (comand_line[i + 1] != NULL && ((i >= 1 && ft_strncmp(comand_line[i], "|", 2) == 0) && ft_strncmp(comand_line[i + 1], "|", 2) == 0 && vars->mas_flags[i + 1] == 0 && vars->mas_flags[i] == 0))
	{
		ft_putstr_fd("minishell> syntax error near unexpected token `|'\n", 2);
		g_error = 258;
		return NULL;
	}
	i = 0;
	while(comand_line[i + 1] != NULL)
	{
		if (ft_strncmp(comand_line[i], ">", 2) == 0)
			break;
		if (ft_strncmp(comand_line[i], ">>", 3) == 0)
			break;
		if (ft_strncmp(comand_line[i], "<", 2) == 0)
			break;	
		i++;
	}
	if (comand_line[i + 1] != NULL && i >= 1 && (ft_strncmp(comand_line[i + 1], ">", 2) == 0 || ft_strncmp(comand_line[i + 1], "<", 2) == 0 || ft_strncmp(comand_line[i + 1], ">>", 2) == 0) && vars->mas_flags[i + 1] == 0 && vars->mas_flags[i] == 0)
	{
		ft_putstr_fd("minishell> syntax error near unexpected token `>'\n", 2);
		g_error = 258;
		return NULL;
	}
	i = 0;	
	while(comand_line[i + 1] != NULL)
	{
		i++;
	}
	if ((ft_strncmp(">", comand_line[i], 2) == 0 || ft_strncmp(">>", comand_line[i], 3) == 0 || ft_strncmp("<", comand_line[i], 3) == 0) && vars->mas_flags[i] == 0)
	{
		ft_putstr_fd("minishell> syntax error near unexpected token `newline'\n", 2);
		g_error = 258;
		return NULL;
	}
	if (ft_strncmp(comand_line[0], "<", 2) == 0 && vars->mas_flags[0] == 0)
	{
		fd = open(comand_line[1], O_RDONLY);
		if (fd > 0)
		{
			free_two_dimensional_array(comand_line);
			return NULL;
		}
		else
		{
			ft_putstr_fd("minishell> ", 2);
			ft_putstr_fd(comand_line[1], 2);
			ft_putstr_fd(" No such file or directory\n", 2);
			free_two_dimensional_array(comand_line);
			return NULL;	
		}
	}
	if (ft_strncmp("|", comand_line[i], 2) == 0 && vars->mas_flags[i] == 0)
	{
		if ((ft_strncmp(">", comand_line[i - 1], 2) == 0 || ft_strncmp(">>", comand_line[i - 1], 3) == 0 || ft_strncmp("<", comand_line[i - 1], 3) == 0) && vars->mas_flags[i - 1] == 0)
		{
		ft_putstr_fd("minishell> syntax error near unexpected token `newline'\n", 2);
		g_error = 258;
		return NULL;
		}
	//}
		write(1, "> ", 2);
		get_next_line_two(0, &line);
		if (ft_strlen(line) != 0)
		{
			i = 0;
			// printf("%s\n", line);
			line = check_space(line);
			argv = ft_pars(line, vars);
			//fre_arr = argv;
			argv = move_arguments(argv, vars);
			//free_two_dimensional_array(fre_arr);
			while(comand_line[i] != NULL)
			{
				i++;
			}			
			while (argv[j] != NULL)
			{
				j++;
			}
			new_comand_line = malloc(sizeof(char *) * (i + 2 + j));
			i = 0;
			j = 0;
			while(comand_line[i] != NULL)
			{
				new_comand_line[i] = ft_strdup(comand_line[i]);
				i++;
			}
			while(argv[j] != NULL)
			{
				new_comand_line[i] = ft_strdup(argv[j]);
				i++;
				j++;
			}
			new_comand_line[i] = NULL;
			if (ft_strncmp(new_comand_line[i - 1], "|", 2) == 0)
			{
				new_comand_line = verification_of_tokens(new_comand_line, vars);
			}
			free(line);
			free_two_dimensional_array(argv);
			free_two_dimensional_array(comand_line);
			return (new_comand_line);
		}
		else
		{
			return comand_line;
		}
	}
	return comand_line;
}

>>>>>>> hmiso_branch
void	execute_command(char *line, t_vars *vars)
{
	char **comand_line = NULL;
	char *comand_path = NULL;
	char *ptr_free;

	line = check_space(line);
	comand_line = ft_pars(line, vars);
<<<<<<< HEAD
	comand_line = move_arguments(comand_line, vars);
	check_pipe(comand_line, vars);
	check_redirect(comand_line, vars);
	if (vars->count_pipe == 0 && vars->count_redirect == 0)
	{
		if(!(checking_recoded_functions(comand_line, vars)))
		{
			comand_path = check_system_funk(vars, comand_line);
			if (comand_path == NULL)
				comand_path = comand_line[0];
			else
			{	
				comand_path = ft_strjoin(comand_path, "/");
				comand_path = ft_strjoin(comand_path, comand_line[0]);
			}			
			system_funk(comand_path, comand_line, vars);
		}
	}
	else
	{
		ft_conveyor(line, comand_line, vars);
		dup2(vars->save_std_in, 0);
		dup2(vars->save_std_out, 1);
=======
	if (comand_line[0] != NULL)
	{
		// comand_line = move_arguments(comand_line, vars);
		// int i = 0;
		// while(comand_line[i])
		// {
		// 	printf("%d %s\n", vars->mas_flags[i], comand_line[i]);
		// 	i++;
		// }
		if ((comand_line = verification_of_tokens(comand_line, vars)) != NULL)
		{
			// int i = 0;
			// while(comand_line[i] != NULL)
			// {
			// 	printf("%s\n", comand_line[i]);
			// 	i++;
			// }
			// exit(0);
			comand_line = move_arguments(comand_line, vars);
			check_pipe(comand_line, vars);
			check_redirect(comand_line, vars);
			if (vars->count_pipe == 0 && vars->count_redirect == 0)
			{
				if(!(checking_recoded_functions(comand_line, vars)))
				{
					comand_path = check_system_funk(vars, comand_line);
					if (comand_path == NULL)
						comand_path = ft_strdup(comand_line[0]);
					else
					{
						ptr_free = comand_path;
						comand_path = ft_strjoin(comand_path, "/");
						free(ptr_free);
						ptr_free = comand_path;
						comand_path = ft_strjoin(comand_path, comand_line[0]);
						free(ptr_free);
					}	
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
>>>>>>> hmiso_branch
	}
	if(comand_line != NULL && comand_line[0] != NULL)
		free_two_dimensional_array(comand_line);
	if (comand_path != NULL)	
		free(comand_path);
}

void	ft_pars_argument(char *line, t_vars *vars)
{
		int	i = 0;
		char **argv;

		argv = semicolon(line);
		while (argv[i] != NULL)
		{
			if (ft_strlen(argv[i]) != 0)
				execute_command(argv[i], vars);
			i++;
		}
		free_two_dimensional_array(argv);
}

void	ft_signals(int signal)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "\n", 1);
	ft_putstr_fd("minishell>", 1);
}

void	ft_signal(int signal)
{
	write(1, "\b\b  \b\b", 6);
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char *ptr;
	char *line = NULL;
	int i = 0;
	vars.count_call_pipe = 0;
	vars.flag_redirect = 0;
	errno = 0;
	g_error = 0;
	g_signal =0;
	vars.err_flag = 0;
	vars.cd_flag = 0;
	vars.mas_flags=NULL;
	vars.save_std_in = dup(0);
	vars.save_std_out = dup(1);
	envp_copy(envp, &vars);
	vars.path = init_patch(&vars, "PATH");
	ft_putstr_fd("minishell>", 1);
	signal(SIGINT, &ft_signals);
	signal(SIGQUIT, &ft_signal);
	while((i = get_next_line(0, &line)) > 0)
	{
		if(ft_strlen(line) == 0)
		{
			ft_putstr_fd("minishell>", 1);
		}
		ft_pars_argument(line, &vars);
		if(ft_strlen(line) != 0)
		{
			if(g_signal == 0)
				ft_putstr_fd("minishell>", 1);
			else
			{
				g_signal = 0;
			}
		}
		free(line);
		line = NULL;
		vars.count_call_pipe = 0;
		free(vars.mas_flags);
		vars.mas_flags = NULL;
	}
	return 0;
}
