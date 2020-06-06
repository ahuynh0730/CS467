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
#include <stdlib.h>
#include <unistd.h>
#include "common.hpp"
#include "Interactable.hpp"
#include "Chest.hpp"
#include "Food.hpp"
#include "Quiz.hpp"
#include "Room.hpp"
#include "Suspect.hpp"
#include "Block.hpp"



class Game {
private:
	std::vector<Room> rooms;
	std::vector<Room*> roomsVisited;
	std::vector<Interactable*> interactables;
	std::vector<Interactable*> inventory;
	Room* currentRoom;
	bool gameOver = false;

	void replaceEscapeCharacters(std::string&);

public:
	Room * getCurrentRoom();
	bool getGameOverStatus();

	void setGameOverStatus(bool status);
	
	void createRooms();
	void displayGameInfo();
	int displayMainScreen();
	void freeGame();
	void previousScreen();
	void saveScreen();


	
	void lookAt(char*);
	void travelTo(char*);
	void gameTake(char*);
	void displayHelpList();
	void displayMap();
	void displayInventory();

	void question(char*);
	void gameAccuse(char*);
	void solve(char*);
	void unlock(char*);
	void open(char*);
	void drop(char*);
	void fastTravel(char*);
	void addToRoomsVisited(Room*);
	void gameFrisk(char*);
	void gameEat(char*);

	std::vector<Interactable*> getInteractables();
	std::vector<Room> getRoomsVector();
	void setCurrentRoom(Room*);

	Interactable* getInteractableByName(std::string);

	void type(char*);
	
};

#endif