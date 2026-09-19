/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urkamins <urkamins@student.42warsaw.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:26:29 by urkamins          #+#    #+#             */
/*   Updated: 2026/06/27 17:27:03 by urkamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_content	*ft_lstget(t_content **lst, int fd)
{
	t_content	*new;

	new = *lst;
	while (new && new->fd != fd)
		new = new->next;
	if (new)
		return (new);
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
		if (bytes <= 0)
			return (free(buff), bytes);
		buff[bytes] = 0;
		temp = node->txt;
		node->txt = ft_strjoin(temp, buff);
		free(temp);
		if (!node->txt)
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
	if (*txt && !**txt)
	{
		free(*txt);
		*txt = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_content	*content;
	t_content			*node;
	char				*line;
	int					was_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_lstget(&content, fd);
	if (!node)
		return (NULL);
	was_read = read_until_endl(node);
	line = NULL;
	if (was_read > 0 || (!was_read && node->txt))
		line = extract_line(&node->txt);
	if (line)
		return (line);
	if (node->prev)
		node->prev->next = node->next;
	else
		content = node->next;
	if (node->next)
		node->next->prev = node->prev;
	return (free(node->txt), free(node), NULL);
}
