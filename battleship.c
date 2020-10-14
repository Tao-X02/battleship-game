#include <stdio.h>
#include <assert.h>

// LED board used is 16*32 px so max board size is 16*16
#define Max_Size 16


void generateEmptyBoard(int board[Max_Size][Max_Size], int size) {
	//Sets all values in board to 0, outside board to -1
	for(int i=0; i<Max_Size; i++) {
		for(int j=0; j<Max_Size; j++) {
			if(i<size && j<size) board[i][j] = 0;
			else board[i][j] = -1;
		}
	}
}


void printBoard(int board[Max_Size][Max_Size]) {
	printf("Printing current board:\n");
	for(int i=0; i<Max_Size; i++) {
		if(board[i][0] < 0) break;  // Ends loop if outside bounds of board
                for(int j=0; j<Max_Size; j++) {
			if(board[i][j] < 0) break;  // Moves to next line if outside bounds of board
			printf("%d ", board[i][j]);
		}
                printf("\n");
        }
	printf("\n");
}


int normalize(int coord, int bsize) {
	if(coord < 0) return --bsize;
	else if(coord >= bsize) return 0;
	else return coord;
}


void selectSquare(int board[Max_Size][Max_Size], int bsize) {
	int x = 0;  // Corresponds to column
	int y = 0;  // Corresponds to row
	while(1) {
		board[y][x] = 1;  // 1 marks where the cursor is
		printBoard(board);
		board[y][x] = 0;  // Removes cursor (until next iteration in loop)
		printf("Enter keyboard input (one lowercase character at a time)\n");
		char input;
		scanf("%c", &input);
		switch(input) {
			case 'w':
				y--;
				break;
			case 's':
				y++;
				break;
			case 'a':
				x--;
				break;
			case 'd':
				x++;
				break;
			default:
				printf("Invalid input\n");
		}
		//Next 2 lines ensure x and y stay within bounds of the board
		x = normalize(x, bsize);
		y = normalize(y, bsize);
	}
}


int main(void) {
	int bsize;  // Board size (board is always square)
	printf("Input board size between 0 and %d (board will be a square)\n", Max_Size);
	scanf("%d", &bsize);
	assert(bsize > 0 && bsize <= Max_Size);
	// Board is array with size Max_Size, values outside bsize are -1, this is to avoid variable sized arrays
	int board[Max_Size][Max_Size];
	generateEmptyBoard(board, bsize);
	//printBoard(board);
	selectSquare(board, bsize);
	return 0;
}
