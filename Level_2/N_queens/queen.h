/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queen.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:03:37 by yolim             #+#    #+#             */
/*   Updated: 2026/03/16 23:03:32 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEEN_H
# define QUEEN_H

#include <stdio.h> // for fprintf
#include <stdlib.h> // for atoi, calloc, free, abs
#include <unistd.h> // for write

int     ft_abs(int x);
int     is_safe(int *board, int col, int row, int n);
void   solve_n_queens(int *board, int col, int n);

#endif

