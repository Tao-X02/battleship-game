#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <stdbool.h>

// LED board used is 16*32 px so max board size is 16*16
#define Max_Size 10

// Functions used to set up board
void generateEmptyBoard(char board[Max_Size][Max_Size], int size);
void placeAllShips(char board[Max_Size][Max_Size], int bsize, bool arduino);
char getButtonPress();
bool gameOver(char board[Max_Size][Max_Size], int bsize);

// Used to display board
void displayBoard(char board[Max_Size][Max_Size]);
void printBoard(char board[Max_Size][Max_Size], bool arduino);

//AI
void placeRandomShipsAI(char board[Max_Size][Max_Size], int boardSize);

#endif
