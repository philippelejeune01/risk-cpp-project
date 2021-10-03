#ifndef Deck_H
#define Deck_H
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Card
{
    private:
        string type;
    public:
        Card();
        Card(string s);
        
        void play();
        
        void setType(string s);

        string getType();
        friend ostream & operator << (ostream &out, const Card &c);
        friend istream & operator >> (istream &in, Card &c);
};
class Hand
{
    private:
        vector<Card*> cards;
    public:
        Hand();
        Hand(vector<Card*> cards);
        ~Hand();

        vector<Card*> getCards();
        friend ostream & operator << (ostream &out, const Hand &h);
        
};
class Deck
{
    private:
        vector<Card*> cards;
    public:
        Deck();
        Deck(vector<Card*> &cards);
        ~Deck();
        
        void draw(Hand &hand);
        vector<Card*> getCards();
        void setCards(vector<Card*> &cards);
        
        friend ostream & operator << (ostream &out, const Deck &d);
        
};




#endif