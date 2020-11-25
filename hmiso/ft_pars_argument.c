/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:17:09 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 13:17:19 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	ft_pars_argument(char *line, t_vars *vars)
{
		int	i = 0;
		char **argv;

		argv = semicolon(line);
		// for (i = 0; argv[i] != NULL; i++)
		// {
		// 	printf("%s\n", argv[i]);
		// }
		// exit(0);
		while (argv[i] != NULL)
		{
			if (ft_strlen(argv[i]) != 0)
					execute_command(argv[i], vars);
			i++;
		}
		free_two_dimensional_array(argv);
}
