#ifndef Winner_hpp
#define Winner_hpp
#include "Card.hpp"
#include <stdio.h>

class Winner {
private:
    static const int handSize = 5;
    Card *p1Card;
    Card *p2Card;
    int face1[5];//the face values of player 1's cards
    int face2[5];//the face values of player 1's cards
    
    bool isFlush(Card pCard[]);//checks if the suits of all cards are the same
    
    //Now, checking the different poker hands
    bool checkPair(int a[]);
    bool checkTwoPair(int a[]);
    bool checkThreeOfAKind(int a[]);
    bool checkStraight(int a[]);
    bool checkFlush(Card pCard[]);
    bool checkFullHouse(int a[]);
    bool checkFourOfAKind(int a[]);
    bool checkStraightFlush(Card pCard[], int a[]);
    bool checkRoyalFlush(Card pCard[], int a[]);
    
    int sameRankingCheck(int val[]);
    int sameRankingFullHouse (int val[]);
    int compareSideCards (int cardMatch);
    int findHandRank(Card pCard[], int a[]);
    int findWinner(int ranking1, int ranking2);
    void sortFaces();
public:
    Winner(Card pCard1[], Card pCard2[]);
    ~Winner();
    int overallWinner();
};

#endif /* Winner_hpp */
