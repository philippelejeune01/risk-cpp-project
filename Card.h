#ifndef Card_H
#define Card_H
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//prototypes
class Deck;
class Card;
class Hand;
//dummy Order, OrderList
class Order{
    private:
        string type;
    public:
        Order(Card &c);
};
class OrderList{
    public:
        vector<Order*> orderList;
        OrderList(vector<Order*> &v);
};

class Card
{
    private:
        string type;
    public:
        Card();
        Card(string s);
        Card(Card &c);
        Order* play(Deck &d, Hand &h);
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
        Hand(vector<Card*> &cards);
        Hand(Hand &h);
        ~Hand();

        vector<Card*>* getCards();
        void setCards(vector<Card*> &cards);
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
        
        Card* draw();
        vector<Card*>* getCards();
        void setCards(vector<Card*> &cards);
        
        friend ostream & operator << (ostream &out, const Deck &d);
        
};





#endif