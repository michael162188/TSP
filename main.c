#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define CITIES 10

// Each city is made with a struct, holding the city's index and coordinates in a plane
typedef struct City{
    int index;
    int position[2];
} City;

double nearestNeighbor(City*, int*);
void swap(City*, int, int);
double calculatePathDistance(City*, int);
void permute(City*, int, int*, double*);

int main () {
    // Create a path of cities with an array of structs
    City path[CITIES];
    int shortestPathIndexes[CITIES + 1];

    // Seed random number generator with current timestamp
    srand(time(0));

    // Initialize index and coordinates of cities in the path, starting from the origin
    for (int i = 0; i < CITIES; i++) {
        if (i == 0) {
            path[i].index = 0;
            path[i].position[0] = 0;
            path[i].position[1] = 0;
        }
        else {
            // Coordinates initalized with values ranging from -100 to 100
            path[i].index = i;
            path[i].position[0] = rand() % 201 - 100;
            path[i].position[1] = rand() % 201 - 100;
        }
        printf("City %d: (%d, %d)\n", i + 1, path[i].position[0], path[i].position[1]);
    }
    printf("\n");

    // Estimate shortest path and its distance with greedy nearest neighbor algorithm
    double minDistance = nearestNeighbor(path, shortestPathIndexes);
    permute(path, 1, shortestPathIndexes, &minDistance);
    
    // Output the path and its distance
    printf("Actual Shortest Path: ");
    for(int i = 0; i <= CITIES; i++) {
        printf("%d ", (shortestPathIndexes[i] + 1));
    }
    printf("\n");
    printf("Actual Shortest Path Distance: %f\n", minDistance);
    
    return 0;
}

double nearestNeighbor(City* path, int* shortestPathIndexes) {
    double distance = 0;
    int index;
    shortestPathIndexes[0] = 0;

    // Initialize all cities in path as not visited except for the first
    int* visited = calloc(CITIES, sizeof(int));
    if (visited == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    visited[0] = 1;

    for (int i = 0; i < (CITIES - 1); i++) {
        // Initialize minimum distance value as largest possible signed 32-bit integer (2^31 - 1)
        double minimum = INT_MAX;
        for (int j = 0; j < CITIES; j++) {
            // Calculate the distance between two cities at a time
            double x = path[j].position[0] - path[shortestPathIndexes[i]].position[0];
            double y = path[j].position[1] - path[shortestPathIndexes[i]].position[1];
            double edge = sqrt((x * x) + (y * y));
            // Checks if the two cities being compared are not the same, if the distance between them is smaller than the shortest measured, and if the second city has not yet been visited
            if (edge != 0 && edge < minimum && visited[j] == 0) {
                // Reassigns the minimum distance value, adds the closest city to the one being visited to the shortest path, saves its index
                minimum = edge;
                shortestPathIndexes[i + 1] = j;
                index = j;
            }
        }
        // Once the closest city to the one currently visited is found, its visited value is changed, and the distance between the two cities is added to the total path distance
        visited[index] = 1;
        distance += minimum;
    }

    // Returns to first city and add the distance to it
    double x = path[index].position[0] * path[index].position[0];
    double y = path[index].position[1] * path[index].position[1];
    distance += sqrt(x + y);
    shortestPathIndexes[CITIES] = 0;

    // Free allocated memory
    free(visited);
    visited = NULL;

    // Output the estimated path and distance
    printf("Estimated Shortest Path: ");
    for(int i = 0; i <= CITIES; i++) {
        printf("%d ", (shortestPathIndexes[i] + 1));
    }
    printf("\n");
    printf("Estimated Shortest Path Distance: %f\n", distance);
    return distance;
}

void swap(City* path, int a, int b) {
    // Swap two cities in the path
    City temp = path[a];
    path[a] = path[b];
    path[b] = temp;
}

double calculatePathDistance(City* path, int pathLength) {
    double pathDistance = 0;
    int i;
    /*
        Loop through the path for the length of the path to be measured
        Calculate the distance between two cities at a time, adding it to the total path distance after
    */
    for (i = 0; i < pathLength - 1; i++) {
        double x = path[i].position[0] - path[i + 1].position[0];
        double y = path[i].position[1] - path[i + 1].position[1];
        double edge = (x * x) + (y * y);
        pathDistance += sqrt((edge));
        // printf("%d ", path[i].index);
    }
    // Add the distance required to return to first city
    double x = path[i].position[0] * path[i].position[0];
    double y = path[i].position[1] * path[i].position[1];
    pathDistance += sqrt(x + y);
    return pathDistance;
}

void permute(City* path, int pathLength, int* shortestPathIndexes, double* minDistance) {
    // If the path's length is equal to the number of cities, check the path's distance
    if (pathLength == CITIES) {
        double pathDistance = calculatePathDistance(path, pathLength);
        // If the path's distance is shorter than the previous shortest path's distance, reassign the shortest path distance and save the order of indexes of the cities
        if (pathDistance < *minDistance) {
            for (int i = 0; i < CITIES; i++) {
                shortestPathIndexes[i] = path[i].index;
            }
            *minDistance = pathDistance;
        }
        return;
    }

    // If the current partial path's distance is longer than the shortest path's distance, stop calculating the distance of the current path
    if (calculatePathDistance(path, pathLength) >= *minDistance) {
        return;
    }

    // Swap cities in the path, and calculate the distance of the next path, adding an additional city to the path, then swap another pair of cities
    for (int i = pathLength; i < CITIES; i++) {
        swap(path, pathLength, i);
        permute(path, pathLength + 1, shortestPathIndexes, minDistance);
        swap(path, pathLength, i);
    }
}
