/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenhamm <obenhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:23:37 by obenhamm          #+#    #+#             */
/*   Updated: 2024/12/12 22:46:22 by obenhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t  ft_strlen(const char *s);
void    *ft_memset(void *b, int c, size_t len);
size_t  ft_strlcat(char *dst, const char *src, size_t dstsize);
void    *ft_calloc(size_t count, size_t size);
char    *ft_strdup(const char *s1);
char    *ft_strjoin(char *s1, char *s2);
int     checkline(const char *line);
char    *lqraya(int fd, char *buffer);
char    *extline(char *buff);
char    *joiner(char *buff);

#endif
