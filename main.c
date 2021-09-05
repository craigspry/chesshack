#include "types.h"
#include "moves.h"
#include <stdlib.h>



int main(void)
{
    Piece *main_board[8][8];
    memset(main_board, 0, sizeof main_board);
    initialise_board(main_board);


    for(int i=0;i<50;++i)
    {
        Board b, b2;
        int topScore=0;
        int topScoreb=0;
        Board* bestMove=NULL;
        copyboard(main_board, b.board);
        b.children = NULL;
        b.score = 0;
        b.lastsibbling = NULL;
        b2.children = NULL;
        generatemovetree(&b, 'w', 'w', 1);
        topScore = b.children->score;
        bestMove = b.children;
        if(b.children = NULL)
        {
            printf("B WIN\n");
            return 0;
        }
        for(Board* best=b.children;best!=NULL; best=best->lastsibbling)
        {
            if(best->score >= topScore)
            {
                topScore = best->score;
                bestMove = best;
            }
        }
        copyboard(bestMove->board, main_board);
        printboard(main_board);
        copyboard(main_board, b2.board);
        generatemovetree(&b2, 'b', 'b', 1);
        bestMove = b2.children;
        if(b2.children == NULL)
        {
            printf("W WIN\n");
        }
        topScoreb = b2.children->score;
        for(Board* best=b2.children;best!=NULL; best=best->lastsibbling)
        {
            if(best->score <= topScoreb)
            {
                topScoreb = best->score;
                bestMove = best;
            }
        }
        copyboard(bestMove, main_board);
        printboard(main_board);
    }

    freemem(main_board);
    return 0;
}



