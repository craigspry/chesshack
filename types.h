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

typedef struct Coords
{
   int row;
   int col;
   int score;
   struct Coords* next;
   struct Coords* last;
} Coord;

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

#endif // TYPES_H_INCLUDED
