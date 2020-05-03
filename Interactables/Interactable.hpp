#ifndef INTERACTABLE_hpp
#define INTERACTABLE_hpp

#include <string>
#include <vector>
#include "../Room.hpp"
#include "../Game.hpp"

class Interactable{
protected:
	std::string name;
	std::string shortDesc;
	std::string longDesc;
	Room* room; //points to the room this interactable is in. if null, interactable is held by player
	Room* originalRoom;
	bool holdable;
	Game* game;
public:
	Interactable();
	Interactable(std::string name_, std::string desc, Room* r, Game* g, bool h);
	void setName(std::string name_);
	void setShortDesc(std::string desc);
	void setLongDesc(std::string desc);
	void setRoom(Room* r);
	void setOriginalRoom(Room* r);
	void setHoldable(Game* g);
	void setGame(bool h);
	std::string getName();
	std::string getShortDesc();
	virtual std::string getLongDesc();
	Room* getRoom();
	Room* getOriginalRoom();
	bool getHoldable();
	Game* getGame();
	virtual std::vector<std::string> listUserOptions(); //send list of things the user can do. the index of the action is what is used in calling callFunction
	virtual std::string callFunction(int n); //calls the function that the user chose
};

#endif
