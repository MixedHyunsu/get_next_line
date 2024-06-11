/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunski2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:37:44 by hyunski2          #+#    #+#             */
/*   Updated: 2024/06/11 16:31:33 by hyunski2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
    int	len;

    len = 0;
    while (str[len])
        len ++;
    return (len);
}

char	*ft_strchr(const char *s, int c)
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

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	str = (char *) malloc(ft_strlen((char *)s1) + 1);
    if (str == NULL)
        return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
    	i++;
    }
    str[i] = '\0';
    return (str);
}

size_t  ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t  i;

    i = 0;
    if (size == 0)
        return (ft_strlen((char *)src));
    else
    {    
		while (i < size - 1 && src[i])
        {
            dest[i] = src[i];
            i ++;
        }
        dest[i] = '\0';
        return (ft_strlen((char *)src));
    }
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    char	*str;
    int		str_len;
    int		i;
    int		j;

    if (!s1 && !s2)
        return (NULL);
    str_len = ft_strlen(s1) + ft_strlen(s2);
    str = (char *)malloc(sizeof(char) * str_len + 1);
    if (!str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return (str);
}
