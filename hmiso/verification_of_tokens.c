/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_of_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:08:39 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/29 15:17:55 by hmiso            ###   ########.fr       */
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
		syntax_error("|");
		free_two_dimensional_array(comand_line);
		return NULL;
	}
	if (comand_line[i + 1] != NULL && ((i >= 1 && ft_strncmp(comand_line[i], "|", 2) == 0) && ft_strncmp(comand_line[i + 1], "|", 2) == 0 && vars->mas_flags[i + 1] == 0 && vars->mas_flags[i] == 0))
	{
		syntax_error("|");
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
		syntax_error(">");
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
		syntax_error("newline");
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
			free_two_dimensional_array(comand_line);
			syntax_error("newline");
			return NULL;
	}
	return comand_line;
}