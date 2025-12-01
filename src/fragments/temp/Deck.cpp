#include "deck.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
using namespace std;

string Deck::getDeckName() {
    return pileName;
}


void Deck::generateStandardDeck() { //Generates A fresh set of cards to Deck
    vector<pair<string, int>> standardDeck= { //temp hard coding
        {"2S", 0},
        {"2C", 1},
        {"2D", 2},
        {"2H", 3},
        {"3S", 4},
        {"3C", 5},
        {"3D", 6},
        {"3H", 7},
        {"4S", 8},
        {"4C", 9},
        {"4D", 10},
        {"4H", 11},
        {"5S", 12},
        {"5C", 13},
        {"5D", 14},
        {"5H", 15},
        {"6S", 16},
        {"6C", 17},
        {"6D", 18},
        {"6H", 19},
        {"7S", 20},
        {"7C", 21},
        {"7D", 22},
        {"7H", 23},
        {"8S", 24},
        {"8C", 25},
        {"8D", 26},
        {"8H", 27},
        {"9S", 28},
        {"9C", 29},
        {"9D", 30},
        {"9H", 31},
        {"10S", 32},
        {"10C", 33},
        {"10D", 34},
        {"10H", 35},
        {"JS", 36},
        {"JC", 37},
        {"JD", 38},
        {"JH", 39},
        {"QS", 40},
        {"QC", 41},
        {"QD", 42},
        {"QH", 43},
        {"KS", 44},
        {"KC", 45},
        {"KD", 46},
        {"KH", 47},
        {"AS", 48},
        {"AC", 49},
        {"AD", 50},
        {"AH", 51}
    };

    for (auto hardcode : standardDeck) {
        pile.push_back(Card(hardcode.first, hardcode.second));
        
    }
}

void Deck::clearDeck() { //Clears all cards from deck
    cout << "Clearing the Pile: " << getDeckName();
    clearPile();
}


void Deck::displayDeck() { //Displays all cards in the deck
    cout << "Displaying Deck: ";
    displayPile();
}

int Deck::displayDeckSize() { //Returns int number of cards in deck
    cout << "Current Card count: ";
    return displayPileSize(); 
}

vector<Card>& Deck::getDeckContents() {  //Returns all cards within Discard Pile
    return getPileContents();
}

//shuffles deck by making a new vector, randomizing values. then overwriting what currently exists in the deck
void Deck::shuffleDeck() { 
    shufflePile();
}

void Deck::addCard(Card card) { //Adds specifed card into the deck. Such as using this as part of loop for discard->deck
    addCardToPile(card);
}

//Also know as drawing a card, takes out top card from the deck (such as when dealing cards or removing cards from hand)
void Deck::removeTopCard() {
    cout << "Attempting to Remove Top Card. ";
    if (pile.empty()) {
        cout << "Deck is Empty\n";
    }
    else {
        cout << "Removing Top Card: " << pile.front().getcardName() << ", " << pile.front().getcardValue() << endl;
        pile.erase(pile.begin());
        cout << "Removal Complete\n";
    }
    cout << "--------------------\n";
}

void Deck::removeCard(int index) {
    removeCardFromPile(index);
}
//====================================================================================================================================
//We'll be using these as part of dealing cards to the other "hands": PlayerPile, DecardPile, InGamePile
Card Deck::returnTopCard() { //For getting info of the top card of the deck
    if (pile.empty()) {
        cout << "Can't display card, deck is empty.\n";
        cout << "--------------------\n";
        return Card("", -1); //return invalid card if empty
    }
    else {
        cout << "Current Top Card in Deck: " << pile.front().getcardName() << ", " << pile.front().getcardValue() << "\n";
        cout << "--------------------\n";
        return pile.front();
    }
}

bool Deck::isDeckEmpty() { //Returns if Deck is empty
    return isPileEmpty();
}