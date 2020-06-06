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
}



void Game::createRooms() {

	std::ifstream inFile;
	std::string inputLine;
	std::string pathName;
	int roomNumber, up, right, down, left, numberInteractables, interactableType;
	bool darkness;

	for (int i = 0; i < 15; i++) {
		rooms.push_back(Room());
	}

	currentRoom = &(rooms[0]);
	

	
	for (int i = 1; i < 16; i++) {
		pathName = "rooms/room" + std::to_string(i) + ".txt";
		inFile.open(pathName);
		inFile >> roomNumber >> up >> right >> down >> left >> darkness;
		
		
		//decrementing numbers to account for zero indexing
		//numbers will be -1 if 0 was read in(or null)
		roomNumber--;
		up--;
		right--;
		down--;
		left--;
		
		//sets darkness
		rooms[roomNumber].setDarkness(darkness);

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
					std::getline(inFile, inputLine);
					break;

				//suspect
				case 1:
					guilty = false;
					inFile >> guilty;
					std::getline(inFile, inputLine);
					std::getline(inFile, answer);
					objectPointer = new Suspect(name, description, guilty, answer);
					std::getline(inFile, inputLine);
					break;

				//quiz
				case 2:{
					std::getline(inFile, answer);
					std::string itemName;
					std::getline(inFile, itemName);
					Interactable* item = getInteractableByName(itemName);
					if(item != nullptr)
						rooms[roomNumber].removeInteractable(item);
					objectPointer = new Quiz(name, description, answer, item);
					std::getline(inFile, inputLine);
					break;
				}

				//chest
				case 3:{
					std::string itemName;
					std::getline(inFile, itemName);
					Interactable* item = getInteractableByName(itemName);
					objectPointer = new Chest(name, description, item);
					int numItems;
					inFile >> numItems;
					std::getline(inFile, inputLine);
					for(int i=0; i<numItems; i++){
						std::getline(inFile, itemName);
						item = getInteractableByName(itemName);
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
					
				//Food	
				case 7:
					objectPointer = new Food(name, description);
					std::getline(inFile, inputLine);
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

	for (unsigned int i = 0; i < rooms.size(); i++) {
		rooms[i].freeRoom();
	}

	for (unsigned int i = 0; i < interactables.size(); i++) {
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

void Game::lookAt(char* object) {
	saveScreen();

	int row = 0;
	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	int inventoryPosition = -1;
	char* name;
	char* description;
	for(unsigned int i = 0; i < inventory.size(); i++){
		name = inventory[i]->getName();
		if (strncmp(object, name, strlen(name) - 1) == 0){
			inventoryPosition = i;
		}
	}
	if (position != -1 || inventoryPosition != -1) {
		if (position != -1){
			name = currentRoom->getItemsList()[position]->getName();
			description = currentRoom->getItemsList()[position]->getDescription();
		} else if (inventoryPosition != -1){
			name = inventory[inventoryPosition]->getName();
			description = inventory[inventoryPosition]->getDescription();
		}
		wmove(win, row, 0);
		wprintw(win, name);
		row++;
		wmove(win, row, 0);
		wprintw(win, description);
		for (unsigned int i = 0; i < strlen(description); i++) {
			if (description[i] == '\n') {
				row++;
			}
		}
		row++;
		
	}
	else {
		wmove(win, row, 0);
		wprintw(win, "That is an invalid object.");
		row++;
	}
	wrefresh(win);
	wmove(win, row, 0);
}

void Game::travelTo(char* destination){
	saveScreen();
	move(0, 0);
	clrtoeol();
	wclear(win);
	wmove(win, 0, 0);
	
	std::string dest(destination);
	int travelNumber = currentRoom->getTravelVectorPosition(dest);
	bool traveled = true;
	
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
			traveled = false;
			break;
	}
	
	if(traveled)
		wprintw(win, "Traveled to Room %d", currentRoom->getRoomNumber());
	else
		wprintw(win, "Invalid location");

	wmove(win, 1, 0);
}

void Game::gameTake(char* object) {
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1) {
		//if item can be taken, will remove from room and add to inventory
		if(currentRoom->getItemsList()[position]->take() == true){
			wmove(win, 0 ,0);
			wprintw(win, "The %s", currentRoom->getItemsList()[position]->getName());
			int nameLength = strlen(currentRoom->getItemsList()[position]->getName());
			wmove(win, 0, nameLength + 4);
			wprintw(win, "was added to your inventory.");
			inventory.push_back(currentRoom->getItemsList()[position]);
			currentRoom->removeInteractable(currentRoom->getItemsList()[position]);
		} else {
			wmove(win, 0, 0);
			wprintw(win, "You cannot take that object.");
		}
	}
	else {
		wmove(win, 0, 0);
		wprintw(win, "Sorry, that is not a valid object");
	}
	wmove(win, 1, 0);
}

void Game::displayHelpList() {
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);


	//list of available commands
	wmove(win, 0, 0);
	wprintw(win, "These are available commands during gameplay.");
	wprintw(win, "\n1. look : This repeats the long explanation of the room");
	wprintw(win, "\n2. look at (object name): This gives an explanation or the object.");
	wprintw(win, "\n3. go (compass direction or exit description): This allows you to travel\n\tto adjacent rooms.");
	wprintw(win, "\n3. map : display the map of the rooms.");
	wprintw(win, "\n4. take (item name): This allows you to put an object in your inventory.");
	wprintw(win, "\n5. help : This will bring up the available commands during gameplay.");
	wprintw(win, "\n6. inventory : This will list the contents of your inventory.");
	wprintw(win, "\n7. savegame (save name): This will allow you to save your game.");
	wprintw(win, "\n8. quitgame : This allows the player to quit at any time.");
	wprintw(win, "\n9. accuse (suspect name): This allows you to accuse a suspect. Game is\n\tover after accusation.");
	wprintw(win, "\n10. question (suspect name): This allows you to question a suspect.");
	wprintw(win, "\n11. solve (quiz name) (answer): This allows you to solve a quiz.");
	wprintw(win, "\n12. drop (item): This allows you to drop an item in your inventory.");
	wprintw(win, "\n13. fasttravel room (number): This allows you to quickly go to a\n\tpreviously visited room");
	wprintw(win, "\n14. unlock (chest name): This attempts to unlock the chest.");
	wprintw(win, "\n15. open (chest name): This attempts to open the chest.");
	wprintw(win, "\n16. eat (item name) : This allows you to eat an item in your inventory.");
	wrefresh(win);
	wmove(win, 21, 0);
}

void Game::displayMap() {
	saveScreen();


	//list of available commands
	wmove(win, 0, 0);
	wprintw(win, "Here is map of the game:");
	wprintw(win, "\n                                       --------");
	wprintw(win, "\n                                      |   14   |");
	wprintw(win, "\n                                       --------");
	wprintw(win, "\n                                           |");
	wprintw(win, "\n                           --------    --------    --------    --------");
	wprintw(win, "\n                          |   11   |--|   12   |--|   13   |--|   15   |");
	wprintw(win, "\n                           --------    --------    --------    --------");
	wprintw(win, "\n                              |");
	wprintw(win, "\n   -------    -------    -------- ");
	wprintw(win, "\n  |   8   |--|   9   |--|   10   |");
	wprintw(win, "\n   -------    -------    -------- ");
	wprintw(win, "\n      |          |           |");
	wprintw(win, "\n   -------    -------    -------- ");
	wprintw(win, "\n  |   5   |--|   6   |--|    7   |");
	wprintw(win, "\n   -------    -------    -------- ");
	wprintw(win, "\n      |          |           |");
	wprintw(win, "\n   -------    -------    -------- ");
	wprintw(win, "\n  |   2   |--|   3   |--|    4   |");
	wprintw(win, "\n   -------    -------    -------- ");
	wprintw(win, "\n      |");
	wprintw(win, "\n   -------");
	wprintw(win, "\n  |   1   |");
	wprintw(win, "\n   -------");
	wrefresh(win);
	wmove(win, 1, 0);

	move(0, 0);
	refresh();
}

void Game::displayInventory() {
	saveScreen();


	int row = 0;
	move(0, 0);
	clrtoeol();
	wclear(win);
	for (unsigned int i = 0; i < inventory.size(); i++){
		wmove(win, row, 0);
		wprintw(win, inventory[i]->getName());
		row++;
	}
	wmove(win, row, 0);
}

void Game::question(char* object){
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1 && currentRoom->getItemsList()[position]->getType() == 1) {
		currentRoom->getItemsList()[position]->question();
	}
	else {
		wmove(win, 0, 0);
		wprintw(win, "Sorry, that is not a valid object");
		wmove(win, 1, 0);
	}
}

void Game::gameAccuse(char* object) {
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1 && currentRoom->getItemsList()[position]->getType() == 1) {
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
}

void Game::solve(char* object){
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);

	//separate answer from object
	char* answer = object + strlen(object)-1;
	while(answer[0] != ' ')
		answer--;
	answer[0] = '\0';
	answer++;

	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1 && currentRoom->getItemsList()[position]->getType() == 2) {
		//if solving quiz comes back with a reward, will remove quiz from room and add reward
		Interactable* reward = currentRoom->getItemsList()[position]->solve(answer);
		if (reward != nullptr){
			currentRoom->removeInteractable(currentRoom->getItemsList()[position]);
			currentRoom->addInteractable(reward);
			wclear(win);
			wmove(win, 0, 0);
			wprintw(win, "Congratulations, that is the correct answer.");
			wmove(win, 1, 0);
			wprintw(win, reward->getName());
			wmove(win, 1, strlen(reward->getName()));
			wprintw(win, "was added to the room.");
			wmove(win, 2, 0);
		}
		else{			
			wclear(win);
			wmove(win, 0, 0);
			wprintw(win, "Sorry, that is not the correct answer.");
			wmove(win, 1, 0);
		}
	}
	else {
		wmove(win, 0, 0);
		wprintw(win, "Sorry, that is not a valid object");
		wmove(win, 1, 0);
	}
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

void Game::type(char* object){
	saveScreen();

	move(0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	wmove(win, 0, 0);
	if (position != -1) 
		wprintw(win, "The object is of type %d", currentRoom->getItemsList()[position]->getType());
	else 
		wprintw(win, "Sorry, that is not a valid object");
	wmove(win, 1, 0);
}

void Game::unlock(char* object){
	saveScreen();

	move(0, 0);
	wmove(win, 0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1 && currentRoom->getItemsList()[position]->getType() == 3) {
		Interactable* key = currentRoom->getItemsList()[position]->unlock(inventory);

		if(key == nullptr){
			wprintw(win, "Sorry, you couldn't unlock the %s", currentRoom->getItemsList()[position]->getName());
			wmove(win, 1, 0);
		}
		else if(key == currentRoom->getItemsList()[position]){
			wprintw(win, "The %s", currentRoom->getItemsList()[position]->getName());
			wmove(win, 0, 4 + strlen(currentRoom->getItemsList()[position]->getName()));
			wprintw(win, "is already unlocked");
			wmove(win, 1, 0);

		}
		else{
			wprintw(win, "You unlocked the %s", currentRoom->getItemsList()[position]->getName());
			wmove(win, 0, 18 + strlen(currentRoom->getItemsList()[position]->getName()));
			wprintw(win, "using your %s", key->getName());
			wmove(win, 1, 0);
		}
	}
	else {
		wprintw(win, "Sorry, that is not a valid object");
		wmove(win, 1, 0);
	}
}

void Game::open(char* object){	
	saveScreen();

	move(0, 0);
	wmove(win, 0, 0);
	clrtoeol();
	wclear(win);
	object[0] = toupper(object[0]);
	std::string obj(object);
	int position = currentRoom->getItemsListPosition(obj);
	if (position != -1 && currentRoom->getItemsList()[position]->getType() == 3) {
		if(currentRoom->getItemsList()[position]->getIsLocked()){
			wprintw(win, "Sorry, the %s", currentRoom->getItemsList()[position]->getName());
			wmove(win, 0, 11 + strlen(currentRoom->getItemsList()[position]->getName()));
			wprintw(win, "is locked");
			wmove(win, 1, 0);
		}
		else{
			std::vector<Interactable*> itemsToAdd = currentRoom->getItemsList()[position]->getItemsList();
			if(itemsToAdd.size() == 0){
				wprintw(win, "The %s", currentRoom->getItemsList()[position]->getName());
				wmove(win, 0, 4 + strlen(currentRoom->getItemsList()[position]->getName()));
				wprintw(win, "is empty");
				wmove(win, 1, 0);
			}
			else{
				wprintw(win, "Objects added to Room %d:", currentRoom->getRoomNumber());
				int row = 1;
				for(std::vector<Interactable*>::iterator it = itemsToAdd.begin(); it != itemsToAdd.end(); it++){
					currentRoom->addInteractable(*it);
					wmove(win, row, 0);
					wprintw(win, "\t%s", (*it)->getName());
					row++;
				}

				currentRoom->getItemsList()[position]->empty();
				wmove(win, row, 0);
				wprintw(win, "The %s", currentRoom->getItemsList()[position]->getName());
				wmove(win, row, 4 + strlen(currentRoom->getItemsList()[position]->getName()));
				wprintw(win, "is now empty");

				row++;
				wmove(win, row, 0);
			}
		}
	}
	else {
		wprintw(win, "Sorry, that is not a valid object");
		wmove(win, 1, 0);
	}
}

void Game::drop(char* object){
	saveScreen();
	
	
	move(0, 0);
	wmove(win, 0, 0);
	clrtoeol();
	wclear(win);
	
	
	object[0] = toupper(object[0]);
	char* name;
	
	int inventoryPosition = -1;
	for(unsigned int i = 0; i < inventory.size(); i++){
		name = inventory[i]->getName();
		if (strncmp(object, name, strlen(name) - 1) == 0){
			inventoryPosition = i;
		}
	}
	
	if (inventoryPosition != -1){
		Interactable* itemToBeDropped = inventory[inventoryPosition];
		currentRoom->addInteractable(itemToBeDropped);
		wmove(win, 0, 0);
		wprintw(win, itemToBeDropped->getName());
		wmove(win, 0, strlen(itemToBeDropped->getName()));
		wprintw(win, "was dropped from your inventory.");
		inventory.erase(inventory.begin() + inventoryPosition);
	} else {
		wmove(win, 0, 0);
		wprintw(win, "Sorry, that is not a valid object");
	}
	
	wmove(win, 1, 0);
}

void Game::fastTravel(char* roomNumber){
	saveScreen();
	
	move(0, 0);
	wmove(win, 0, 0);
	clrtoeol();
	wclear(win);
	
	int roomNum = atoi(roomNumber);
	bool roomFound = false;
	
	for (unsigned int i = 0; i< roomsVisited.size(); i++){
		if (roomsVisited[i]->getRoomNumber() == roomNum){
			roomFound = true;
			currentRoom = roomsVisited[i];
			wmove(win, 0, 0);
			wprintw(win, "Moving to Room %d", roomsVisited[i]->getRoomNumber());
			break;
		}
		if (roomFound == false && i == roomsVisited.size() - 1){
			wmove(win, 0, 0);
			wprintw(win, "Either you have not been there, or that is not a room name");
		}
	}
	
	wmove(win, 1, 0);
}

void Game::addToRoomsVisited(Room* room){
	for (unsigned int i = 0; i < roomsVisited.size(); i++){
		if (roomsVisited[i] == room){
			return;
		}
	}
	roomsVisited.push_back(room);
}

void Game::gameFrisk(char* suspect){
	saveScreen();
	
	move(0, 0);
	wmove(win, 0, 0);
	clrtoeol();
	wclear(win);
	
	suspect[0] = toupper(suspect[0]);
	std::string sus(suspect);
	int position = currentRoom->getItemsListPosition(sus);
	if (position != -1) {
		if(currentRoom->getItemsList()[position]->getType() == 1)
			currentRoom->getItemsList()[position]->frisk();
		else
			wprintw(win, "You cannot frisk the %s", suspect);
	}
	else
		wprintw(win, "Sorry, that is not a valid object");
	
	wmove(win, 1, 0);
}

void Game::gameEat(char* object){
	saveScreen();
	
	move(0, 0);
	wmove(win, 0, 0);
	clrtoeol();
	wclear(win);
	
	object[0] = toupper(object[0]);
	std::string foodName(object);
	int inventoryPosition = -1;
	for(unsigned int i = 0; i < inventory.size(); i++){
		if (foodName.compare((std::string)inventory[i]->getName())){
			inventoryPosition = i;
		}
	}
	if (inventoryPosition != -1){
		Interactable* itemToBeEaten = inventory[inventoryPosition];
		//check that the item is food
		if(itemToBeEaten->getType() == 7){
			inventory.erase(inventory.begin() + inventoryPosition);
			wprintw(win, "You just ate the %s", object);
		}
		else{
			wprintw(win, "You cannot eat the %s", object);
		}
	}
	else {
		wprintw(win, "That item is not in your inventory");
	}
	
	wmove(win, 1, 0);
}