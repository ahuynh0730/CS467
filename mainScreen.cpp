#include "mainScreen.hpp"

#include <cmath>
#include <string.h>



void displayMainScreen(WINDOW* win) {

	const char* gameTitle = "Murder Mystery";
	const char* startOption = "Start New Game";
	const char* loadOption = "Load Game";
	const char* quitGame = "Quit Game";
	const char* arrow = "->";
	int arrowPosition = 0;
	char playerInput = '0';
	

	
	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(win, height, width);
	
	//initializes middleWidth
	int middleWidth = ceil(width / 2);

	//loop until player hits a button
	while (playerInput != 'a') {
		//boxes window
		box(win, '|', '_');

		//moves cursor to middle of fifth row and prints game title
		wmove(win, 5, middleWidth - strlen(gameTitle) / 2);
		wprintw(win, gameTitle);


		//moves cursor and prints start new game option
		int newGameRow = height - 10;
		wmove(win, newGameRow, middleWidth - strlen(startOption) / 2);
		wprintw(win, startOption);

		//moves cursor and prints load game option
		int loadGameRow = newGameRow + 1;
		wmove(win, loadGameRow, middleWidth - strlen(loadOption) / 2);
		wprintw(win, loadOption);


		//moves cursor and prints quit option
		int quitGameRow = loadGameRow + 1;
		wmove(win, quitGameRow, middleWidth - strlen(quitGame) / 2);
		wprintw(win, quitGame);

		//will print arrow on correct row
		switch (arrowPosition) {
		case 0:
			wmove(win, newGameRow, middleWidth - strlen(startOption) / 2 - 3);
			wprintw(win, arrow);
			break;
		case 1:
			wmove(win, loadGameRow, middleWidth - strlen(loadOption) / 2 - 3);
			wprintw(win, arrow);
			break;
		case 2:
			wmove(win, quitGameRow, middleWidth - strlen(quitGame) / 2 - 3);
			wprintw(win, arrow);
			break;
		default:
			break;
		}

		//refreshes screen
		wrefresh(win);

		//will move arrows up and down with w and s
		playerInput = wgetch(win);
		switch (playerInput) {
		case 'w':
			arrowPosition = (arrowPosition + 2) % 3;
			break;
		case 's':
			arrowPosition = (arrowPosition + 1) % 3;
			break;
		default:
			break;
		}

		//clears window before printing again
		wclear(win);
	}




	
}

