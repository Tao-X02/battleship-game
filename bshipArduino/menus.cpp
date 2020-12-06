//#include <LiquidCrystal.h>
#include <RGBmatrixPanel.h>
#include "menus.h"


/* GAMEMODES
	0 - exit game
	1 - pvp
	2 - easy AI
	3 - hard AI
*/
int mainmenu(RGBmatrixPanel matrix) {
	clear(matrix);
	exiticon(0, 0, matrix);
	playicon(11, 1, matrix);
	settingsicon(26, 11, matrix);
	helpicon(5, 10, matrix);

	char button;

	do {
		button = getButtonPress();
	} while (!(button == 'x' || button == 'd' /*|| button == 'r' || button == 's'*/));

	switch(button) {
		case 'x'://exit
			return 0;
		case 'd'://play
			return gamemode(matrix);
		/*case 'r'://tutorial
			//tutorial();
			break;
		case 's'://settings
			//settings();*/
	}
}

int gamemode(RGBmatrixPanel matrix) {
	clear(matrix);
	exiticon(0, 0, matrix);
	pvpicon(9, 6, matrix);
	pvcicon(20, 6, matrix);
	char button;
	do {
		button = getButtonPress();
	} while (!(button == 'x' || button == 'd' ||  button == 's'));

	switch(button) {
		case 'x'://back to main menu
			return mainmenu(matrix);
		case 'd'://PvC
			return difficulty(matrix);
		case 's'://PvP
			return 1;
	}
}

int difficulty(RGBmatrixPanel matrix) {
	clear(matrix);
	exiticon(0, 0, matrix);
	difficon(5, 4, matrix);
	char button;
	do {
		button = getButtonPress();
	} while (!(button == 'x' || button == 'd' || button == 's'));

	switch(button) {
		case 'x'://back to gamemode
			return gamemode(matrix);
		case 'd'://hard
			return 3;
		case 's'://easy
			return 2;
	}
}

/* This has already been done in the .ino file
void gamescreen(int p1[10][10], int p2[10][10]){
	clear();
	exiticon(0, 0);
	printGrid(p1, 3, 3);
	printGrid(p2, 18, 3);
}*/
//void tutorial();
//void settings();

/*Button Displays*/
void exiticon(int x, int y, RGBmatrixPanel matrix) {
	matrix.drawLine(0, 0, 2, 2, matrix.Color333(7, 0, 0));
	matrix.drawLine(0, 2, 2, 0, matrix.Color333(7, 0, 0));
}
void playicon(int x, int y, RGBmatrixPanel matrix) {//green
	matrix.drawLine(x, y, x+1, y, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+1, x+3, y+1, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+2, x+5, y+2, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+3, x+7, y+3, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+4, x+9, y+4, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+5, x+9, y+5, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+6, x+7, y+6, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+7, x+5, y+7, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+8, x+3, y+8, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+9, x+1, y+9, matrix.Color333(0, 7, 0));
}
void settingsicon(int x, int y, RGBmatrixPanel matrix) {//white
	matrix.drawCircle(x, y, 3, matrix.Color333(7, 7, 7));
	matrix.drawLine(x, y-1, x+1, y, matrix.Color333(7, 7, 7));
	matrix.drawLine(x-1, y, x, y+1, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x-1, y-4, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+1, y-4, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+4, y-1, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+4, y+1, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+1, y+4, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x-1, y+4, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x-4, y+1, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x-4, y-1, matrix.Color333(7, 7, 7));
}
void helpicon(int x, int y, RGBmatrixPanel matrix) {//purple
	matrix.drawCircle(x, y, 2, matrix.Color333(7, 0, 7));
	matrix.drawPixel(x-2, y, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x-2, y+1, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x-1, y+2, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x, y+3, matrix.Color333(7, 0, 7));
	matrix.drawPixel(x, y+5, matrix.Color333(7, 0, 7));
}
void pvpicon(int x, int y, RGBmatrixPanel matrix) {
	matrix.fillCircle(x, y, 2, matrix.Color333(0, 0, 7));
	matrix.drawPixel(x-1, y, matrix.Color333(0, 0, 0));
	matrix.drawLine(x-2, y+3, x+2, y+3, matrix.Color333(0, 0, 7));
	matrix.fillRect(x-3, y+4, 7, 2, matrix.Color333(0, 0, 7));

	matrix.fillCircle(x+2, y, 2, matrix.Color333(7, 0, 0));
	matrix.drawPixel(x+1, y, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x+3, y, matrix.Color333(0, 0, 0));
	matrix.drawLine(x, y+3, x+4, y+3, matrix.Color333(7, 0, 0));
	matrix.fillRect(x-1, y+4, 7, 2, matrix.Color333(7, 0, 0));
}
void pvcicon(int x, int y, RGBmatrixPanel matrix) {
	matrix.fillCircle(x, y, 2, matrix.Color333(0, 0, 7));
	matrix.drawPixel(x-1, y, matrix.Color333(0, 0, 0));
	matrix.drawLine(x-2, y-3, x+2, y-3, matrix.Color333(0, 0, 7));
	matrix.fillRect(x-3, y-4, 7, 2, matrix.Color333(0, 0, 7));

	matrix.drawRect(x, y-2, 6, 5, matrix.Color333(7, 0, 0));
	matrix.drawRect(x+1, y-1, 4, 3, matrix.Color333(0, 0, 0));
	matrix.drawLine(x+2, y+3, x+3, y+3, matrix.Color333(7, 0, 0));
	matrix.drawLine(x+1, y+4, x+4, y+4, matrix.Color333(7, 0, 0));
	matrix.drawLine(x, y+5, x+5, y+5, matrix.Color333(7, 0, 0));
}
void difficon(int x, int y, RGBmatrixPanel matrix) {
	matrix.fillRect(x, y+4, 2, 3, matrix.Color333(0, 7, 0));//easy

	//matrix.fillRect(x+6, y+4, 2, 3, matrix.Color333(7, 7, 0));//medium
	//matrix.fillRect(x+9, y+2, 2, 5, matrix.Color333(7, 7, 0));

	matrix.fillRect(x+15, y+4, 2, 3, matrix.Color333(7, 0, 0));//hard
	matrix.fillRect(x+18, y+2, 2, 5, matrix.Color333(7, 0, 0));
	matrix.fillRect(x+21, y, 2, 7, matrix.Color333(7, 0, 0));
}

void clear(RGBmatrixPanel matrix) {
	matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 0));
}

/* Already done in .ino file
void printGrid(int board[10][10], int x, int y, int size) {
	drawRect(x-1, y-1, size+2, size+2, matrix.Color333(7, 7, 7));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			switch (board[i][j]) {
				case 1: //miss
					matrix.drawPixel(x+i, y+j, matrix.Color333(7, 0, 0));//red
				case 2://player's ships
					matrix.drawPixel(x+i, y+j, matrix.Color333(0, 0, 7));//blue
				case 3://hit
					matrix.drawPixel(x+i, y+j, matrix.Color333(0, 7, 0));//green
				default://empty water
					matrix.drawPixel(x+i, y+j, matrix.Color333(0, 0, 0));
			}
		}
	}
}*/
