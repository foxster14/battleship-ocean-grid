#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include "header.h"

Cell* getCell(Grid* grid, int x, int y)
{
    return &(grid->cells[(y*grid->height)+x]);
}

void setSymbol(Grid* grid, int x, int y, char c)
{
    Cell *cell = getCell(grid,x,y);
    cell->symbol = c;
    cell->position.row = x;
    cell->position.column = y;
}

// creats an empty ocean grid
void initializeOceanGrid(Grid* grid){
    Cell* temporary = (Cell*)malloc(sizeof(Cell)*ROW*ROW);
    grid->cells = temporary;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < ROW; j++){
            setSymbol(grid,i,j,WATER);
            /* grid->cells[i][j].symbol = WATER;
            grid->cells[i][j].position.row = i;
            grid->cells[i][j].position.column = j; */
        }
    }
    
}

void displayOceanGrid(Grid *grid)
{
    // Print the Column headers
    int numOfAlphabetChars = ROW + 65;
    printf("%5c|", ' ');
    for(int i = 0; i < ROW; i++){
        printf("%4d ", i+1);
    }
    
    printf("\n");

    for(int row = 0; row < ROW; row++){
        printf("%5c|", row+65); // Print row headers
        for(int column = 0; column < COLUMN; column++){
            // Print each coordinate on ocean grid
            Cell* c = getCell(grid,row,column);
            printf("%4c|", c->symbol);
            //printf("%5d", table[row][column]);
        }
        printf("\n");
    }
}

void displayEnemyGrid(Grid *grid){
// Print the Column headers
    int numOfAlphabetChars = ROW + 65;
    printf("%5c|", ' ');
    for(int i = 0; i < ROW; i++){
        printf("%4d ", i+1);
    }
    
    printf("\n");

    for(int row = 0; row < ROW; row++){
        printf("%5c|", row+65); // Print row headers
        for(int column = 0; column < COLUMN; column++){
            // Print each coordinate on ocean grid
            Cell* c = getCell(grid,row,column);
            char symbol = c->symbol;
            if(symbol==SHIP){
                symbol = WATER;
            }
            printf("%4c|", symbol);
            //printf("%5d", table[row][column]);
        }
        printf("\n");
    }
}

bool updateOceanGrid(Grid *grid, Coordinate target )
{
    Cell* cell = getCell(grid,target.row,target.column);
    if(cell->symbol==SHIP)
    {
        setSymbol(grid,target.row,target.column,HIT);
        return true;
    }else{
        setSymbol(grid,target.row,target.column,MISS);
        return false;
    }
}


void clearScreen(){
    printf("\033[H\033[2J");
    fflush(stdin);
}

void pressEnterToContinue(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void welcomeMessage()
{
    clearScreen();
    printf("Welcome to our Battleship game!\n"
    "This is a CLI version of Battleship made by Sarah Fox, Jake Cermak, Mitchell Humphries, and Christopher Ferrie\n\nPress 'Enter' to continue");
    pressEnterToContinue();
}

void gridSelection(Grid* grid)
{
    clearScreen();
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
        grid->height = ROW;
        grid->width = COLUMN;
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
    initializeOceanGrid(grid);
}

void howToPlay()
{
    clearScreen();
    printf("\n=========================================== How To Play ===========================================\n\n");
    //printf("1. Select a grid size.\n\n");
    printf("1. Place your fleet of 5 ships.\n\n"
    "Each ship can be placed either horizontally or vertically.\n"
    "Depending on the ship type, it will be anywhere from 2 to 5 squares in length\n"
    "Once all ships are placed, they cannot be moved\n"
    "No overlapping with other ships ");
    pressEnterToContinue();
    clearScreen();
    //printf("3. Decide who goes first.\n\n");
    printf("\n2. Player will take turns guessing where the opponent's ships are\n"
    "Player chooses a coordinate on the ocean grid that hasn't been chosen yet as their attack on opponent's ships\n\n"
    "This target will be marked as either a hit or a miss on your view of the opponent's ocean grid\n"
    "If it's a hit, the program will say which ship was hit and the corresponding coordinate will be labeled as a hit\n"
    "If it's a miss, the program will say it's a miss and the corresponding coordinate will be labeled as a miss ");

    pressEnterToContinue();
    clearScreen();
    printf("\n3. The goal of the game is to successfully hit and sink all of the opponent's ships\n"
    "Once all coordinates of a single ship are hit, the ship will be marked as sunk ");

    pressEnterToContinue();
    clearScreen();
    printf("\n4. Continue targetting coordinates until the outcome of the game is decided");
    
    pressEnterToContinue();
    clearScreen();
    printf("\n5. Whoever sinks the opposing fleet of ships first wins the game ");
    pressEnterToContinue();
    printf("\n=============================== Place Your Ships ===============================\n\n");
    printf("You will now begin placing your ships\n");
    printf("You have five ships.\n");
    printf(
        "1. Carrier [5]\n"
        "2. Battleship [4]\n"
        "3. Submarine [3]\n"
        "4. Cruiser [3]\n"
        "5. Destroyer [2]\n\n"
    );
}

void getCoordinates(Coordinate* coordinates)  //change to one input
{
    //char endChar;
    char input_x;
    int input_y;
    int valid = 0;
    while(!valid){
        printf("\nChoose a coordinate (Example: A4): \n");
        scanf("%c%d", &input_x,&input_y);
        input_x = toupper(input_x);
        //printf("%c%d\n",input_x,input_y);
        //printf("what?\n");
        if((input_x >= 'A' && input_x <= ('A'+ROW))&&(input_y >= 1 && input_y <= COLUMN))
        {
            coordinates->row = input_x - 'A';
            coordinates->column = input_y - 1;
            valid = 1;
            //printf("what3?\n");
        }
    }   
    //printf("what2?\n");
    while ((input_x = getchar()) != '\n' && input_x != EOF) {}
}

bool checkLocation(Grid* grid, int size, int orientation, int x, int y);

void shipSelection(Grid* playerGrid) 
{
    clearScreen();
    //displayOceanGrid(playerGrid);
    char *ships[5] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};
    int sizes[5] = {5, 4, 3, 3, 2};
    char direction_input;
    int orientation;
    
    // TODO: This loop should iterate through length of ships array
    // TODO: try using the ShipType enums?
    for (int i = 0; i < 5; i++)
    {
        clearScreen();
        displayOceanGrid(playerGrid);
        while(true)
        {
            printf("\nPick a location to place your %s with a length of: %d", ships[i], sizes[i]);
            Coordinate coordinates = {0};
            getCoordinates(&coordinates);

            printf("\nUser entered:\nrow: %d column: %d\n", coordinates.row, coordinates.column);

            printf("Enter 'V' to place the ship vertically or 'H' to place the ship horizontally:\t");
            scanf("%c", &direction_input);
            direction_input = toupper(direction_input);
            
            if (direction_input == 'V')
            {
                orientation = 0;
            }
            else if (direction_input == 'H')
            {
                orientation = 1;
            }
            else
            {
                printf("Invalid orientation\n");
                continue;
            }
            if(coordinates.row+(sizes[i]*((orientation+1)%2)) >= playerGrid->width || coordinates.column+(sizes[i]*orientation) >= playerGrid->height )
            {
                printf("Invalid Entry, ship out of bounds\n");
                continue;
            }

            while ((direction_input = getchar()) != '\n' && direction_input != EOF) {}  // consume all characters in the input buffer until the \n
            bool available = checkLocation(playerGrid, sizes[i], orientation, coordinates.row, coordinates.column);
            //printf("%s\n",(available)?"available":"unavailable");
            if (available)
            {
                for(int e = 0;((e<sizes[i]) && (e<playerGrid->height));e++)
                {
                    //printf("updating %d:%d - %s\n",coordinates.row,coordinates.column,(orientation)?"Horizontal":"Vertical");
                    //printf("updating %d:%d\n",coordinates.row + (e*((orientation+1)%2)), coordinates.column + (e*orientation));
                    setSymbol(playerGrid, coordinates.row + (e*((orientation+1)%2)), coordinates.column + (e*orientation), SHIP);
                }
                break;
            }
            else 
            {
                printf("Invalid entry, overlapping ship\n");
                continue;
            }
        }
    }
}

//Creates random number
//Used to determine turn order
int GenerateRandomNumber()
{
    int lower = 1, upper = 2;
    int num = (rand() % (upper - lower + 1) + lower);
    printf("%d\n", num);
    return(num);
}

int InitialTurnOrder()
{
    int playerTurn = GenerateRandomNumber();
    if(playerTurn == 1)
    {
        printf("Player 1 starts\n");
        return(1);
    }
    else
    {
        printf("Player 2 starts\n");
        return(0);
    }
}

//Chris's code
bool checkLocation(Grid* grid, int size, int orientation, int x, int y)
{
    //printf("Checking ship location\n");
    for(int i=0;i<size;i++)
    {
        //printf("%d:%d - %s\t", x + (i*((orientation+1)%2)), y + (i*orientation),(orientation)?"Horizontal":"Vertical");
        Cell* loc = getCell(grid, x + (i*((orientation+1)%2)), y + (i*orientation)); //get cell at location x,y
        if(loc->symbol==SHIP)
        {
            return false;
        }
    }
    return true;
}

void ai_placeships(Grid* grid)
{
    int shipSize;
    for(int i=0;i<5;i++)
    {
        if(i<2)
        {
            shipSize = i+2;
        }
        else
        {
            shipSize = i+1;
        }
        while(1)
        {
            int orientation = (rand()%2);
            int startingLocX = (rand()%(grid->height - shipSize*((orientation+1)%2)));
            int startingLocY = (rand()%(grid->height - shipSize*orientation));
            if(!checkLocation(grid,shipSize,orientation,startingLocX,startingLocY))
            {
                continue;
            }
            
            if(orientation==0)
            {
                //horizontal
                for(int e = startingLocX;(e<startingLocX+shipSize) && (e<grid->height);e++)
                {
                    setSymbol(grid, e, startingLocY, SHIP);
                }
            }
            else
            {
                //vertical
                for(int e = startingLocY;(e<startingLocY+shipSize) && (e<grid->height);e++)
                {
                    setSymbol(grid, startingLocX, e, SHIP);
                }
            }
            break;
        }
    }
}

bool checkViable(Cell* cell)
{
    if(cell->symbol==SHIP || cell->symbol==WATER)
    {
        return true;
    }
    return false;
}

int checkDirections(Grid* grid,Cell* cell)
{
    int ret = 0;
    Cell* currentCell;
    for(int i=0;i<4;i++)
    {
        switch(i)
        {
            case 0:
                if(cell->position.row-1<0){
                    continue;
                }
                //set currentCell to up
                currentCell = getCell(grid,cell->position.row-1,cell->position.column);
                break;
            case 1:
                if(cell->position.row+1<grid->height){
                    continue;
                }
                //set currentCell to down
                currentCell = getCell(grid,cell->position.row+1,cell->position.column);
                break;
            case 2:
                if(cell->position.column-1<0){
                    continue;
                }
                //set currentCell to left
                currentCell = getCell(grid,cell->position.row,cell->position.column-1);
                break;
            case 3:
                if(cell->position.column+1<grid->height){
                    continue;
                }
                //set currentCell to right
                currentCell = getCell(grid,cell->position.row,cell->position.column+1);
        }
        if(!(currentCell->symbol==MISS||currentCell->symbol==HIT))
        {
            ret += 1<<i; //going to do some bit magic
        }
    }
}

bool ai_placeAttack(Grid* grid)
{
    int test = 0;
    printf("placing an attack\n");
    static int mode = 0; //determines if it's focus fire or random guess || random guess is 0, focused is 1
    static Cell* lastHit;
    char ship;
    int randx;
    int randy;
    Cell* guess; 
    int guesses;
    //printf("test %d\n",test++);
    switch(mode)
    {
        case 0:
            do
            {
                printf("test %d\n",test++);
                randx = rand()%grid->height;
                randy = rand()%grid->height;
                guess = getCell(grid,randx,randy);
                printf("%d:%d\n",randx,randy);
                pressEnterToContinue();
            }while(!checkViable(guess));
        case 1:
            printf("test %d\n",test++);
            guesses = checkDirections(grid, lastHit);
            if(guesses==0)
            {
                mode = 0;
                return ai_placeAttack(grid);
            }
            for(int i=0;i<4;i++)
            {
                if(guesses>>(3-i)==1)
                {
                    printf("test %d\n",test++);
                    switch(i)
                    {
                        case 0:
                            //set guess to up
                            guess = getCell(grid,lastHit->position.row-1,lastHit->position.column);
                            break;
                        case 1:
                            //set guess to down
                            guess = getCell(grid,lastHit->position.row+1,lastHit->position.column);
                            break;
                        case 2:
                            //set guess to left
                            guess = getCell(grid,lastHit->position.row,lastHit->position.column-=1);
                            break;
                        case 3:
                            //set guess to right
                            guess = getCell(grid,lastHit->position.row,lastHit->position.column+=1);
                    }
                    break;
                }
            }
    }
    printf("test %d\n",test++);
    return updateOceanGrid(grid,guess->position);
}

//Chris's code

int main(void)
{
    setlocale(LC_CTYPE, "");
    srand(time(NULL));

    //Initial turn order, will need to change based on how we setup plyer. Bool is temp
    int turn = InitialTurnOrder();

    //Needed for GenerateRandomNumber function

    welcomeMessage();
    howToPlay();
    
    Grid playerGrid = {ROW,COLUMN};
    Grid aiGrid = {ROW,COLUMN};
    
    initializeOceanGrid(&playerGrid);
    initializeOceanGrid(&aiGrid);
    
    //place ships
    
    ai_placeships(&playerGrid);
    //shipSelection(&playerGrid);
    
    //printf("AI ship placement\n");
    ai_placeships(&aiGrid);
    //printf("Check ai ship placement\n");
    //displayOceanGrid(&aiGrid);
    printf("%d,%s\n",turn,(turn)?"Ai goes first":"Player goes first");
    pressEnterToContinue();

    int player1HP = 17;
    int player2HP = 17;

    while(player2HP > 0 && player1HP >0){ //main gameplay loop
        if(turn==0){
            clearScreen();
            printf("----------Enemy Grid----------\n");
            displayEnemyGrid(&aiGrid);
            printf("\n----------Player Grid----------\n");
            displayOceanGrid(&playerGrid);
            // tell user to choose a location to attack
            Cell* attack={0};
            bool valid;
            Coordinate coord = {0};
            do{
                int i=0;
                printf("%d",i++);
                getCoordinates(&coord);
                printf("%d",i++);
                attack = getCell(&aiGrid,coord.row,coord.column);
                printf("%d",i++);
                valid = checkViable(attack);
                printf("%d",i++);
                if(!valid){
                    printf("invalid attack location\n");
                }
            }while(!valid);
            if(updateOceanGrid(&aiGrid,attack->position)){
                player2HP--;
            }
        }else{
            printf("AI's turn\n");
            if(ai_placeAttack(&playerGrid)){
                player1HP--;
            }
            pressEnterToContinue();
        }
        turn = (turn+1)%2; // flip the turn
    }
    // TODO: This should go in separate function?
    if(player2HP == 0)
    {
        printf("Player 1 wins\n");
    }
    else if(player1HP == 0)
    {
        printf("Player 2 wins\n");
    }

}