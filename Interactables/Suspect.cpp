#include "Suspect.hpp"

Suspect::Suspect(): Interactable{}, isMurderer{false}{}

bool Suspect::getIsMurderer(){
	return isMurderer;
}

std::vector<std::string> Suspect::listUserOptions(){
	return std::vector<std::string>();
}

bool Suspect::callFunction(int n){
	if(n < 0 || n > userOptions)
		return false;
	switch(n){
		case 0:

			break;
		case 1:

			break;
	}
}
