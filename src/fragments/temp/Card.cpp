#include "card.h"
#include <string>
using namespace std;

Card::Card(string x, int y) { //setup
    cardName = x;
    cardValue = y;
    numValue = (y / 4) + 2; //cards start at 2
    suitValue = (y % 4); //numbers 1-4 represented as suits. (1-Spades, 2-Clubs, 3-Diamonds, 4-Hearts) 
        // Game Ruleset determines highest card suit
}
    
string Card::getcardName() const{ //cardName value
    return cardName;
}

int Card::getcardValue() const{ //cardValue value
    return cardValue;
}

int Card::getnumValue() const{ //numberValue
    return numValue;
}

int Card::getsuitValue() const{
    return suitValue;
}

bool Card::isValid() const {
    if (cardValue == -1) {
        return false; //invalid if cardvalue = -1
    }
    else {
        return true; //valid if anything else | Ensure to program your card values correctly
    }
}