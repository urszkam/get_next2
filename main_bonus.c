/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urkamins <urkamins@student.42warsaw.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 00:00:00 by urkamins          #+#    #+#             */
/*   Updated: 2026/08/11 00:00:00 by urkamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	fds[argc - 1];
	int	done = 0;

	for (int i = 0; i < argc - 1; i++)
		fds[i] = open(argv[i + 1], O_RDONLY);
	while (!done)
	{
		done = 1;
		for (int i = 0; i < argc - 1; i++)
		{
			if (fds[i] < 0)
				continue ;
			char *line = get_next_line(fds[i]);
			if (line)
			{
				done = 0;
				printf("output: %s", line);
				free(line);
			}
			else
			{
				close(fds[i]);
				fds[i] = -1;
			}
		}
	}
	return (0);
}
