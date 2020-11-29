/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curreg <curreg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 16:49:43 by hmiso             #+#    #+#             */
/*   Updated: 2020/11/29 19:02:37 by curreg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1000
# include <stdlib.h>
# include <unistd.h>

char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(const char *str1, const char *str2);
int			get_next_line(int fd, char **line);
int			get_next_line_two(int fd, char **line);
size_t		ft_strlen(const char *str);
int			check_line(int i, char *line);

#endif
