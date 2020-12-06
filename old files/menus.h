#ifndef MENUS_H
#define MENUS_H

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

/*MENU LAYOUT*/

int mainmenu(RGBmatrixPanel matrix); //returns gamemode
				//0 for exit
				//1 for pvp
				//2 for easy AI
				//3 for hard AI
int gamemode(RGBmatrixPanel matrix);
int difficulty(RGBmatrixPanel matrix);
//void gamescreen(int p1[10][10], int p2[10][10]);
void settings(RGBmatrixPanel matrix);
void help(RGBmatrixPanel matrix);//how to play

/*DISPLAYS*/
void clear(void, RGBmatrixPanel matrix);
void exiticon(int x, int y, RGBmatrixPanel matrix);
void helpicon(int x, int y, RGBmatrixPanel matrix);
void settingsicon(int x, int y, RGBmatrixPanel matrix);
void playicon(int x, int y, RGBmatrixPanel matrix);
void pvpicon(int x, int y, RGBmatrixPanel matrix);
void pvcicon(int x, int y, RGBmatrixPanel matrix);
//void printGrid(int board[10][10], int x, int y);
	//for player 1's board, enter (3, 3) for (x, y)
	//for player 2's board(or comp), enter (18, 3)
void difficon(int x, int y, RGBmatrixPanel matrix);

#endif
