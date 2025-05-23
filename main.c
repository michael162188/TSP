#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CITIES 10

void getDistances(double[CITIES][CITIES], int[CITIES * 2]);

int nearestNeighbor(int[CITIES * 2], int[CITIES]);

int main () {
    double distances[CITIES][CITIES];
    int shortestPath[CITIES];
    int coordinates[CITIES * 2];
    coordinates[0] = 0;
    coordinates[1] = 0;

    srand(time(0));

    for (int i = 2; i < 20; i++) {
        coordinates[i] = rand() % 201 - 100;
    }
    for (int i = 0; i < CITIES; i++) {
        printf("City %d: (%d, %d)\n", i, coordinates[i], coordinates[i + 1]);
    }

    printf("\n");

    getDistances(distances, coordinates);
    
    int minDistance = nearestNeighbor(coordinates, shortestPath);
}

void getDistances(double distances[CITIES][CITIES], int coordinates[CITIES * 2]) {
    for (int i = 0; i < CITIES; i++) {
        for (int j = 0; j <= i; j++) {
            int x = coordinates[i * 2] - coordinates[j * 2];
            int y = coordinates[i * 2 + 1] - coordinates[j * 2 + 1];
            distances[i][j] = sqrt((x * x) + (y * y));
            distances[j][i] = distances[i][j];
        }
    }
}

int nearestNeighbor(int coordinates[CITIES * 2], int shortestPath[CITIES]) {
    int distance = 0;
    
    return distance;
}