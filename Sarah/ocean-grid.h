#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int column;
} Coordinate;

typedef struct {
	char symbol; 
	Coordinate position;
} Cell;

typedef struct {
    int height;
    int width;
    int n;
    Cell *cells; // pointer to the 2D array of Cell structs
} Grid;

