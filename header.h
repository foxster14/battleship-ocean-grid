#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <time.h>


#define WATER       ' '
#define MISS        '~'
#define HIT         'X'//'\u2715' //switch with ascii character or figure out how to make unicode work 
#define SHIP        '#'//'\u25A0' //switch with ascii character or figure out how to make unicode work 
//#define SHIP		'H'

#define ROW         10
#define COLUMN      10


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
    Cell* cells;
} Grid;

void placeships(Grid* grid);
bool placeAttack(Grid* grid);
void displayOceanGrid(Grid *grid);

//Variables and values for players health
int player1HP = 17, player2HP = 17;