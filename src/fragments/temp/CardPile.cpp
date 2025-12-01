#include "cardpile.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

string CardPile::getPileName() {
    return pileName;
}

void CardPile::clearPile() {
    pile.clear();
}

//----------------------------------------------------
void CardPile::displayPile() {
    if (pile.empty()) {
        cout << "Currently Empty.";
    }
    else {
        for (Card card: pile) {
            cout << "(" << card.getcardName() << ") ";
        }
    }
    cout << "\n--------------------\n";
}

int CardPile::displayPileSize() { 
    cout << pile.size();
    cout << "\n--------------------\n";
    return pile.size();
}

vector<Card>& CardPile::getPileContents() {
    return pile;
}

//----------------------------------------------------
void CardPile::addCardToPile(Card card) {
    if (card.isValid()) {
        pile.push_back(card); //Add to back of pile
    }
    else{
        cout << "The card (" << card.getcardName() << ", " << card.getcardValue() << ") is not valid. Can't Add.\n";
    }
}

void CardPile::removeCardFromPile(int index) {
    if (pile.empty()) {
        cout << "Can't Remove Already Empty.";
    }
    else {
        if (index >= 0 && index < pile.size()) { //TODO TEST FOR COUT ACCURACY
            cout << "Removing Card at index (" << index << ":" << pile.front().getcardName() << ", " << pile.front().getcardValue() << ")";
            pile.erase(pile.begin() + index);
        }
    }
    cout << "\n--------------------\n";
}

void CardPile::shufflePile() {
    random_device rd;
    mt19937 rng(rd()); //the rng used for the shuffle
    shuffle(pile.begin(), pile.end(), rng);
}

void CardPile::transferCard(CardPile& source, CardPile& destination, int index) {
    vector<Card>& sourcePile = source.getPileContents(); //just for the if statement, wait is this needed?
    if (index >= 0 && index < sourcePile.size()) {
        Card cardToTransfer = sourcePile[index];
        source.removeCardFromPile(index);
        destination.addCardToPile(cardToTransfer);

        cout << "Card: " << cardToTransfer.getcardName() << " has been transferred from source to destination.";
    }
    else {
        cout << "Invalid index detected.";
    }
    cout << "\n--------------------\n";
}

Card CardPile::returnCard(int index) {
    if (index >= 0 && index < pile.size()) {
        return pile[index];
    }
    else{
        cout << "Invalid index." << endl;
        return Card("", -1);
    }
}
//----------------------------------------------------
bool CardPile::isPileEmpty() {
    return false;
}
