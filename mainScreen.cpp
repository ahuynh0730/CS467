#include "mainScreen.hpp"

#include <cmath>
#include <string.h>



void displayMainScreen(WINDOW* win) {

	const char* gameTitle = "Murder Mystery";
	const char* startOption = "Start New Game";
	const char* loadOption = "Load Game";
	const char* quitGame = "Quit Game";

	
	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(win, height, width);
	
	//initializes middleWidth
	int middleWidth = ceil(width / 2);

	//moves cursor to middle of fifth row and prints game title
	wmove(win, 5, middleWidth - strlen(gameTitle) / 2);
	wprintw(win, gameTitle);


	//moves cursor and prints start new game option
	int startingRow = height - 10;
	wmove(win, startingRow, middleWidth - strlen(startOption) / 2);
	wprintw(win, startOption);

	//moves cursor and prints load game option
	startingRow++;
	wmove(win, startingRow, middleWidth - strlen(loadOption) / 2);
	wprintw(win, loadOption);


	//moves cursor and prints quit option
	startingRow++;
	wmove(win, startingRow, middleWidth - strlen(quitGame) / 2);
	wprintw(win, quitGame);

	//refreshes screen
	wrefresh(win);

	getch();

	
}

