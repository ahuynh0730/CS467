#include "gameFunctions.hpp"


int displayMainScreen() {

	const char* gameTitle = "Murder Mystery";
	const char* startOption = "Start New Game";
	const char* loadOption = "Load Game";
	const char* quitGame = "Quit Game";
	const char* arrow = "->";
	int arrowPosition = 0;
	int playerInput = -1;
	

	
	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(win, height, width);
	
	//initializes middleWidth
	int middleWidth = ceil(width / 2);

	//loop that will only end upon hitting enter, and returns position of arrow
	while (1) {
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
			break;
		case 1:
			wmove(win, loadGameRow, middleWidth - strlen(loadOption) / 2 - 3);
			break;
		case 2:
			wmove(win, quitGameRow, middleWidth - strlen(quitGame) / 2 - 3);
			break;
		default:
			break;
		}

		wprintw(win, arrow);

		//refreshes screen
		wrefresh(win);

		//will move arrows up and down with up and down arrows
		playerInput = wgetch(win);
		switch (playerInput) {
		case KEY_UP:
			arrowPosition = (arrowPosition + 2) % 3;
			break;
		case KEY_DOWN:
			arrowPosition = (arrowPosition + 1) % 3;
			break;
		case 10:
			return arrowPosition;
			break;
		}
		

		//clears window before printing again
		wclear(win);
	}


	
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

void displayHelpList() {
	
	saveScreen();

	//clears and boxes window
	wclear(win);
	box(win, '|', '_');

	//list of available commands
	wmove(win, 1, 1);
	wprintw(win, "These are available commands during gameplay.");
	wmove(win, 2, 1);
	wprintw(win, "1. look : This repeats the long explanation of the room");
	wmove(win, 3, 1);
	wprintw(win, "2. look at : This gives an explanation or the object.");
	wmove(win, 4, 1);
	wprintw(win, "3. go : This allows you to travel to adjacent rooms.");
	wmove(win, 5, 1);
	wprintw(win, "4. take : This allows you to put an object in your inventory.");
	wmove(win, 6, 1);
	wprintw(win, "5. help : This will bring up the available commands during gameplay.");
	wmove(win, 7, 1);
	wprintw(win, "6. inventory : This will list the contents of your inventory.");

	wrefresh(win);
	move(0, 0);
	printw("Press any key to return to previous screen.");
	refresh();
	getch();

	previousScreen();
	
}

// this function saves content on screen and should be called before a new screen is displayed
void saveScreen() {
	//opens a file and puts stdscr content in file
	FILE* myFile;
	myFile = fopen("stdscrWindow.txt", "w");
	putwin(stdscr, myFile);
	fclose(myFile);

	//opens file and puts subwindow content in file
	myFile = fopen("subwindow.txt", "w");
	putwin(win, myFile);
	fclose(myFile);
}

//restores what the screen looked like prior to new screen
void previousScreen() {
	FILE* myFile;
	//frees window before opening again 
	delwin(win);
	endwin();

	//returns mainscreen to how it was before
	myFile = fopen("stdscrWindow.txt", "r");
	stdscr = getwin(myFile);
	fclose(myFile);

	//returns subscreen
	//opens file for reading window content and updates window
	myFile = fopen("subwindow.txt", "r");
	win = getwin(myFile);
	fclose(myFile);

	//removes newly created files for windows
	remove("stdscrWindow.txt");
	remove("subwindow.txt");


	//updates screen
	refresh();
	wrefresh(win);
}