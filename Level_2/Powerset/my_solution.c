/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:06:52 by yolim             #+#    #+#             */
/*   Updated: 2026/03/18 17:47:51 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"

void    powerset(int *src, int src_len, int target, int *subset, int subset_len, int index, int current_sum) {
    // Base case : processed all elements
    if (index == src_len) {
        // Check if sum matches target
        if (current_sum == target) {
            // Print the subset
            int i = 0;
            while (i < subset_len) {
                if (i > 0)
                    printf(" ");
                printf("%d", subset[i]);
                i++;
            }
            printf("\n");
        }
        return ;
    }

    // Option 1 : Include current element
    subset[subset_len] = src[index]; // use subset_size
    powerset(src, src_len, target, subset, subset_len + 1, index + 1, current_sum + src[index]);

    // Option 2 : Exclude current element
    powerset(src, src_len, target, subset, subset_len, index + 1, current_sum);
}

int main(int argc, char **argv) {
    /*
     * - Validate arg
     * - Get target amount
     * - Get set_len
     * - Assign input set into set_array
     * - Generate powerset
     * - Memory free
     * - Return
     */

    if (argc < 3)
        return 1;

    int target = atoi(argv[1]);
    int src_len = argc - 2;
    int *src = malloc(sizeof(int) * src_len);
    int *subset = malloc(sizeof(int) * src_len);

    if (!src || !subset)
        return (1);

    // parse input src into src_array
    int i = 0;
    while (i < src_len) {
        src[i] = atoi(argv[i + 2]);
        i++;
    }

    // Find all subsets with target sum
    powerset(src, src_len, target, subset, 0, 0, 0);
    free(src);
    free(subset);
    return 0;
}