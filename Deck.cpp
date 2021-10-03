#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "Deck.h"

using namespace std;

string types[] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

//Card functions
//initializes a card with a random type
Card::Card(){
    srand (time(NULL));
    int randomType = rand() % 5;
    type = types[randomType];
}
//initialize with a specific string
Card::Card(string s){
    type = s;
}

void Card::play(){
    /* TO-DO */
}
void Card::setType(string s){
    type = s;
}
string Card::getType(){
    return type;
}
ostream & operator << (ostream &out, const Card &c){
    out << "Card object with type " << c.type << endl;
    return out;
}
istream & operator >> (istream &in, Card &c){
    cout << "Enter the card type: ";
    in >> c.type;
    return in;
}
//Deck functions
Deck::Deck(){
    vector<Card*> v;
    this->cards = v;
}
Deck::Deck(vector<Card*> &cards){
    this->cards = cards;
}
Deck::~Deck(){
    for(int i=0; i < cards.size(); i++){
        cards.at(i) = NULL;
    }
}
void Deck::draw(Hand &hand){
    srand (time(NULL));
    int i = rand() % getCards().size();
    hand.getCards().push_back(cards.at(i));
    
}
vector<Card*> Deck::getCards(){
    return cards;
}
void Deck::setCards(vector<Card*> &cards){
    cards = cards;
}
ostream & operator << (ostream &out, const Deck &d){
    vector<Card*> v = d.cards;
    out << "This is a deck with cards: ";
    for(int i=0; i < v.size(); i++){
        out << *v.at(i) << ' ';
    }
    return out;
}

Hand::Hand(){
    vector<Card*> v;
    cards = v;
}
Hand::Hand(vector<Card*> cards){
    cards = cards;
}
Hand::~Hand(){
    for(int i=0; i < cards.size(); i++){
        cards.at(i) = NULL;
    }
}
vector<Card*> Hand::getCards(){
    return cards;
}
ostream & operator << (ostream &out, const Hand &h){
    vector<Card*> v = h.cards;
    out << "This is a hand with cards: ";
    for(int i=0; i < v.size(); i++){
        out << *v.at(i) << ' ';
    }
    out << endl;
    return out;
}


//driver
int main(){
   
    
}