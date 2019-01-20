//this is the dealer class since I cannot rename the main.cpp class
#include <iostream>
#include <algorithm>
#include "Winner.hpp"
#include "DeckOfCards.hpp"

using namespace std;

int betAmount (char c, int dealerBet) {//method to see how much user would like to bet
    int amount = 0;
    cout << endl;
    if (c=='b') {
        cout << "How much would you like to increase the bet (on top of the dealer's bet)?";
        int bet;
        cin >> bet;
        amount = dealerBet + bet;
        cout << "You have bet a total of " << amount << " dollars." << endl;
    }
    else if (c=='m') {
        cout << "You have chosen to match the dealer's bet of " << dealerBet << " dollars .";
        amount = dealerBet;
    }
    else if (c=='f') {
        cout << "You have given up the game.";
        amount = -1;
    }
    return amount;
}

int main() {
    Card p1Card[5];
    Card p2Card[5];
    
    DeckOfCards p1;
    p1.shuffle();
    int i=0, j=0, k=0;//incrementation values
    while(p1.moreCards() && (i<5 || j<5 ) ) {
        Card c = p1.dealCard();
        if (k%2==0) {//modulus so that it is truly like a poker game, in the sense that the cards are distributed one at a time
            p1Card[i] = c;
            i++;
        }
        else {
            p2Card[j] = c;
            j++;
        }
        ++k;
    }
    
    
    cout << "Welcome to Aurchon's Casino! Here, you have the best chances to win BIG in our legendary poker game! ";
    cout << "As you probably know already the prize pool has a default $50 that you can EASILY win. Now, enough of the babbling, GOOD LUCK!" << endl << endl;
    
    cout << "Here are your cards: " << endl;
    for (int i=0; i<5; i++) {
        cout << p1Card[i].toString() << " ";
    }
    
  
    int dealerBet = rand()%500 + 1;//dealer bets a random amount to throw off the player :)
    cout << endl << "The dealer sees their cards as well... They bet "  << dealerBet << " dollars on their cards. " << endl;
    
    
    cout << endl << "Hmmm... You gotta carefully think of your chances of winning. You can enter 'b' to bet more money on top of what the dealer has bet, 'm' to match the dealer's bet or 'f' to fold your cards (give up without betting): ";
    char choice;
    cin >> choice;
    int bet = betAmount (choice, dealerBet);
    
    
    cout << endl << "The dealer had the following cards: " << endl;
    for (int i=0; i<5; i++) {
        cout << p2Card[i].toString() << " ";
    }
    cout << endl;
    Winner winner = Winner(p1Card, p2Card);
    int overallWinner = winner.overallWinner();
    
    int prizeMoney = 50 + bet + dealerBet;
    
    if (bet>=0) {
        if (overallWinner==1) {
            cout << "You won the game and the total prize money of " << prizeMoney << " dollars! :) ";
        }
        else {
            cout << "Unfortunately, you lost the game and did not get the " << prizeMoney << " dollars. :( ";
        }
    }
    
    else {
        if (overallWinner==1) {
            cout << "You would've won the game and the total prize money of " << prizeMoney << " dollars, too bad you folded :( ";
        }
        else {
            cout << "It was a good idea that you folded, since you would've lost the game!";
        }
    }
    
    return 0;
}
