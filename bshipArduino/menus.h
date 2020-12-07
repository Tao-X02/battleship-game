#ifndef MENUS_H
#define MENUS_H

#include <RGBmatrixPanel.h>
/*
This will mostly just be designing the
look of the game on the LED display
and the printing the words on the LCD
*/

//We can use this to change color in settings
struct colorScheme {
  uint16_t c0, c1, c2, c3, c4;
};

char getButtonPress();

/*MENU LAYOUT*/

void mainmenu(RGBmatrixPanel matrix, int arr[], struct colorScheme schemes[3]); //returns gamemode and colorscheme
				//0 for exit
				//1 for pvp
				//2 for easy AI
				//3 for hard AI
void gamemode(RGBmatrixPanel matrix, int arr[], struct colorScheme schemes[3]);
void difficulty(RGBmatrixPanel matrix, int arr[], struct colorScheme schemes[3]);
void settings(RGBmatrixPanel matrix, int arr[], struct colorScheme schemes[3]);
void colorscheme(RGBmatrixPanel matrix, int arr[], struct colorScheme schemes[3]);
void help(RGBmatrixPanel matrix);//how to play

/*DISPLAYS*/
void clear(RGBmatrixPanel matrix);
void exiticon(int x, int y, RGBmatrixPanel matrix);
void helpicon(int x, int y, RGBmatrixPanel matrix);
void settingsicon(int x, int y, RGBmatrixPanel matrix);
void playicon(int x, int y, RGBmatrixPanel matrix);
void pvpicon(int x, int y, RGBmatrixPanel matrix);
void pvcicon(int x, int y, RGBmatrixPanel matrix);
void colorsicon(int x, int y, RGBmatrixPanel matrix);
void soundicon(int x, int y, RGBmatrixPanel matrix);
void outline(int x, int y, RGBmatrixPanel matrix);
void scheme(int x, int y, RGBmatrixPanel matrix);
void difficon(int x, int y, RGBmatrixPanel matrix);
void schemeicon(int x, int y, RGBmatrixPanel matrix, struct colorScheme scheme);

#endif
