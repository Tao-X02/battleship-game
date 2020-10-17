#ifndef MENUS_H
#define MENUS_H

/*
This will mostly just be designing the
look of the game on the LED display
and the printing the words on the LCD
*/

/*MENU LAYOUT*/

void mainmenu();//done
 void battleship();
  //two player
  //against AI
   //easy
   //medium
    //hard
 void settings();
 void help();//how to play

/*BUTTONS*/
void exiticon(int x, int y);
void helpicon(int x, int y);
void settingsicon(int x, int y);
void playicon(int x, int y);
void pvpicon(int x, int y);
void pvcicon(int x, int y);

#endif