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
#define BUFFER_SIZE 1

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
        char	*str;
        size_t	s_len;

        if (s == NULL)
                return (NULL);
        s_len = ft_strlen(s);
        if (start >= s_len)
                return (ft_strdup(""));
        if (start + len > s_len)
                len = s_len - start;
        str = (char *)malloc(sizeof(char) * (len + 1));
        if (str == NULL)
                return (NULL);
        ft_strlcpy(str, s + start, len + 1);
        return (str);
}

int	fill_line_buffer(char **line, char *buffer)
{
	char	*str;
	size_t	length;
	
	if (ft_strchr(buffer, '\n') != NULL)
	{
		length = ft_strchr(buffer, '\n') - buffer;
		str = ft_substr(buffer, 0, length);
		*line = str;
		return(0);
	}
	else
	{
		str = ft_strdup(buffer);
		*line = str;
		return(-1);
	}
}

char	*set_line(char *left_c, char *line_buffer)
{
	char	*line;

	if (!left_c)
		line = line_buffer;
	else
		line = ft_strjoin(left_c, line_buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line_buffer;
	char		*line;
	static char	*left_c;
	ssize_t		read_size;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || !(buffer = (char *)malloc(BUFFER_SIZE + 1)))
		return (NULL);

	while ((read_size = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_size] = '\0';
		i = fill_line_buffer(&line_buffer, buffer);
		if (i == 0)
		{
			line = set_line(left_c, line_buffer);
			return(line);
		}
		line = set_line(left_c, line_buffer);
		left_c = line;
	}
	return (line);
}


/*
int main(void)
{
	int fd;
	fd = open("./text.txt", O_RDONLY);
	if (fd == -1)
		printf("file open error");
	else
	{
		char	*line = get_next_line(fd);
		printf("%s", line);
		free(line);
		close(fd);
	}
	return(0);
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

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
        free(line);
    }

    // Close the file
    close(fd);
    return (0);
}
*/