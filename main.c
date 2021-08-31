#include "types.h"
#include "moves.h"



int main(void)
{
    Piece *main_board[8][8];
    memset(main_board, 0, sizeof main_board);
    initialise_board(main_board);
    getmoves(1,1, 'b', main_board);
    printboard(main_board);
    freemem(main_board);
    return 0;
}



