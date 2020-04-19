#include <iostream>
#include <curses.h>
#include "mainScreen.hpp"


int main() {
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";

	//initializes screen, allocates memory for screen
	initscr();

	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(stdscr, height, width);

	int newHeight, newWidth, start_y, start_x;
	newHeight = 25;
	newWidth = 75;
	start_y = (height - newHeight) / 2;
	start_x = (width - newWidth) / 2;

	//will display message if screen needs to be bigger
	if (height < newHeight + 4 || width < newWidth + 4) {
		if (height < newHeight + 4 && width < newWidth + 4) {
			printf("%s\n", makeWiderAndTaller);
		}
		else if (height < newHeight + 4) {
			printf("%s\n", makeTaller);
		}
		else if (width < newWidth + 4) {
			printf("%s\n", makeWider);
		}
	}

	else {
		//creates new window from parameters
		WINDOW* win = newwin(newHeight, newWidth, start_y, start_x);
		refresh();

		keypad(win, TRUE);

		displayMainScreen(win);
	}
	//deallocates memory and ends ncurses
	endwin();

	return 0;
}

