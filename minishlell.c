/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishlell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:03 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/09 10:37:46 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char	**move_arguments(char **comand_line)
{
	int i;
	int poz;
	char *ptr;
	int flag;

	flag = 0;
	i = 0;
	poz = 0;
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

		comand_line = ft_split(line, ' ');
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