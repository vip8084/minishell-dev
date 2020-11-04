/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:07:14 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/04 19:12:17 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void		ft_redirects(char *path, char **comand, char **mas_redirektion, t_vars *vars)
{
    pid_t pid;
    int mas[2];
    int status;
    int i;
	int fd;
	char **comand_s;
	char *name_file;

	i = 0;
	// while(vars->count_redirect > 0)
	// {
	// 	name_file = ft_strtrim(comand[i], " ");
	// 	fd = open(name_file, O_WRONLY | O_CREAT, 0666);
	// 	if(vars->count_redirect > 1)
	// 		close(fd);
	// 	i++;
	// 	vars->count_redirect--;
	// }

	while(mas_redirektion[i] != NULL)
	{
		fd = open(mas_redirektion[i], O_WRONLY | O_CREAT, 0666);
		if(vars->count_redirect > 1)
			close(fd);
		i++;
		if (vars->count_redirect > 0)
			vars->count_redirect--;
	}
    pipe(mas);
    pid = fork();
    if (pid == 0)
    {
        close(mas[0]);
        dup2(fd, 1);
        close(mas[1]);
		if(checking_recoded_functions(comand, vars))
		{
			exit (0);// забирать значение эрно из внутренних функций и передавать сюда
		}
		if ((status = execve(path, comand, vars->envp_copy)) == -1)
			exit(WEXITSTATUS(status));
    }
	else if (pid < 0)
		ft_putendl_fd("error", 2);
	else
    {
        close(mas[1]);
        dup2(fd, 0);
        close(mas[0]);
        waitpid(pid, &status, WUNTRACED);
		vars->g_exit_code = WEXITSTATUS(status);
		close(fd);
    }
}
// менеджмент ошибок

// void	ft_conveyor_test(char *line, char **comand_line, t_vars *vars)
// {
// 	char **line_pipe;
// 	char *comand_path;
// 	int i;

// 	i = 0;
// 	line_pipe = ft_split(line, '>');
// 	if (vars->count_redirect - i > 0)
// 	{
// 		comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
// 		comand_line = ft_split(line_pipe[i], ' ');
// 		comand_path = ft_strjoin(comand_path, "/");
// 		comand_path = ft_strjoin(comand_path, comand_line[0]);
// 		ft_redirects(comand_path, line_pipe, vars);
// 		vars->count_redirect = 0;
// 	}
// 	else
// 	{
// 		if(!(checking_recoded_functions(&line_pipe[i], vars)))			
// 		{
// 			comand_line = ft_split(line_pipe[i], ' ');
// 			comand_path = check_system_funk(vars, ft_split(line_pipe[i], ' '));
// 			comand_path = ft_strjoin(comand_path, "/");
// 			comand_path = ft_strjoin(comand_path, comand_line[0]);
// 			system_funk(comand_path, comand_line, vars);
// 		}
// 	}
// 	dup2(vars->save_std_in, 0);
// 	dup2(vars->save_std_out, 1);	
// }

// void	ft_pars_argument_test(char *line, t_vars *vars)
// {
// 		char **comand_line;
// 		char **line_pipe;
// 		char *comand_path;
// 		char **argv;
// 		char *ptr;
// 		int mas[2];
// 		int count = 0;
// 		int	i = 0;
// 		int t = 0;

// 		comand_line = ft_split(line, ' ');
// 		check_redirect(comand_line, vars);
// 		if (vars->count_redirect == 0)
// 		{
// 			if(!(checking_recoded_functions(comand_line, vars)))
// 			{
// 				comand_path = check_system_funk(vars, comand_line);
// 				comand_path = ft_strjoin(comand_path, "/");
// 				comand_path = ft_strjoin(comand_path, comand_line[0]);			
// 				system_funk(comand_path, comand_line, vars);
// 			}
// 		}
// 		else
// 		{
// 			ft_conveyor_test(line, comand_line, vars);
// 			dup2(vars->save_std_in, 0);
// 			dup2(vars->save_std_out, 1);
// 		}
// }

// int main(int argc, char **argv, char **envp)
// {
// 	t_vars	vars;
// 	char *ptr;
// 	char *line = NULL;
// 	int i = 0;
// 	struct dirent *dir;
// 	vars.save_std_in = dup(0);
// 	vars.save_std_out = dup(1);
// 	envp_copy(envp, &vars);
// 	vars.count_redirect = 0;
// 	vars.path = init_patch(&vars, "PATH");
// 	ft_putstr_fd("minishell>", 1);
// 	while((i = get_next_line(0, &line)) > 0)
// 	{
// 		ft_pars_argument_test(line, &vars);
// 		free(line);
// 		line = NULL;
// 		ft_putstr_fd("minishell>", 1);
// 	}
// 	return 0;
// }