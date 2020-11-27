/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:17:09 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/27 21:12:58 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	ft_pars_argument(char *line, t_vars *vars)
{
		int	i = 0;
		char **argv;

		if (line[0] == ';')
		{
			syntax_error(line);
			return;
		}
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
