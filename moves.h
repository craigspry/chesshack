#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED

#include "types.h"

void initialise_board(Piece *board[8][8]);
Piece* initialise_piece(char type, char colour, int id, int importance);
void initialise_side(Piece *board[8][8], char colour, int row, int prow, int multiplier);
void freemem(Piece *Poard[8][8]);
void movepiece(int row, int col, int newrow, int newcol, Piece *board[8][8]);

void printboard(Piece *board[8][8]);

MoveList* getmoves(int row, int col, char colour, Piece *board[8][8]);
MoveList* rookmoves(int row, int col, Piece *board[8][8]);
MoveList* pawnmoves(int row, int col, Piece *board[8][8]);
MoveList* bishopmoves(int row, int col, Piece *board[8][8]);
MoveList* kingmoves(int row, int col, Piece *board[8][8]);
MoveList* knightmoves(int row, int col, Piece *board[8][8]);


MoveList* generatemove(int row, int col, int newrow, int newcol, Piece *board[8][8], MoveList* list);
int validatemove(int orow,int ocol, int nrow, int ncol, Piece *board[8][8], MoveList** movelist);

int incheck(char colour, Piece *board[8][8]);
MoveList* getmovelisthead(MoveList* list1);
MoveList* getmovelisttail(MoveList* list1);
MoveList* joinmovelists(MoveList* list1, MoveList* list2);



BoardList* gethead(BoardList* list1);
BoardList* gettail(BoardList* list1);
BoardList* joinlists(BoardList* list1, BoardList* list2);



void copyboard(Piece *origboard[8][8], Piece *newboard[8][8]);
int calcscore(Piece *board[8][8]);
void generatemovetree(Board *root, char rootcolour, char movecolour, int depth);



#endif // MOVES_H_INCLUDED
