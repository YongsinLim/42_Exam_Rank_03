/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:49:04 by yolim             #+#    #+#             */
/*   Updated: 2026/03/18 14:13:54 by yolim            ###   ########.fr       */
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
    while(s[i])
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

    // no need to check !desk and !src
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
    while (s && s[len]) // check both
        len++;
    return (len);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1;
    char    *tmp;

    if (*s1) // dont forget to check *s1 != NULL
        size1 = ft_strlen(*s1);
    else
        size1 = 0; // remember !

    tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;
    ft_memcpy(tmp, *s1, size1);
    free(*s1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
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
    if (dest > src) // backward copy
    {
        i = n;
        while (i >= 0) // must include 0, bcos 0 index
        {
            i--;
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
    else if (dest < src) // copy from front
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

    while (1)
    {
        tmp =  ft_strchr(b, '\n');
        if (tmp)
        {
            if (!str_append_mem(&ret, b, tmp - b + 1)) // tmp - b + 1 : eg. calculate "hello\nworld" 's hello\n how long bytes
            {
                free(ret); // don't free(tmp) bcos tmp is the address inside b, not separate allocation
                return (NULL);
            }
            ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); // copy remaining ch after \n + '\0' to b !!
            return (ret);
        }

        if (!str_append_str(&ret, b))
            return (NULL);
        int read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret <= 0) // nothing to read dy
        {
            b[0] = '\0'; // null terminate buffer
            if (ret && *ret) // if ret got remaining , return
                return ret;
            free(ret);  // if no, free and return null
            return NULL;
        }
        b[read_ret] = '\0';
    }
}

/* int    main(int argc, char **argv)
{
    if (argc != 2)
        return (printf("error argv"), 1); // don't forget to check
    int fd = open(argv[1], O_RDONLY); // remember file to open
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
    close(fd); // dont forget to close
    return (0);
}
*/