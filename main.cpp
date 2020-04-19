#include <curses.h>
#include <iostream>
#include "mainScreen.hpp"


int main() {
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";
	const char* hitButton = "Please enter any button to continue.";
	const char* menuInstructions = "Please use the arrow keys to move up/down. Hit enter to select option.";
	int menuChoice;

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
			//printf("%s\n", makeWiderAndTaller);
		}
		else if (height < newHeight + 4) {
			printw(makeTaller);
			//printf("%s\n", makeTaller);
		}
		else if (width < newWidth + 4) {
			printw(makeWider);
			//printf("%s\n", makeWider);
		}
		move(1, 0);
		printw(hitButton);
		refresh();
	}

	else {
		move(0, 0);
		printw(menuInstructions);

		//creates new window from parameters
		WINDOW* win = newwin(newHeight, newWidth, start_y, start_x);
		refresh();

		keypad(win, TRUE);

		menuChoice = displayMainScreen(win);
	}
	getch();

	//deallocates memory and ends ncurses
	endwin();


	return 0;
}

