#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "moves.h"
#include <string.h>
#include <unistd.h>

void printboard(Piece *board[8][8])
{
    system ( "clear" );
    printf("\n_________________________________\n");
    for(int i=0;i<8;++i)
    {

        printf("|");
        for(int j=0;j<8;++j)
        {
            if(board[i][j])
            {
                printf("%c%c%i|", board[i][j]->colour, board[i][j]->type, board[i][j]->id);
            }
            else
            {
                printf("   |");
            }

        }
        printf("\n_________________________________\n");
    }
    sleep(1);

}

MoveList* getmoves(int row, int col, char colour, Piece *board[8][8])
{
    MoveList* list = NULL;
    if(board[row][col] == NULL)
    {
        return NULL;
    }
    if(board[row][col]->colour != colour)
    {
        return NULL;
    }
    if(board[row][col]->type == 'p' && board[row][col]->colour==colour)
    {
        list = pawnmoves(row,col, board);
    }
    if(board[row][col]->type == 'r' && board[row][col]->colour==colour)
    {
        list = rookmoves(row,col, board);
    }
    if(board[row][col]->type == 'b' && board[row][col]->colour==colour)
    {
        list = bishopmoves(row,col, board);
    }
    if(board[row][col]->type == 'q' && board[row][col]->colour==colour)
    {
        list = rookmoves(row,col, board);
        list = joinmovelists(list, bishopmoves(row,col, board));
    }
    if(board[row][col]->type == 'k' && board[row][col]->colour==colour)
    {
        list = kingmoves(row,col, board);
    }
    if(board[row][col]->type == 'n' && board[row][col]->colour==colour)
    {
        list = knightmoves(row,col, board);
    }
    return list;
}

char oppositecolour(char colour)
{
    return colour == 'w' ?  'b' : 'w';
}

void generatemovetree(Board *root, char rootcolour, char movecolour, int depth)
{
    if(depth < 1)
    {
        return;
    }
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            MoveList* moves = getmoves(i,j, movecolour, root->board);
            MoveList* move = getmovelisthead(moves);
            while(move != NULL)
            {
                Board *board = (Board*) malloc(sizeof(Board));
                copyboard(root->board, board->board);
                movepiece(move->orow, move->ocol, move->row, move->col, board->board);
                board->score = calcscore(board->board);
                if(incheck(movecolour, board->board)==0)
                {
                    if(root->children == NULL)
                    {
                        root->children = board;
                    }
                    else
                    {
                            root->children->nextsibbling = board;
                            board->lastsibbling = root->children;
                            root->children = board;
                    }
                    generatemovetree(root->children, oppositecolour(movecolour), rootcolour, depth-1);
                }
                else
                {
                    free(board);
                }
                //BoardList* nextmove = move->next;
                MoveList* lastmove = move;
                move = move->next;
                free(lastmove);
            }
        }
    }
}

MoveList* generatemoves(Piece *board[8][8], char movecolour)
{
    MoveList* rtn=NULL;
    int cntr = 0;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            MoveList* moves = getmoves(i,j, movecolour, board);
            if(moves != NULL)
            {
                ++cntr;
            }
            rtn = joinmovelists(rtn, moves);
        }
    }
    return getmovelisthead(rtn);
}

int calcscore(Piece *board[8][8])
{
    int score = 0;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(board[i][j])
            {
                score += board[i][j]->importance;
            }
        }
    }
    return score;
}

void copyPiece(Piece* in, Piece* out)
{
    out->colour = in->colour;
    out->id = in->id;
    out->importance = in->importance;
    out->moves = in->moves;
    out->type = in->type;
}

void copyboard(Piece *origboard[8][8], Piece *newboard[8][8])
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            //printf("%d %d\n", i, j);
            if(origboard[i][j])
            {
                Piece *pce = (Piece*) malloc(sizeof(Piece));
                copyPiece(origboard[i][j], pce);
                newboard[i][j] = pce;
            }
            else
            {
                newboard[i][j] = origboard[i][j];
            }

        }
    }
}


MoveList* generatemove(int row, int col, int newrow, int newcol, Piece *board[8][8], MoveList* list)
{
    MoveList* rtn = (MoveList*) malloc(sizeof(MoveList));
    rtn->ocol = col;
    rtn->orow = row;
    rtn->col = newcol;
    rtn->row = newrow;
    rtn->next = NULL;
    if(list != NULL)
    {
        list->next = rtn;
        rtn->last = list;
    }
    else
    {
        rtn->last = NULL;
        rtn->next = NULL;
    }
    return rtn;

}


void movepiece(int row, int col, int newrow, int newcol, Piece *board[8][8])
{
    board[newrow][newcol] = board[row][col];
    //board[newrow][newcol]->moves++;
    board[row][col] = NULL;
}

MoveList* pawnmoves(int row, int col, Piece *board[8][8])
{
    MoveList* rtn = NULL;

    if(board[row][col]->type == 'p' && board[row][col]->colour=='w')
    {
        if(row>0 && !board[row-1][col])
        {
            rtn = generatemove(row, col, row-1, col, board, rtn);
        }
        if(row>0 && col<7 && board[row-1][col+1] != NULL && board[row-1][col+1]->colour=='b')
        {
            rtn = generatemove(row, col, row-1, col+1, board, rtn);
        }
        if(row>0 && col>0 && board[row-1][col-1] != NULL && board[row-1][col-1]->colour=='b')
        {
            rtn = generatemove(row, col, row-1, col-1, board, rtn);
        }
        if(row==6 && !board[row-2][col])
        {
            rtn = generatemove(row, col, row-2, col, board, rtn);
        }

    }
    if(board[row][col]->type == 'p' && board[row][col]->colour=='b')
    {
        if(row<7 && !board[row+1][col])
        {
            rtn = generatemove(row, col, row+1, col, board, rtn);
        }
        if(row<7 && col<7 && board[row+1][col+1] != NULL && board[row+1][col+1]->colour=='w')
        {
            rtn = generatemove(row, col, row+1, col+1, board, rtn);
        }
        if(row<7 && col>0 && board[row+1][col-1] != NULL && board[row+1][col-1]->colour=='w')
        {
            rtn = generatemove(row, col, row+1, col-1, board, rtn);
        }
        if(row==1 && !board[row+2][col])
        {
            rtn = generatemove(row, col, row+2, col, board, rtn);
        }
    }
    return rtn;
}

MoveList* rookmoves(int row, int col, Piece *board[8][8])
{
    MoveList* rtn = NULL;

    for(int i=row+1;i<8;++i)
    {
        if(validatemove(row, col, i, col, board, &rtn)<0)
        {
            break;
        }
    }
    for(int i=row-1;i>=0;--i)
    {
        if(validatemove(row, col, i, col, board, &rtn)<0)
        {
            break;
        }
    }

    for(int i=col-1;i>=0;--i)
    {
        if(validatemove(row, col, row, i, board, &rtn)<0)
        {
            break;
        }
    }
    for(int i=col+1;i<8;++i)
    {
        if(validatemove(row, col, row, i, board, &rtn)<0)
        {
            break;
        }
    }
    return rtn;
}

int validatemove(int orow,int ocol, int nrow, int ncol, Piece *board[8][8], MoveList** movelist)
{
    if((nrow>7 || nrow<0) || (ncol>7 || ncol<0))
    {
        return -4;
    }
    if(board[nrow][ncol] && board[nrow][ncol]->colour==board[orow][ocol]->colour)
    {
        return -1;
    }
    *movelist = generatemove(orow, ocol, nrow, ncol, board, *movelist);
    if(board[nrow][ncol] && board[nrow][ncol]->colour!=board[orow][ocol]->colour)
    {
        return -2;
    }
    return 0;
}

int incheck(char colour, Piece *board[8][8])
{
    int isincheck=0;
    MoveList* moves = generatemoves(board, oppositecolour(colour));
    int krow=-1, kcol=-1;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(board[i][j] && board[i][j]->type=='k' && board[i][j]->colour == colour)
            {
                krow = i;
                kcol = j;
            }
        }
    }
    moves = getmovelisthead(moves);
    while(moves!=NULL)
    {
        if(moves->col == kcol && moves->row == krow)
        {
            isincheck = 1;
        }
        MoveList* lastmove = moves;
        moves = moves->next;
        free(lastmove);
        lastmove = NULL;

    }
    return isincheck;

}

MoveList* bishopmoves(int row, int col, Piece *board[8][8])
{
    MoveList* rtn = NULL;
    for(int i=row+1,j=col+1;i<8&&j<8;++i,++j)
    {
        if(validatemove(row, col, i,j, board, &rtn)<0)
        {
            break;
        }
    }

    for(int i=row-1,j=col+1;i>-1&&j<8;--i,++j)
    {
        if(validatemove(row, col, i,j, board, &rtn)<0)
        {
            break;
        }
    }

    for(int i=row+1,j=col-1;i<8&&j>-1;++i,--j)
    {
        if(validatemove(row, col, i,j, board, &rtn)<0)
        {
            break;
        }
    }
    for(int i=row-1,j=col-1;i>-1&&j>-1;--i,--j)
    {
        if(validatemove(row, col, i,j, board, &rtn)<0)
        {
            break;
        }
    }
    return rtn;
}

MoveList* kingmoves(int row, int col, Piece *board[8][8])
{
    MoveList* rtn = NULL;
    for(int i=-1;i<2;++i)
    {
        for(int j=-1;j<2;++j)
        {
            if(!(i==0 && j==0))
            {
                validatemove(row, col, row+i,col+j, board, &rtn);
            }
        }
    }
    return rtn;
}

MoveList* knightmoves(int row, int col, Piece *board[8][8])
{
    MoveList* rtn = NULL;
    int cols[] ={-2,-2,-1,-1,1,1, 2,2};
    int rows[] ={-1, 1,-2, 2,2,-2,1,-1};
    for(int i=0;i<7;++i)
    {
        validatemove(row, col, row+rows[i],col+cols[i], board, &rtn);
    }
    return rtn;
}

BoardList* joinlists(BoardList* list1, BoardList* list2)
{
    if(list1==NULL && list2 == NULL)
    {
        return NULL;
    }
    if(list1!=NULL && list2 == NULL)
    {
        return gethead(list1);
    }
    if((list1==NULL && list2 != NULL))
    {
        return gethead(list2);
    }
    BoardList* head2=gethead(list2);
    BoardList* tail1=gettail(list1);

    tail1->next = head2;
    head2->last = tail1;

    return gethead(head2);

}

BoardList* gethead(BoardList* list1)
{
    BoardList *head = list1;
    if(head==NULL)
    {
        return NULL;
    }
    while(head->last!=NULL)
    {
        head = head->last;
    }
    return head;
}

BoardList* gettail(BoardList* list1)
{
    BoardList *tail = list1;
    if(tail==NULL)
    {
        return NULL;
    }
    while(tail->next!=NULL)
    {
        tail = tail->next;
    }
    return tail;
}


MoveList* getmovelisthead(MoveList* list1)
{
    MoveList *head = list1;
    if(head==NULL)
    {
        return NULL;
    }
    while(head->last!=NULL)
    {
        head = head->last;
    }
    return head;
}

MoveList* getmovelisttail(MoveList* list1)
{
    MoveList *tail = list1;
    if(tail==NULL)
    {
        return NULL;
    }
    while(tail->next!=NULL)
    {
        tail = tail->next;
    }
    return tail;
}

MoveList* joinmovelists(MoveList* list1, MoveList* list2)
{
    if(list1==NULL && list2 == NULL)
    {
        return NULL;
    }
    if(list1!=NULL && list2 == NULL)
    {
        return getmovelisthead(list1);
    }
    if((list1==NULL && list2 != NULL))
    {
        return getmovelisthead(list2);
    }
    MoveList* head2=getmovelisthead(list2);
    MoveList* tail1=getmovelisttail(list1);

    tail1->next = head2;
    head2->last = tail1;

    return getmovelisthead(head2);

}

void initialise_board(Piece *board[8][8])
{
    initialise_side(board, 'b', 0, 1, -1);
    initialise_side(board, 'w', 7, 6, 1);
}

void initialise_side(Piece *board[8][8], char colour, int row, int prow, int multiplier)
{
    board[row][0] = initialise_piece( 'r', colour, 1, 50 * multiplier);
    board[row][1] = initialise_piece( 'n', colour, 1, 30 * multiplier);
    board[row][2] = initialise_piece( 'b', colour, 1, 30 * multiplier);
    board[row][3] = initialise_piece( 'q', colour, 1, 90 * multiplier);
    board[row][4] = initialise_piece( 'k', colour, 1, 900 * multiplier);
    board[row][5] = initialise_piece( 'b', colour, 2, 30 * multiplier);
    board[row][6] = initialise_piece( 'n', colour, 2, 30* multiplier);
    board[row][7] = initialise_piece( 'r', colour, 2, 50);

    for(int i=0;i<8;++i)
    {
        board[prow][i] = initialise_piece( 'p', colour, i+1, 10* multiplier);
    }
}

Piece* initialise_piece(char type, char colour, int id, int importance)
{
    Piece *pce = (Piece*) malloc(sizeof(Piece));
    pce->type = type;
    pce->colour = colour;
    pce->id = id;
    pce->importance = importance;
    return pce;
}

void freemem(Piece *board[8][8])
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(board[i][j])
            {
                free(board[i][j]);
            }

        }
    }
}
