#ifndef MENUS_H
#define MENUS_H

#include <RGBmatrixPanel.h>
/*
This will mostly just be designing the
look of the game on the LED display
and the printing the words on the LCD
*/

//We can use this to change color in settings
/* Note: Something similar has already been implemented in the .ino file
struct color {
	int r, g, b;
};*/

char getButtonPress();

/*MENU LAYOUT*/

void mainmenu(RGBmatrixPanel matrix, int arr[]); //returns gamemode and colorscheme
				//0 for exit
				//1 for pvp
				//2 for easy AI
				//3 for hard AI
void gamemode(RGBmatrixPanel matrix, int arr[]);
void difficulty(RGBmatrixPanel matrix, int arr[]);
void settings(RGBmatrixPanel matrix);
void colorscheme(RGBmatrixPanel matrix, int arr[]);
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

#endif
