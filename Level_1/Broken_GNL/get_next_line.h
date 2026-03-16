/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:05:14 by yolim             #+#    #+#             */
/*   Updated: 2026/03/16 15:16:13 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h> // for read, close
#include <stdlib.h> // for malloc, free
#include <stdio.h> for printf
#include <fcntl.h> // for open, O_RDONLY, if cannot remember library use "man creat / man stdin"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char *get_next_line(int fd);

#endif