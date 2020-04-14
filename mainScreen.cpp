#include "mainScreen.hpp"

#include <cmath>
#include <curses.h>
#include <string.h>



void displayMainScreen() {

	const char* gameTitle = "Murder Mystery";
	const char* startOption = "Start New Game";
	const char* loadOption = "Load Game";
	const char* quitGame = "Quit Game";

	//initializes screen, allocates memory for screen
	initscr();

	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(stdscr, height, width);

	//initializes middleWidth
	int middleWidth = ceil(width / 2);

	//moves cursor to middle of first row
	move(5, middleWidth - strlen(gameTitle) / 2);

	//prints game title to window
	printw(gameTitle);

	//moves cursor and prints start new game option
	int startingRow = height - 10;
	move(startingRow, middleWidth - strlen(startOption) / 2);
	printw(startOption);

	//moves cursor and prints load game option
	startingRow++;
	move(startingRow, middleWidth - strlen(loadOption) / 2);
	printw(loadOption);


	//moves cursor and prints quit option
	startingRow++;
	move(startingRow, middleWidth - strlen(quitGame) / 2);
	printw(quitGame);

	//refreshes screen
	refresh();

	getch();

	//deallocates memory and ends ncurses
	endwin();
	/*
	clearScreen();
	std::cout << "Murder Mystery" << std::endl;

	std::cout << std::endl << std::endl << "Start Game" << std::endl;
	std::cout << "Load Game" << std::endl;
	std::cout << "Quit" << std::endl;*/

}

