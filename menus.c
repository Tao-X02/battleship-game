#include <LiquidCrystal.h>
//#include led display library
#include "menus.h"

void mainmenu() {
	matrix.setCursor(15, 7);
	exitbutton(0, 0);
	playbutton(11, 1);
	settingsbutton(26, 11);
	helpbutton(5, 10);
}
void battleship() {
	matrix.setCursor(15, 7);
	exitbutton(0, 0);
	pvpicon(9, 6);
	pvcicon(20, 6);
}



/*Button Displays*/
void exiticon(int x, int y) {
	matrix.drawLine(0, 0, 2, 2, matrix.Color333(7, 0, 0));
	matrix.drawLine(0, 2, 2, 0, matrix.Color333(7, 0, 0));
}
void playicon(int x, int y) {//green
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
void settingsicon(int x, int y) {//white
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
void helpicon(int x, int y) {//purple
	matrix.drawCircle(x, y, 2, matrix.Color333(7, 0, 7));
	matrix.drawPixel(x-2, y, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x-2, y+1, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x-1, y+2, matrix.Color333(0, 0, 0));
	matrix.drawPixel(x, y+3, matrix.Color333(7, 0, 7));
	matrix.drawPixel(x, y+5, matrix.Color333(7, 0, 7));
}
void pvpicon(int x, int y) {
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
void pvcicon(int x, int y) {
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