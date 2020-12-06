/* Note: The code here is almost identical to the code in battleship.c and bshipArduino.ino
The only difference is that any unnecessary strings, libraries, and printf statements have
been removed to save memory */

//#include <stdbool.h>
//#include <stdlib.h>
#include <time.h>

#include "menus.h"

#include <RGBmatrixPanel.h>

// LED board used is 16*32 px so max board size is 16*16
#define Max_Size 10

// Defining pins used for LED board
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
// Set up LED matrix
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

// These are the pins used to represent each keyboard key
#define dPin 2
#define sPin 3
#define rPin 5
#define xPin 7

/* The game board is a set of integers (represented by chars to save memory). Each of these integers has a certain meaning:
255 = Outside of game boundaries
0  = Empty water
2  = Current position of ship
4  = Overlapping ships (only used when placing ship, should not be present when playing the game)
1  = Miss
3  = Hit
*/

struct colorScheme {
  uint16_t c0, c1, c2, c3, c4;
};

// Defines some colors for later use
uint16_t red = matrix.Color333(255, 0, 0);
uint16_t black = matrix.Color333(0, 0, 0);
uint16_t white = matrix.Color333(255, 255, 255);
uint16_t green = matrix.Color333(0, 255, 0);
// uint16_t blue = matrix.Color333(0, 0, 255);
uint16_t yellow = matrix.Color333(255, 255, 0);

struct colorScheme defaultScheme = {black, white, green, red, yellow};
// Add extra color schemes here
struct colorScheme currentScheme = defaultScheme;

// Converts button press to character for use in other programs,
char getButtonPress() {
  Serial.println("Looking for button press");
  while(1) {
    if(digitalRead(dPin) == LOW) {
      delay(200);
      return 'd';
    } else if(digitalRead(sPin) == LOW) {
      delay(200);
      return 's';
    } else if(digitalRead(rPin) == LOW) {
      delay(200);
      return 'r';
    } else if(digitalRead(xPin) == LOW) {
      delay(200);
      return 'x';
    } else continue;
  }
}



struct AIMedium {
    int bSize;
    char board[Max_Size][Max_Size];
	char used;
};

void AIMediumAttack(struct AIMedium *ai, char board[Max_Size][Max_Size], int *x, int *y);

void generateEmptyBoard(char board[Max_Size][Max_Size], int size) {
	//Sets all values in board to 0, outside board to 255
	for(int i=0; i<Max_Size; i++) {
		for(int j=0; j<Max_Size; j++) {
			if(i<size && j<size) board[i][j] = 0;
			else board[i][j] = 255;
		}
	}
}

void displayBoard(char board[Max_Size][Max_Size], bool isEnemy, int bsize) {
  Serial.println(F("Drawing"));
  // Find x and y adjustments to center boards
  int xAdj = (16 - bsize) / 2;
  int yAdj = xAdj;
  if(isEnemy) xAdj+=16;
  if(bsize < 15) matrix.drawRect(xAdj-1, yAdj-1, bsize+2, bsize+2, matrix.Color333(7, 7, 7));  // Draw border
  for(int i=0; i<Max_Size; i++) {
    if(board[i][0] == 255) break;  // Ends loop if outside bounds of board
    for(int j=0; j<Max_Size; j++) {
      if(board[i][j] == 255) break;  // Moves to next line if outside bounds of board
      int x = i+xAdj;
      int y = j + yAdj;
      switch(board[i][j]) {
        case 0:
          matrix.drawPixel(x, y, currentScheme.c0);
          break;
        case 1:
          matrix.drawPixel(x, y, currentScheme.c1);
          break;
        case 2:
          // Draws ships as ocean if drawing enemy's board
          if(isEnemy) matrix.drawPixel(x, y, currentScheme.c0);
          else matrix.drawPixel(x, y, currentScheme.c2);
          break;
        case 3:
          matrix.drawPixel(x, y, currentScheme.c3);
          break;
        case 4:
          // If isEnemy, that means it's a cursor
          matrix.drawPixel(x, y, currentScheme.c4);
          break;
      }
    }
  }
}

// Prints board in terminal
void printBoard(char board[Max_Size][Max_Size], int bsize) { displayBoard(board, false, bsize); }

// Prints a board that only shows hit or miss targets
void printOpponentBoard(char board[Max_Size][Max_Size], int bsize) { displayBoard(board, true, bsize); }


// Helper function for placeShip, draws ship on board
void drawShip(char board[Max_Size][Max_Size], int shipSize, int x, int y, bool isVertical) {
	for(int i=0; i<shipSize; i++) {
		if(isVertical) board[y+i][x] += 2;
		else board[y][x+i] += 2;
	}
}


// Checks to see if current ship position overlaps with other ships (helper function for placeShip)
bool isOverlap(char board[Max_Size][Max_Size]) {
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


// Bool arduino is true if arduino controller being used for input
void placeShip(char board[Max_Size][Max_Size], int bsize, int shipSize, bool arduino) {
	// Note: x, y coords are for the top left square of the ship
	int x = 0;  // Corresponds to column
	int y = 0;  // Corresponds to row
	bool isVertical = true;
	while(1) {
		// Creates tempBoard, a copy of board
		char tempBoard[Max_Size][Max_Size];
		for(int i=0; i<Max_Size; i++) for(int j=0; j<Max_Size; j++) tempBoard[i][j] = board[i][j];

		// Draws ship in current position on tempBoard and displays tempBoard
		drawShip(tempBoard, shipSize, x, y, isVertical);
		//printf("Printing current board:\n");
		printBoard(tempBoard, bsize);

		// Get user input
		char input = getButtonPress();
		// //else {
		// 	printf("Use WASD to select ship position (one lowercase character at a time). ");
		// 	printf("Enter 'r' to rotate ship. Enter 'x' to choose the current position.\n");
		// 	scanf("%c", &input);
		// //}

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
				if(isVertical && x+shipSize > bsize) break;//printf("Cannot rotate, current position is too far to the right\n");
				else if(!isVertical && y+shipSize > bsize) break;//printf("Cannot rotate, current position is too far down\n");
				else isVertical = !isVertical;
				break;
			case 'x':
				// Checks if valid ship position
				if(isOverlap(tempBoard)) {
					//printf("Invalid ship position: Ship overlaps with other ships.\n");
					break;
				}
				drawShip(board, shipSize, x, y, isVertical);  // Draws ship on actual board
				return;
			default:
				break;//printf("Invalid input\n");
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


void placeAllShips(char board[Max_Size][Max_Size], int bsize, bool arduino) {
	// printf("Place your ships:\n");
	// printf("Place your aircraft carrier (5 squares long)\n");
	placeShip(board, bsize, 5, arduino);
	// printf("Place your battleship (4 squares long)\n");
	placeShip(board, bsize, 4, arduino);
	// printf("Place your cruiser (3 squares long)\n");
	placeShip(board, bsize, 3, arduino);
	// printf("Place your submarine (3 squares long)\n");
	placeShip(board, bsize, 3, arduino);
	// printf("Place your destroyer (2 squares long)\n");
	placeShip(board, bsize, 2, arduino);
}

//Returns list of valid ship placement coordinates
void findAllValidPlacements(char board[Max_Size][Max_Size], int shipSize, int boardSize, char placements[Max_Size][Max_Size]) {
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
void choosePlacement(char placements[Max_Size][Max_Size], char location[3], int boardSize) {
	char validInd[Max_Size*Max_Size][3];
	int numOfValidInd = 0;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (placements[i][j] != 0) {
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
void placeRandomShipsAI(char board[Max_Size][Max_Size], int boardSize) {
	int ships[] = {5,4,3,3,2};
	for (int i = 0; i < 5; i++)
	{
		char placements[Max_Size][Max_Size];
		findAllValidPlacements(board, ships[i], boardSize, placements);
		char location[3];
		choosePlacement(placements, location, boardSize);
		drawShip(board, ships[i], location[0], location[1], location[2]);
	}
}

/*
//Fill the board with ships with defined positions (for now)
void placeBoard2(char board2[Max_Size][Max_Size]) {
	drawShip(board2, 5, 0, 0, true); //Aircraft carrier
	drawShip(board2, 4, 1, 0, true); //Battleship
	drawShip(board2, 3, 2, 0, true); //Cruiser
	drawShip(board2, 3, 3, 0, true); //Submarine
	drawShip(board2, 2, 4, 0, true); //Destroyer
	//printBoard(board2, false); //Delete later
}*/


bool checkPosition(char board[Max_Size][Max_Size], int x, int y, int bsize) {
  if(board[x-1][y-1] == 2) {
    board[x-1][y-1]++; //Hit: 3
    printOpponentBoard(board, bsize);
    return true;
  }
  else
  {
    board[x-1][y-1] = 1;
    printOpponentBoard(board, bsize);
    return false; //Miss: 1
  }
}


bool gameOver(char board[Max_Size][Max_Size], int bsize) {
	for (int i = 0; i < bsize; i++) {
		for (int j = 0; j < bsize; j++) {
			if(board[i][j] == 2) return false; //Check if all ships have been completely destroyed
		}
	}
	return true;
}

// int getPosition(char increment) {
//   int res = 0;
//   while(true) {
//     char input = getButtonPress();
//     if(input==increment) res++;
//     if(input=='x') return res;
//   }
// }
//
// int getXPos(int bsize) { return getPosition('d')%bsize; }
// int getYPos(int bsize) { return getPosition('s')%bsize; }

bool playerTurn (char board1[Max_Size][Max_Size], char board2[Max_Size][Max_Size], int bsize) {
    printBoard(board1, bsize);
    printOpponentBoard(board2, bsize);
    int x = 0;
    int y = 0;
    bool validAttack = false;
    Serial.println(F("Choose position to attack"));
    while(!validAttack) {  // Allow user to input attack using cursor
      x %= bsize;
      y %= bsize;
  		// Creates tempBoard, a copy of board
  		char tempBoard[Max_Size][Max_Size];
  		for(int i=0; i<Max_Size; i++) for(int j=0; j<Max_Size; j++) tempBoard[i][j] = board2[i][j];
      tempBoard[x][y] = 4;

      Serial.print("x: ");
      Serial.print(x);
      Serial.print("\ty: ");
      Serial.println(y);

      //printf("Printing current board:\n");
  		printOpponentBoard(tempBoard, bsize);

  		// Get user input
  		char input = getButtonPress();

  		switch(input) {
  			case 's':
  				y++;
  				break;
  			case 'd':
  				x++;
  				break;
  			case 'x':
  				// Checks if valid attack position
  				if(board2[x][y]==1 || board2[x][y]==3) Serial.println(F("Cannot attack square that was already attacked"));
  			  else validAttack = true;
  		}
    }

    //Get user inputs (Might make this process interactive)
    // printf("Please place your target's row:\n");
    // scanf("%d", &x);
    // printf("Please place your target's column:\n");
    // scanf("%d", &y);
    // if (x > bsize || y > bsize)
    //     printf("Out of bound inputs\n");
    
    return checkPosition(board2, ++x, ++y, bsize); //Play until target missed
}

bool AIturn (char board1[Max_Size][Max_Size], char board2[Max_Size][Max_Size], int bsize, struct AIMedium *ai){
	if (ai->used) {
		int x = 0; int y = 0;
		AIMediumAttack(ai, board2, &x, &y);
		x++;y++;
		// printf("Computer input: x=%d, y=%d\n", x, y);
		// printf("Your current board:\n");
		printOpponentBoard(board2, bsize);
		return checkPosition(board2, x, y, bsize); //Play until target missed
	} else {
		//Random target if ai is NULL
		int x, y;
		x = rand() % bsize + 1;
		y = rand() % bsize + 1;
		// printf("Computer input: x=%d, y=%d\n", x, y);
		// printf("Your current board:\n");
		printOpponentBoard(board2, bsize);
		return checkPosition(board2, x, y, bsize); //Play until target missed
	}
}

void gameAI(char board1[Max_Size][Max_Size], char board2[Max_Size][Max_Size], int bsize, int mode, struct AIMedium *ai) {
  int x;
  int y;
  bool playable = true;
  bool over = false;
  int turn = 1;
	if(mode == 1) {
		while (!over) {
        //Player
        if (turn == 1) {
            // Clear board to allow players to switch
            clear(matrix);
            delay(4000);
            printBoard(board1, bsize);
            printOpponentBoard(board2, bsize);
            Serial.println(F("Player 1's turn:"));
            while (playable) playable = playerTurn(board1, board2, bsize);
            if (!gameOver(board2, bsize)) {
                turn++;
                playable = true;
            }
            else over = true;
        }
        //Player 2
        if (turn == 2) {
            // Clear board to allow players to switch
            clear(matrix);
            delay(4000);
            printBoard(board2, bsize);
            printOpponentBoard(board1, bsize);
			      Serial.println(F("Player 2's turn:"));
            while (playable) playable = playerTurn(board2, board1, bsize);
            if (!gameOver(board1, bsize)) {
                turn--;
                playable = true;
            }
            else over = true;
        }
    }
	}
	if(mode == 2){
		while (!over) {
        printBoard(board1, bsize);
        printOpponentBoard(board2, bsize);
        //Player
        if (turn == 1) {
            Serial.println(F("Player 1's turn:"));
            while (playable) playable = playerTurn(board1, board2, bsize);
            if (!gameOver(board2, bsize)) {
                turn++;
                playable = true;
            }
            else over = true;
        }
        //AI opponent
        if (turn == 2) {
            Serial.println(F("AI's turn:"));
            while (playable) playable = AIturn(board2, board1, bsize, ai);
            if (!gameOver(board1, bsize)) {
                turn--;
                playable = true;
            }
            else over = true;
        }
    }
	}
}


// ****************************
// The following functions are for the medium AI.
// This comment is just to group the functions together to find them easier.

struct AIMedium createMediumAI(int bSize, char used) {
    char b[Max_Size][Max_Size];
    generateEmptyBoard(b,bSize);
    struct AIMedium ai = {bSize, {0}, used};
    // i honestly have no idea why i have to do this loop but whatever it works
    for (int i=0; i<Max_Size; i++) for(int j=0; j<Max_Size; j++) ai.board[i][j] = b[i][j];
    return ai;
}

int AICheckWin(struct AIMedium ai) {
    char count = 0;
    for (char i = 0; i < ai.bSize; i++) {
        for (char j = 0; j < ai.bSize; j++) {
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

void AIMediumRandom(struct AIMedium *ai, char board[Max_Size][Max_Size], int *x, int *y) {
    int randomMovesCount = 0;
    for (char i = 0; i < (ai->bSize); i++) {
        for (char j = 0; j < ai->bSize; j++) {
            if ((i+j)%2 == 1 && ai->board[i][j] == 0) {
                randomMovesCount++;
            }
        }
    }

    int move = rand() % (randomMovesCount);
    randomMovesCount = 0;

    for (int i = 0; i < (ai->bSize); i++)
    {
        if (randomMovesCount == -1) break;
        for (int j = 0; j < ai->bSize; j++)
        {
            if ((i+j)%2 == 1 && ai->board[i][j] == 0) {
                if (randomMovesCount == move) {
                    ai->board[i][j] = board[i][j] == 2 ? 'X' : 'o' ;
					          *x = i;*y = j;
                    randomMovesCount = -1;
                    break;
                }
                randomMovesCount++;
            }
        }
    }
}

void AIMediumAttack(struct AIMedium *ai, char board[Max_Size][Max_Size], int *x, int *y) {
    for (int i = 0; i < (ai->bSize); i++)
    {
        for (int j = 0; j < ai->bSize; j++)
        {
            if (ai->board[i][j] == 'X') {
                if (AIMediumIsEmpty(ai, i-1, j)) {
					ai->board[i-1][j] = board[i-1][j] == 2 ? 'X' : 'o' ;
					*x = i-1;*y = j;
				} else if (AIMediumIsEmpty(ai, i, j-1)) {
					ai->board[i][j-1] = board[i][j-1] == 2 ? 'X' : 'o' ;
					*x = i;*y = j-1;
				} else if (AIMediumIsEmpty(ai, i+1, j)) {
					ai->board[i+1][j] = board[i+1][j] == 2 ? 'X' : 'o' ;
					*x = i+1;*y = j;
				} else if (AIMediumIsEmpty(ai, i, j+1)) {
					ai->board[i][j+1] = board[i][j+1] == 2 ? 'X' : 'o' ;
					*x = i;*y = j+1;
				} else {ai->board[i][j] = 'W'; continue;}
				return;
            }
        }
    }
    AIMediumRandom(ai, board, x, y);
}

// This is the end of the medium AI functions
// ****************************

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
  // Defines pins used for input
  pinMode(dPin, INPUT_PULLUP);
  pinMode(sPin, INPUT_PULLUP);
  pinMode(rPin, INPUT_PULLUP);
  pinMode(xPin, INPUT_PULLUP);

  matrix.begin();

  srand( time(NULL) ); //seed random with time. Otherwise the sequences are always the same
}

void loop() {
  /*
  // Note: The following is just for testing, should be input by menu
  int bsize = 5;  // Board size (board is always square)
  int mode = 1;
  int dif = 1;
  */

  //Using menu input
  int bsize = 5;
  int mode = 0;
  int dif;
  while(mode == 0) {
    switch(mainmenu(matrix)) {  // Run main menu and get instructions to setup
      case 1:
        mode = 1;
        dif = 0;
        break;
      case 2:
        mode = 2;
        dif = 1;
        break;
      case 3:
        mode = 2;
        dif = 2;
        break;
    }
  }

  // Print out values entered
  Serial.print("Bsize: ");
  Serial.print(bsize);
  Serial.print("\tMode: ");
  Serial.print(mode);
  Serial.print("\tDif: ");
  Serial.println(dif);

  clear(matrix);

  char board[Max_Size][Max_Size];
	char board2[Max_Size][Max_Size]; //Second set of board

	struct AIMedium ai = createMediumAI(bsize, dif-1);
	//printf("Size of(AIMedium) = %d %d\n", sizeof(struct AIMedium), sizeof(struct AIMedium *));

	generateEmptyBoard(board, bsize);
	generateEmptyBoard(board2, bsize); //Second set of board
  printBoard(board, bsize);
  printOpponentBoard(board2, bsize);
	if(mode == 1){
		Serial.println(F("Placing Player 1's Board\n"));
    placeAllShips(board, bsize, false);
		Serial.println(F("Placing Player 2's Board\n"));
    placeAllShips(board2, bsize, false);
  }
  else if (mode == 2) {
    placeAllShips(board, bsize, false);
    placeRandomShipsAI(board2, bsize);
  }
	gameAI(board, board2, bsize, mode, &ai); //Main game function
}

/*
int main(void) {
	srand( time(NULL) ); //seed random with time. Otherwise the sequences are always the same
	int bsize;  // Board size (board is always square)
	int mode;
	while(true) {
		printf("Please choose gamemode:\nMultiplayer (input 1)\nAI (input 2)\n");
		if(scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) printf("Invalid input\n");
		else break;
	}
	// Board size must be at least 5 to fit aircraft carrier and less than Max_Size to fit on LED board
	while(true) {
		printf("Input board width between 5 and %d (board will be a square)\n", Max_Size);
		if(scanf("%d", &bsize) != 1 || (bsize<5 || bsize>Max_Size)) printf("Invalid input\n");
		else break;
	}

	int dif;
	if (mode == 2) {
		while(true) {
			printf("Please choose AI difficulty:\nEasy (input 1)\nHard (input 2)\n");
			if(scanf("%d", &dif) != 1 || (dif != 1 && dif != 2)) printf("Invalid input\n");
			else break;
		}
	}
	printf("dif: %d\n", dif);
	// Board is array with size Max_Size, values outside bsize are -1, this is to avoid variable sized arrays
	char board[Max_Size][Max_Size];
	char board2[Max_Size][Max_Size]; //Second set of board

	// Initialize object to store AI data


	struct AIMedium ai = createMediumAI(bsize, dif-1);
	printf("Size of(AIMedium) = %d %d\n", sizeof(struct AIMedium), sizeof(struct AIMedium *));

	// int testBoard[Max_Size][Max_Size]; //Board for testing random ship placement
	// generateEmptyBoard(testBoard, bsize);
	// placeRandomShipsAI(testBoard, bsize);

	generateEmptyBoard(board, bsize);
	generateEmptyBoard(board2, bsize); //Second set of board
	if(mode == 1){
		printf("Placing Player 1's Board\n");
        placeAllShips(board, bsize, false);
		printf("Placing Player 2's Board\n");
        placeAllShips(board2, bsize, false);
    }
    else if (mode == 2){
        placeAllShips(board, bsize, false);
        placeRandomShipsAI(board2, bsize);
    }
	gameAI(board, board2, bsize, mode, &ai); //Main game function
	return 0;
}*/
