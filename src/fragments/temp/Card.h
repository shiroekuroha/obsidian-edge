#ifndef CARD_H
#define CARD_H

#include "node2d.h"
#include <string>
using namespace std;

class Card{
private:
//given value of card say 26 represents floor(26/4) = 6. 
//26 % 4 = 2
// Use the floor division as a the card value, the modulo as the suit.
    std::string cardName; //Name of card
    int cardValue = 0;    //Raw value number
    int numValue = 0;     //Number on card after calculation 2-15 (face cards, aces & possible jokers as number values > 10)
    int suitValue = 0;    //Suit of card after calculation

public:
    Card(string x, int y);

    string getcardName() const; //Returns name of card Ex:8◆
    int getcardValue() const;   //Returns value of card Ex:26
    int getnumValue() const;    //Returns number of card Ex:8
    int getsuitValue() const;   //Returns suit of card (1-Spades, 2-Clubs, 3-Diamonds, 4-Hearts)

    bool isValid() const; //Detects if a card has -1, which indicates that it shouldn't be added to any vector.
};
#endif