#include "Game.hpp"

void Game::displayGameInfo() {

	//clears window 
	wclear(win);
	

	//moves cursor and displays starting game message
	wmove(win, 0, 0);
	wprintw(win, "Welcome to Murder Mystery.");

	wmove(win, 1, 0);
	wprintw(win, "Somebody has been murdered and it is up to you to find the killer and\n\tbring them to justice.\n");
	wprintw(win, "There are a number of rooms you must explore. The first room is where you\n\twill start. ");
	wprintw(win, "All of the suspects have been detained in this room.");
	wprintw(win, "\n\tThe other rooms will contain clues or puzzles that ");
	wprintw(win, "will lead you\n\tto clues.\n");

	wprintw(win, "You win the game by guessing the correct murderer. You may guess who");
	wprintw(win, "\n\tthe murderer is at any point, but if you are wrong, the game");
	wprintw(win, "\n\tends and you lose.\n");

	wprintw(win, "At any point in the game, you may type help to see a list of possible");
	wprintw(win, "\n\t commands.\n");
	wprintw(win, hitButton);
	move(0, 0);
	wrefresh(win);
	getch();

}

void Game::createRooms() {
	std::ifstream inFile;
	std::string inputLine;
	std::string pathName;
	int roomNumber, up, right, down, left;

	for (int i = 0; i < 15; i++) {
		rooms.push_back(Room());
	}
	

	
	for (int i = 1; i < 16; i++) {
		pathName = "rooms/room" + std::to_string(i) + ".txt";
		inFile.open(pathName);
		inFile >> roomNumber >> up >> right >> down >> left;
		//extra getline is needed to prevent reading the trailing '\n' at end of line for left room
		std::getline(inFile, inputLine);
		std::getline(inFile, inputLine);
		
		//decrementing numbers to account for zero indexing
		//numbers will be -1 if 0 was read in(or null)
		roomNumber--;
		up--;
		right--;
		down--;
		left--;


		rooms[roomNumber].setRoomNumber(roomNumber + 1);
		
		//will assign pointer to correct room unless it is < 0
		if (up > -1) {
			rooms[roomNumber].connectUp(&(rooms[up]));
		}
		if (right > -1) {
			rooms[roomNumber].connectRight(&(rooms[right]));
		}
		if (down > -1) {
			rooms[roomNumber].connectDown(&(rooms[down]));
		}
		if (left > -1) {
			rooms[roomNumber].connectLeft(&(rooms[left]));
		}
		rooms[roomNumber].setLongDescription(inputLine);

		inFile.close();
	}

	currentRoom = &(rooms[0]);

}

Room * Game::getCurrentRoom(){
	return currentRoom;
}

bool Game::getGameOverStatus(){
	return gameOver;
}

void Game::freeGame(){
	for (unsigned int i = 0; i < rooms.size(); i++) {
		rooms[i].freeRoom();
	}
}

void Game::displayHelpList(){
	saveScreen();


	//list of available commands
	wmove(win, 0, 0);
	wprintw(win, "These are available commands during gameplay.");
	wprintw(win, "\n1. look : This repeats the long explanation of the room");
	wprintw(win, "\n2. look at : This gives an explanation or the object.");
	wprintw(win, "\n3. go : This allows you to travel to adjacent rooms.");
	wprintw(win, "\n4. take : This allows you to put an object in your inventory.");
	wprintw(win, "\n5. help : This will bring up the available commands during gameplay.");
	wprintw(win, "\n6. inventory : This will list the contents of your inventory.");
	wrefresh(win);

	move(0, 0);
	printw("Press any key to return to previous screen.");
	refresh();
	getch();

	previousScreen();
	wrefresh(win);
	wrefresh(borderWindow);
	refresh();
}

void Game::saveScreen(){
	//opens a file and puts stdscr content in file
	FILE* myFile;
	myFile = fopen("stdscrWindow.txt", "w");
	putwin(stdscr, myFile);
	fclose(myFile);

	//opens file and puts border content in file
	myFile = fopen("borderWindow.txt", "w");
	putwin(borderWindow, myFile);
	fclose(myFile);

	//opens file and puts subwindow content in file
	myFile = fopen("subwindow.txt", "w");
	putwin(win, myFile);
	fclose(myFile);
}

void Game::previousScreen(){

	FILE* myFile;
	//frees window before opening again 
	delwin(borderWindow);
	delwin(win);
	endwin();

	//returns mainscreen to how it was before
	myFile = fopen("stdscrWindow.txt", "r");
	stdscr = getwin(myFile);
	fclose(myFile);

	//returns border subscreen
	//opens file for reading window content and updates window
	myFile = fopen("borderWindow.txt", "r");
	borderWindow = getwin(myFile);
	fclose(myFile);

	//returns subscreen
	//opens file for reading window content and updates window
	myFile = fopen("subwindow.txt", "r");
	win = getwin(myFile);
	fclose(myFile);

	//removes newly created files for windows
	remove("stdscrWindow.txt");
	remove("subwindow.txt");
	remove("borderWindow.txt");


	//updates screen
	wrefresh(win);
	wrefresh(borderWindow);
	refresh();

	move(0, 0);
	clrtoeol();
}

int Game::displayMainScreen(){
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

void Game::loadGame(){
	
	//clears and boxes window 
	wclear(win);

	//moves cursor and displays loading game message
	wmove(win, 0, 0);
	wprintw(win, "Loading game\n");
	wprintw(win, hitButton);
	wrefresh(win);
	getch();

	gameOver = true;
}

