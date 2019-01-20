#ifndef Card_hpp
#define Card_hpp

#include <iostream>
#include <string>

using namespace std;

class Card {
private:
    int face;
    int suit;
public:
    static const int totalFaces = 13;
    static const int totalSuits = 4;
    static string const faceNames[totalFaces];
    static string const suitNames[totalSuits];
    Card();
    Card(int face, int suit);
    int getFace();
    int getSuit();
    void setFace(int i);
    void setSuit(int i);
    
    string toString();
    
};

#endif /* Card_hpp */
