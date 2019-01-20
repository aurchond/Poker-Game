#ifndef DeckOfCards_hpp
#define DeckOfCards_hpp
#include "Card.hpp"
#include <stdio.h>

class DeckOfCards {
    Card* deck;
    int currentCard;
public:
    DeckOfCards();
    ~DeckOfCards();
    const int static SIZE_OF_DECK = 52;
    void shuffle();
    Card dealCard();
    bool moreCards();
};

#endif /* DeckOfCards_hpp */
