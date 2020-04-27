#ifndef SUSPECT_hpp
#define SUSPECT_hpp

#include "Interactable.hpp"

class Suspect: public Interactable{
private:
	bool isMurderer;
	int userOptions;
public:
	Suspect();
	std::vector<std::string> listUserOptions();
	bool callFunction(int n);
	bool getIsMurderer();
};

#endif
