#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED

#include "types.h"

void initialise_board(Piece *board[8][8]);
Piece* initialise_piece(char type, char colour, int id, int importance);
void initialise_side(Piece *board[8][8], char colour, int row, int prow, int multiplier);
void freemem(Piece *Poard[8][8]);
Coord* getmoves(int row, int col, char colour, Piece *board[8][8]);
void printboard(Piece *board[8][8]);
BoardList* rookmoves(int row, int col, Piece *board[8][8]);
BoardList* pawnmoves(int row, int col, Piece *board[8][8]);
BoardList* joinlists(BoardList* list1, BoardList* list2);
BoardList* gethead(BoardList* list1);
BoardList* gettail(BoardList* list1);


#endif // MOVES_H_INCLUDED
