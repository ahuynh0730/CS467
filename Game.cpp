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

void Game::createInteractables() {
	/*
	interactables.insert(std::pair<std::string, Interactable*>("Adam", new Interactable("Adam", "Adam's description", nullptr, this, false)));
	interactables.insert(std::pair<std::string, Interactable*>("Sofia", new Suspect(true, "Sofia", "Sofia's description", nullptr, this)));
	interactables.insert(std::pair<std::string, Interactable*>("Lucas", new Suspect(false, "Lucas", "Lucas's description", nullptr, this)));
	interactables.insert(std::pair<std::string, Interactable*>("Daniel", new Suspect(false, "Daniel", "Daniel's description", nullptr, this)));
	interactables.insert(std::pair<std::string, Interactable*>("Chris", new Suspect(false, "Chris", "Chris's description", nullptr, this)));
	interactables.insert(std::pair<std::string, Interactable*>("Jack", new Suspect(false, "Jack", "Jack's description", nullptr, this)));
	interactables.insert(std::pair<std::string, Interactable*>("Tiana", new Suspect(false, "Tiana", "Tiana's description", nullptr, this)));
	*/
}

void Game::freeInteractables() {
	/*
	for(std::map<std::string, Interactable*>::iterator it = interactables.begin(); it != interactables.end(); it++){
		delete it->second;
	}
	interactables.clear();
	*/
}

void Game::createRooms() {
	//createInteractables();

	std::ifstream inFile;
	std::string inputLine;
	std::string pathName;
	int roomNumber, up, right, down, left, numberInteractables, interactableType;

	for (int i = 0; i < 15; i++) {
		rooms.push_back(Room());
	}

	currentRoom = &(rooms[0]);
	

	
	for (int i = 1; i < 16; i++) {
		pathName = "rooms/room" + std::to_string(i) + ".txt";
		inFile.open(pathName);
		inFile >> roomNumber >> up >> right >> down >> left;
		
		
		//decrementing numbers to account for zero indexing
		//numbers will be -1 if 0 was read in(or null)
		roomNumber--;
		up--;
		right--;
		down--;
		left--;

		//reads in long description
		//extra getline is needed to prevent reading the trailing '\n' at end of line for left room
		std::getline(inFile, inputLine);
		std::getline(inFile, inputLine);
		replaceEscapeCharacters(inputLine);
		rooms[roomNumber].setLongDescription(inputLine);


		//reads in short description
		std::getline(inFile, inputLine);
		replaceEscapeCharacters(inputLine);
		rooms[roomNumber].setShortDescription(inputLine);

		//reads in commands user can enter for traveling
		for (int j = 0; j < 8; j++) {
			std::getline(inFile, inputLine);
			rooms[roomNumber].addTravelCommand(inputLine);
		}

		//reads in number of interactables the room will start with
		inFile >> numberInteractables;

		//loop that reads in object descriptions and creates them
		std::string name;
		std::string description;
		std::string blockedDescription;
		std::string answer;
		Interactable* objectPointer = NULL;
		bool guilty = false;
		for (int j = 0; j < numberInteractables; j++) {
			inFile >> interactableType;
			std::getline(inFile, inputLine);
			std::getline(inFile, name);
			std::getline(inFile, description);
			replaceEscapeCharacters(description);
			switch (interactableType) {
				//base interactable
				case 0:
					objectPointer = new Interactable(name, description);
					break;

				//suspect
				case 1:
					guilty = false;
					inFile >> guilty;
					std::getline(inFile, inputLine);
					objectPointer = new Suspect(name, description, guilty);
					std::getline(inFile, inputLine);
					break;

				//quiz
				case 2:
					std::getline(inFile, answer);
					objectPointer = new Quiz(name, description, answer);
					std::getline(inFile, inputLine);
					break;

				//chest
				case 3:{
					objectPointer = new Chest(name, description);
					int numItems;
					inFile >> numItems;
					std::getline(inFile, inputLine);
					for(int i=0; i<numItems; i++){
						std::string itemName;
						std::getline(inFile, itemName);
						Interactable* item = getInteractableByName(itemName);
						if(item != nullptr && rooms[roomNumber].removeInteractable(item)){
							objectPointer->addItem(item);
						}
					}
					std::getline(inFile, inputLine);
					break;
				}

				//block
				case 4:
					std::getline(inFile, blockedDescription);
					objectPointer = new Block(name, description, blockedDescription);
					break;

				//unblock
				case 5:
					break;

				//creator
				case 6:
					break;

				default:
					break;
			}
			interactables.push_back(objectPointer);
			rooms[roomNumber].addInteractable(objectPointer);

		}
		

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
		

		inFile.close();
	}
}

Room * Game::getCurrentRoom(){
	return currentRoom;
}

bool Game::getGameOverStatus(){
	return gameOver;
}

void Game::setGameOverStatus(bool status){
	gameOver = status;
}

void Game::freeGame(){
	freeInteractables();

	for (unsigned int i = 0; i < rooms.size(); i++) {
		rooms[i].freeRoom();
	}

	for (unsigned int i = 0; i < interactables.size(); i++) {
		interactables[i]->freeInteractable();
		delete(interactables[i]);
	}
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

//dummy function
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

void Game::lookAt(char* object) {
	saveScreen();

	int row = 0;
	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1) {
		wmove(win, row, 0);
		wprintw(win, currentRoom->getItemsList()[position]->getName());
		row++;
		wmove(win, row, 0);
		wprintw(win, currentRoom->getItemsList()[position]->getDescription());
		char* description = currentRoom->getItemsList()[position]->getDescription();
		for (unsigned int i = 0; i < strlen(description); i++) {
			if (description[i] == '\n') {
				row++;
			}
		}
		wrefresh(win);
	}
	else {
		wmove(win, row, 0);
		wprintw(win, "That is an invalid object.");
		row++;
	}
	wmove(win, row, 0);
	wprintw(win, hitButton);
	wrefresh(win);
	getch();

	previousScreen();
}

void Game::travelTo(char* destination){
	
	std::string dest(destination);
	int travelNumber = currentRoom->getTravelVectorPosition(dest);
	
	//will set current room based on travelNumber
	switch (travelNumber) {
		case 0:
		case 1:
			currentRoom = currentRoom->getNorthRoom();
			break;
		case 2:
		case 3:
			currentRoom = currentRoom->getEastRoom();
			break;
		case 4:
		case 5:
			currentRoom = currentRoom->getSouthRoom();
			break;
		case 6:
		case 7:
			currentRoom = currentRoom->getWestRoom();
			break;
		default:
			move(0, 0);
			printw("Invalid location.");
			refresh();
			usleep(1000000);
			break;
	}
	
}

//dummy function
void Game::take() {
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	wprintw(win, "Taking .");
	wprintw(win, "\n%s", hitButton);
	wrefresh(win);
	getch();

	previousScreen();
}

void Game::displayHelpList() {
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
	wprintw(win, "\n7. savegame : This will allow you to save your game.");
	wprintw(win, "\n8. quitgame : This allows the player to quit at any time.");
	wprintw(win, "\n9. accuse : This allows you to accuse a suspect. Game is over after \n\taccusation.");
	wprintw(win, "\n10. solve : This allows you to solve a quiz.");
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

//dummy function
void Game::displayInventory() {
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	wprintw(win, "Displaying inventory.");
	wprintw(win, "\n%s", hitButton);
	wrefresh(win);
	getch();

	previousScreen();
}


//dummy function
void Game::saveGame(){
	move(0, 0);
	clrtoeol();
	wclear(win);
	wprintw(win, "Game is being saved.");
	wprintw(win, "\n%s", hitButton);
	wrefresh(win);
	getch();
}

void Game::gameAccuse(char* object) {
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1) {
		gameOver = currentRoom->getItemsList()[position]->accuse();
	}
	else {
		wmove(win, 0, 0);
		wprintw(win, "Sorry, that is not a valid object");
	}
	wmove(win, 1, 0);
	if (gameOver) {
		wprintw(win, "The game is now over.\n");
	}
	wprintw(win, hitButton);
	wrefresh(win);
	getch();

	previousScreen();
}

void Game::solve(char* object){
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1) {
		currentRoom->getItemsList()[position]->solve();
	}
	else {
		wmove(win, 0, 0);
		wprintw(win, "Sorry, that is not a valid object");
		wmove(win, 1, 0);
		wprintw(win, hitButton);
		wrefresh(win);
	}
	getch();
	previousScreen();
}

std::vector<Interactable*> Game::getInteractables(){
	return interactables;
}



void Game::replaceEscapeCharacters(std::string& stringIn){
	for (unsigned int i = 0; i < stringIn.size(); i++) {
		if (stringIn[i] == '\\') {
			if (stringIn[i + 1] == 'n') {
				stringIn[i] = '\n';
				stringIn.erase(i + 1, 1);
			}
			if (stringIn[i + 1] == 't') {
				stringIn[i] = '\t';
				stringIn.erase(i + 1, 1);
			}
		}
	}
}

std::vector<Room> Game::getRoomsVector(){
	return rooms;
}

void Game::setCurrentRoom(Room* roomIn)
{
	currentRoom = roomIn;
}


Interactable* Game::getInteractableByName(std::string name){
	for(std::vector<Interactable*>::iterator it = interactables.begin(); it != interactables.end(); it++){
		if(strcmp(name.c_str(), (*it)->getName()) == 0){
			return *it;
		}
	}
	return nullptr;
}



void Game::unlock(char* object){// just to test chest, will be removed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1 && currentRoom->getItemsList()[position]->unlock()) {
		std::vector<Interactable*> itemsToAdd = currentRoom->getItemsList()[position]->getItemsList();
		for(std::vector<Interactable*>::iterator it = itemsToAdd.begin(); it != itemsToAdd.end(); it++){
			currentRoom->addInteractable(*it);
		}
	}
}