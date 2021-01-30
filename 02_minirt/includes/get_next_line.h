/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nawhes <sehpark@student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:48:28 by nawhes            #+#    #+#             */
/*   Updated: 2020/12/23 01:50:25 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int			get_next_line(int fd, char **line);

#endif
