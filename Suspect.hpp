#ifndef SUSPECT_hpp
#define SUSPECT_hpp

#include "Interactable.hpp"

class Suspect: public Interactable{
private:
	bool isMurderer;
	char* answer;
	//will add all the suspect details here
public:
	Suspect();
	Suspect(std::string, std::string, bool, std::string);
	~Suspect();
	
	void question();
	bool accuse();
	void frisk();

	
};

#endif
