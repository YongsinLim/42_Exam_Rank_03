/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:01:57 by yolim             #+#    #+#             */
/*   Updated: 2026/03/14 23:52:19 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // for puts
#include <unistd.h> // for write

int ft_strlen(char *str) {
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int get_min_removals(char *s)
{
    int open = 0;
    int close = 0;
    int i = 0;

    while (s[i])
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

void rip_helper(char *s, int index, char *current, int removals, int min_removals, int open, int close, int len)
{
    //Base case : processed all characters
    if (index == len) {
        // Valid only if balanced AND uses minimum removals
        if (open == close && removals == min_removals)
            puts(current); // print the solution;
        return ;
    }

    // Pruning : if already removed more than minimum, skip
    if (removals > min_removals)
        return ;

    // Option 1 : Keep the character
    if (s[index] == '(') {
        current[index] = '(';
        rip_helper(s, index + 1, current, removals, min_removals, open + 1, close, len);
    }
    else // for ')'
    {
        // Can only keep ')' if we have unmatched '('
        if (open > close) {
            current[index] = ')';
            rip_helper(s, index + 1, current, removals, min_removals, open, close + 1, len);
        }
    }

    // Option 2 : Replace with space (remove)
    current[index] = ' ';
    rip_helper(s, index + 1, current, removals + 1, min_removals, open, close, len);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *s = argv[1];
    int len = ft_strlen(s);
    int min_removals = get_min_removals(s);

    char current[len + 1];
    current[len] = '\0';
    rip_helper(s, 0, current, 0, min_removals, 0, 0, len);
    return 0;
}








