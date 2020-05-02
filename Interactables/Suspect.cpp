#include "Suspect.hpp"

Suspect::Suspect(): Interactable{}, isMurderer{false}{}

Suspect::Suspect(bool m, std::string name_, std::string desc, Room* r, Game* g):
	Interactable{std::string name_, std::string desc, Room* r, Game* g, false}, isMurderer{m}{}

bool Suspect::getIsMurderer(){
	return isMurderer;
}

void Suspect::setIsMurderer(bool m){
	isMurderer = m;
}

std::string Suspect::accuse(){
	game->setGameOver(true);
	if(isMurderer){
		return "You chose correctly."
	}
	else{
		return "You chose incorrectly."
	}
}

std::vector<std::string> Suspect::listUserOptions(){
	return std::vector<std::string>{"Accuse"};
}

std::string Suspect::callFunction(int n){
	return accuse();
}
