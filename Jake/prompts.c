#include <stdio.h>
#include <ctype.h>

typedef struct {
	int row;
	int column;
} Coordinate;

/* typedef struct {
    char row;
    int column;
} Coordinates; */

void welcomeMessage()
{
    printf("Welcome to our Battleship game!\n"
    "This is a CLI version of Battleship made by Sarah Fox, Jake Cermak, Mitchell Humphries, and Christopher Ferrie\n");
}

/*void gridSelection(Grid* grid)
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
}*/

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

    printf("Enter in a letter between A-%c.\n", toupper(endChar));
    scanf("%c", &input_x);


    if((input_x >= 'a' && input_x <= endChar) ||
    (input_x >= 'A' && input_x <= toupper(endChar)))
    {
        coordinates->row = input_x - 'A';
    }
    else
    {
        printf("Invalid user input.\n");
    }
    // consume all characters in the input buffer until the \n
    while ((input_x = getchar()) != '\n' && input_x != EOF) {}

    int input_y;

    printf("Enter in a letter between 1-%d.\n", height);
    scanf("%d", &input_y);


    if((input_y >= 1 && input_y <= height))
    {
        coordinates->column = input_y - 1;
    }
    else
    {
        printf("Invalid user input.\n");
    }
    // consume all characters in the input buffer until the \n
    while ((input_y = getchar()) != '\n' && input_y != EOF) {}
}

void shipSelection(Coordinate* coordinates, int height)
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
    char direction_input;

    for (int i = 0; i < 5; i++)
    {
        getCoordinates(coordinates, height);
        printf("User entered: %d%d.\n", coordinates->row, coordinates->column);

        printf("Enter V to place the %s vertically or H to place the %s horizontally.\n", ships[i], ships[i]);
        scanf("%c", &direction_input);
        printf("User entered: %c.\n", direction_input);
        // consume all characters in the input buffer until the \n
        while ((direction_input = getchar()) != '\n' && direction_input != EOF) {}
    }
}

int main(void)
{
    //Grid grid = {0};
    Coordinate coordinates = {0};
    int height = 12;

    //welcomeMessage();
    //gridSelection(&grid);
    //howToPlay();
    //getCoordinates(&coordinates, grid.height);
    shipSelection(&coordinates, height);
}