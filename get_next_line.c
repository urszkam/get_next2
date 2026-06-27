/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukaminsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:11:48 by urkamins          #+#    #+#             */
/*   Updated: 2026/06/26 21:08:35 by ukaminsk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

static int	free_txt(char **ptr, int ret)
{
	if (ptr && *ptr)
		free(*ptr);
	*ptr = NULL;
	return (ret);
}

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
		if (bytes <= 0 )
			return (free_txt(&buff, bytes));
		buff[bytes] = 0;
		temp = *txt;
		*txt = ft_strjoin(temp, buff);
		free(temp);
		if (!*txt)
			return (free_txt(&buff, -1));
	}
	return (free_txt(&buff, 1));
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
		free_txt(txt, 0);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	int			is_read;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	is_read = read_until_endl(fd, &txt);
	if ((!is_read && (!txt || !*txt)) || is_read < 0)
	{
		free_txt(&txt, 0);
		return (NULL);
	}
	return (extract_line(&txt));
}
