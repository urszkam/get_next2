/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urkamins <urkamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:21:42 by urkamins          #+#    #+#             */
/*   Updated: 2026/06/22 20:05:21 by urkamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int endl_idx(char *str, int size)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (i)
        i++;
    }
    return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	tot_len;
	char	*sub;

	if (!s)
		return (NULL);
	if (len > tot_len - start)
		len = tot_len - start;
	i = 0;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[i + start] && i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = 0;
	return (sub);
}