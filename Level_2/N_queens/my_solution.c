/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:54:36 by yolim             #+#    #+#             */
/*   Updated: 2026/03/14 20:04:48 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queen.h"

int ft_abs(int x)
{
    if (x < 0)
        return -x;
    return x;
}

int is_safe(int *board, int col, int row, int n)
{
    // check row conflict
    int i = 0;
    while (i < col)
    {
        if (board[i] == row)
            return 0;
        i++;
    }

    // check diagonals
    int j = 0;
    while (j < col)
    {
        if (ft_abs(board[j] - row) == ft_abs(j - col))
            return 0;
        j++;
    }
    return 1;
}

void   solve_n_queens(int *board, int col, int n)
{
    if (col == n)
    {
        int i = 0;
        while (i < n) {
            if (i < n - 1)
                fprintf(stdout, "%d ", board[i]);
            else
                fprintf(stdout, "%d\n", board[i]);
            i++;
        }
        return ;
    }
    int row = 0;
    while (row < n) {
        if (is_safe(board, col, row, n)) {
            // Place Queen
            board[col] = row;
            // Recursively try next col (col + 1) to place queens, This moves forward: column 0 -> ... → column n
            solve_n_queens(board, col + 1, n);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = atoi(argv[1]);
    if (n < 1)
        return 0;
    int *board = calloc(n, sizeof(int));
    solve_n_queens(board, 0, n);
    free(board);
    return 0;
}