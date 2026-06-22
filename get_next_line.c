/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urkamins <urkamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:11:48 by urkamins          #+#    #+#             */
/*   Updated: 2026/06/22 20:05:21 by urkamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*txt;
	char		buff[BUFFER_SIZE];
	int			endl_idx;

	if (fd < 0)
		return (NULL);
	while (read(fd, buff, BUFFER_SIZE) > 0 || txt != NULL)
	{
		endl_idx = endl_idx(txt);
		if ( endl_idx >= 0 )
			return (ft_substr(txt, 0, endl_idx + 1))

	}
	return (NULL);
}

