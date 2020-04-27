#include <curses.h>
#include <iostream>
#include <string.h>
#include "common.hpp"
#include "Game.hpp"
#include "gameFunctions.hpp"

WINDOW* stdscr;
WINDOW* win;
const char* hitButton = "Please enter any button to continue.";


int main() {
	//Game game1;
	//game1.createRooms();

	//below is formatting code to be uncommented later
	//include initializing screen, making sure screen is big enough, creating a new screen, and displaying the main menu
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";
	const char* menuInstructions = "Please use the arrow keys to move up/down. Hit enter to select option.";
	int menuChoice;

	//initializes screen, allocates memory for screen
	stdscr = initscr();

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
		endwin();
		return 0;
	}

	//will print instructions for menu
	move(0, 0);
	printw(menuInstructions);

	//creates new window from parameters
	win = newwin(newHeight, newWidth, start_y, start_x);
	refresh();

	//this allows arrow keys and enter button to be captured
	keypad(win, TRUE);

	//obtains menu choice from user and acts accordingly
	menuChoice = displayMainScreen();
	move(0, 0);
	clrtoeol();
	refresh();
	switch (menuChoice) {
	case 0:
		Game game1;
		game1.displayGameInfo();
		break;
	case 1:
		loadGame();
		break;
	case 2:
		delwin(win);
		endwin();
		return 0;
		break;
	}

	//frees memory used by created subwindow
	delwin(win);
	

	//deallocates memory and ends ncurses
	endwin();


	return 0;
}






