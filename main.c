#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "2048.h"

#include "SDL2/SDL.h"

int main(int argc, char* args[])
{
    time_t t;
    srand((unsigned) time(&t));

    char Dir = '\0';


    GameBoard * theBoard;
    theBoard = (GameBoard *) malloc(sizeof(GameBoard));
  
    InitBoard(theBoard);


    PrintBoard(theBoard);
    while (true)
    {
        printf("\n");
        scanf("%c", &Dir);
        printf("\n");

        switch (Dir)
        {
            case 'w':
                MoveBoardUp(theBoard);
                break;
            case 'a':
                MoveBoardLeft(theBoard);
                break;
            case 's':
                MoveBoardDown(theBoard);
                break;
            case 'd':
                MoveBoardRight(theBoard);
                break;
            default:
                break;
        }
        PrintBoard(theBoard);
    }



}
