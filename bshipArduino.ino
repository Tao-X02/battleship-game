#include "battleship.h"
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

//#define Max_Size 10  // Temporary


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
void displayBoard(char board[Max_Size][Max_Size]) {
  Serial.println("Drawing");
  for(int i=0; i<Max_Size; i++) {
    if(board[i][0] == 255) break;  // Ends loop if outside bounds of board
    for(int j=0; j<Max_Size; j++) {
      if(board[i][j] == 255) break;  // Moves to next line if outside bounds of board
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



void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
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
  char board[Max_Size][Max_Size];
  int bsize = 10;
  generateEmptyBoard(board, bsize);
//  matrix.fillScreen(matrix.Color333(5, 5, 0));
  /*for(int i=0; i<bsize; i++) {
    for(int j=0; j<bsize; j++) {
      Serial.print(board[i][j]);
      Serial.print(" ");
      if(board[i][j] == 0) matrix.drawPixel(i, j, yellow);
    }
    Serial.println(" ");
  }
  delay(1000);*/

  //Multiplayer
  char board2[Max_Size][Max_Size];
  generateEmptyBoard(board2, bsize);
  placeAllShips(board2, bsize, true);
  gameAI(board, board2, bsize, 1); //Main game function
}

void loop() {

}
