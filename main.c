#include "types.h"
#include "moves.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    Piece *main_board[8][8];
    memset(main_board, 0, sizeof main_board);
    initialise_board(main_board);


    for(int i=0;i<50;++i)
    {
        MoveList* move = generatemovetree(main_board, 'w', 'w', 5);
        if(move == NULL)
        {
            printf("B WIN\n");
            return 0;
        }
        printf("W Best move %d\n", move->score);
        movepiecereal(move->orow, move->ocol, move->row, move->col, main_board);
        move->last=NULL;
        move->next=NULL;
        free(move);


        //copyboard(bestMove->board, main_board);
        printboard(main_board);
        move = generatemovetree(main_board, 'b', 'b', 5);
        if(move == NULL)
        {
            printf("W WIN\n");
            return 0;
        }
        printf("B Best move %d\n", move->score);
        movepiecereal(move->orow, move->ocol, move->row, move->col, main_board);
        printboard(main_board);
    }

    freemem(main_board);
    return 0;
}



