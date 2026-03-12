/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:49:04 by yolim             #+#    #+#             */
/*   Updated: 2026/03/11 14:27:30 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* EXERCISE: BROKEN_GNL (Get Next Line)
 *
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
    if (!s)
        return (NULL);
    int i = 0;
    while(s[i] != '\0')
    {
        if (s[i] == c)
            return s + i;
        i++;
    }
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t    i;

    i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

size_t ft_strlen(char *s)
{
    size_t len;

    len = 0;
    if (!s)
        return (0);
    while (s && s[len] != '\0')
        len++;
    return (len);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1;
    char    *tmp;

    if (*s1)
        size1 = ft_strlen(*s1);
    else
        size1 = 0;

    tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;
    if (*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t    i;

    if (!dest || !src)
        return (NULL);
    if (dest > src)
    {
        i = n;
        while (i >= 0)
        {
            i--;
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
    else if (dest < src)
    {
        i = 0;
        while (i < n)
        {
            ((char *)dest)[i] = ((char *)src)[i];
            i++;
        }
    }
    return dest;
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp;

    while(1)
    {
        tmp =  ft_strchr(b, '\n');
        if (tmp)
        {
            if (!str_append_mem(&ret, b, tmp - b + 1))
            {
                free(ret);
                free(tmp);
                return (NULL);
            }
            ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
            return (ret);
        }

        if (!str_append_str(&ret, b))
            return (NULL);
        int read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret <= 0)
        {
            b[0] = '\0';
            if (ret && *ret)
                return ret;
            free(ret);
            return NULL;
        }
        b[read_ret] = '\0';
    }
}

/* int    main(int argc, char **argv)
{
    if (argc != 2)
        return (printf("error argv"), 1);
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (printf("fd less than 0"), 1);
    char *line;
    int count = 0;

    while ((line = get_next_line(fd)))
    {
        printf("%d : %s", count + 1, line);
        free(line);
        count++;
    }
    close(fd);
    return (0);
}
*/