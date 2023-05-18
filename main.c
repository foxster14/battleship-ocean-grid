#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include "header.h"
#include "battleship-text.c"

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
        }
    }
    
}

void displayOceanGrid(Grid *grid)
{
    // Print the Column headers
    printf("%5c|", ' ');
    for(int i = 0; i < ROW; i++){
        printf("%4d ", i+1);
    }
    
    printf("\n");

    for(int row = 0; row < ROW; row++){
        printf("%5c|", row+'A'); // Print row headers
        for(int column = 0; column < COLUMN; column++){
            // Print each coordinate on ocean grid
            Cell* c = getCell(grid,row,column);
            printf("%s%4c%s|", WATER_COLOR, c->symbol, DEFAULT);
        }
        printf("\n");
    }
}

void displayEnemyGrid(Grid *grid){
// Print the Column headers
    printf("%5c|", ' ');
    for(int i = 0; i < ROW; i++){
        printf("%4d ", i+1);
    }
    
    printf("\n");

    for(int row = 0; row < ROW; row++){
        printf("%5c|", row+'A'); // Print row headers
        for(int column = 0; column < COLUMN; column++){
            // Print each coordinate on ocean grid
            Cell* c = getCell(grid,row,column);
            char symbol = c->symbol;
            if(symbol==SHIP){
                symbol = WATER;
            }
            printf("%s%4c%s|", WATER_COLOR, symbol, DEFAULT);
        }
        printf("\n");
    }
}

bool updateOceanGrid(Grid *grid, Coordinate target )
{
    Cell* cell = getCell(grid,target.row,target.column);
    if(cell->symbol==SHIP)
    {
        //printf("%s", RED);
        setSymbol(grid,target.row,target.column,HIT);
        printf("%s", DEFAULT);
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
    coolText();
    printf("Press 'enter' to continue.");
    pressEnterToContinue();
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

void welcomeHeader(char* c){
    printf("=========================================== %s ===========================================\n\n", c);
}

void howToPlay()
{
    clearScreen();
    welcomeHeader("How To Play");
    //printf("1. Select a grid size.\n\n");
    printf("1. Place your fleet of 5 ships.\n\n"
    "Each ship can be placed either horizontally or vertically.\n"
    "Depending on the ship type, it will be anywhere from 2 to 5 squares in length\n"
    "Once all ships are placed, they cannot be moved\n"
    "No overlapping with other ships ");
    pressEnterToContinue();
    clearScreen();
    //printf("3. Decide who goes first.\n\n");
    welcomeHeader("How To Play");
    printf("2. Player will take turns guessing where the opponent's ships are\n"
    "Player chooses a coordinate on the ocean grid that hasn't been chosen yet as their attack on opponent's ships\n\n"
    "This target will be marked as either a hit or a miss on your view of the opponent's ocean grid\n"
    "If it's a hit, the program will say which ship was hit and the corresponding coordinate will be labeled as a hit\n"
    "If it's a miss, the program will say it's a miss and the corresponding coordinate will be labeled as a miss\n");

    pressEnterToContinue();
    clearScreen();
    welcomeHeader("How To Play");
    printf("3. The goal of the game is to successfully hit and sink all of the opponent's ships\n"
    "Once all coordinates of a single ship are hit, the ship will be marked as sunk\n");

    pressEnterToContinue();
    clearScreen();
    welcomeHeader("How To Play");
    printf("4. Continue targetting coordinates until the outcome of the game is decided\n");
    
    pressEnterToContinue();
    clearScreen();
    welcomeHeader("How To Play");
    printf("5. Whoever sinks the opposing fleet of ships first wins the game!\n");
    printf("Now press 'enter' and let's play!\n");
    pressEnterToContinue();
    clearScreen();

    welcomeHeader("Place Your Ships");
    printf("You will now begin placing your ships\n");
    printf("You have five ships.\n");
    printf(
        "1. Carrier [5]\n"
        "2. Battleship [4]\n"
        "3. Submarine [3]\n"
        "4. Cruiser [3]\n"
        "5. Destroyer [2]\n\n"
    );
    pressEnterToContinue();
    clearScreen();
}

void getCoordinates(Coordinate* coordinates) 
{
    char input_x;
    int input_y;
    int valid = 0;
    while(!valid){
        printf("\nChoose a coordinate (Example - A4):  ");
        scanf("%c%d", &input_x,&input_y);
        input_x = toupper(input_x);

        if((input_x >= 'A' && input_x <= ('A'+ROW))&&(input_y >= 1 && input_y <= COLUMN))
        {
            coordinates->row = input_x - 'A';
            coordinates->column = input_y - 1;
            valid = 1;
        }
    }   
    while ((input_x = getchar()) != '\n' && input_x != EOF) {}
}

bool checkLocation(Grid* grid, int size, int orientation, int x, int y);

void shipSelection(Grid* playerGrid) 
{
    clearScreen();
    char *ships[5] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};
    int sizes[5] = {5, 4, 3, 3, 2};
    char direction_input;
    int orientation;
    
    //Iterate through ship array to place all 5 ships
    for (int i = 0; i < 5; i++)
    {
        clearScreen();
        welcomeHeader("Ship Placement");
        displayOceanGrid(playerGrid);
        while(true)
        {
            
            printf("\nPick a location to place your %s[%d]:  ", ships[i], sizes[i]);
            Coordinate coordinates = {0};
            getCoordinates(&coordinates);

            printf("Enter 'V' to place the ship vertically or 'H' to place the ship horizontally:  ");
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
            if(coordinates.row+(sizes[i]*((orientation+1)%2)) > playerGrid->width || coordinates.column+(sizes[i]*orientation) > playerGrid->height )
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
        //printf("Player 1 starts\n");
        return(1);
    }
    else
    {
        //printf("Player 2 starts\n");
        return(0);
    }
}


bool checkLocation(Grid* grid, int size, int orientation, int x, int y)
{
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

void randomlyPlaceShips(Grid* grid)
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

int checkDirections(Grid* grid,Cell cell)
{
    int ret = 0;
    int add;
    Cell* currentCell;
    for(int i=0;i<4;i++)
    {
        switch(i)
        {
            case 0:
                if(cell.position.row-1<0){
                    continue;
                }
                //printf("set currentCell to up\n");
                currentCell = getCell(grid,cell.position.row-1,cell.position.column);
                add = 1;
                break;
            case 1:
                if(cell.position.row+1>=grid->height){
                    continue;
                }
                //printf("set currentCell to down\n");
                currentCell = getCell(grid,cell.position.row+1,cell.position.column);
                add = 2;
                break;
            case 2:
                if(cell.position.column-1<0){
                    continue;
                }
                //printf("set currentCell to left\n");
                currentCell = getCell(grid,cell.position.row,cell.position.column-1);
                add = 4;
                break;
            case 3:
                if(cell.position.column+1>=grid->height){
                    continue;
                }
                //printf("set currentCell to right\n");
                currentCell = getCell(grid,cell.position.row,cell.position.column+1);
                add = 8;
        }
        if(!(currentCell->symbol==MISS||currentCell->symbol==HIT))
        {
            //printf("%c\n",currentCell->symbol);
            ret += add; //going to do some bit magic
        }
    }
    return ret;
}

bool ai_placeAttack(Grid* grid,Coordinate* pos)
{
    static int mode = 0; //determines if it's focus fire or random guess || random guess is 0, focused is 1
    static Cell lastHit = {0};
    int randx;
    int randy;
    Cell* guess; 
    int guesses;
    //printf("Last hit = %d:%d\n",lastHit.position.row,lastHit.position.column);
    switch(mode)
    {
        case 0:
            do
            {
                //printf("test %d\n",test++);
                randx = rand()%grid->height;
                randy = rand()%grid->height;
                guess = getCell(grid,randx,randy);
                //printf("%d:%d\n",guess->position.row,guess->position.column);
                //pressEnterToContinue();
            }while(!checkViable(guess));
            break;
        case 1:
            guesses = checkDirections(grid, lastHit);
            //printf("Guesses: %d\n",guesses);
            if(guesses==0)
            {
                mode = 0;
                return ai_placeAttack(grid,pos);
            }
            for(int i=0;i<4;i++)
            {
                //printf("guesses: %d\n",guesses>>(3-i));
                if(guesses>>(3-i)==1)
                {
                    switch(i)
                    {
                        case 3:
                            //printf("set guess to up\n");
                            guess = getCell(grid,lastHit.position.row-1,lastHit.position.column);
                            break;
                        case 2:
                            //printf("set guess to down\n");
                            guess = getCell(grid,lastHit.position.row+1,lastHit.position.column);
                            break;
                        case 1:
                            //printf("set guess to left\n");
                            guess = getCell(grid,lastHit.position.row,lastHit.position.column-1);
                            break;
                        case 0:
                            //printf("set guess to right");
                            guess = getCell(grid,lastHit.position.row,lastHit.position.column+1);
                    }
                    break;
                }
            }
        break;
    }
    //printf("test %d\n",test++);
    bool status = updateOceanGrid(grid,guess->position);
    //printf("Computer chose: %c%d -> %s\n",(guess->position.row + 65),guess->position.column, (status)?"Hit":"Miss");
    if(status)
    {
        //printf("hit condition\n");
        lastHit = *guess;
        mode = 1;
    }
    *pos = guess->position;
    return status;
}

void showDisplays(Grid *player, Grid* enemy)
{
    printf("\n");
    printf("\n");
    welcomeHeader("Enemy Grid");
    displayEnemyGrid(enemy);
    printf("\n");
    welcomeHeader("Player Grid");
    displayOceanGrid(player);
}

int main(void)
{
    //setlocale(LC_CTYPE, ""); //Needed for Unicode (couldn't get unicode to work)
    srand(time(NULL)); //Needed for GenerateRandomNumber function

    int turn = InitialTurnOrder();

    welcomeMessage();
    howToPlay();
    
    Grid playerGrid = {10,10, 0};
    Grid aiGrid = {10,10, 0};
    
    initializeOceanGrid(&playerGrid);
    initializeOceanGrid(&aiGrid);
    randomlyPlaceShips(&aiGrid);
    //place ships
    
    bool cont = true;
    char selection,c;
    while(cont){
        clearScreen();
        printf("Would you like to Manually (m) or Randomly (r) place your ships?  ");
        scanf("%c",&selection);
        selection = tolower(selection);
        while ((c = getchar()) != '\n' && c != EOF) {}
        if(selection=='r'){
            randomlyPlaceShips(&playerGrid);
        }else{
            shipSelection(&playerGrid);
        }
        displayOceanGrid(&playerGrid);
        printf("\nContinue with current ship layout? (y,n)  ");
        scanf("%c",&selection);
        while ((c = getchar()) != '\n' && c != EOF) {}
        if(selection=='y'){
            cont = false;
        }else{
            initializeOceanGrid(&playerGrid);
        }
    }
    
    
    printf("\n%s",(turn)? "Computer goes first" : "Player goes first");
    printf("\nPress 'enter' to continue.");
    pressEnterToContinue();
    clearScreen();

    int player1HP = 17;
    int player2HP = 17;

    while(player2HP > 0 && player1HP >0){ //main gameplay loop
        if(turn == 0){
            clearScreen();
            showDisplays(&playerGrid,&aiGrid);
            // tell user to choose a location to attack
            Cell* attack={0};
            bool valid;
            Coordinate coord = {0};
            do{
                getCoordinates(&coord);
                attack = getCell(&aiGrid,coord.row,coord.column);
                valid = checkViable(attack);
                if(!valid){
                    printf("Invalid attack location, please try again\n");
                }
            }while(!valid);

            bool hit = updateOceanGrid(&aiGrid,attack->position);
            clearScreen();
            showDisplays(&playerGrid,&aiGrid);
            if(hit){
                printf("Hit!\n");
                player2HP--;
            }else{
                printf("Miss\n");
            }
            pressEnterToContinue();
        }else{
            clearScreen();
            printf("\nComputer's turn: \n");
            Coordinate guess = {0};
            bool hit = ai_placeAttack(&playerGrid,&guess);
            showDisplays(&playerGrid,&aiGrid);
            printf("Computer chose: %c%d -> %s\n",(guess.row + 'A'), guess.column + 1, (hit)?"Hit":"Miss");
            if(hit){
                player1HP--;
            }
            printf("Press 'enter' to continue.");
            pressEnterToContinue();
        }
        turn = (turn+1)%2; // flip the turn
    }
    
    if(player2HP == 0)
    {
        printf("Congratulations!!! You have won!!\n");
    }
    else if(player1HP == 0)
    {
        printf("Better luck next time, Computer wins.\n");
    }

}