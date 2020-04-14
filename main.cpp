#include <iostream>
#include <curses.h>
#include "mainScreen.hpp"


int main() {
	const char* makeTaller = "Please make your console screen taller.";
	const char* makeWider = "Please make your console screen wider.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider.";

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
		move(0, 0);
		if (height < newHeight + 4 && width < newWidth + 4) {
			printw(makeWiderAndTaller);
		}
		else if (height < newHeight + 4) {
			printw(makeTaller);
		}
		else if (width < newWidth + 4) {
			printw(makeWider);
		}
	}

	else {
		//creates new window from parameters
		WINDOW* win = newwin(newHeight, newWidth, start_y, start_x);
		refresh();

		//boxes window
		box(win, '|', '_');
		displayMainScreen(win);
	}

	//deallocates memory and ends ncurses
	endwin();

	return 0;
}

