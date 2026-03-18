/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:16:33 by yolim             #+#    #+#             */
/*   Updated: 2026/03/18 16:42:50 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIP_H
# define RIP_H

#include <unistd.h> // for write
#include <stdio.h> // for puts

int    ft_strlen(char *s);
int    get_min_removals(char *s);
void    rip(char *src, int src_len, char *current, int min_removals, int removals, int open, int close, int index);
int    main(int argc, char **argv);


#endif