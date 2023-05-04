#include <stdio.h>
#include <ctype.h>
#include "~/submission/group3/Sarah/ocean-grid.h"

typedef struct {
    int height;
    int width;
} Grid;

typedef struct {
    char x_cord;
    int y_cord;
} Coordinates;

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

void getCoordinates(Coordinates* coordinates, int height)
{
    char endChar;

    if (height == 8)
    {
        endChar = 'h';
    }
    else if (height == 12)
    {
        endChar = 'l';
    } else if (height == 24)
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
        coordinates->x_cord = input_x;
        printf("X Coordinate: %c\n\n", coordinates->x_cord);
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
        coordinates->y_cord = input_y;
        printf("Y Coordinate: %d\n\n", coordinates->y_cord);
    }
    else
    {
        printf("Invalid user input.\n");
    }
}

void shipSelection()
{
    printf("You have five ships.\n\n");
    printf("You have five ships.\n\n");
}

void main()
{
    Grid grid = {0};
    Coordinates coordinates = {0};

    //welcomeMessage();
    gridSelection(&grid);
    //howToPlay();
    getCoordinates(&coordinates, grid.height);
}