#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include "cardpile.h"
#include <string>
#include <vector>
using namespace std;

class DiscardPile : public CardPile {
private:
    string discardPileName;

public:
    DiscardPile(string name) : CardPile(name){
        discardPileName = name;
    } //Have to make it modular for games that have player unique discard piles or multiple discard piles
    string getDiscardPileName();    //Returns name of DiscardPile

    void clearDiscardPile();        //Clears all cards from discard pile

    void displayDiscardPile();      //Displays cards in discardpile
    int displayDiscardPileSize();   //Returns int number of cards in discard pile
    vector<Card>& getDiscardPileContents(); //Returns all cards within Discard Pile

    void addCard(Card card);        //Add specified card to discard pile
    void removeCard(int index);     //Remove specified card from discard pile
    

    bool isDiscardPileEmpty(); //0=false 1=true

    
};
#endif