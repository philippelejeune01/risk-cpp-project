#include <ctime>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

string types[] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

//Card functions
//initializes a card with a random type
Card::Card(){
    int randomType = rand() % 5  ;
    type = types[randomType];
}
//initialize with a specific string
Card::Card(string s){
    type = s;
}
//copy constructor of card
Card::Card(Card &c){
    type = c.type;
}
/*
    Returns a pointer to an order with the card as a member,
    as well as deleting the card from the passed hand and placing
    it in the passed deck.
*/
Order* Card::play(Deck &d, Hand &h){
    Order* o = new Order(*this);
    d.getCards()->push_back(this);
    h.getCards()->erase(h.getCards()->begin());
    return o;
}
//getters and setters
void Card::setType(string s){
    type = s;
}
string Card::getType(){
    return type;
}
//stream operators
ostream & operator << (ostream &out, const Card &c){
    out << "Card object with type " << c.type;
    return out;
}
istream & operator >> (istream &in, Card &c){
    cout << "Enter the card type: ";
    in >> c.type;
    return in;
}
//Deck functions
//creates empty card vector
Deck::Deck(){
    vector<Card*> v;
    this->cards = v;
}
//created deck from existing vector
Deck::Deck(vector<Card*> &c){
    int i;
    for(i=0;i<c.size();i++){
        cards.push_back(c.at(i));
    }
}
//copy constructor
Deck::Deck(Deck &d){
    int i;
    for(i=0;i<d.cards.size();i++){
        cards.push_back(d.cards.at(i));
    }
}
//destructor
Deck::~Deck(){
    for(int i=0; i < cards.size(); i++){
        cards.at(i) = NULL;
    }
}
/*
    Returns a card pointer of a random cards in the deck
    as well as removing said card from it
*/
Card* Deck::draw(){
    srand (time(NULL));
    int i = rand() % getCards()->size();
    Card *drawn = cards.at(i);
    cards.erase(cards.begin()+i);
    return drawn;
}
//getters and setters
vector<Card*>* Deck::getCards(){
    return &cards;
}
void Deck::setCards(vector<Card*> &c){
    cards = c;
}
//stream operators
ostream & operator << (ostream &out, const Deck &d){
    vector<Card*> v = d.cards;
    out << "This is a deck with cards: " << endl;
    for(int i=0; i < v.size(); i++){
        out << *v.at(i) << endl;;
    }
    return out;
}
//Hand functions
//create hand with empty card vector
Hand::Hand(){
    vector<Card*> v;
    cards = v;
}
//create hand with existing vector
Hand::Hand(vector<Card*> &h){
    int i;
    for(i=0;i<h.size();i++){
        cards.push_back(h.at(i));
    }
}
//copy constructor
Hand::Hand(Hand &h){
    int i;
    for(i=0;i<h.cards.size();i++){
        cards.push_back(h.cards.at(i));
    }
}
//destructor
Hand::~Hand(){
    for(int i=0; i < cards.size(); i++){
        cards.at(i) = NULL;
    }
}
//getters and setters
vector<Card*>* Hand::getCards(){
    return &cards;
}
void Hand::setCards(vector<Card*> &c){
    cards = c;
}
ostream & operator << (ostream &out, const Hand &h){
    vector<Card*> v = h.cards;
    out << "This is a hand with cards: " << endl;
    for(int i=0; i < v.size(); i++){
        out << *v.at(i) << endl;
    }
    
    return out;
}
Order::Order(Card &c){
    type=c.getType();
}
OrderList::OrderList(vector<Order*> &v){
    orderList = v;
}