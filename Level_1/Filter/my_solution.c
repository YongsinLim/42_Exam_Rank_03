/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:47:25 by yolim             #+#    #+#             */
/*   Updated: 2026/03/11 19:26:13 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Q given dy
#include <errno.h> // for perror
#include <string.h> // for memmem, strlen
#include <fcntl.h> // for read
// #define _GNU_SOURCE // for memmem()

// Q not given
#include <stdio.h> // for printf
#include <stdlib.h> // for realloc
#include <unistd.h> // for write

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


/*
Function to find and replace all occurrences

SEARCH AND REPLACE ALGORITHM:
* - Traverse the buffer character by character
* - At each position, check if it matches the pattern
* - If it matches, write asterisks and skip the length of the pattern
* - If it doesn't match, write the original character
*/

void    filter(char *buffer, char *target)
{
    int    i;
    int    j;
    int    n;
    int    target_len;

    target_len = strlen(target);
    i = 0;
    while (buffer[i])
    {
        j = 0;
        // Check for a match from the current position
        while (target[j] && buffer[i + j] == target[j])
            j++;
        if (j == target_len) // Full match found
        {
            // Write asterisks instead of the pattern
            n = 0;
            while (n < target_len)
            {
                write(1, "*", 1);
                n++;
            }
            i += target_len; // Skip the entire pattern
        }
        else
        {
            // No match, write original character
            write(1, &buffer[i], 1);
            i++;
        }
    }
}

int    main(int argc, char **argv)
{
    int    fd;

    // ARGUMENT VALIDATION: There must be exactly 1 argument and The argument cannot be empty
    if (argc != 2 || argv[1][0] == '\0')
        return (1);

    /*
    * DYNAMIC READING OF STDIN:
    * - Use a temporary buffer to read chunks
    * - Use realloc() to expand the main buffer
    * - Keep track of the total read
    */

    char temp[BUFFER_SIZE];
    char *buffer;
    char *result = NULL;
    int total_read = 0;
    ssize_t bytes;    // bcos read must remember


    // Read from stdin to EOF
    while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        // Expand the main buffer to accommodate the new data
        /* realloc\(\) must receive a pointer previously allocated by malloc\(\)/realloc\(\) (or NULL).
            result is the dynamic heap buffer that stores all accumulated input, so it can be grown each read.
            temp is a fixed local array on the stack (char temp\[BUFFER\_SIZE\]), only used as a temporary chunk buffer.
            Stack arrays cannot be resized with realloc\(\).
        */
        buffer = realloc(result, total_read + bytes + 1);
        if (!buffer)
        {
            free(result);
            perror("Error: Realloc");
            return (1);
        }
        result = buffer;

        // Copy the new data to the main buffer
        memmove(result + total_read, temp, bytes);
        total_read += bytes;
        result[total_read] = '\0';
    }

    // Check for read errors
    if (bytes < 0)
    {
        perror("Error: read");
        free(result);
        return (1);
    }

    // If nothing was read, exit without error
    if (!result)
        return (0);

    // Process the buffer and apply the filter
    filter(result, argv[1]);

    // Free up memory
    free(result);
    return (0);
}

/*

* KEY POINTS FOR THE EXAM:
* 1. MEMORY MANAGEMENT:
* - Always check the return value of malloc/realloc
* - Free memory in case of an error
* - Use memmove() instead of memcpy() for overlaps

* 2. ERROR HANDLING:
* - Use perror() for system errors
* - Return appropriate error codes
* - Validate arguments before using them

* 3. DYNAMIC READING:
* - The buffer can be filled with any amount of data
* - Use realloc() to expand as needed
* - Maintain a valid null terminator

* 4. EFFICIENT ALGORITHM:
* - Simple character-by-character search
* - Avoid using disallowed functions
* - Write directly to stdout without storing the result
*/
