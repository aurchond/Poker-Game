#include "DeckOfCards.hpp"
#include <stdlib.h>
#include <ctime>


DeckOfCards::DeckOfCards() {
    deck = new Card[SIZE_OF_DECK];
    int k=0;//only used to increase the deck value independently
    for (int i=0;i<Card::totalFaces;i++) {
        for (int j=0; j<Card::totalSuits; j++) {
            deck[k]=Card(i,j);
            k++;
        }
    }
    currentCard = 0;
}

void DeckOfCards::shuffle() {
    srand(time(0));
    for (int i = 0; i < 500; i++) {
        int firstValue = rand() % 51;
        int secondValue = rand() % 51;
       
        Card tempVariable = deck[firstValue];
        deck[firstValue].setFace(deck[secondValue].getFace());
        deck[firstValue].setSuit(deck[secondValue].getSuit());
        deck[secondValue].setFace(tempVariable.getFace());
        deck[secondValue].setSuit(tempVariable.getSuit());
        deck[secondValue] = tempVariable;
    }
    
}


Card DeckOfCards::dealCard () {
    return deck[currentCard++];
}

bool DeckOfCards::moreCards () {
    if (currentCard==SIZE_OF_DECK) {
        return false;
    }
    else {
        return true;
    }
}

DeckOfCards::~DeckOfCards() {
    delete deck;
}
