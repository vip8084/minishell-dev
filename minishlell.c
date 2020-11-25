/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishlell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:03 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/25 16:23:26 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

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
	vars.err_flag_export = 0;
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
		ptr_free(&line);
		line = NULL;
		vars.count_call_pipe = 0;
	}
	return 0;
}
