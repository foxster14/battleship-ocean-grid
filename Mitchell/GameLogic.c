#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct TempPlayer
{
    int playerID;
    int playerHP;
}player;

//Creates random number
//Used to determine turn order
int GenerateRandomNumber()
{
    int lower = 1, upper = 2;
    int num = (rand() % (upper - lower + 1) + lower);
    printf("%d\n", num);
    return(num);
}

/* bool DetermineTurnOrder()
{
    int randomNum = GenerateRandomNumber();
    int player1Guess = 0;

    bool player1Turn = false;
    
    printf("Guess a 1 (Heads) or 2 (Tails) to determine turn order.\n");
    scanf("%d", &player1Guess);

    printf("You entered: %s | Actual: %s\n", (player1Guess ? "Heads" : "Tails"), (randomNum ? "Heads" : "Tails"));

    //Sets player order
    if(player1Guess == randomNum)
    {
        player1Turn = true;

        return(player1Turn);
    }
    else
    {
        player1Turn = false;

        return(player1Turn);
    }
} */

void PlayGame()
{
    //temp variables and values for players health
    int player1HP = 2, player2HP = 2;

    //Needed for GenerateRandomNumber function
    srand(time(NULL));

    //Initial turn order, will need to change based on how we setup plyer. Bool is temp
    int player = InitialTurnOrder();

    do 
    {
        switch(player)
        {
        //Player 
        case(1):
            printf("------------------PLAYER 2's OCEAN GRID------------------\n");
            //METHOD FOR PRINTING BOARD HERE
            printf("Player 1's turn\n");
            //METHOD FOR PICKING HIT LOCATION
            player2HP--; //Method will be here to determine if hit damages player
            player = 0;
        break;

        //Computer
        case(2):
            //METHOD FOR PRINTING BOARD HERE
            printf("Wait for other player.\n");
            //METHOD FOR PICKING HIT LOCATION
            player1HP--; //Method will be here to determine if hit damages player
            player = 1;
        break;
        }
    }while(player1HP > 0 && player2HP > 0);

    if(player2HP == 0)
    {
        printf("Player 1 wins\n");
    }
    else
    {
        printf("Player 2 wins\n");
    }
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
        return(2);
    }
}

/* void HandleTurns(struct TempPlayer currentPlayer)
{
    currentPlayer.playerID = InitialTurnOrder();
    printf("Player %d's turn.\n", currentPlayer.playerID);
    printf("------------------PLAYER 1's OCEAN GRID------------------\n");
    do
    {
        
    } while (currentPlayer.playerHP > 0);
    
} */

/* int main(void)
{
    srand(time(NULL));
    player p1 = {1, 17};
    player p2 = {2, 17};
    
    
    //printf("Player ID: %d\n", p1.playerID);
    //printf("Player HP: %d\n", p2.playerHP);

    //InitialTurnOrder();
    //HandleTurns(p1);
    PlayGame();
} */