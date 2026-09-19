/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urkamins <urkamins@student.42warsaw.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:24:30 by urkamins          #+#    #+#             */
/*   Updated: 2026/06/27 17:25:04 by urkamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_until_endl(int fd, char **txt)
{
	char	*buff;
	char	*temp;
	int		bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!*txt || !ft_strchr(*txt, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
			return (free(buff), bytes);
		buff[bytes] = 0;
		temp = *txt;
		*txt = ft_strjoin(temp, buff);
		free(temp);
		if (!*txt)
			return (free(buff), -1);
	}
	return (free(buff), 1);
}

static char	*extract_line(char **txt)
{
	char	*tmp;
	char	*line;
	int		pos;

	pos = 0;
	while ((*txt)[pos] && (*txt)[pos] != '\n')
		pos++;
	tmp = *txt;
	line = ft_substr(*txt, 0, pos + 1);
	*txt = ft_substr(*txt, pos + 1, ft_strlen(*txt) - (pos + 1));
	free(tmp);
	if (!line || !*txt)
	{
		free(line);
		free(*txt);
		*txt = NULL;
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	int			was_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	was_read = read_until_endl(fd, &txt);
	if ((!was_read && (!txt || !*txt)) || was_read < 0)
	{
		free(txt);
		txt = NULL;
		return (NULL);
	}
	return (extract_line(&txt));
}
