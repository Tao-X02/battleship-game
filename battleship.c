#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// LED board used is 16*32 px so max board size is 16*16
#define Max_Size 16

/* The game board is a set of integers. Each of these integers has a certain meaning:
-1 = Outside of game boundaries
0  = Empty water
2  = Current position of ship
4  = Overlapping ships (only used when placing ship, should not be present when playing the game)
1  = Miss
3  = Hit
*/

void generateEmptyBoard(int board[Max_Size][Max_Size], int size) {
	//Sets all values in board to 0, outside board to -1
	for(int i=0; i<Max_Size; i++) {
		for(int j=0; j<Max_Size; j++) {
			if(i<size && j<size) board[i][j] = 0;
			else board[i][j] = -1;
		}
	}
}


// Prints board in terminal
void printBoard(int board[Max_Size][Max_Size]) {
	//printf("Printing current board:\n");
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

/* Used for testing purposes, unnecessary now
// Helper function for selectSqare
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
		printf("Use WASD to select a square (one lowercase character at a time). ");
		printf("Enter 'x' to choose the current square.\n");
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
			case 'x':
				return;
			default:
				printf("Invalid input\n");
		}
		//Next 2 lines ensure x and y stay within bounds of the board
		x = normalize(x, bsize);
		y = normalize(y, bsize);
	}
}
*/


// Helper function for placeShip, draws ship on board
void drawShip(int board[Max_Size][Max_Size], int shipSize, int x, int y, bool isVertical) {
	for(int i=0; i<shipSize; i++) {
		if(isVertical) board[y+i][x] += 2;
		else board[y][x+i] += 2;
	}
}


// Checks to see if current ship position overlaps with other ships (used in placeShip)
bool isOverlap(int board[Max_Size][Max_Size]) {
	for(int i=0; i<Max_Size*Max_Size; i++)
		if(board[0][i] == 4) return true;
	return false;
}


// Helper function for placeShip, avoids ships going out of bounds
int normalize(int coord, int bsize, int shipSize) {
	if(coord < 0) return bsize - shipSize;  // If coord too small, shifts to largest possible coord
	else if(coord + shipSize > bsize) return 0;  // If coord too large, shifts smallest possible coord
	else return coord;  // If not out of bounds, simply returns coordinate
}


void placeShip(int board[Max_Size][Max_Size], int bsize, int shipSize) {
	// Note: x, y coords are for the top left square of the ship
	int x = 0;  // Corresponds to column
	int y = 0;  // Corresponds to row
	bool isVertical = true;
	while(1) {
		// Creates tempBoard, a copy of board
		int tempBoard[Max_Size][Max_Size];
		for(int i=0; i<Max_Size*Max_Size; i++) tempBoard[0][i] = board[0][i];

		// Draws ship in current position on tempBoard and displays tempBoard
		drawShip(tempBoard, shipSize, x, y, isVertical);
		printf("Printing current board:\n");
		printBoard(tempBoard);

		// Get user input
		printf("Use WASD to select ship position (one lowercase character at a time). ");
		printf("Enter 'r' to rotate ship. Enter 'x' to choose the current position.\n");
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
			case 'r':
				//Checks if rotation possible, and if it is, changes isVertical
				if(isVertical && x+shipSize > bsize) printf("Cannot rotate, current position is too far to the right\n");
				else if(!isVertical && y+shipSize > bsize) printf("Cannot rotate, current position is too far down\n");
				else isVertical = !isVertical;
				break;
			case 'x':
				// Checks if valid ship position
				if(isOverlap(tempBoard)) {
					printf("Invalid ship position: Ship overlaps with other ships.\n");
					break;
				}
				drawShip(board, shipSize, x, y, isVertical);  // Draws ship on actual board
				return;
			default:
				printf("Invalid input\n");
		}

		// Make sure ship is within bounds of the board
		if(isVertical) {
			x = normalize(x, bsize, 1);  // shipSize=1 for axis that isn't in ship's direction
			y = normalize(y, bsize, shipSize);
		}
		else {
			x = normalize(x, bsize, shipSize);
			y = normalize(y, bsize, 1);
		}
	}
}


void placeAllShips(int board[Max_Size][Max_Size], int bsize) {
	printf("Place your ships:\n");
	printf("Place your aircraft carrier (5 squares long)\n");
	placeShip(board, bsize, 5);
	printf("Place your battleship (4 squares long)\n");
	placeShip(board, bsize, 4);
	printf("Place your cruiser (3 squares long)\n");
	placeShip(board, bsize, 3);
	printf("Place your submarine (3 squares long)\n");
	placeShip(board, bsize, 3);
	printf("Place your destroyer (2 squares long)\n");
	placeShip(board, bsize, 2);
}

//Returns list of valid ship placement coordinates
void findAllValidPlacements(int board[Max_Size][Max_Size], int shipSize, int boardSize, int placements[Max_Size][Max_Size]) {
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			int horizontal = 1; //boolean value, 1 if horizontal placement is valid at coordinate
			//check horizontal
			for (int s = 0; s < shipSize; s++) {
				if (x+s < boardSize) {
					if (board[y][x+s] == 2) {
						horizontal = 0;
						break;
					}
				} else {
					horizontal = 0;
					break;
				}
				
			}

			int vertical = 2; //boolean value, 2 if vertical placement is valid at coordinate
			//check horizontal
			for (int s = 0; s < shipSize; s++) {
				if (y+s < boardSize) {
					if (board[y+s][x] == 2) {
						vertical = 0;
						break;
					}
				} else {
					vertical = 0;
					break;
				}
			}
			placements[x][y] = horizontal + vertical;
			
		}
	}
}

//chooses random place for ship given a list of valid placements
//sets the value of list location[3]
//location[3] has the form {x,y,r}, where r is a boolean for whether the ship is vertical or not
void choosePlacement(int placements[Max_Size][Max_Size], int location[3], int boardSize) {
	int validInd[Max_Size*Max_Size][3];
	int numOfValidInd = 0;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (placements[i][j] != 0)
			{
				validInd[numOfValidInd][0] = i;
				validInd[numOfValidInd][1] = j;
				if (placements[i][j] == 3) {
					validInd[numOfValidInd][2] = rand() % 2;
				} else if (placements[i][j] == 2) {
					validInd[numOfValidInd][2] = 1;
				} else {
					validInd[numOfValidInd][2] = 0;
				}
				numOfValidInd++;
			}
		}
	}
	int index = rand() % (numOfValidInd + 1);
	location[0] = validInd[index][0];
	location[1] = validInd[index][1];
	location[2] = validInd[index][2];
}

//Place ships in random positions on the AI board
void placeRandomShipsAI(int board[Max_Size][Max_Size], int boardSize) {
	int ships[] = {5,4,3,3,2};
	for (int i = 0; i < 5; i++)
	{
		int placements[Max_Size][Max_Size];
		findAllValidPlacements(board, ships[i], boardSize, placements);
		int location[3];
		choosePlacement(placements, location, boardSize);
		drawShip(board, ships[i], location[0], location[1], location[2]);
	}
	printBoard(board);
}

//Fill the board with ships with defined positions (for now)
void placeBoard2(int board2[Max_Size][Max_Size]) {
	drawShip(board2, 5, 0, 0, true); //Aircraft carrier
	drawShip(board2, 4, 1, 0, true); //Battleship
	drawShip(board2, 3, 2, 0, true); //Cruiser
	drawShip(board2, 3, 3, 0, true); //Submarine
	drawShip(board2, 2, 4, 0, true); //Destroyer
	printBoard(board2); //Delete later
}


bool checkPosition(int board[Max_Size][Max_Size], int x, int y) {
	if(board[x-1][y-1] == 2) {
		board[x-1][y-1]++; //Hit: 3
		return true;
	}
	board[x-1][y-1] = 1; //Miss: 1
	return false;
}


bool gameOver(int board[Max_Size][Max_Size], int bsize) {
	for (int i = 0; i < bsize; i++) {
		for (int j = 0; j < bsize; j++) {
			if(board[i][j] == 2) return false; //Check if all ships have been completely destroyed
		}
	}
	return true;
}


void game(int board[Max_Size][Max_Size], int board2[Max_Size][Max_Size], int bsize) {
	int x;
	int y;
	bool playable = true;
	bool over = false;
	int turn = 1;

	while(over == false) {
		//Player
		if (turn == 1) {
			while (playable == true) {
				printf("Your opponent's board:\n");
				printBoard(board2); //Delete later
				//Get user inputs (Might make this process interactive)
				printf("Please place your target's row:\n");
				scanf("%d", &x);
				printf("Please place your target's column:\n");
				scanf("%d", &y);
				if (x > bsize || y > bsize) printf("Out of bound inputs");
				playable = checkPosition(board2, x, y); //Play until target missed
			}
			if (gameOver(board2, bsize) == false) {
				turn = 2;
				playable = true;
			} else {
				over = true;
			}
		}

		//AI opponent
		else if (turn == 2) {
			while (playable == true) {
				//Random target (for now)
				x = rand() % bsize + 1;
				y = rand() % bsize + 1;
				printf("Computer input: x=%d, y=%d\n", x, y);
				playable = checkPosition(board, x, y); //Play until target missed
				printf("Your current board:\n");
				printBoard(board); 
			}
			if (gameOver(board, bsize) == false) {
				turn = 1;
				playable = true;
			} else {
				over = true;
			}
		}
	}
}


int main(void) {
	int bsize;  // Board size (board is always square)
	printf("Input board width between 5 and %d (board will be a square)\n", Max_Size);
	scanf("%d", &bsize);
	// Board size must be at least 5 to fit aircraft carrier and less than Max_Size to fit on LED board
	assert(bsize >= 5 && bsize <= Max_Size);
	// Board is array with size Max_Size, values outside bsize are -1, this is to avoid variable sized arrays
	int board[Max_Size][Max_Size];
	int board2[Max_Size][Max_Size]; //Second set of board
	
	// int testBoard[Max_Size][Max_Size]; //Board for testing random ship placement
	// generateEmptyBoard(testBoard, bsize);
	// placeRandomShipsAI(testBoard, bsize);
	
	generateEmptyBoard(board, bsize);
	generateEmptyBoard(board2, bsize); //Second set of board
	//selectSquare(board, bsize);
	placeAllShips(board, bsize);
	// placeBoard2(board2); //Fill the second set of board
	placeRandomShipsAI(board2, bsize);
	game(board, board2, bsize); //Main game function
	return 0;
}
