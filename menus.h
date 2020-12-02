#ifndef MENUS_H
#define MENUS_H

/*
This will mostly just be designing the
look of the game on the LED display
and the printing the words on the LCD
*/

//We can use this to change color in settings
struct color {
	int r, g, b;
};

/*MENU LAYOUT*/

void mainmenu();//done
void gamemode();
void difficulty();
//void gamescreen(int p1[10][10], int p2[10][10]);
void settings();
void help();//how to play

/*DISPLAYS*/
void clear(void);
void exiticon(int x, int y);
void helpicon(int x, int y);
void settingsicon(int x, int y);
void playicon(int x, int y);
void pvpicon(int x, int y);
void pvcicon(int x, int y);
//void printGrid(int board[10][10], int x, int y);
	//for player 1's board, enter (3, 3) for (x, y)
	//for player 2's board(or comp), enter (18, 3)
void difficon(int x, int y);

#endif
