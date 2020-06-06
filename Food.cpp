#include "Food.hpp"

Food::Food() {
	type = 7;
}

Food::Food(std::string nameIn, std::string descriptionIn) : Interactable(nameIn, descriptionIn){
	type = 7;
}
