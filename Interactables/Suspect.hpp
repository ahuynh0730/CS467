#ifndef SUSPECT_hpp
#define SUSPECT_hpp

#include "Interactable.hpp"

class Suspect: public Interactable{
private:
	bool isMurderer;
	int userOptions;
public:
	Suspect();
	Suspect(bool m, std::string name_, std::string desc, Room* r, Game* g);
	std::vector<std::string> listUserOptions();
	std::string callFunction(int n);
	std::string accuse();
};

#endif
