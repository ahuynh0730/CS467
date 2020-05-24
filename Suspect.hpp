#ifndef SUSPECT_hpp
#define SUSPECT_hpp

#include "Interactable.hpp"

class Suspect: public Interactable{
private:
	bool isMurderer;
	//will add all the suspect details here
public:
	Suspect();
	Suspect(std::string, std::string);

	virtual bool accuse();

	/*Suspect();
	Suspect(bool m, std::string name_, std::string desc, Room* r, Game* g);
	std::string getDesc();
	bool getIsMurderer();
	void setIsMurderer(bool m);
	std::vector<std::string> listUserOptions();
	std::string callFunction(int n);
	std::string accuse();*/
};

#endif
