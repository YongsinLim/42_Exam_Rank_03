/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:21:06 by yolim             #+#    #+#             */
/*   Updated: 2026/03/12 23:35:27 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* EXERCISE: PERMUTATIONS
* Generate all permutations of a given string in alphabetical order.

* ALGORITHM:
* 1. Sort the original string alphabetically
* 2. For each position, test each unused character
* 3. Mark characters as used and recurse
* 4. Unmark characters upon returning (backtrack)
* 5. Print when a permutation is complete
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int    ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return i;
}

// Function to swap two characters
void    ft_swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// Function to sort strings alphabetically
void    sort_str(char *str, int n)
{
    int i = 0;
    int j;
    int min;

    while (i < n - 1)
    {
        min = i;
        j = i + 1;
        while (j < n)
        {
            if (str[j] < str[min])
                min = j;
            j++;
        }
        if (min != i)
            ft_swap(&str[i], &str[min]);
        i++;
    }
}

// Recursive function to generate permutations
void    backtrack(char *src, int arg_len, int *used, char *output, int position)
{
    /*
    * BACKTRACKING ALGORITHM FOR PERMUTATIONS:

    * BASE CASE: If position == arg_len, we have a complete permutation
    * - Print the current permutation and \n
    * - Return to try other options

    * RECURSIVE CASE: For each character in source:
    * - If it's not used, try it
    * - Add it to output[position] & set it "used"
    * - Recurse for the next position

    * - Remove character (backtrack) to try others
    * - look for next option

    */

    if (position == arg_len)
    {
        puts(output);
        return ;
    }

    // Test each character of source
    int i = 0;
    while (i < arg_len)
    {
        if (used[i] == 1) // Skip this character if it is already used
        {
            i++;
            continue;
        }

        // CHOOSE: mark as used and place character
        used[i] = 1;
        output[position] = src[i];

        // RECURSE: fill the next position
        backtrack(src, arg_len, used, output, position + 1);

        // UNCHOOSE (backtrack): unmark so other branches can use it
        used[i] = 0;  // trick!!!

        i++; // look for next option !!! trick !!!
    }
}

int    main(int argc, char **argv)
{
    /*
    * Step :
    * - Verify valid arguments
    * - Validate that it contains only letters
    * - Sort string alphabetically
    * - Initialize buffer for result
    * - Generate all permutations
    */

    int arg_len;
    char *src;
    char *output;
    int *used;
    int i;

    if (argc != 2)
        return 1;

    /*
    // Check for empty string or only spaces
    if (ft_strlen(argv[1]) == 0 || (argv[1][0] == ' ' && !argv[1][1]))
        return 0;

    // Validate that it only contains alphabetic characters
    int i = 0;
    while (argv[1][i])
    {
        if (!ft_isalpha(argv[1][i]))
            return 0;
        i++;
    }
    */

    arg_len = ft_strlen(argv[1]);
    src = (char *)malloc((arg_len + 1) * sizeof(char));
    output = (char *)malloc((arg_len + 1) * sizeof(char));
    used = (int *)calloc(arg_len, sizeof(int));

    if (!src || !output || !used)
        return (free(src), free(output), free(used), 1);

    i = 0;
    while (i < arg_len)
    {
        src[i] = argv[1][i];
        i++;
    }
    src[arg_len] = '\0';
    output[arg_len] = '\0';
    sort_str(src, arg_len);
    backtrack(src, arg_len, used, output, 0);

    free(src);
    free(output);
    free(used);

    return 0;
}

/*
* KEY POINTS FOR THE EXAM:

* 1. ALPHABETICAL ORDER:
* - CRUCIAL: Sort the string before generating permutations
* - Without sorting, alphabetical order is not guaranteed
* - Use a simple but correct sorting algorithm

* 2. EFFICIENT BACKTRACKING:
* - Use an int array to mark/unmark used characters correctly
* - Don't forget to clear the state upon return

* 3. MEMORY MANAGEMENT:
* - Allocate buffer to store current permutation
* - Use calloc() to initialize to '\0'
* - Free memory upon completion

* 4. ROBUST VALIDATION:
* - Verify the number of arguments
* - Validate that it contains only letters
* - Handle special cases (empty string, spaces)

* 5. OPTIMIZATIONS:
* - For very long strings, consider the Heap algorithm
* - Avoid regenerating duplicate permutations

void heap_permute(char *str, int size)
{
    // Caso base
    if (size == 1)
    {
        puts(str);
        return;
    }

    int i;
    for (i = 0; i < size; i++)
    {
        heap_permute(str, size - 1);

        // Si size es impar, intercambiar primer y último
        // Si size es par, intercambiar i-ésimo y último
        if (size % 2 == 1)
            ft_swap(&str[0], &str[size - 1]);
        else
            ft_swap(&str[i], &str[size - 1]);
    }
}

*/