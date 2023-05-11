#include <stdio.h>
#include "header.h"

#define WATER       '~'
#define HIT         '✕' 
#define SHIP        "■"

#define ROW         12
#define COLUMN      12



void welcomeMessage()
{
    printf("Welcome to our Battleship game!\n"
    "This is a CLI version of Battleship made by Sarah Fox, Jake Cermak, Mitchell Humphries, and Christopher Ferrie\n");
}

void gridSelection(Grid* grid)
{
    printf("Select grid size.\n"
    "Enter a number between 1-3:\n"
    "1. 8 x 8\n"
    "2. 12 x 12\n"
    "3. 24 x 24\n");

    int input_x;
    scanf("%d", &input_x); 
    if (input_x == 1)
    {
        grid->height = 8;
        grid->width = 8;
        printf("You chose grid 1.\n"
        "The height and width have been updated.\n");
        printf("Height: %d\nWidth: %d\n\n", grid->height, grid->width);
    }
    else if (input_x == 2)
    {
        grid->height = 12;
        grid->width = 12;
        printf("You chose grid 2.\n"
        "The height and width have been updated.\n");
        printf("Height: %d\nWidth: %d\n\n", grid->height, grid->width);
    }
    else if (input_x == 3)
    {
        grid->height = 24;
        grid->width = 24;
        printf("You chose grid 3.\n"
        "The height and width have been updated.\n");
        printf("Height: %d\nWidth: %d\n\n", grid->height, grid->width);
    }
    else
    {
        printf("Invalid entry.\n");
    }
}

void howToPlay()
{
    printf("=========================================== How To Play ===========================================\n\n");
    printf("1. Select a grid size.\n\n");
    printf("2. Place your fleet of 5 ships.\n"
    "Each ship can be placed either horizontally or vertically.\n"
    "Once the ships are placed, they cannot be moved.\n"
    "No overlapping with other ships.\n\n");
    printf("3. Decide who goes first.\n\n");
    printf("4. Pick a target coordinate on the target grid that hasn't been chosen yet.\n"
    "This target will be marked as either a hit or a miss on the opposing player's ocean grid.\n"
    "If it's a hit, the program will say what ship was hit and the coordinate will be marked as a hit.\n"
    "If it's a miss, the program will say that it's a miss and the coordinate will be marked as a miss.\n"
    "Once all coordinates of a ship are marked, the program will say what ship was sunk.\n"
    "Keep targetting coordinates until the outcome of the game is decided.\n"
    "Whoever sinks the opposing fleet of ships first wins the game.\n");
}

void getCoordinates(Coordinate* coordinates, int height)
{
    char endChar;

    if (height == 8)
    {
        endChar = 'h';
    }
    else if (height == 12)
    {
        endChar = 'l';
    } 
    else if (height == 24)
    {
        endChar = 'x';
    }
    else
    {
        printf("Invalid grid size.\n");
    }
    
    char input_x;

    // consume all characters in the input buffer until the \n
    while ((input_x = getchar()) != '\n' && input_x != EOF) {}

    printf("Enter in a letter between A-%c.\n", toupper(endChar));
    scanf("%c", &input_x);

    if((input_x >= 'a' && input_x <= endChar) ||
    (input_x >= 'A' && input_x <= toupper(endChar)))
    {
        printf("You entered %c\n", input_x);
        coordinates->row = input_x;
        printf("X Coordinate: %c\n\n", coordinates->row);
    }
    else
    {
        printf("Invalid user input.\n");
    }

    int input_y;

    // consume all characters in the input buffer until the \n
    while ((input_y = getchar()) != '\n' && input_y != EOF) {}

    printf("Enter in a letter between 1-%d.\n", height);
    scanf("%d", &input_y);

    if((input_y >= 1 && input_y <= height))
    {
        printf("You entered %d\n", input_y);
        coordinates->column = input_y;
        printf("Y Coordinate: %d\n\n", coordinates->column);
    }
    else
    {
        printf("Invalid user input.\n");
    }
}

void shipSelection()
{
    printf("You have five ships.\n");
    printf(
    "1. Carrier [5]\n"
    "2. Battleship [4]\n"
    "3. Submarine [3]\n"
    "4. Cruiser [3]\n"
    "5. Destroyer [2]\n\n"
    );

    char ships[5][11] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};
    char coordinate_input;
    char direction_input;

    for (int i = 0; i < 5; i++)
    {
        printf("Enter first coordinate (e.g. A1) for %s.\n", ships[i]);
        scanf("%c", &coordinate_input);
        printf("User entered: %c.\n", coordinate_input);
        // consume all characters in the input buffer until the \n
        while ((coordinate_input = getchar()) != '\n' && coordinate_input != EOF) {}

        printf("Enter V to place the %s vertically or H to place the %s horizontally.\n", ships[i], ships[i]);
        scanf("%c", &direction_input);
        printf("User entered: %c.\n", direction_input);
        // consume all characters in the input buffer until the \n
        while ((direction_input = getchar()) != '\n' && direction_input != EOF) {}
    }
}

// creats an empty ocean grid
void initializeOceanGrid(Grid* grid){
    //grid->cells = malloc(sizeof(Cell) * (12*12));
    // grid->cells = malloc(sizeof(Cell) * (n));

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            changeCell(grid,i,j,WATER);
        }
        //grid->cells[i] = malloc((sizeof(Cell) * (n*n)));
    }
    //grid->cells = oceanGridArray; // doesn't work

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



void updateOceanGrid(Grid *grid, Coordinate target )
{

}

int main(void)
{
    printf("hello");
}