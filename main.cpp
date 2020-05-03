#include <curses.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include "common.hpp"
#include "Game.hpp"

WINDOW* stdscr;
WINDOW* win;
WINDOW* borderWindow;
const char* hitButton = "Please enter any button to continue.";


int main() {
	//char* direction = (char*)"north";
	//Game game1;
	//game1.createRooms();
	//for (unsigned int i = 0; i < game1.getCurrentRoom()->getTravelCommandsVector().size(); i++) {
		//std::cout << game1.getCurrentRoom()->getTravelCommandsVector()[i] << std::endl;
	//}
	//game1.travelTo((char*)"north\0");
	//game1.travelTo(direction);

	
	//below is formatting code to be uncommented later
	//include initializing screen, making sure screen is big enough, creating a new screen, and displaying the main menu
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";
	const char* menuInstructions = "Please use the arrow keys to move up/down. Hit enter to select option.";
	char playerInput[100];
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
	//borderWindow will only be used for the border of the game
	borderWindow = newwin(newHeight + 2, newWidth + 2, start_y - 1, start_x - 1);
	box(borderWindow, '|', '_');
	win = newwin(newHeight, newWidth, start_y, start_x);
	refresh();
	wrefresh(borderWindow);
	

	//this allows arrow keys and enter button to be captured
	keypad(win, TRUE);

	//obtains menu choice from user and acts accordingly
	Game game1;
	menuChoice = game1.displayMainScreen();
	move(0, 0);
	clrtoeol();
	refresh();
	switch (menuChoice) {
	
	//option for starting new game
	case 0:
		game1.displayGameInfo();
		game1.createRooms();
		break;

	//option for loading game
	case 1:
		game1.loadGame();
		break;

	//option for quitting game
	case 2:
		delwin(win);
		delwin(borderWindow);
		endwin();
		return 0;
		break;
	}

	//runs until game is over
	while (game1.getGameOverStatus() == false) {
		move(0, 0);
		clrtoeol();
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, game1.getCurrentRoom()->getDescription());
		wrefresh(win);
		move(0, 0);

		//gets player command and will tell player if the command is invalid
		getstr(playerInput);
		for (unsigned int i = 0; i < strlen(playerInput); i++) {
			playerInput[i] = tolower(playerInput[i]);
		}
		if (strcmp("look", playerInput) == 0) {
			game1.saveScreen();
			wclear(win);
			wrefresh(win);
			wprintw(win, game1.getCurrentRoom()->getLongDescription());
			wmove(win, 1, 0);
			wprintw(win, hitButton);
			wrefresh(win);
			getch();
			game1.previousScreen();
		}
		else if (strncmp("look at ", playerInput, 8) == 0) {
			game1.lookAt();
		}
		else if (strncmp("go ", playerInput, 2) == 0) {
			char* destination = &(playerInput[3]);
			game1.travelTo(destination);
		}
		else if (game1.getCurrentRoom()->getTravelVectorPosition((std::string) playerInput) != -1) {
			game1.travelTo(playerInput);
		}
		else if (strncmp("take ", playerInput, 5) == 0) {
			game1.take();
		}
		else if (strcmp("help", playerInput) == 0) {
			game1.displayHelpList();
		}
		else if (strcmp("inventory", playerInput) == 0) {
			game1.displayInventory();
		}
		else if (strcmp("savegame", playerInput) == 0) {
			game1.saveGame();
			break;
		}
		else {
			move(0, 0);
			printw("Invalid command. Please try again.");
			refresh();
			usleep(1000000);
		}

	}

	
	//frees memory used by created subwindows
	delwin(win);
	delwin(borderWindow);
	


	//deallocates memory and ends ncurses
	endwin();
	game1.freeGame();
	


	return 0;
}






