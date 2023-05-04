#include <stdio.h>

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

    int userInput;
    scanf("%d", &userInput); 
    if (userInput == 1)
    {
        grid->height = 8;
        grid->width = 8;
        printf("You chose grid 1.\n"
        "The height and width have been updated.\n");
        printf("Height: %d\nWidth: %d\n\n", grid->height, grid->width);
    }
    else if (userInput == 2)
    {
        grid->height = 12;
        grid->width = 12;
        printf("You chose grid 2.\n"
        "The height and width have been updated.\n");
        printf("Height: %d\nWidth: %d\n\n", grid->height, grid->width);
    }
    else if (userInput == 3)
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
    if (height == 8)
    {
        printf("Enter in a letter between A-H.\n");
        char userInput;
        scanf("%s", &userInput);
        if((userInput >= 'a' && userInput <= 'h') || (userInput >= 'A' && userInput <= 'H'))
        {
            printf("You entered %c\n", userInput);
        }
        else
        {
            printf("Invalid user input.\n");
        }
    }
    else if (height == 12)
    {
        printf("Enter in a letter between A-L.\n");
        char userInput;
        scanf("%s", &userInput); 
    }
    else if (height == 24)
    {
        printf("Enter in a letter between A-X.\n");
        char userInput;
        scanf("%s", &userInput); 
    }
    else
    {
        printf("Invalid grid size.\n");
    }
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