#ifndef Card_H
#define Card_H
#include <stdlib.h>
#include <string>
#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

//prototypes
class Deck;
class Card;
class Hand;

class Card
{
    private:
        string type;
    public:
        Card();
        Card(string s);
        Card(Card &c);
        ~Card();
        Order* play(Deck* d, Hand* h, Territory* territoryToAttack, Territory* territoryToDefend, int randIndexSource, int nOfArmies, Player* player, Player* enemyPlayer);
        void setType(string s);
        Card& operator = (const Card& c);
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
        Hand(vector<Card*> &cards);
        Hand(Hand &h);
        ~Hand();
        Hand& operator = (const Hand& h);
        vector<Card*>* getCards();
        void setCards(vector<Card*> &cards);
        void addCard(Card* card);
        friend ostream & operator << (ostream &out, const Hand &h);

};
class Deck
{
    private:
        vector<Card*> cards;
    public:
        Deck();
        Deck(vector<Card*> &cards);
        Deck(Deck &d);
        ~Deck();
        Deck& operator = (const Deck &d);
        Card* draw();
        vector<Card*>* getCards();
        void setCards(vector<Card*> &cards);

        friend ostream & operator << (ostream &out, const Deck &d);

};
#endif
