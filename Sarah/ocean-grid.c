#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> // for using Unicode
#include <locale.h> // also for using Unicode
#include <stdbool.h> // Header-file for boolean data-type.

#define WATER       '~'
#define HIT         '✕' 
#define SHIP        "\u25A0"

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
    Cell *cells; // pointer to the 2D array of Cell structs
} Grid;

// void DrawOceanGrid(Grid* grid, Coordinate* Coordinate){
//     //two for loops
//     //only involves printing it to the terminal
//     //grid->height
//     // for(int i = 1; i <= grid->height; i++){
//     // }  
// }

// creats an empty ocean grid
void initializeOceanGrid(Grid* grid, int n, Cell oceanGridArray[n][n]){
    grid->cells = malloc(sizeof(Cell) * (n*n));
    // grid->cells = malloc(sizeof(Cell) * (n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            oceanGridArray[i][j].symbol = WATER;
            oceanGridArray[i][j].position.row = i;
            oceanGridArray[i][j].position.column = j;
        }
        //grid->cells[i] = malloc((sizeof(Cell) * (n*n)));
    }
    grid->cells = oceanGridArray; // doesn't work

    //grid->cells = tempCellArray[grid->height][grid->width];
    //return *grid;
}

void displayOceanGrid(Grid *grid, int n, Cell oceanGridArray[n][n])
{
    // Print the Column headers
    int numOfAlphabetChars = n + 65;
    printf("%5c|", ' ');
    for(int i = 65; i < numOfAlphabetChars; i++){
        printf("%4c ", i);
    }
    
    printf("\n");

    for(int row = 0; row < n; row++){
        printf("%5d|", row+1); // Print row headers
        for(int column = 0; column < n; column++){
            // Print each coordinate on ocean grid
            printf("%4c|", grid->cells->symbol);
            //printf("%5d", table[row][column]);
        }
        printf("\n");
    }
}



void updateOceanGrid(Grid *grid, Coordinate target ){

}


/* int main(){

    // unsigned table10[10][10];
    // fillTimesTable(10, table10);
    // printTimesTable(10, table10);
    setlocale(LC_CTYPE, "");
    Grid grid1;
    grid1.height = 12;
    grid1.width = 12;

    Cell cell1;
    grid1.cells = cell1[12][12];

    //CreateGridArray();
    //int table1[12][12];
    //displayOceanGrid(12, table1);

    initializeOceanGrid(&grid1, 12);
    displayOceanGrid(&grid1, 12);
    //printf("%d", grid1.cells[0][1]);

} */