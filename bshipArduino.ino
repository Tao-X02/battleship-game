// #include "battleship.h"
#include <RGBmatrixPanel.h>

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

#define Max_Size 10  // Temporary


struct colorScheme {
  uint16_t c0, c1, c2, c3, c4;
};

// Defines some colors for later use
uint16_t red = matrix.Color333(255, 0, 0);
uint16_t black = matrix.Color333(0, 0, 0);
uint16_t white = matrix.Color333(255, 255, 255);
uint16_t green = matrix.Color333(0, 255, 0);
//uint16_t blue = matrix.Color333(0, 0, 255);
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

// Note: for now this makes no distinction between player and enemy board
void displayBoard(int board[Max_Size][Max_Size]) {
  Serial.println("Drawing");
  for(int i=0; i<Max_Size; i++) {
    if(board[i][0] < 0) break;  // Ends loop if outside bounds of board
    for(int j=0; j<Max_Size; j++) {
      if(board[i][j] < 0) break;  // Moves to next line if outside bounds of board
      switch(board[i][j]) {
        case 0:
          matrix.drawPixel(i, j, currentScheme.c0);
          break;
        case 1:
          matrix.drawPixel(i, j, currentScheme.c1);
          break;
        case 2:
          matrix.drawPixel(i, j, currentScheme.c2);
          break;
        case 3:
          matrix.drawPixel(i, j, currentScheme.c3);
          break;
        case 4:
          matrix.drawPixel(i, j, currentScheme.c4);
          break;
      }
    }
  }
}


//Below is temporary code, used until I fix import problems
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
void printBoard(int board[Max_Size][Max_Size], bool arduino) {
  if(arduino) {  // Uses displayBoard to display on LED board
    displayBoard(board);
    return;
  }
  for(int i=0; i<Max_Size; i++) {
    if(board[i][0] < 0) break;  // Ends loop if outside bounds of board
    for(int j=0; j<Max_Size; j++) {
      if(board[i][j] < 0) break;  // Moves to next line if outside bounds of board
      if (board[i][j] == 1) printf("%d ", 0);  // Displays enemy's misses as ocean
      else printf("%d ", board[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// Helper function for placeShip, draws ship on board
void drawShip(int board[Max_Size][Max_Size], int shipSize, int x, int y, bool isVertical) {
  for(int i=0; i<shipSize; i++) {
    if(isVertical) board[y+i][x] += 2;
    else board[y][x+i] += 2;
  }
}


// Checks to see if current ship position overlaps with other ships (helper function for placeShip)
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


// Bool arduino is true if arduino controller being used for input
void placeShip(int board[Max_Size][Max_Size], int bsize, int shipSize, bool arduino) {
  // Note: x, y coords are for the top left square of the ship
  int x = 0;  // Corresponds to column
  int y = 0;  // Corresponds to row
  bool isVertical = true;
  while(1) {
    // Creates tempBoard, a copy of board
    int tempBoard[Max_Size][Max_Size];
    for(int i=0; i<Max_Size; i++) for(int j=0; j<Max_Size; j++) tempBoard[i][j] = board[i][j];

    // Draws ship in current position on tempBoard and displays tempBoard
    drawShip(tempBoard, shipSize, x, y, isVertical);
    printf("Printing current board:\n");
    printBoard(tempBoard, arduino);

    // Get user input
    char input;
    if(arduino) input = getButtonPress();
    else {
      printf("Use WASD to select ship position (one lowercase character at a time). ");
      printf("Enter 'r' to rotate ship. Enter 'x' to choose the current position.\n");
      scanf("%c", &input);
    }

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



void setup() {
  Serial.begin(9600);
  Serial.print("test");
  // Defines pins used for input
  pinMode(dPin, INPUT_PULLUP);
  pinMode(sPin, INPUT_PULLUP);
  pinMode(rPin, INPUT_PULLUP);
  pinMode(xPin, INPUT_PULLUP);

  matrix.begin();
//  matrix.fillScreen(matrix.Color333(255, 0, 0));
  /*for(uint8_t x=0; x<32; x++) {
    for(uint8_t y=0; y<16; y++) {
      matrix.drawPixel(x, y, matrix.Color333(255, 0, 0));
    }
  }*/
//  delay(2000);  // 2 second delay

  //Set up board
  int board[Max_Size][Max_Size];
  int bsize = 10;
  generateEmptyBoard(board, bsize);
//  matrix.fillScreen(matrix.Color333(5, 5, 0));
  delay(500);
  for(int i=0; i<bsize; i++) {
    for(int j=0; j<bsize; j++) {
      Serial.print(board[i][j]);
      Serial.print(" ");
      if(board[i][j] == 0) matrix.drawPixel(i, j, yellow);
    }
    Serial.println(" ");
  }
  delay(1000);
  //placeAllShips(board, bsize, true);
  Serial.println("");
  Serial.println("Place your ships:");
  Serial.println("Place your aircraft carrier (5 squares long)\n");
  delay(1000);
  placeShip(board, bsize, 5, true);
  Serial.println("Place your battleship (4 squares long)\n");
  placeShip(board, bsize, 4, true);
  Serial.println("Place your cruiser (3 squares long)\n");
  placeShip(board, bsize, 3, true);
  Serial.println("Place your submarine (3 squares long)\n");
  placeShip(board, bsize, 3, true);
  Serial.println("Place your destroyer (2 squares long)\n");
  placeShip(board, bsize, 2, true);
  delay(1000);
}

void loop() {

}
