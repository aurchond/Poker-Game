#include "Card.hpp"

Card::Card() {
    face=0;
    suit=0;
}

Card::Card(int face, int suit) {
    this->face = face;
    this->suit = suit;
}

int Card::getFace() {
    return face;
}

int Card::getSuit() {
    return suit;
}

void Card::setFace(int i){
    face = i;
}

void Card::setSuit(int i){
    suit = i;
}

string Card::toString() {
    string str = faceNames[face];
    string str2 = suitNames[suit];
    return str + " of " + str2 + "  ";
}


 const string Card::faceNames[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
 const string Card::suitNames[] = { "♣", "♦", "♥", "♠" };

