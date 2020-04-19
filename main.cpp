#include <curses.h>
#include <iostream>
#include "mainScreen.hpp"

void startNewGame(WINDOW*);
void loadGame(WINDOW*);

const char* hitButton = "Please enter any button to continue.";

int main() {
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";
	const char* menuInstructions = "Please use the arrow keys to move up/down. Hit enter to select option.";
	int menuChoice;

	//initializes screen, allocates memory for screen
	initscr();

	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(stdscr, height, width);

	//dimensions for new screen
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
		move(1, 0);
		printw(hitButton);
		refresh();
		getch();
	}

	else {
		//will print instructions for menu
		move(0, 0);
		printw(menuInstructions);

		//creates new window from parameters
		WINDOW* win = newwin(newHeight, newWidth, start_y, start_x);
		refresh();

		//this allows arrow keys and enter button to be captured
		keypad(win, TRUE);

		//obtains menu choice from user and acts accordingly
		menuChoice = displayMainScreen(win);
		move(0, 0);
		clrtoeol();
		refresh();
		switch (menuChoice) {
		case 0:
			startNewGame(win);
			break;
		case 1:
			loadGame(win);
			break;
		case 2:
			break;
		}
	}

	//deallocates memory and ends ncurses
	endwin();


	return 0;
}

void startNewGame(WINDOW* win) {
	//clears and boxes window 
	wclear(win);
	box(win, '|', '_');

	//moves cursor and displays starting game message
	wmove(win, 1, 1);
	wprintw(win, "Starting game");
	wmove(win, 2, 1);
	wprintw(win, hitButton);
	wrefresh(win);
	getch();
}

void loadGame(WINDOW* win) {
	//clears and boxes window 
	wclear(win);
	box(win, '|', '_');

	//moves cursor and displays loading game message
	wmove(win, 1, 1);
	wprintw(win, "Loading game");
	wmove(win, 2, 1);
	wprintw(win, hitButton);
	wrefresh(win);
	getch();
}


