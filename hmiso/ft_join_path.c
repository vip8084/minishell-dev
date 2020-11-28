/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:22:30 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/28 18:56:19 by hmiso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*ft_join_path(t_vars *vars, char **com_whis_flags)
{
	char *comand_path;
	char *fre_ptr;
	char *ptr;

	ptr = ft_strdup(com_whis_flags[0]);
	comand_path = check_system_funk(vars, ptr);
	if (comand_path == NULL)
	{
		comand_path = ft_strdup(com_whis_flags[0]);
	}
	else
	{
		fre_ptr = comand_path;
		comand_path = ft_strjoin(comand_path, "/");
		ptr_free(&fre_ptr);
		fre_ptr = comand_path;
		comand_path = ft_strjoin(comand_path, com_whis_flags[0]);
		ptr_free(&fre_ptr);
	}
	ptr_free(&ptr);
	return (comand_path);
}
