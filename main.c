#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CITIES 10

int nearestNeighbor(int*, int*);

int main () {
    int* minDistance;
    int coordinates[20];
    coordinates[0] = 0;
    coordinates[1] = 0;

    srand(time(0));

    for (int i = 2; i < 20; i++) {
        coordinates[i] = rand() % 201 - 100;
    }
    for (int i = 0; i < CITIES; i++) {
        printf("City %d: (%d, %d)\n", i, coordinates[i], coordinates[i + 1]);
    }


}

int nearestNeighbor(int* coordinates, int* minDistance) {
    
    return *minDistance;
}