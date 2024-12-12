/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenhamm <obenhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:25:54 by obenhamm          #+#    #+#             */
/*   Updated: 2024/12/12 23:11:27 by obenhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = c;
		i++;
	}
	return ((void *)p);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlength;
	size_t	srclength;

	if (dstsize == 0 && !dst && src)
		return (ft_strlen(src));
	dstlength = ft_strlen(dst);
	srclength = ft_strlen(src);
	i = dstlength;
	j = 0;
	if (dstsize == 0 || dstlength >= dstsize)
		return (dstsize + srclength);
	if (dstsize > 0)
	{
		while (src[j] != '\0' && i < dstsize - 1)
		{
			dst[i] = (char)src[j];
			j++;
			i++;
		}
		dst[i] = '\0';
	}
	return (dstlength + srclength);
}



void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (!str)
		return (NULL);
	return(ft_memset(str, 0,count * size));
	
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
    i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	srclen;
	size_t	destlen;
	char	*str;

    if(!s1 && !s2)
	return(NULL);
    else if (!s1)
        return(s2);
    else if(!s2)
        return(s1);
    srclen = ft_strlen(s1);
    destlen = ft_strlen(s2);
    str = ft_calloc((srclen + destlen) + 1, sizeof(char));
    if (!str)
	return (NULL);
    ft_strlcat(str, s1, srclen + 1);
    ft_strlcat(str, s2, destlen + srclen + 1);
    return (str);
}

int checkline(const char *line)
{
    int i;
    
    i = 0;
    if (!line)
        return 0;
    while (line[i])
    {
        if (line[i] == '\n')
            return 1;
        i++;
    }
    return 0;
}

char	*lqraya(int fd, char *buffer)
{
    char *line;
    char *buff;
    char *temp;
    ssize_t	bytes_tqraw;
    
    if (!buffer || !buffer[0])
        line = ft_strdup("");
    else
        line = ft_strdup(buffer);
    if(!line)
        return (NULL);
    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if(!buff)
    {   
        free(line);
        return (NULL);
    }

    while(1)
    {
        bytes_tqraw = read(fd, buff, BUFFER_SIZE);
        if (bytes_tqraw == -1)
        {
            free(line);
            free(buff);
            return (NULL);
        }
        if (bytes_tqraw == 0)
            break;
        buff[bytes_tqraw] = '\0';
	temp = ft_strjoin(line, buff);
        if (!temp)
        {
            free(line);
            free(buff);
            return (NULL);
        }
        line = temp;

        if (checkline(line))
            break;
    }
    free(buff);   
    return (line); 
}

char *extline(char *buff)
{
    size_t i;
    size_t len;
    char    *str;

    i = 0;
    len = 0;
    if (!buff || !buff[0])
        return NULL;
    while(buff[len] != '\n' && buff[len] != '\0')
        len++;
    str = malloc(sizeof(char) *( len + 1 + (buff[len] == '\n')));
    if(!str)
        return (NULL);
    while(buff[i] != '\n' && buff[i] != '\0')
    {
        str[i] = buff[i];
        ++i;
    }
    if(buff[i] == '\n')
    {
        str[i] = '\n';
        str[++i] = '\0';
    }
    else
        str[i] = '\0';
    return (str);
}
char *joiner(char *buff)
{
    int i;
    int j;
    i = 0;
    j = 0;
    if(!buff || !buff[0])
    {
        free(buff);
        return (NULL);
    }
    while(buff[i] != '\n' && buff[i] != '\0')
        i++;
    if (buff[i] == '\n')
        i++;
    while (buff[i])
        buff[j++] = buff[i++];
    buff[j] = '\0';
   return buff;
}
char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
     buff = lqraya(fd, buff);
     if (!buff)
        return (NULL);
    line = extline(buff);
    buff = joiner(buff);
    return (line);
}
int main(int ac, char **av)
{
    if (ac < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", av[0]);
        return 1;
    }

    int fd = open(av[ac - 1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *s;
    while ((s = get_next_line(fd)) != NULL)
    {
        printf("LINE: %s", s);
        free(s);
    }

    close(fd);
    return 0;
}
