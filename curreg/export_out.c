/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:52:35 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/21 12:19:21 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	export_out(t_vars *vars, char **line)//команда export добавление + вывод
{
	int i;
	int count = 0;
	char **argv;

	i = 1;
	if(line[i] != NULL)
	{
		argv = &line[i];
		argv = check_duplicate(argv);
		update_envp(argv, vars);
		while(line[i] != NULL)
			i++;
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
	}
}
//выводит export
// течет хз на каком этапе
