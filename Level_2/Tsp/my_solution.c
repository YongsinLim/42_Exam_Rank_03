/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:57:34 by yolim             #+#    #+#             */
/*   Updated: 2026/03/15 16:13:09 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // for fprintf
#include <unistd.h> // for write
#include <math.h> // for sqrtf
#include <stdlib.h> // for malloc, free
#include <float.h> // for __FLT_MAX

typedef struct s_city {
    float x;
    float y;
} t_city;

float distance(t_city a, t_city b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy); // x2 + y2 = z2, to get z = sqrtf(x2 + y2)
}

float calculate_path(t_city *cities, int *path, int count)
{
    float total = 0.00;

    int i = 0;
    while (i < count) {
        // path = array label city 排列
        int current = path[i];
        int next = path[(i + 1) % count]; // Connect back to start_city;
        total = total + distance(cities[current], cities[next]);
        i++;
    }
    return (total);
}

// float *min_distance bcos want to keep the latest value for recursion call
void find_shortest_path(t_city *cities, int *path, int count, int index, float *min_distance)
{
    if (index == count)
    {
        float path_length = calculate_path(cities, path, count);
        if (path_length < *min_distance)
            *min_distance = path_length;
        return ;
    }

    int i = 0;
    while (i < count) {
        // Swap
        int temp = path[index];
        path[index] = path[i];
        path[i] = temp;

        find_shortest_path(cities, path, count, index + 1, min_distance);

        // Swap back
        temp = path[index];
        path[index] = path[i];
        path[i] = temp;

        i++;
    }
}

int main(void) {
    t_city cities[11];
    int count = 0;

    /*
    fscanf(stdin, ...): Read formatted data (cities) from standard input
    "%f, %f\n": Format specifier for two floats separated by a comma and space
    &cities[count].x: Address of the x-coordinate (where to store first float)
    &cities[count].y: Address of the y-coordinate (where to store second float)
    == 2: Check if exactly 2 values were successfully read

    fscanf returns the number of items successfully assigned.
    Why &cities[count].x? Need the memory address (pointer) bcos fscanf needs to know where to store the value
    */
    while (fscanf(stdin, "%f, %f\n", &cities[count].x, &cities[count].y) == 2)
        count++;

    // Initialize path as 0, 1, 2, ..., count - 1
    int *path = malloc(sizeof(int) * count);

    int i = 0;
    while (i < count) {
        path[i] = i;
        i++;
    }

    float min_distance = __FLT_MAX__; // must include float.h, if cannot remember use 999999.0f
    find_shortest_path(cities, path, count, 0, &min_distance);

    fprintf(stdout, "%.2f\n", min_distance);

    free(path);
    return 0;
}

// Compile: cc tcp.c -o tsp -lm (the -lm links the math library for sqrtf)