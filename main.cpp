#include <curses.h>
#include <iostream>
#include <string.h>
#include "common.hpp"
#include "mainScreen.hpp"
#include "verbs.hpp"

WINDOW* stdscr;
WINDOW* win;

void startNewGame();
void loadGame();


const char* hitButton = "Please enter any button to continue.";

int main() {
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
	}

	else {
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
			startNewGame();
			break;
		case 1:
			loadGame();
			break;
		case 2:
			break;
		}

		//frees memory used by created subwindow
		delwin(win);
	}

	//deallocates memory and ends ncurses
	endwin();


	return 0;
}

void startNewGame() {

	//clears and boxes window 
	wclear(win);
	box(win, '|', '_');

	//moves cursor and displays starting game message
	wmove(win, 1, 1);
	wprintw(win, "Welcome to Murder Mystery."); 
	wmove(win, 2, 1);
	wprintw(win, "Somebody has been murdered and it is up to you to find the killer and"); 
	wmove(win, 3, 1);
	wprintw(win, "\tbring them to justice.");
	wmove(win, 4, 1);
	wprintw(win, "There are a number of rooms you must explore. The first room is where");
	wmove(win, 5, 1);
	wprintw(win, "\tyou will start. All of the suspects have been detained in this");
	wmove(win, 6, 1);
	wprintw(win, "\troom. The other rooms will contain clues or puzzles that");
	wmove(win, 7, 1);
	wprintw(win, "\twill lead you to clues.");
	wmove(win, 8, 1);
	wprintw(win, "You win the game by guessing the correct murderer. You may guess who");
	wmove(win, 9, 1);
	wprintw(win, "\tthe murderer is at any point, but if you are wrong, the game");
	wmove(win, 10, 1);
	wprintw(win, "\tends and you lose.");
	wmove(win, 11, 1);
	wprintw(win, "At any point in the game, you may type help to see a list of possible");
	wmove(win, 12, 1);
	wprintw(win, "\t commands.");
	wmove(win, 13, 1);
	wprintw(win, hitButton);
	move(0, 0);
	wrefresh(win);
	getch();
}

void loadGame() {
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


