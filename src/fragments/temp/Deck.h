#ifndef DECK_H
#define DECK_H

#include "cardpile.h"
#include <string>
#include <vector>
using namespace std;

class Deck : public CardPile{
private:
    string deckName;

public:
    Deck(string name) : CardPile(name){
        deckName = name;
    }
    string getDeckName(); //Get specified Deck name
    
    void generateStandardDeck(); //Generate a fresh set of Cards
    void clearDeck();           //clears all cards from deck
    //Use clear then generate for start of new round

    void displayDeck();         //Displays all cards of deck
    int displayDeckSize();      //Returns Size of deck
    vector<Card>& getDeckContents(); //Returns all cards within Deck

    void shuffleDeck();            //Shuffling cards
    void addCard(Card card);       //Add specified card to deck
    void removeTopCard();          //Remove top card from deck
    void removeCard(int index);
    

    Card returnTopCard();       //Returns top card of deck
    bool isDeckEmpty();     //0=false 1=true | Returns if deck is empty


};
#endif