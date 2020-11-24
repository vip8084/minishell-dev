/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:52:35 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/24 22:26:00 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void check_line_value(char **line)
{
    int i;
    int length;
    char *temp;

    i = 0;
    temp = NULL;
    length = ft_strlen(*line);
    if (length > 1 && (*line)[length - 1] == '=')
    {
      temp = *line;
      *line = ft_strjoin(*line, "\"\"");
	  //free(temp);
      temp = NULL;
    }
}

void	export_out(t_vars *vars, char **line)//команда export добавление + вывод
{
	int i;
	int count = 0;
	char **argv;

	i = 1;
	ft_sort_str_arr(vars->envp_copy);
	if(line[i] != NULL)
	{
		check_line_value(&line[i]);	
		argv = &line[i];
		if (!check_valid_id(line[i]))
		{
			id_error(line[i], vars);
			vars->err_flag_export = 1;
			return;
		}
		argv = check_duplicate(argv);
		update_envp(argv, vars);
	}
	else
	{	
		while(vars->envp_copy[i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			argv = ft_split(vars->envp_copy[i], '=');
			ft_putstr_fd(argv[0], 1);
			if(argv[1] != NULL)
			{
				ft_putchar_fd('=', 1);
				if (!ft_strncmp(argv[1], """", 3))
					ft_putchar_fd('"', 1);
				ft_putstr_fd(argv[1], 1);
				if (!ft_strncmp(argv[1], """", 3))
					ft_putchar_fd('"', 1);				
			}
			ft_putchar_fd('\n', 1);
			free_two_dimensional_array(argv);
			i++;
		}
	}
}
//выводит export
// течет хз на каком этапе
