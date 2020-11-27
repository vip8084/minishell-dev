/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_of_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:08:39 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/27 17:02:14 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

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
	char *fre_ptr;
	int fd =0;
	line = NULL;
	while(comand_line[i + 1] != NULL && ft_strncmp(comand_line[i], "|", 2) !=0 && vars->mas_flags[i] == 0)
	{
		i++;
	}
	if ((i == 0 && ft_strncmp(comand_line[i], "|", 2) == 0) && vars->mas_flags[i] == 0)
	{
		ft_putstr_fd("minishell>syntax error near unexpected token `|'\n", 2);
		g_error = 258;
		free_two_dimensional_array(comand_line);
		return NULL;
	}
	if (comand_line[i + 1] != NULL && ((i >= 1 && ft_strncmp(comand_line[i], "|", 2) == 0) && ft_strncmp(comand_line[i + 1], "|", 2) == 0 && vars->mas_flags[i + 1] == 0 && vars->mas_flags[i] == 0))
	{
		ft_putstr_fd("minishell>syntax error near unexpected token `|'\n", 2);
		g_error = 258;
		free_two_dimensional_array(comand_line);
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
		ft_putstr_fd("minishell>syntax error near unexpected token `>'\n", 2);
		g_error = 258;
		free_two_dimensional_array(comand_line);
		return NULL;
	}
	i = 0;	
	while(comand_line[i + 1] != NULL)
	{
		i++;
	}
	if ((ft_strncmp(">", comand_line[i], 2) == 0 || ft_strncmp(">>", comand_line[i], 3) == 0 || ft_strncmp("<", comand_line[i], 3) == 0) && vars->mas_flags[i] == 0)
	{
		ft_putstr_fd("minishell>syntax error near unexpected token `newline'\n", 2);
		g_error = 258;
		free_two_dimensional_array(comand_line);
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
		// if ((ft_strncmp(">", comand_line[i - 1], 2) == 0 || ft_strncmp(">>", comand_line[i - 1], 3) == 0 || ft_strncmp("<", comand_line[i - 1], 3) == 0) && vars->mas_flags[i - 1] == 0)
		// {
			free_two_dimensional_array(comand_line);
			ft_putstr_fd("minishell>syntax error near unexpected token `newline'\n", 2);
			g_error = 258;
			return NULL;
	}
		// }
	// //}
	// 	write(1, "> ", 2);
	// 	get_next_line_two(0, &line);
	// 	if (ft_strlen(line) != 0)
	// 	{
	// 		i = 0;
	// 		// printf("%s\n", line);
	// 		fre_ptr = line;
	// 		line = check_space(line);
	// 		ptr_free(&fre_ptr);
	// 		argv = ft_pars(line, vars);
	// 		//fre_arr = argv;
	// 		argv = move_arguments(argv, vars);
	// 		//free_two_dimensional_array(fre_arr);
	// 		while(comand_line[i] != NULL)
	// 		{
	// 			i++;
	// 		}			
	// 		while (argv[j] != NULL)
	// 		{
	// 			j++;
	// 		}
	// 		new_comand_line = malloc(sizeof(char *) * (i + 2 + j));
	// 		i = 0;
	// 		j = 0;
	// 		while(comand_line[i] != NULL)
	// 		{
	// 			new_comand_line[i] = ft_strdup(comand_line[i]);
	// 			i++;
	// 		}
	// 		while(argv[j] != NULL)
	// 		{
	// 			new_comand_line[i] = ft_strdup(argv[j]);
	// 			i++;
	// 			j++;
	// 		}
	// 		new_comand_line[i] = NULL;
	// 		if (ft_strncmp(new_comand_line[i - 1], "|", 2) == 0)
	// 		{
	// 			new_comand_line = verification_of_tokens(new_comand_line, vars);
	// 		}
	// 		ptr_free(&line);
	// 		free_two_dimensional_array(argv);
	// 		free_two_dimensional_array(comand_line);
	// 		return (new_comand_line);
	// 	}
	// 	else
	// 	{
	// 		return comand_line;
	// 	}

	return comand_line;
}