#include "types.h"
#include "moves.h"



int main(void)
{
    Piece *main_board[8][8];
    memset(main_board, 0, sizeof main_board);
    initialise_board(main_board);

    //BoardList* list = getmoves(1,1, 'b', main_board);
    Board b ;
    copyboard(main_board, b.board);
    //b.board = main_board;
    generatemovetree(&b, 'w', 'w');
    generatemovetree(&b, 'b', 'b');
    printboard(main_board);
    freemem(main_board);
    return 0;
}



