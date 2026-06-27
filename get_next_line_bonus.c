/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukaminsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:11:48 by urkamins          #+#    #+#             */
/*   Updated: 2026/06/25 23:32:30 by ukaminsk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line_bonus.h"

static int	free_str(char **ptr, int ret)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (ret);
}

static t_content	*ft_lstadd_front(t_content **lst, int fd)
{
	t_content	*new;

	new = (t_content *)malloc(sizeof(t_content));
	if (!new)
		return (NULL);
	new->txt = NULL;
	new->fd = fd;
	new->prev = NULL;
	new->next = *lst;
	if (new->next)
		new->next->prev = new;
	*lst = new;
	return (*lst);
}

static int	read_until_endl(t_content *node)
{
	char	*buff;
	char	*temp;
	int		bytes;

	if (!node)
		return (-1);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!node->txt || !ft_strchr(node->txt, '\n'))
	{
		bytes = read(node->fd, buff, BUFFER_SIZE);
		if (bytes <= 0 )
			return (free_str(&buff, bytes));
		buff[bytes] = 0;
		temp = node->txt;
		node->txt = ft_strjoin(temp, buff);
		free(temp);
		if (!node->txt)
			return (free_str(&buff, -1));
	}
	return (free_str(&buff, 1));
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
	if (!line)
	{
		free_str(txt, 0);
		return (NULL);
	}
	if (*txt && !**txt)
		free_str(txt, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_content	*content;
	t_content			*node;
	int					is_read;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = content;
	while (node && node->fd != fd)
		node = node->next;
	if (!node)
		node = ft_lstadd_front(&content, fd);
	if (!node)
		return (NULL);
	is_read = read_until_endl(node);
	if ((!is_read && !node->txt) || is_read < 0)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		free(node->txt);
		free(node);
		return (NULL);
	}
	return (extract_line(&node->txt));
}
