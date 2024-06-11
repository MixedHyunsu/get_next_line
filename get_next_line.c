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

int	fill_line_buffer(char **line_buffer, char *buffer)
{
	size_t	length;
	char	*newline_pos;
	
	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos != NULL) // \n 발견한경우.
	{
		length = ft_strlen(buffer) - ft_strlen(newline_pos);
		*line_buffer = ft_substr(buffer, 0, length);
		return(length + 1);
	}
	else if (ft_strlen(buffer) < BUFFER_SIZE)
	{
		*line_buffer = ft_strdup(buffer);
		return (0); // \0 으로 문서 끝남
	}
	else
	{
		*line_buffer = ft_strdup(buffer);
		return (-1); // \n 발견 못하고 문서도 안끝남
	}
}

void	set_line(char **left_c, char *line_buffer, int i)
{
	char	*tmp;

	if (*left_c == NULL)
		*left_c = ft_strdup(line_buffer);
	else
	{
		tmp = ft_strjoin(*left_c, line_buffer);
		*left_c = NULL;
		*left_c = tmp;
	}
	if (i >= 0)
	{
		*left_c = NULL;
		*left_c = ft_strjoin(tmp, "\n");
	}
}
#include<stdio.h>
char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line_buffer;
	static char	*left_c;
	ssize_t		read_size;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || !(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);

	while ((read_size = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_size] = '\0';
		i = fill_line_buffer(&line_buffer, buffer);
		printf("%d", i);
		set_line(&left_c, line_buffer, i);
		if (i >= 0)
		{
			free(buffer);
			return (left_c);
		}
	}
	free(buffer);
    return (0);
}


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

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
		printf("hi\n");
		free(line);
		close(fd);
	}

}

/*
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