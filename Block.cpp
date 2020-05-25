#include "Block.hpp"

Block::Block() {

}

Block::Block(std::string nameIn, std::string descriptionIn, std::string blockedStringIn) : Interactable(nameIn, descriptionIn) {
    isBlocked = true;
    blockedString = blockedStringIn;
}