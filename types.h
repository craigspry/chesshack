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

typedef struct Moves
{
    int orow;
    int ocol;
    int row;
    int col;
    int score;
    struct Moves* next;
    struct Moves* last;
} MoveList;

#endif // TYPES_H_INCLUDED
