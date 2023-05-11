#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>


#define WATER       '~'
#define MISS        'O'
#define HIT         '✕' 
#define SHIP        "■"

#define ROW         12
#define COLUMN      12


typedef struct {
    char symbol;
    int length;
    char *name[];
} Ship;

typedef enum {
	eCARRIER    = 5, 
	eBATTLESHIP = 4,
	eCRUISER    = 3, 
	eSUBMARINE  = 3,
	eDESTROYER  = 2
} ShipType;

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
    Cell cells[];
} Grid;

void placeships(Grid* grid);
bool placeAttack(Grid* grid);
void displayOceanGrid(Grid *grid);