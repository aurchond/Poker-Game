#include "Winner.hpp"
#include <algorithm>

Winner::Winner(Card p1Card[], Card p2Card[]) {
    this->p1Card = p1Card;
    this->p2Card = p2Card;
    for (int i=0;i<5;i++) {
        face1[i]=p1Card[i].getFace();
        face2[i]=p2Card[i].getFace();
    }
    sortFaces();
}

Winner::~Winner() {
    
}

void Winner::sortFaces() {
    sort(face1,face1+5);
    sort(face2,face2+5);
}
bool Winner::isFlush(Card pCard[]) {
    bool works = true;
    int suitType=pCard[0].getSuit();
    for (int i=1; i<handSize; i++) {
        if (pCard[i].getSuit()!=suitType) {
            works= false;
        }
    }
    return works;
}

//Method to check if either player has a pair
bool Winner::checkPair(int a[]) {
    bool works = false;//Assumes there is no pair until proven otherwise
    for (int i = 0; i < handSize - 1; i++) {
        if (a[i] == a[i + 1]) {
            works = true;//Finds a pair
        }
    }
    return works;
}

//Method to check if either player has two pairs
bool Winner::checkTwoPair(int a[]) {
    int pair = 0;
    bool works = false;//Assumes there are not two pairs until proven otherwise
    for (int i = 0; i < handSize - 1; i++) {
        if (a[i] == a[i + 1]) {
            pair++;
            if (pair==2) {//Only goes into this loop if there is another pair already existing
                works = true;//Finds the second pair
            }
        }
    }
    return works;
}

//Method to check if either player has a three of a kind
bool Winner::checkThreeOfAKind(int a[]) {
    bool works = false;// Assumes there are no three-of-a-kinds until proven otherwise
    for (int i = 0; i < handSize - 2; i++) {
        if (a[i] == a[i + 1] && a[i] == a[i + 2]) {// Works if a card is equal to both the next card and the one after that
            works = true;
        }
    }
    return works;
}

//Method to check if either player has a straight
bool Winner::checkStraight(int a[]) {
    bool works = true;//Assumes that the cards are a straight at the beginning until proven otherwise
    for (int i = 0; i < handSize - 1; i++) {
        if (a[i] != a[i + 1] - 1) {
            works = false;//This means that the cards are not in the form of a straight
        }
    }
    return works;
}

//Method to check if either player has a flush
bool Winner::checkFlush(Card pCard[]) {
    if (isFlush(pCard)) {
        return true;
    }
    else {
        return false;
    }
}

//Method to check if either player has a full house
bool Winner::checkFullHouse(int a[]) {
    bool works = false;//Assumed to be initially not be true until proven otherwise
    
    if (a[0] == a[1]) {
        if ((a[2] == a[3] && a[2] == a[4])) {
            works = true;
        }
    }
    if (a[3] == a[4]) {
        if ((a[0] == a[1] && a[0] == a[2])) {
            works = true;
        }
    }
    
    return works;
}

//Method to check if either player has a four of a kind
bool Winner::checkFourOfAKind(int a[]) {
    bool works = true;//Assumed to be a full house until proven otherwise
    
    for (int i = 1; i < handSize; i++) {
        if (a[0] == a[1]) {
            if (a[i - 1] != a[0]) {
                works = false;
            }
        }
        
        else if (a[1] == a[2]) {
            if (a[i] != a[1]) {
                works = false;
            }
        }
        
        else {
            return false;
        }
    }
    return works;
}

//Method to check if there is a straight flush present in either player's hands
bool Winner::checkStraightFlush(Card pCard[], int a[]) {
    bool works1 = true;
    bool works2 = true;
    
    if (isFlush(pCard)) {
        works1 = true;
    }
    
    for (int i = 0; i < handSize - 1; i++) {
        if (a[i] != a[i + 1] - 1) {
            works2 = false;//This means that the cards are not in the form of a straight
        }
    }
    
    if (works1 && works2) {
        return true;
    }
    
    else {
        return false;
    }
}

//Method to check if there is a royal flush present in either player's hands
bool Winner::checkRoyalFlush(Card pCard[], int a[]) {
    bool works1 = false;
    bool works2 = false;
    
    if (isFlush(pCard)) {
        works1 = true;
    }
    
    if (a[0] == 8 && a[1] == 9 && a[2] == 10 && a[3] == 11 && a[4] == 12) {
        works2 = true;//This means that the cards are in the correct order for a royal flush
    }
    
    if (works1==true && works2==true) {
        return true;
    }
    
    else {
        return false;
    }
}

int Winner::findHandRank (Card pCard[], int a[]) {
    
    int ranking = 0;
    
    if (checkRoyalFlush(pCard, a)) {
        ranking = 9;
    }
    
    else if (checkStraightFlush(pCard, a)) {
        ranking = 8;
    }
    
    else if (checkFourOfAKind(a)) {
        ranking = 7;
    }
    
    else if (checkFullHouse(a)) {
        ranking = 6;
    }
    
    else if (checkFlush(pCard)) {
        ranking = 5;
    }
    
    else if (checkStraight(a)) {
        ranking = 4;
    }
    
    else if (checkThreeOfAKind(a)) {
        ranking = 3;
    }
    
    else if (checkTwoPair(a)) {
        ranking = 2;
    }
    
    else if (checkPair(a)) {
        ranking = 1;
    }
    return ranking;
}

int Winner::sameRankingCheck (int val[]) {//Initial checker to see which match in the card ranking is higher
    int cardMatch = 0;
    for (int i = 0; i < handSize - 1; i++) {
        if (val[i] == val[i + 1]) {
            cardMatch = val[i];//Only finds one match value, (in 2 pair, the second, larger value, overrides the first value)
        }
    }
    return cardMatch;
}

int Winner::sameRankingFullHouse (int val[]) {//Checks for full house (ranking 6), which is different than rankings 7 and 3 because two pairs are
    //in a full house hand, but just like 3 and 7, only one check occurs because 2 sets of 3 cards can't equal each other
    int cardMatch = 0;
    for (int i = 0; i < handSize - 2; i++) {
        if (val[i] == val[i + 1] && val[i] == val[i + 2]) {
            cardMatch = val[i];
        }
    }
    return cardMatch;
}

int Winner::compareSideCards (int cardMatch) {//Method if both rankings are a tie, and the cardMatch is a tie too
    int winner = 0;
    int sideCards1[3];//Three is the max size of the array because 5 minus 2 (the size of one pair, not in the side cards) is 3
    int sideCards2[3];
    for (int i = 0; i < 3; i++) {//Initializing this array
        sideCards1[i] = 0;
        sideCards2[i] = 0;
    }
    int j=0, k=0;
    for (int i = 0; i < handSize ; i++) {
        if (face1[i] != cardMatch && j<3) {
            sideCards1[j] = face1[i];
            j++;
        }
    }
    
    
    for (int i = 0; i < handSize ; i++) {
        if (face2[i] != cardMatch && k<3) {
            sideCards2[k] = face2[i];
            k++;
        }
    }
    
    for (int i = sizeof(sideCards1)/sizeof(sideCards1[0]) - 1; i >= 0; i--) {
        if (sideCards1[i]>sideCards2[i]) {
            winner = 1;
            break;
        }
        else if (sideCards1[i]<sideCards2[i]) {
            winner = 2;
            break;
        }
    }
    return winner;
}

//Method to find the winner of the game
int Winner::findWinner (int ranking1, int ranking2) {
    int winner = 0;//Variable to find if there is a winner (1, 2) or a tie (0)
    int cardMatch = 0;//This is a variable that is only used if the ranking, and card match are both equal for both hands (eg both have two 3 of spades)
    if (ranking1 > ranking2) {
        winner = 1;//The winner is player 1
    }
    
    else if (ranking1 < ranking2) {
        winner = 2;//The winner is player 2
    }
    
    else if (ranking1 == ranking2) {//Goes deeper in if both players have the same ranking (eg. both have pair)
        if (ranking1 == 9 || ranking1 == 8 || ranking1 == 5 || ranking1 == 4 || ranking1 == 0) {// Only happens for combinations that do not use
            //card matches (eg. pair, three of a kind)of cards
            for (int i=handSize-1; i>=0; i--) {
                
                if (face1[i]>face2[i]) {
                    winner = 1;
                    break;
                }
                else if (face1[i]<face2[i]) {
                    winner = 2;
                    break;
                }
            }
        }
        
        else {//All the other cards have combinations and them as thus must be treated differently
            if (ranking1 == 7 || ranking1 == 3) {//They have their own separate category because the card matches will never equal each other (8 of one card doesn't exist)
                if (sameRankingCheck(face1)>sameRankingCheck(face2)){
                    winner = 1;
                }
                if (sameRankingCheck(face1)<sameRankingCheck(face2)){
                    winner = 2;
                }
            }
            
            else if (ranking1 == 6) {//Has its own loop because only the three of a kinds in both hands are weighed against each other
                if (sameRankingFullHouse(face1)>sameRankingFullHouse(face2)){
                    winner = 1;
                }
                if (sameRankingFullHouse(face1)<sameRankingFullHouse(face2)){
                    winner = 2;
                }
            }
            
            else if (ranking1 == 2 || ranking1 == 1) {//Occurs for the combinations can have equal card matches, so the side cards need to be ranked against each other
                cardMatch = sameRankingCheck(face1);//A variable that can be used later if needed, it is given the value here of the first card match because
                //it is used when the card matches are equal and the side cards have to be used to determine the winner
                if (sameRankingCheck(face1)>sameRankingCheck(face2)){
                    winner = 1;
                }
                else if (sameRankingCheck(face1)<sameRankingCheck(face2)){
                    winner = 2;
                }
                
                else {
                    winner = compareSideCards(cardMatch);
                }
            }
        }
    }
    return winner;
}

int Winner::overallWinner () {
    int winningPlayer = findWinner (findHandRank(p1Card, face1), (findHandRank(p2Card, face2)));
    return winningPlayer;
}

