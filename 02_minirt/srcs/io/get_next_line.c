/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nawhes <sehpark@student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:48:16 by nawhes            #+#    #+#             */
/*   Updated: 2021/01/30 04:08:50 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int	error_handle(char **buffer, char **line)
{
	free_all(buffer, line);
	return (-1);
}

static int	read_file(int fd, char **buffer, char **offset)
{
	char	read_buffer[BUFFER_SIZE];
	ssize_t	handler;
	char	*tmp;

	while (*buffer == NULL || !(*offset = ft_strchr(*buffer, '\n')))
	{
		if ((handler = read(fd, read_buffer, BUFFER_SIZE)) <= 0)
			return (handler);
		read_buffer[handler] = '\0';
		if (*buffer == NULL)
		{
			if (!(*buffer = ft_strndup(read_buffer, handler)))
				return (-1);
		}
		else
		{
			if (!(tmp = ft_strjoin(*buffer, read_buffer)))
				return (-1);
			free(*buffer);
			*buffer = tmp;
		}
	}
	return (1);
}

static int	update_line(char **buffer, char **line, char *offset)
{
	char	*tmp;

	if (offset)
	{
		*offset = '\0';
		if (!(*line = ft_strndup(*buffer, ft_strlen(*buffer))))
			return (-1);
		if (!(tmp = ft_strndup(offset + 1, ft_strlen(offset + 1))))
			return (-1);
		free(*buffer);
		*buffer = tmp;
	}
	else
		*line = *buffer;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char			*buffer[256] = {NULL, };
	char				*offset;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (read_file(fd, &buffer[fd], &offset) == -1)
		return (error_handle(&buffer[fd], line));
	if (update_line(&buffer[fd], line, offset) == -1)
		return (error_handle(&buffer[fd], line));
	if (read_file(fd, &buffer[fd], &offset) == -1)
		return (error_handle(&buffer[fd], line));
	if (ft_strlen(buffer[fd]) == 0)
	{
		free(buffer[fd]);
		return (0);
	}
	return (1);
}
