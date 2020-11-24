/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conveyor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:27:08 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/24 12:17:44 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	**make_comand_mas_start(char **comand_line, int i, int j)
{
	int k;
	int count = 0;
	char **comand_whis_flags;

	k = i - j; //смещение до пайпа или редиректа
	comand_whis_flags = malloc(sizeof(char *) * (j + 1));
	while (k < i)
	{
		comand_whis_flags[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	comand_whis_flags[count] = NULL;	
	return comand_whis_flags;
}

char	**make_list_rederection(char **comand_line, int i, int j, t_vars *vars)
{
	int count;
	int k;
	char **mas;

	count = 0;
	k = i - j;
	while(k <= i && ((ft_strncmp(comand_line[k], "|", 2) != 0) || vars->mas_flags[k] == 1))
	{
		if (((ft_strncmp(comand_line[k], ">", 2) == 0) && vars->mas_flags[k] == 0) || ((ft_strncmp(comand_line[k], ">>", 3) == 0 ) && vars->mas_flags[k] == 0))
		{
			if (((ft_strncmp(comand_line[k - 1], ">", 2) != 0 && vars->mas_flags[k - 1] == 0)) || (ft_strncmp(comand_line[k - 1], ">>", 3) != 0 && vars->mas_flags[k - 1] == 0))
			{
				k++;
				continue;
			}
		}
		k++;
		count++;
	}
	mas = malloc(sizeof(char *) * (count + 1));
	k = i - j;
	count = 0;
	while(k <= i && (ft_strncmp(comand_line[k], "|", 2) != 0 || vars->mas_flags[k] == 1))
	{
		if (((ft_strncmp(comand_line[k], ">", 2) == 0) && vars->mas_flags[k] == 0) || ((ft_strncmp(comand_line[k], ">>", 3) == 0 ) && vars->mas_flags[k] == 0))
		{
			if (((ft_strncmp(comand_line[k - 1], ">", 2) != 0 && vars->mas_flags[k - 1] == 0)) || (ft_strncmp(comand_line[k - 1], ">>", 3) != 0 && vars->mas_flags[k - 1] == 0))
			{
				k++;
				continue;
			}
		}
		mas[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	mas[count] = NULL;
	return mas;
}

char	**make_list_rederection_revers(char **comand_line, int i, int j, t_vars *vars)
{
	int count;
	int k;
	char **mas;

	count = 0;
	k = i - j;
	while(k <= i && (ft_strncmp(comand_line[k], "|", 2) != 0 || vars->mas_flags[k] == 1) && (ft_strncmp(comand_line[k], ">", 2) != 0 || vars->mas_flags[k] == 1) && ((ft_strncmp(comand_line[k], ">>", 3) != 0) || vars->mas_flags[k] == 1))
	{
		if ((ft_strncmp(comand_line[k], "<", 2) == 0) && vars->mas_flags[k] == 0)
		{
			if ((ft_strncmp(comand_line[k - 1], "<", 2) != 0 && vars->mas_flags[k - 1] == 0))
			{
				k++;
				continue;
			}
		}
		k++;
		count++;
	}
	mas = malloc(sizeof(char *) * (count + 1));
	k = i - j;
	count = 0;
	while(k <= i&& (ft_strncmp(comand_line[k], "|", 2) != 0 || vars->mas_flags[k] == 1) && (ft_strncmp(comand_line[k], ">", 2) != 0 || vars->mas_flags[k] == 1) && ((ft_strncmp(comand_line[k], ">>", 3) != 0) || vars->mas_flags[k] == 1))
	{
		if ((ft_strncmp(comand_line[k], "<", 2) == 0) && vars->mas_flags[k] == 0)
		{
			if ((ft_strncmp(comand_line[k - 1], "<", 2) != 0 ) && vars->mas_flags[k - 1] == 0)
			{
				k++;
				continue;
			}
		}
		mas[count] = ft_strdup(comand_line[k]);
		k++;
		count++;
	}
	mas[count] = NULL;
	return mas;
}

char	**make_comand_mas_end(char **comand_line, int i, t_vars *vars)
{
	int k = 1;
	int count = 0;
	int j = 0;
	char **comand_whis_flags;

	if(vars->count_call_pipe == 0 || (vars->count_pipe - vars->count_call_pipe) == 0)
	{
		while (i - k > 0)
		{
			if(((ft_strncmp(comand_line[i - k], "|", 1) == 0) || (ft_strncmp(comand_line[i - k], ">", 1) == 0)) && k != 0)
				break;
			k++;
		}
	}
	else
	{
		while (i - k > 0)
		{
			if(((ft_strncmp(comand_line[i - k], "|", 1) == 0) || (ft_strncmp(comand_line[i - k], ">", 1) == 0)) && k != 0)
				break;
			k++;
		}
		k--;
	}	
	comand_whis_flags = malloc(sizeof(char *) * (k + 1));
	j = k;
	if (vars->count_call_pipe == 0)
	{
		while (count < j)
		{
			comand_whis_flags[count] = ft_strdup(comand_line[i - k]);
			k--;
			count++;
		}
	}
	else if ((vars->count_pipe - vars->count_call_pipe) == 0)
	{
		while (count < j)
		{
			comand_whis_flags[count] = ft_strdup(comand_line[i - k + 1]);
			k--;
			count++;
		}
	}
	else
	{
		while (count < j)
		{
			comand_whis_flags[count] = ft_strdup(comand_line[i - k]);
			k--;
			count++;
		}		
	}
	
	vars->count_call_pipe++;
	comand_whis_flags[count] = NULL;	
	return comand_whis_flags;
}


char	**make_comand_mas_end_red(char **comand_line, int i, t_vars *vars)
{
	int k = 1;
	int count = 0;
	int j = 0;
	char **comand_whis_flags;

	if(vars->count_call_pipe == 0 || (vars->count_pipe - vars->count_call_pipe) == 0)
	{
		while (i - k > 0)
		{
			if(((ft_strncmp(comand_line[i - k], "|", 1) == 0) || (ft_strncmp(comand_line[i - k], ">", 1) == 0)) && k != 0)
				break;
			k++;
		}		
	}
	else
	{
		while (i - k > 0)
		{
			if(((ft_strncmp(comand_line[i - k], "|", 1) == 0) || (ft_strncmp(comand_line[i - k], ">", 1) == 0)) && k != 0)
				break;
			k++;
		}
		k--;
	}	
	comand_whis_flags = malloc(sizeof(char *) * (k + 1));
	j = k;
	if (vars->count_call_pipe == 0)
	{
		while (count < j)
		{
			comand_whis_flags[count] = ft_strdup(comand_line[i - k]);
			k--;
			count++;
		}
	}
	else if ((vars->count_pipe - vars->count_call_pipe) == 0)
	{
		while (count < j)
		{
			comand_whis_flags[count] = ft_strdup(comand_line[i - k + 1]);
			k--;
			count++;
		}
	}
	else
	{
		while (count < j)
		{
			comand_whis_flags[count] = ft_strdup(comand_line[i - k]);
			k--;
			count++;
		}		
	}
	vars->count_call_pipe++;
	comand_whis_flags[count] = NULL;	
	return comand_whis_flags;
}


char	*ft_join_path(t_vars *vars, char **com_whis_flags)
{
	char *comand_path;
	char *free_ptr;

	comand_path = check_system_funk(vars, &com_whis_flags[0]);
	if (comand_path == NULL)
	{
		comand_path = com_whis_flags[0];
	}
	else
	{
		free_ptr = comand_path;
		comand_path = ft_strjoin(comand_path, "/");
		free(free_ptr);
		free_ptr = comand_path;
		comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
		free(free_ptr);
	}
	return (comand_path);
}

void		ft_pipe_eof(void)
{
    int mas[2];

    pipe(mas);
	write(mas[1], "", 0);
	dup2(mas[0], 0);
	close(mas[1]);    
}

void	create_file(char **comand_line,int *mas_flags)
{
	int i;
	int fd;

	fd = 0;
	i = 0;
	while (comand_line[i] != NULL)
	{
		if (ft_strncmp(comand_line[i], ">", 2) == 0 && comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (fd == -1)
			{
				ft_putstr_fd(comand_line[i + 1], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				break;
			}
			close(fd);
		}
		if (ft_strncmp(comand_line[i], "<", 2) == 0 && comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_RDONLY);
			if (fd == -1)
			{
				// ft_putstr_fd(comand_line[i + 1], 2);
				// ft_putstr_fd(": Permission denied\n", 2);
				break;
			}
			close(fd);
		}		
		if (ft_strncmp(comand_line[i], ">>", 3) == 0 && comand_line[i + 1] != NULL && mas_flags[i] == 0)
		{
			fd = open(comand_line[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd == -1)
			{
				ft_putstr_fd(comand_line[i + 1], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				break;
			}			
			close(fd);
		}
		i++;
	}
}

void	ft_conveyor(char *line, char **comand_line, t_vars *vars)
{
	char **line_pipe;
	char *comand_path;
	char **com_whis_flags;
	char **mas_redirektion;
	char **mas_redirektion2;
	int i;
	int j;
	int k;
	int fd;

	j = 1;
	i = 0;
	k = 0;
	int t = 0;
	int flag = 0;
	int flag_pipe = 0;
	// while (comand_line[i] != NULL)
	// {
	// 	if (ft_strncmp(comand_line[i], ">", 2) == 0 && comand_line[i + 1] != NULL)
	// 	{
	// 		fd = open(comand_line[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	// 		if (fd == -1)
	// 		{
	// 			ft_putstr_fd(comand_line[i + 1], 2);
	// 			ft_putstr_fd(": Permission denied\n", 2);
	// 			break;
	// 		}
	// 		close(fd);
	// 	}
	// 	if (ft_strncmp(comand_line[i], ">>", 3) == 0 && comand_line[i + 1] != NULL)
	// 	{
	// 		fd = open(comand_line[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	// 		if (fd == -1)
	// 		{
	// 			ft_putstr_fd(comand_line[i + 1], 2);
	// 			ft_putstr_fd(": Permission denied\n", 2);
	// 			break;
	// 		}			
	// 		close(fd);
	// 	}		
	// 	i++;
	// }
	create_file(comand_line, vars->mas_flags);
	i = 0;
	while(comand_line[i] != NULL)
	{
		if (i != 0 && ((ft_strncmp(comand_line[i], "|", 2) == 0) && vars->flag_redirect == 1)  && vars->mas_flags[i] != 1)
		{		
			ft_pipe_eof();
			create_file(&comand_line[i], &vars->mas_flags[i]);
			vars->flag_redirect = 0;
			flag_pipe = 1;
			i++;
		}
		if ((ft_strncmp(comand_line[i], "|", 2) == 0) && vars->flag_redirect == 0 && vars->mas_flags[i] != 1)
		{
			create_file(&comand_line[i], &vars->mas_flags[i]);
			com_whis_flags = make_comand_mas_start(comand_line, i, (j - 1));
			comand_path = ft_join_path(vars, com_whis_flags);
			ft_pipe(comand_path, com_whis_flags, vars);	
			j = 0;
			vars->flag_redirect = 0;
			flag_pipe = 1;
			free_two_dimensional_array(com_whis_flags);
			free(comand_path);
		}
		else if (((ft_strncmp(comand_line[i], ">", 2) == 0) || (ft_strncmp(comand_line[i], ">>", 3) == 0)) && vars->mas_flags[i] != 1)
		{
			com_whis_flags = make_comand_mas_start(comand_line, i, (j - 1));
			if (com_whis_flags[0] != NULL)
			{
				comand_path = ft_join_path(vars, com_whis_flags);
				while(comand_line[i + 1] != NULL)
				{
					if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
					{
						break;
					}
					i++;
					k++;
				}
				mas_redirektion = make_list_rederection(comand_line, i, k, vars);
				ft_redirects(comand_path, com_whis_flags, mas_redirektion, vars);
				j = 0;
				k = 0;
				vars->flag_redirect = 1;
				flag_pipe = 0;			
				if(mas_redirektion[0] != NULL)
					i--;
				free_two_dimensional_array(com_whis_flags);
				free(comand_path);
				free_two_dimensional_array(mas_redirektion);
			}
			else
			{
				while(comand_line[i + 1] != NULL)
				{
					if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
					{
						break;
					}
					i++;
					k++;
				}
				k = 0;
				vars->flag_redirect = 1;
				flag_pipe = 0;
				i--;
			}
		}
		else if ((ft_strncmp(comand_line[i], "<", 2) == 0) && vars->mas_flags[i] != 1)
		{
			com_whis_flags = make_comand_mas_start(comand_line, i, (j - 1));
			if(com_whis_flags[0] != NULL)
			{
				comand_path = ft_join_path(vars, com_whis_flags);
				while(comand_line[i + 1] != NULL)
				{
					if ((ft_strncmp(comand_line[i], "|", 2) == 0 || ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] != 1)
					{
						if ((ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] == 0)
							flag = 2;
						else 
							flag = 1;
						break;
					}
					i++;
					k++;
				}
				mas_redirektion = make_list_rederection_revers(comand_line, i, k, vars);
				if (flag == 0)
				{
					ft_redirects_revers(comand_path, com_whis_flags, mas_redirektion, vars);
					flag_pipe = 1;
				}
				if (flag == 1)
				{
					ft_redirects_pipe(comand_path, com_whis_flags, mas_redirektion, vars);
					flag_pipe = 1;
				}
				if (flag == 2)
				{
					j = 0;
					k = 0;
					while(comand_line[i + 1] != NULL)
					{
						if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
						{
							break;
						}
						i++;
						k++;
					}
					mas_redirektion2 = make_list_rederection(comand_line, i, j, vars);
					ft_redirects_redirect(comand_path, com_whis_flags, mas_redirektion, mas_redirektion2, vars);
					//i++;
					flag_pipe = 0;
					free_two_dimensional_array(mas_redirektion2);
				}	
				j = 0;
				k = 0;
				flag = 0;
				free_two_dimensional_array(com_whis_flags);
				free(comand_path);
				free_two_dimensional_array(mas_redirektion);
			}
			else
			{
				while(comand_line[i + 1] != NULL)
				{
					if ((ft_strncmp(comand_line[i], "|", 2) == 0 || ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] != 1)
					{
						if ((ft_strncmp(comand_line[i], ">", 2) == 0 || ft_strncmp(comand_line[i], ">>", 3) == 0) && vars->mas_flags[i] == 0)
							flag = 2;
						else 
							flag = 1;
						break;
					}
					i++;
					k++;
				}
				mas_redirektion = make_list_rederection_revers(comand_line, i, k, vars);
				if (flag == 0)
				{
					flag_pipe = 1;
				}
				if (flag == 1)
				{
					flag_pipe = 1;
				}
				if (flag == 2)
				{
					j = 0;
					k = 0;
					while(comand_line[i + 1] != NULL)
					{
						if (ft_strncmp(comand_line[i], "|", 2) == 0 && vars->mas_flags[i] == 0)
						{
							break;
						}
						i++;
						k++;
					}
					mas_redirektion2 = make_list_rederection(comand_line, i, j, vars);
					flag_pipe = 0;
					free_two_dimensional_array(mas_redirektion2);
				}	
				j = 0;
				k = 0;
				flag = 0;
				free_two_dimensional_array(mas_redirektion);
			}
		}
		else if (comand_line[i + 1] == NULL && flag_pipe == 1)
		{
			com_whis_flags = make_comand_mas_start(comand_line, i + 1, j);
			comand_path = ft_join_path(vars, com_whis_flags);
			system_funk(comand_path, com_whis_flags, vars);
			j = 0;
			vars->flag_redirect = 0;
			free_two_dimensional_array(com_whis_flags);
			free(comand_path);			
		}
		j++;
		i++;
	}
	vars->count_pipe = 0;
	vars->count_redirect = 0;
	vars->flag_redirect = 0;
	dup2(vars->save_std_in, 0);
	dup2(vars->save_std_out, 1);
}