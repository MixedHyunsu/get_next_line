/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunski2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:37:32 by hyunski2          #+#    #+#             */
/*   Updated: 2024/06/11 16:29:46 by hyunski2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

static char	*set_line(char *line_buffer)
{
	char	*left_c;
	int		i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (left_c);
}

static char	*fill_line_buffer(char *left_c, char *buffer, int fd)
{
	char	*stock;
	ssize_t	read_size;

	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (read_size == 0)
			break;
		buffer[read_size] = '\0';
		if (!left_c)
			left_c = ft_strdup("");
		stock = left_c;
		left_c = ft_strjoin(stock, buffer);
		free (stock);
		stock = NULL;
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return (left_c);
}

char	*get_next_line(int fd)
{
	char		*line_buffer;
	char		*buffer;
	static char	*left_c;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(left_c);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	}
	line_buffer = fill_line_buffer(left_c, buffer, fd);
	free(buffer);
	buffer = NULL;
	if (!line_buffer)
		return (NULL);
	left_c = set_line(line_buffer);
	return (line_buffer);
}

/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    // Open the file in read-only mode
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Read and print lines until get_next_line returns NULL
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        //free(line);
    }

    // Close the file
    close(fd);
    return (0);
}

*/
