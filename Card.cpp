#include <ctime>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "Card.h"
#include "Player.h"

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
//Destructor of Card
Card::~Card()
{

}
//Assignment operator overload of Card
Card& Card:: operator = (const Card& c)
{
    this->type = c.type;
    return *this;
}
/*
    Returns a pointer to an order with the card as a member,
    as well as deleting the card from the passed hand and placing
    it in the passed deck.
*/
Order* Card::play(Deck* d, Hand* h, Territory* territoryToAttack, Territory* territoryToDefend, int randIndexSource, int nOfArmies, Player* player, Player* enemyPlayer){

    vector<Territory*>* playerTerritories = player->getPointerToTerritories();
    Order* o=NULL;
    if (type.compare("bomb") == 0)
    {
        o = new Bomb(territoryToAttack, playerTerritories);
        //Set the attack status to false on the territory where an attack order has been created
        //territoryToAttack->setAttackStatus(false);
    }
    else if (type.compare("reinforcement") == 0)
    {
       player->addToPool(5);
       cout<<"added 5 armies to player's reinforcement pool\n";
    }
    else if (type.compare("blockade") == 0)
    {
        //Create a neutral player
        Player* neutralPlayer = new Player("neutral");
        o = new Blockade(territoryToDefend, playerTerritories, neutralPlayer);

    }
    else if (type.compare("airlift") == 0)
    {
        if(nOfArmies != 0)
        {
            o = new Airlift(territoryToDefend, playerTerritories, nOfArmies, playerTerritories->at(randIndexSource));
        }
        else
        {
            o = NULL;
            cout << "Cannot create airlift order - No armies in source territory " << playerTerritories->at(randIndexSource)->getName() << "\n" << endl;
        }
    }
    else if (type.compare("diplomacy") == 0)
    {
        o = new Negotiate(player, enemyPlayer);
    }
    else
    {
        o = NULL;
        cout << "Cannot create order" << endl;
    }
    d->getCards()->push_back(this);
    h->getCards()->erase(h->getCards()->begin());
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
    out << "- Card with type " << c.type << endl;
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
    //This deletes all the Card objects stored in the vector
    for(vector<Card*>::iterator it = cards.begin(); it != cards.end(); ++it)
    {
        delete *it;
    }
    //This erases all the pointers stored in the vector
    cards.clear();
}
//Assignment operator overload
Deck& Deck::operator = (const Deck &d)
{
    int i;
    for (i=0;i<d.cards.size();i++)
    {
        this->cards.push_back(d.cards.at(i));
    }
    return *this;
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
    //This deletes all the Card objects stored in the vector
    for(vector<Card*>::iterator it = cards.begin(); it != cards.end(); ++it)
    {
        delete *it;
    }
    //This erases all the pointers stored in the vector
    cards.clear();
}
//Assignment operator overload
Hand& Hand::operator = (const Hand& h)
{
    int i;
    for(i=0;i<h.cards.size();i++)
    {
        this->cards.push_back(h.cards.at(i));
    }
    return *this;
}
//getters and setters
vector<Card*>* Hand::getCards(){
    return &cards;
}
void Hand::setCards(vector<Card*> &c){
    cards = c;
}
void Hand::addCard(Card* card)
{
    cards.push_back(card);
}
ostream & operator << (ostream &out, const Hand &h){
    out << "Hand: \n";
    for(vector<Card*>::const_iterator it = h.cards.begin(); it != h.cards.end();++it){
        out << *(*it);
    }
    return out;
}
