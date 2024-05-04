/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunski2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:37:32 by hyunski2          #+#    #+#             */
/*   Updated: 2024/05/02 13:37:36 by hyunski2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 28


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char	*get_next_line(int fd)
{
	char	*word;
	int	nr;

	nr = read(fd, word, BUFFER_SIZE);
//	if (nr == -1)
//		return (NULL);

	printf("%d\n", nr);
	return (word);
}



int main(void)
{
//	char buf[BUFFER_SIZE + 1];
	int fd;
//	int temp_read_size = 0;

	fd = open("./text.txt", O_RDONLY);
	if (fd == -1)
		printf("file open error");
	else
	{
		printf("%s", get_next_line(fd));
//		memset(buf, 0, BUFFER_SIZE);
		close(fd);
	}
	return(0);
}