#include "Suspect.hpp"

Suspect::Suspect() {
	isMurderer = false;
}

Suspect::Suspect(std::string nameIn, std::string descriptionIn) : Interactable(nameIn, descriptionIn) {
	isMurderer = false;
}
/*
Suspect::Suspect(bool m, std::string name_, std::string desc, Room* r, Game* g):
	Interactable{name_, desc, r, g, false}, isMurderer{m}{}

std::string Suspect::getDesc(){
	//will send a concatenation of the suspects details
	return "";
}

bool Suspect::getIsMurderer(){
	return isMurderer;
}

void Suspect::setIsMurderer(bool m){
	isMurderer = m;
}

std::string Suspect::accuse(){
	game->setGameOverStatus(true);
	if(isMurderer){
		return "You chose correctly.";
	}
	else{
		return "You chose incorrectly.";
	}
}

std::vector<std::string> Suspect::listUserOptions(){
	return std::vector<std::string>{"Describe", "Accuse"};
}

std::string Suspect::callFunction(int n){
	switch(n){
		case 0:
			return longDesc;
			break;
		case 1:
			return accuse();
			break;
		default:
			return "You cannot do that.";
	}
	
}
*/
