#ifndef CARDPILE_H
#define CARDPILE_H

#include "card.h"
#include <string>
#include <vector>
using namespace std;

class CardPile { //Template for Several Piles
protected:
    vector<Card> pile;  //represents Cards in Pile (Pile can be anything)
    string pileName;    //Name for pile (There can be multiple piles in the same group)

public:
    CardPile(string name) {
        pileName = name;
    }
    string getPileName();
    void clearPile();       //Clears pile

    void displayPile();         //Displays the pile
    int displayPileSize();      //Displays the size of pile
    vector<Card>& getPileContents(); //Returns all cards within a class (deck, player, discardpile...)

    void addCardToPile(Card card);    //Adds specified card to pile
    void removeCardFromPile(int index); //Removes specified card (using index)
    void shufflePile();                 //shuffles the pile "Randomly"
    static void transferCard(CardPile& source, CardPile& destination, int index); //Meant to allow generic transfer of cards among the GUI, forgot about that earlier in the text prototypes...
    Card returnCard(int index); //returns card specified at given index


    bool isPileEmpty();     //Checks if pile is empty
    

};
#endif