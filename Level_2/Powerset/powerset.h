/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:52:37 by yolim             #+#    #+#             */
/*   Updated: 2026/03/18 17:40:39 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERSET_H
# define POWERSET_H

#include <stdlib.h> // for atoi, malloc, free, calloc
#include <stdio.h> // for printf, fprintf, stdout
#include <unistd.h> // for write

void    powerset(int *src, int src_len, int target, int *subset, int subset_len, int index, int current_sum);
int     main(int argc, char **argv);

#endif