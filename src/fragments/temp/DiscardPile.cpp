#include "discardpile.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

string DiscardPile::getDiscardPileName() {
    return discardPileName;
}


void DiscardPile::clearDiscardPile() { //Clears all cards from Discard Pile
    clearPile();
}


void DiscardPile::displayDiscardPile() { //displays all card in pile
    displayPile();
}

int DiscardPile::displayDiscardPileSize() { //displays discardpile size
    return displayPileSize();
}

vector<Card>& DiscardPile::getDiscardPileContents() {   //Returns all cards within Discard Pile
    return getPileContents();
}


void DiscardPile::addCard(Card card) {
    addCardToPile(card);
}

void DiscardPile::removeCard(int index) { //not sure if this will be useful but good to have anyway, just in case
    removeCardFromPile(index);
}


bool DiscardPile::isDiscardPileEmpty() { //returns if it is empty or not
    return isPileEmpty();
}


