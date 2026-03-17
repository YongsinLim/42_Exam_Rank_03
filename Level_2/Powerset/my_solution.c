/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:06:52 by yolim             #+#    #+#             */
/*   Updated: 2026/03/14 22:01:18 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // for atoi, malloc, free, calloc,
#include <stdio.h> // for printf

void    powerset(int *set, int set_size, int target, int *subset, int subset_size, int index, int current_sum) {
    // Base case : processed all elements
    if (index == set_size) {
        // Check if sum matches target
        if (current_sum == target) {
            // Print the subset
            int i = 0;
            while (i < subset_size) {
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
    subset[subset_size] = set[index];
    powerset(set, set_size, target, subset, subset_size + 1, index + 1, current_sum + set[index]);

    // Option 2 : Exclude current element
    powerset(set, set_size, target, subset, subset_size, index + 1, current_sum);
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

    if (argc < 2) // or argc < 3 if want to catch non-empty subset
        return 1;

    int target = atoi(argv[1]);
    int set_size = argc - 2;
    int *set = malloc(sizeof(int) * set_size);
    int *subset = malloc(sizeof(int) * set_size);

    if (!set || !subset) {
        free(set);
        free(subset);
        return 1;
    }

    // parse input set into set_array
    int i = 0;
    while (i < set_size) {
        set[i] = atoi(argv[i + 2]);
        i++;
    }

    // Find all subsets with target sum
    powerset(set, set_size, target, subset, 0, 0, 0);
    free(set);
    free(subset);
    return 0;
}