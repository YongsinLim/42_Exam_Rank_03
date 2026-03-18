/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:01:57 by yolim             #+#    #+#             */
/*   Updated: 2026/03/18 16:35:24 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

int ft_strlen(char *s)
{
    if (!s || !*s)
        return (0);
    int i = 0;
    while (s && s[i])
        i++;
    return i;
}

int get_min_removals(char *s)
{
    int i = 0;
    int open = 0;
    int close = 0;

    if (!s || !*s)
        return (0);
    while (s && s[i])
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')') {
            if (open > 0)
                open--;
            else
                close++;
        }
        i++;
    }
    return (open + close);
}

void    rip(char *src, int src_len, char *current, int min_removals, int removals, int open, int close, int index)
{
    //Base case : processed all characters
    if (index == src_len) {
        // Valid only if balanced AND uses minimum removals
        if (open == close && removals == min_removals) {
            current[src_len] = '\0';
            puts(current); // print the solution;
        }
        return ; // must be outside if condition.
    }

    // Pruning : if already removed more than minimum, skip
    if (removals > min_removals)
        return ;

    // Option 1 : Keep the character
    if (src[index] == '(') {
        current[index] = '(';
        rip(src, src_len, current, min_removals, removals, open + 1, close, index + 1);
    }
    else // for ')'
    {
        // Can only keep ')' if we have unmatched '('
        if (open > close) {
            current[index] = ')';
            rip(src, src_len, current, min_removals, removals, open, close + 1, index + 1);
        }
    }

    // Option 2 : Replace with space (remove)
    current[index] = ' ';
    rip(src, src_len, current, min_removals, removals + 1, open, close, index + 1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *s = argv[1];
    int src_len = ft_strlen(s);
    int min_removals = get_min_removals(s);

    char current[src_len + 1]; // declare variable to store result (cannot use malloc)
    rip(s, src_len, current, min_removals, 0, 0, 0, 0);
    return 0;
}








