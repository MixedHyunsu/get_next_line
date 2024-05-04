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
#define BUFFER_SIZE 3


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char	*get_next_line(int fd)
{
	char	*buffer[BUFFER_SIZE + 1];
	long	bytes_read;
	long	total_bytes_read = 0;
	int	nr;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '/0';
		total_bytes_read += bytes_read;
	}


	printf("%d\n", nr);
	return (buffer);
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