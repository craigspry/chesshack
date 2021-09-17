#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef struct Pieces
{
    char colour;
    char type;
    int id;
    int importance;
    int moves;

} Piece;

typedef struct Boards
{
    Piece *board[8][8];
    int score;
    int depth;
    struct Boards* parent;
    struct Boards* children;
    struct Boards* lastsibbling;
    struct Boards* nextsibbling;
} Board;

typedef struct BoardLists
{
    Piece *board[8][8];
    struct BoardLists* next;
    struct BoardLists* last;
} BoardList;


typedef struct Moves
{
    int orow;
    int ocol;
    int row;
    int col;
    struct Moves* next;
    struct Moves* last;
} MoveList;

#endif // TYPES_H_INCLUDED
