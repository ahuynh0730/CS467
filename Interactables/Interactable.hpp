#ifndef INTERACTABLE_hpp
#define INTERACTABLE_hpp

#include <string>
#include <vector>
#include "../Room.hpp"
#include "../Game.hpp"

class Interactable{
protected:
	std::string name;
	std::string description;
	Room* room; //points to the room this interactable is in. if null, interactable is held by player
	bool holdable;
	Game* game;
public:
	Interactable();
	Interactable(std::string name_, std::string desc, Room* r, Game* g, bool h);
	void setName(std::string name_);
	void setDesc(std::string desc);
	void setRoom(Room* r);
	void setHoldable(Game* g);
	void setGame(bool h);
	std::string getName();
	std::string getDesc();
	Room* getRoom();
	bool getHoldable();
	Game* getGame();
	virtual std::vector<std::string> listUserOptions() = 0; //send list of things the user can do. the index of the action is what is used in calling callFunction
	virtual std::string callFunction(int n) = 0; //calls the function that the user chose. Used to call functions only derived classes have
};

#endif
