#include "header.h"

void getCoordinates(Coordinate* coordinates, int height)  //change to one input
{
    char endChar;

    switch(height){
        case 8:
            endChar = 'H';
            break;
        case 8:
            endChar = 'L';
            break;
        case 8:
            endChar = 'X';
            break;
        default:
        printf("Invalid grid size\n");
    }

    char input_x;
    int input_y;
    int valid = 0;
    while(!valid){
        printf("\nYou will now choose where you would like to place your ships.\n");
        scanf("%c%d", &input_x,&input_y);
        input_x = toupper(input_x);

        if((input_x >= 'A' && input_x <= endChar)&&(input_y >= 1 && input_y <= height))
        {
            coordinates->row = input_x - 'A';
            coordinates->column = input_y - 1;
            valid = 1;
        }
        while ((input_x = getchar()) != '\n' && input_x != EOF) {}
    }   
}

int main(){
    Coordinate coord;

    getCoordinates(&coord,12);

    printf("%c%d\n",coord.row+'A',coord.column+1);
}