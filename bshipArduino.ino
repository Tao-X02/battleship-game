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
#define wPin 8
#define sPin 7
#define rPin 9
#define xPin 10

struct colorScheme {
  uint16_t c0, c1, c2, c3, c4;
};

// Defines some colors for later use
#define red matrix.Color333(255, 0, 0)
#define black matrix.Color333(0, 0, 0)
#define white matrix.Color333(255, 255, 255)
#define green matrix.Color333(0, 255, 0)
#define blue matrix.Color333(0, 0, 255)

struct colorScheme defaultScheme = {black, white, green, red, blue};
struct colorScheme currentScheme = defaultScheme;

void setup() {
  // Defines pins used for input
  pinMode(wPin, INPUT_PULLUP);
  pinMode(sPin, INPUT_PULLUP);
  pinMode(rPin, INPUT_PULLUP);
  pinMode(xPin, INPUT_PULLUP);

  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 200));  // Fills screen with blue
  delay(1000);  // 1 second delay
  // uint8_t r=0, g=0, b=0;

  //Set up board
  int board[Max_Size][Max_Size];
  int bsize = 10;
  generateEmptyBoard(board, bsize);
  placeAllShips(board, bsize, true);
}

void loop() {

}

/*int main(void) {
  //Initialise arduino ( so millis, delay work ).
  init();
  #if defined(USBCON)
    USB.attach();
  #endif

  // Defines pins used for input
  pinMode(wPin, INPUT_PULLUP);
  pinMode(sPin, INPUT_PULLUP);
  pinMode(rPin, INPUT_PULLUP);
  pinMode(xPin, INPUT_PULLUP);

  //Set up board
  int board[Max_Size][Max_Size];
  int bsize = 10;
  generateEmptyBoard(board, bsize);
  placeAllShips(board, bsize, true);
}*/


// Converts button press to character for use in other programs,
char getButtonPress() {
  while(1) {
    if(digitalRead(wPin) == LOW) {
      delay(200);
      return 'w';
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
