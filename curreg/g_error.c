/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:52:29 by curreg            #+#    #+#             */
/*   Updated: 2020/11/07 17:11:58 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

static void reset_g_error()
{
      g_error = 0;
}

void set_g_error(int err)
{
    if (err == 2 || err == 20)
        g_error = 1;
}

void show_g_error()
{
    char *error;
    
    error = ft_itoa(g_error);
    ft_putstr_fd(error, 1);
    reset_g_error();
}