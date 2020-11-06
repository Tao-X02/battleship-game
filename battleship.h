#ifndef BATTLESHIP_H
#define BATTLESHIP_H

// LED board used is 16*32 px so max board size is 16*16
#define Max_Size 16

// Functions used to set up board
void generateEmptyBoard(int board[Max_Size][Max_Size], int size);
void placeAllShips(int board[Max_Size][Max_Size], int bsize, bool arduino);
char getButtonPress();
bool gameOver(int board[Max_Size][Max_Size], int bsize);

// Used to display board
void displayBoard(int board[Max_Size][Max_Size]);
void printBoard(int board[Max_Size][Max_Size], bool arduino);

//AI
void placeRandomShipsAI(int board[Max_Size][Max_Size], int boardSize);

#endif
