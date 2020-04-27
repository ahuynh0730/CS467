#include "Interactable.hpp"

Interactable::Interactable(): name{"default"}, description{"default"} {}

void Interactable::setName(std::string name_){
	name = name_;
}

void Interactable::setDesc(std::string desc){
	description = desc;
}

std::string Interactable::getName(){
	return name;
}

std::string Interactable::getDesc(){
	return description;
}

std::vector<std::string> Interactable::listUserOptions(){
	return std::vector<std::string>();
}

bool Interactable::callFunction(int n){
	return false;
}
