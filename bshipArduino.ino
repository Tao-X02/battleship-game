#include "battleship.h"

// These are the pins used to represent each keyboard key
#define wPin 8
#define sPin 7
#define rPin 9
#define xPin 10

void setup() {
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
