#include "battleship.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prints board in terminal
void printBoardChar(char board[Max_Size][Max_Size], bool arduino) {
	for(char i=0; i<Max_Size; i++) {
		if(board[i][0] < 0) break;  // Ends loop if outside bounds of board
        for(char j=0; j<Max_Size; j++) {
            if(board[i][j] < 0) break;
            if (board[i][j] == 0) printf(". ");
            else printf("%c ", board[i][j]);
        }
        printf("\n");
  }
	printf("\n");
}

struct AIMedium {
    int bSize;
    char board[Max_Size][Max_Size];
};

struct AIMedium createMediumAI(int bSize) {
    char b[Max_Size][Max_Size];
    generateEmptyBoard(b,bSize);
    struct AIMedium ai = {bSize, {0}};
    // i honestly have no idea why i have to do this loop but whatever it works
    for (int i = 0; i < Max_Size*Max_Size; i++)
    {
        ai.board[0][i] = b[0][i];
    }
    return ai;
}

int AICheckWin(struct AIMedium ai) {
    char count = 0;
    for (char i = 0; i < ai.bSize; i++)
    {
        for (char j = 0; j < ai.bSize; j++)
        {
            if (ai.board[i][j] == 'X' || ai.board[i][j] == 'W') count++;
        }
    }
    return count == 17 ? 1 : 0;
}

// returns boolean for if location hasnt been attacked yet
int AIMediumIsEmpty(struct AIMedium *ai, char i, char j) {
    if (i < 0 || i >= ai->bSize || j < 0 || j >= ai->bSize) return 0;
    return ai->board[i][j] == 0 ? 1 : 0;
}

void AIMediumRandom(struct AIMedium *ai, char board[Max_Size][Max_Size]) {
    int randomMovesCount = 0;
    for (char i = 0; i < (ai->bSize); i++)
    {
        for (char j = 0; j < ai->bSize; j++)
        {
            if ((i+j)%2 == 1 && ai->board[i][j] == 0) {
                randomMovesCount++;
            }
        }
    }

    int move = rand() % (randomMovesCount);
    randomMovesCount = 0;

    for (char i = 0; i < (ai->bSize); i++)
    {
        if (randomMovesCount == -1) break;
        for (char j = 0; j < ai->bSize; j++)
        {
            if ((i+j)%2 == 1 && ai->board[i][j] == 0) {
                if (randomMovesCount == move) {
                    ai->board[i][j] = board[i][j] == 2 ? 'X' : 'o' ;
                    randomMovesCount = -1;
                    break;
                }
                randomMovesCount++;
            }
        }
    }
}

void AIMediumAttack(struct AIMedium *ai, char board[Max_Size][Max_Size]) {
    for (char i = 0; i < (ai->bSize); i++)
    {
        for (char j = 0; j < ai->bSize; j++)
        {
            if (ai->board[i][j] == 'X') {
                if (AIMediumIsEmpty(ai, i-1, j)) { ai->board[i-1][j] = board[i-1][j] == 2 ? 'X' : 'o' ;}
                else if (AIMediumIsEmpty(ai, i, j-1)) { ai->board[i][j-1] = board[i][j-1] == 2 ? 'X' : 'o' ;}
                else if (AIMediumIsEmpty(ai, i+1, j)) { ai->board[i+1][j] = board[i+1][j] == 2 ? 'X' : 'o' ;}
                else if (AIMediumIsEmpty(ai, i, j+1)) { ai->board[i][j+1] = board[i][j+1] == 2 ? 'X' : 'o' ;}
                else {ai->board[i][j] = 'W'; continue;}
                return;
            }
        }
    }
    AIMediumRandom(ai, board);
}

int main(void) {
    srand( time(NULL) );
    int bsize = 10;
    //printf("Input board width between 5 and %d (board will be a square)\n", Max_Size);
	//scanf("%d", &bsize);
    char board[Max_Size][Max_Size];
    generateEmptyBoard(board, bsize);
    placeRandomShipsAI(board, bsize);

    struct AIMedium ai = createMediumAI(bsize);

    printBoard(board, false);
    // for (int i = 0; i < 20; i++)
    // {
    //     AIMediumAttack(&ai, board);
    //     printBoardChar(ai.board, false);
    // }

    //int temp;

    while (!AICheckWin(ai)) {
        AIMediumAttack(&ai, board);
        printBoardChar(board, false);
        printBoardChar(ai.board, false);
        //scanf("%d", &temp); // uncomment this to see the moves one at a time
    }

    printf("success\n");
    return 0;
}
