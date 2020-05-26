#ifndef GAME_hpp
#define GAME_hpp

#include <cmath>
#include <curses.h>
#include <dirent.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.hpp"
#include "Interactable.hpp"
#include "Chest.hpp"
#include "Quiz.hpp"
#include "Room.hpp"
#include "Suspect.hpp"
#include "Block.hpp"



class Game {
private:
	std::vector<Room> rooms;
	std::vector<Interactable*> interactables;
	std::vector<Interactable*> inventory;
	//std::map<std::string, Interactable> interactables; //key is name of interactable
	//std::map<
	Room* currentRoom;
	bool gameOver = false;

	void replaceEscapeCharacters(std::string&);
public:
	Room * getCurrentRoom();
	bool getGameOverStatus();

	void setGameOverStatus(bool status);
	
	void createRooms();
	void createInteractables();
	void displayGameInfo();
	int displayMainScreen();
	void freeGame();
	void freeInteractables();
	void previousScreen();
	void saveScreen();


	
	void loadGame();
	void lookAt(char*);
	void travelTo(char*);
	void take();
	void displayHelpList();
	void displayInventory();
	void saveGame();

	void gameAccuse(char*);
	void solve(char*);
	void unlock(char*);// just to test chest, will be removed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	std::vector<Interactable*> getInteractables();
	std::vector<Room> getRoomsVector();
	void setCurrentRoom(Room*);

	Interactable* getInteractableByName(std::string);
	
};

#endif