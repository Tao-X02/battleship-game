//#include <LiquidCrystal.h>
#include <RGBmatrixPanel.h>
#include "menus.h"


/* GAMEMODES
	0 - exit game
	1 - pvp
	2 - easy AI
	3 - hard AI
*/
void mainmenu(RGBmatrixPanel matrix, int arr[]) {
	clear(matrix);
	exiticon(0, 0, matrix);
	playicon(11, 1, matrix);
	settingsicon(26, 11, matrix);
	helpicon(5, 10, matrix);

	char button;

	do {
		button = getButtonPress();
	} while (!(button == 'x' || button == 'd' /*|| button == 'r'*/ || button == 's'));

	switch(button) {
		case 'x'://exit
			arr[0] = 0;
		case 'd'://play
			gamemode(matrix, arr);
		/*case 'r'://tutorial
			//tutorial();
			break;*/
		case 's'://settings
			settings();
	}
}

void gamemode(RGBmatrixPanel matrix, int arr[]) {
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
			mainmenu(matrix, arr);
		case 'd'://PvC
			difficulty(matrix, arr);
		case 's'://PvP
			arr[0] = 1;
	}
}

void difficulty(RGBmatrixPanel matrix, int arr[]) {
	clear(matrix);
	exiticon(0, 0, matrix);
	difficon(5, 4, matrix);
	char button;
	do {
		button = getButtonPress();
	} while (!(button == 'x' || button == 'd' /*|| button == 'r'*/ || button == 's'));

	switch(button) {
		case 'x'://back to gamemode
			gamemode(matrix, arr);
		case 'd'://hard
			arr[0] = 3;
		//case 'r'://medium
			//arr[0] = 3;
		case 's'://easy
			arr[0] = 2;
	}
}

//void tutorial();
void settings(RGBmatrixPanel matrix, int arr[]) {
	clear(matrix);
	exiticon(0, 0, matrix);
	colorsicon(6, 5, matrix);
	soundicon(17, 7, matrix);

	char button;

	do {
		button = getButtonPress();
	} while (!(button == 'x' || button == 'r' /*|| button == 's'*/));

	switch(button) {
		case 'x'://exit
			mainmenu(matrix, arr);
		case 'r'://colors
			colorscheme(matrix, arr);
		//case 's'://sound
			//sounds
	}
}

void colorscheme(RGBmatrixPanel matrix, int arr[]) {
	clear(matrix);
	exiticon(0, 0, matrix);
	schemeicon(6, 5, matrix, defaultScheme);//default
	schemeicon(14, 5, matrix, scheme1);
	schemeicon(22, 5, matrix, scheme2);

	char button = getButtonPress();

	while (button != 'x') {
		switch(button) {
			case 'x'://exit
				settings(matrix, arr);
			case 'd'://default scheme
				outline(5, 4, matrix);
				arr[1] = 0;
			case 'r':
				arr[1] = 1;
				outline(13, 4, matrix);
			case 's':
				arr[1] = 2;
				outline(21, 4, matrix);
		}

		if (button != 'x') button = getButtonPress();
	}
}

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
	matrix.drawLine(x-2, y+3, x+2, y+3, matrix.Color333(0, 0, 7));
	matrix.fillRect(x-3, y+4, 7, 2, matrix.Color333(0, 0, 7));

	matrix.drawRect(x, y-2, 6, 5, matrix.Color333(7, 0, 0));
	matrix.drawRect(x+1, y-1, 4, 3, matrix.Color333(0, 0, 0));
	matrix.drawLine(x+2, y+3, x+3, y+3, matrix.Color333(7, 0, 0));
	matrix.drawLine(x+1, y+4, x+4, y+4, matrix.Color333(7, 0, 0));
	matrix.drawLine(x, y+5, x+5, y+5, matrix.Color333(7, 0, 0));
}
void difficon(int x, int y, RGBmatrixPanel matrix) {
	matrix.fillRect(x, y+4, 2, 3, matrix.Color333(0, 7, 0));//easy

	matrix.fillRect(x+6, y+4, 2, 3, matrix.Color333(7, 7, 0));//medium
	matrix.fillRect(x+9, y+2, 2, 5, matrix.Color333(7, 7, 0));

	matrix.fillRect(x+15, y+4, 2, 3, matrix.Color333(7, 0, 0));//hard
	matrix.fillRect(x+18, y+2, 2, 5, matrix.Color333(7, 0, 0));
	matrix.fillRect(x+21, y, 2, 7, matrix.Color333(7, 0, 0));
}

void colorsicon(int x, int y, RGBmatrixPanel matrix) {
	matrix.drawPixel(x, y, matrix.Color333(7, 0, 0));
	matrix.drawLine(x, y+1, x+1, y, matrix.Color333(7, 4, 0));
	matrix.drawLine(x, y+2, x+2, y, matrix.Color333(7, 7, 0));
	matrix.drawLine(x, y+3, x+3, y, matrix.Color333(4, 7, 0));
	matrix.drawLine(x, y+4, x+4, y, matrix.Color333(0, 7, 0));
	matrix.drawLine(x, y+5, x+5, y, matrix.Color333(0, 7, 4));
	matrix.drawLine(x+1, y+5, x+5, y+1, matrix.Color333(0, 7, 7));
	matrix.drawLine(x+2, y+5, x+5, y+2, matrix.Color333(0, 4, 7));
	matrix.drawLine(x+3, y+5, x+5, y+3, matrix.Color333(0, 0, 7));
	matrix.drawLine(x+4, y+5, x+5, y+4, matrix.Color333(4, 0, 7));
	matrix.drawPixel(x+5, y+5, matrix.Color333(7, 0, 7));
}
void soundicon(int x, int y, RGBmatrixPanel matrix) {
	matrix.fillRect(x, y-1, 2, 3, matrix.Color333(7, 7, 7));
	matrix.drawLine(x+2, y-2, x+2, y+2, matrix.Color333(7, 7, 7));
	matrix.drawLine(x+3, y-3, x+3, y+3, matrix.Color333(7, 7, 7));

	matrix.drawPixel(x+5, y-2, matrix.Color333(7, 7, 7));
	matrix.drawLine(x+6, y-1, x+6, y+1, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+5, y+2, matrix.Color333(7, 7, 7));

	matrix.drawPixel(x+6, y-4, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+7, y-3, matrix.Color333(7, 7, 7));
	matrix.drawLine(x+8, y-2, x+8, y+2, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+7, y+3, matrix.Color333(7, 7, 7));
	matrix.drawPixel(x+6, y+4, matrix.Color333(7, 7, 7));
}
void outline(int x, int y, RGBmatrixPanel matrix) {
	matrix.drawRect(x, y, 7, 7, matrix.Color333(7, 7, 7));
}
void schemeicon(int x, int y, RGBmatrixPanel matrix, struct colorScheme scheme) {
	matrix.drawLine(x, y, x, y+4, scheme.c0);
	matrix.drawLine(x+1, y, x+1, y+4, scheme.c1);
	matrix.drawLine(x+2, y, x+2, y+4, scheme.c2);
	matrix.drawLine(x+3, y, x+3, y+4, scheme.c3);
	matrix.drawLine(x+3, y, x+3, y+4, scheme.c4);
}

void clear(RGBmatrixPanel matrix) {
	matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 0));
}
