#ifndef CHEST_hpp
#define CHEST_hpp

#include "Interactable.hpp"

class Chest: public Interactable{
private:
	std::string successString;
	std::string failString;
	std::vector<int> combination;
	std::set<Interactable*> neededItems;
	bool isOpen;
	std::set<Interactable*> itemsInside;
public:
	Chest();
	Chest(std::string name_, std::string desc, Room* r, Game* g, bool h);
	void setSuccessString(std::string s);
	void setFailString(std::string s);
	void setIsOpen(bool c);
	std::string getSuccessString();
	std::string getFailString();
	bool getIsOpen();
	bool addNeededItem(Interactable* i);
	bool removeNeededItem(Interactable* i);
	std::set<Interactable*> getNeededItems();
	void setCombination(std::vector<int> arr);
	std::vector<int> getCombination();
	bool addItemInside(Interactable* i);
	bool removeItemInside(Interactable* i);
	std::vector<std::string> listItemsInside();
	std::vector<std::string> listUserOptions();
	std::string callFunction(int n);
	std::string tryOpen();
	std::string takeItem();
	std::string leaveItem();
};

#endif
