#include "Player.h"
#include <time.h>
#include <iostream>
#include <set>
#include <vector>
#include <list>

using namespace std;

//OrdersList Implementation:
//Default Constructor
OrdersList::OrdersList()
{
}
//Constructor with 1 arg: list<Order*>
OrdersList::OrdersList(list<Order*> ls)
{
    ordList = ls;
}
//Copy Constructor
OrdersList::OrdersList(const OrdersList& ls)
{
    //This copies all the values stored in the list
    ordList = ls.ordList;
}
//Destructor
OrdersList::~OrdersList()
{
    for(list<Order*>::iterator it = ordList.begin(); it != ordList.end(); ++it)
    {
        delete *it;
    }
    ordList.clear();
}
//Assignment operator overload
OrdersList& OrdersList :: operator = (const OrdersList& ls)
{
    //This copy all the pointers stored in the list
    this->ordList = ls.ordList;

    return *this;
}
//Stream insertion operator
ostream& operator <<(ostream &strm, const OrdersList &ordLs)
{

    strm << "OrdersList(\n";
    int index = 1;
    for (list<Order*>::const_iterator it = ordLs.ordList.begin(); it != ordLs.ordList.end();++it)
    {
        strm << index++ << ": " << *(*it) << "\n";
    }

    return strm << ")";
}

//Stream insertion operator
ostream& operator <<(ostream &strm, const OrdersList* ordLs)
{
    strm << "\n";
    int index = 1;
    for (list<Order*>::const_iterator it = ordLs->ordList.begin(); it != ordLs->ordList.end();++it)
    {

        strm << index++ << ": " << *(*it) << "\n";
    }

    return strm << endl;
}
//Getter
list<Order*> const &OrdersList:: getOrdList() const
{
    return ordList;
}
//Moves an order in the list
void OrdersList::move(Order* order, int index)
{
    //Error check
    if (index < 0 || index > ordList.size())
    {
        cout << "Error: the index you have given is out of range." << endl;
        return;
    }

    list<Order*>::iterator oldPos = ordList.begin();
    list<Order*>::iterator newPos = ordList.begin();

    //Determines the original position of the Order. If the order is not in the list, then the oldPos points to the endpoint
    for(;oldPos != ordList.end();++oldPos)
    {
        if(*oldPos == order)
        {
            break;
        }
    }

    //Gets the position to insert the Order.
    for(int i = 0; i < index; i++)
    {
        ++newPos;
    }

    //If the element is not in the list, it inserts it at the given index.
    if(oldPos == ordList.end())
    {
        ordList.insert(newPos,order);
    }
    //Otherwise, it moves the order from its old position to its new one.
    else
    {
        ordList.splice(newPos, ordList, oldPos);
    }

}

void OrdersList::remove(int index)
{
    //Error check
    if (index < 0 || index > ordList.size())
    {
        cout << "Error: the index you have given is out of range." << endl;
        return;
    }
    //Cycles through the list to find the position
    list<Order*>::iterator removeAt = ordList.begin();
    for (int i = 0; i < index; i++)
    {
        ++removeAt;
    }
    //Deletes the order object pointed by the pointer
    delete *removeAt;
    //Removes the pointer from the list
    ordList.erase(removeAt);
}
//Private method that determines the location of an order in the list. Returns -1 if the order is not located in the list
int OrdersList::findOrder(Order* ord)
{
    int index = -1;
    //Iterates through the list to find the index of the Order


    return index;
}

//Order Implementation
//Default Constructor
Order::Order()
{
    orderType = "Generic order";
}
//Two arg constructor
Order::Order(Territory* targetTerr, vector<Territory*>* ownedTerr)
{
    targetTerritory = targetTerr;
    ownedTerritories = ownedTerr;
    orderType = "Generic order";
}
//Copy Constructor
Order::Order(const Order& ord)
{
    targetTerritory = ord.getTargetTerritory();
    ownedTerritories = ord.getOwnedTerritories();
    orderType = ord.orderType;
}
//Assignment operator overload.
Order& Order::operator = (const Order& ord)
{
    this->targetTerritory = ord.targetTerritory;
    this->ownedTerritories = ord.ownedTerritories;
    this->orderType = ord.orderType;
    return *this;
}
//Destructor
Order:: ~Order()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    orderType = "";
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Order &ord)
{
    if(ord.getOrderType() == "Negotiate"){
        return strm << "(" << ord.getOrderType() << ") Order";
    }
    return strm << "(" << ord.getOrderType() << ") Targetted Territory: "<<*(ord.targetTerritory);
}

//Getters and Setters
Territory* Order::getTargetTerritory() const
{
    return targetTerritory;
}
vector<Territory*>* Order::getOwnedTerritories() const
{
    return ownedTerritories;
}
void Order:: setTargetTerritory(Territory* newTarTerr)
{
    targetTerritory = newTarTerr;
}
void Order:: setOwnedTerritories(vector<Territory*>* ownedTerr)
{
    ownedTerritories = ownedTerr;
}
//Get Order Type
string Order::getOrderType() const
{
    return orderType;
}

//validate implementation
bool Order:: validate()
{
    //If both pointers don't point to an existing object, then it is not valid
    if (targetTerritory== NULL || ownedTerritories == NULL)
    {
        return false;
    }
    //Otherwise
    return true;

}
//Execute implementation
void Order:: execute()
{
    if(validate())
    {
        cout << "The order can be executed." << endl;
    }
    else
    {
        cout << "The order cannot be executed." << endl;
    }
}
//Deploy implementation
//Default constructor
Deploy::Deploy():Order()
{
    nAddedArmies = 0;
    orderType = "Deploy";
}
//3-arg constructor
Deploy::Deploy(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies)
: Order(targetTerritory,ownedTerr)
{
    nAddedArmies = nOfArmies;
    orderType = "Deploy";
}
//Copy Constructor
Deploy::Deploy(const Deploy& depl): Order(depl.targetTerritory, depl.ownedTerritories)
{
    nAddedArmies = depl.nAddedArmies;
    orderType = depl.orderType;
}
//Assignment operator overload
Deploy& Deploy:: operator = (const Deploy& depl)
{
    Order::operator=(depl);
    this->nAddedArmies = depl.nAddedArmies;
    this->orderType = depl.orderType;
    return *this;
}
//Destructor
Deploy:: ~Deploy()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nAddedArmies = 0;
    orderType = "";
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Deploy &depl)
{
    return strm << "Deploy " << depl.nAddedArmies << " armies on " << *(depl.targetTerritory);
}
//Setter and Getter
string Deploy::getOrderType() const
{
    return orderType;
}
void Deploy::setNAddedArmies(int nAA)
{
    nAddedArmies = nAA;
}
int Deploy::getNAddedArmies()
{
    return nAddedArmies;
}
//Implementation of validate
bool Deploy::validate()
{
    //If the pointers points to an existing object and the number of armies deployed is not equal or less than 0,
    //It returns false
    if(targetTerritory == NULL || ownedTerritories == NULL || nAddedArmies <= 0)
    {
        return false;
    }

    //Cycles through the list of territories a player has to check if the targetted territory is owned by the player
    for(int i = 0; ownedTerritories->size(); i++)
    {
        //Getting the pointer
        Territory* currentTerr = ownedTerritories->at(i);
        if (currentTerr == targetTerritory)
        {
            return true;
        }
    }
    //Otherwise, returns false
    return false;

}
//Implementation of execute
void Deploy::execute()
{
    //If the order is valid, it describes the action
    if (validate())
    {
        cout << "Deploying " << nAddedArmies << " armies on the targetted territory." << endl;
    }
    //Warns the player the order could not be done
    else
    {
        cout << "This order cannot be executed." << endl;
    }
}

//Advance Implementation
//Default Constructor
Advance::Advance():Order()
{
    nMovedArmies = 0;
    sourceTerritory = NULL;
    orderType = "Advance";
}
//4 args constructor
Advance::Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr,
                  int nOfArmies, Territory* sourceTerr): Order(targetTerritory,ownedTerr)
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
    orderType = "Advance";
}
//Copy Constructor
Advance::Advance(const Advance& adv):Order(adv.targetTerritory, adv.ownedTerritories)
{
    nMovedArmies = adv.nMovedArmies;
    sourceTerritory = adv.sourceTerritory;
    orderType = adv.orderType;
}
//Assignment operator overload
Advance& Advance :: operator = (const Advance& adv)
{
    Order::operator=(adv);
    this->nMovedArmies = adv.nMovedArmies;
    this->sourceTerritory = adv.sourceTerritory;
    this->orderType = adv.orderType;
    return *this;
}
//Destructor
Advance::~Advance()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nMovedArmies = 0;
    sourceTerritory = NULL;
    orderType = "";
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Advance &adv)
{
    return strm << "Advance " << adv.nMovedArmies << " armies : From "
    << *(adv.sourceTerritory) << " to " << *(adv.targetTerritory);
}

//setters and getters
string Advance::getOrderType() const
{
    return orderType;
}
void Advance:: setNOfArmies(int nOA)
{
    nMovedArmies = nOA;
}
void Advance::setSourceTerritory(Territory* sourceTerr)
{
    sourceTerritory = sourceTerr;
}
int Advance:: getNOfArmies()
{
    return nMovedArmies;
}
Territory* Advance:: getSourceTerritory()
{
    return sourceTerritory;
}
//Implementation of validate function
bool Advance:: validate()
{
    //Checks if the pointers to an existing object, that the number of
    //of armies is not equal or below 0.
    //If the target territory is not adjacent to the source territory, then it is not valid
    //If the sourceTerritory does not have enough armies, then it is not valid
    if (sourceTerritory == NULL || targetTerritory == NULL || nMovedArmies <= 0 || ownedTerritories == NULL
        || !targetTerritory->isAdjacent(sourceTerritory) || sourceTerritory->getAmountOfArmies() < nMovedArmies)
    {
        return false;
    }

    //Checking if the source territory is owned by the player
    for (int i = 0; ownedTerritories->size(); i++)
    {
        //If the source territory is owned by the player, then it is valid and returns true
        if (sourceTerritory == ownedTerritories->at(i))
        {
            return true;
        }
    }
    //Otherwise, returns false
    return false;
}
//Implementation of execute function
void Advance:: execute()
{
    //Checks if the order is valid
    if(validate())
    {
        //Determines if the targetted territory is an allied or an enemy
        bool* targetIsEnemy = new bool(true);
        for (int i = 0; ownedTerritories->size(); i++)
        {
            //If the target territory is owned by the player, then it is an ally
            if (targetTerritory == ownedTerritories->at(i))
            {
                *targetIsEnemy = false;
            }
        }
        if (targetIsEnemy)
        {
            cout << "Initiating an attack! Advancing " << nMovedArmies << " armies to the targetted enemy territory." << endl;
        }
        else
        {
            cout << "Initiating a reinforcement! Advancing " << nMovedArmies << " armies to the targetted ally territory." << endl;
        }

        delete targetIsEnemy;
        targetIsEnemy = NULL;
    }
    //
    else
    {
        cout << "This order cannot be executed";
    }
}
//Implementation of the subclass Bomb
//Default constructor
Bomb::Bomb():Order()
{
    orderType = "Bomb";
}
//1 arg constructor
Bomb::Bomb(Territory* targetTerritory, vector<Territory*>* ownedTerr): Order(targetTerritory,ownedTerr)
{
    orderType = "Bomb";
}
//Copy constructor
Bomb::Bomb(const Bomb& bomb): Order(bomb.targetTerritory, bomb.ownedTerritories)
{
    orderType = bomb.orderType;
}
//Overload assignment operator
Bomb& Bomb :: operator = (const Bomb& bomb)
{
    Order::operator=(bomb);
    this->orderType = bomb.orderType;
    return *this;
}
//Destructor
Bomb::~Bomb()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    orderType = "";
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Bomb &bomb)
{
    return strm << "Bomb " << *(bomb.targetTerritory);
}
string Bomb::getOrderType() const
{
    return orderType;
}
//Implementation of validate
bool Bomb::validate()
{
    //If the pointers point to an existing object
    if (targetTerritory == NULL || ownedTerritories == NULL)
    {
        return false;
    }
     //Checking if the target territory is owned by the player
    for (int i = 0; ownedTerritories->size(); i++)
    {
        //If the target territory is owned by the player, then the order is not valid.
        if (targetTerritory == ownedTerritories->at(i))
        {
            return false;
        }
    }
    //Checking if the targetted territory is adjacent to any
    for (int i = 0; ownedTerritories->size(); i++)
    {
        if (targetTerritory->isAdjacent(ownedTerritories->at(i)))
        {
            return true;
        }
    }
    //Otherwise
    return false;
}
//Implementation of execute
void Bomb::execute()
{
    //If the order validates, it executes it
    if(validate())
    {
        cout << "Bomb the targetted Territory " << *targetTerritory << endl;
    }
    //Otherwise, it sends an error message
    else
    {
        cout << "This order cannot be executed." << endl;
    }
}

//Implementation of Blockade
//Default Constructor
Blockade::Blockade():Order()
{
    orderType = "Blockade";
}
//2 arg Constructor
Blockade::Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr):Order(targetTerritory, ownedTerr)
{
    orderType = "Blockade";
}
//Copy Constructor
Blockade::Blockade(const Blockade& block):Order(block.targetTerritory,block.ownedTerritories)
{
    orderType = block.orderType;

}
//Overload the assignment operator
Blockade& Blockade::operator = (const Blockade& block)
{
    Order::operator=(block);
    this->orderType = block.orderType;
    return *this;
}
//Destructor
Blockade::~Blockade()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    orderType = "";
}
//Stream insertion operator
ostream& operator <<(ostream &strm, const Blockade &block)
{
    return strm << "Blockade " << *(block.targetTerritory);
}
string Blockade::getOrderType() const
{
    return orderType;
}
//Implementation of validate
bool Blockade:: validate()
{
    //Checks if the pointers point to an existing object
    if (targetTerritory == NULL || ownedTerritories == NULL)
    {
        return false;
    }
    //Checks if the targetted territory is owned by the player
    for (int i = 0; ownedTerritories->size(); i++)
    {
        //If it is, then the order is valid and the function returns true
        if (targetTerritory == ownedTerritories->at(i))
        {
            return true;
        }
    }
    //Otherwise, returns false
    return false;
}
//Implementation of execute
void Blockade:: execute()
{
    //Checks if the order is valid
    if (validate())
    {
        cout << "Blockade the targetted territory " << *(targetTerritory) << ". It has now 3 times the amount of armies and is neutral" << endl;
    }
    //Otherwise, sends an error message
    else
    {
        cout << "This order cannot be executed." << endl;
    }
}

//Implementation of Airlift
//Default Constructor
Airlift::Airlift():Order()
{
    orderType = "Airlift";
}
//4 args constructor
Airlift::Airlift(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr):
    Order(targetTerritory, ownedTerr)
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
    orderType = "Airlift";
}
//Copy Constructor
Airlift::Airlift(const Airlift& airLi):Order(airLi.targetTerritory, airLi.ownedTerritories)
{
    nMovedArmies = airLi.nMovedArmies;
    sourceTerritory = airLi.sourceTerritory;
    orderType = airLi.orderType;
}
//Overload assignment Operator
Airlift& Airlift::operator = (const Airlift& airLi)
{
    Order::operator=(airLi);
    this->nMovedArmies = airLi.nMovedArmies;
    this->sourceTerritory = airLi.sourceTerritory;
    this->orderType = airLi.orderType;
    return *this;
}
//Destructor
Airlift::~Airlift()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nMovedArmies = 0;
    sourceTerritory = NULL;
    orderType = "";
}
//Stream insertion operator
ostream& operator <<(ostream &strm, const Airlift &airL)
{
    return strm << "Airlift: From " << *(airL.sourceTerritory) << " To " << *(airL.targetTerritory);
}

//Getters and Setters
string Airlift::getOrderType() const
{
    return orderType;
}
void Airlift::setNOfArmies(int nOA)
{
    nMovedArmies = nOA;
}
void Airlift::setSourceTerritory(Territory* sourceTerr)
{
    sourceTerritory = sourceTerr;
}
int Airlift::getNOfArmies()
{
    return nMovedArmies;
}
Territory* Airlift::getSourceTerritory()
{
    return sourceTerritory;
}
//Implementation of validate
bool Airlift::validate()
{
    //If the pointers don't point to an existing object
    if(nMovedArmies == 0 || sourceTerritory == NULL || targetTerritory == NULL || ownedTerritories == NULL
       || sourceTerritory->getAmountOfArmies() < nMovedArmies)
    {
        cout << "Wrong values" << endl;
        return false;
    }
    //Checks if the source territory is owned by the player
    for(int i = 0; ownedTerritories->size(); i++)
    {
        //If the source territory is owned, then it is valid and returns true
        if(sourceTerritory == ownedTerritories->at(i))
        {
            return true;
        }
    }
    //Otherwise, it is not valid
    cout << "Not owned by player" << endl;
    return false;
}
//Implementation of execute
void Airlift::execute()
{
    if (validate())
    {
        bool* isEnemy = new bool(true);
        for(int i = 0; ownedTerritories->size(); i++)
        {
            if (targetTerritory == ownedTerritories->at(i))
            {
                *isEnemy = false;
                break;
            }
        }
        if(*isEnemy)
        {
            cout << "Airlift attack with! From " << *(sourceTerritory) << " To " << *(targetTerritory) << endl;
        }
        else
        {
            cout << "Airlift deployment! From " << *(sourceTerritory) << " To " << *(targetTerritory) << endl;
        }
        delete isEnemy;
        isEnemy = NULL;
    }
    else
    {
        cout << "The order cannot be executed" << endl;
    }
}

//Negotiate Implementation
//Default Constructor
Negotiate::Negotiate():Order()
{
    orderType = "Negotiate";
}
//2 args constructor
Negotiate::Negotiate(Player* cPlayer, Player* tPlayer):Order()
{
    callingPlayer = cPlayer;
    targetPlayer = tPlayer;
    orderType = "Negotiate";
}
//Copy Constructor
Negotiate::Negotiate(const Negotiate& negotiate): Order()
{
    callingPlayer = negotiate.callingPlayer;
    targetPlayer = negotiate.targetPlayer;
    orderType = negotiate.orderType;
}
//Assignment Operator overload
Negotiate& Negotiate::operator = (const Negotiate& negotiate)
{
    Order::operator=(negotiate);
    this->callingPlayer = negotiate.callingPlayer;
    this->targetPlayer = negotiate.targetPlayer;
    this->orderType = negotiate.orderType;
    return *this;
}
//Destructor
Negotiate::~Negotiate()
{
    callingPlayer = NULL;
    targetPlayer = NULL;
    orderType = "";
}

//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Negotiate &negotiate)
{
    return strm << "Negotiate: From " << *(negotiate.callingPlayer) << " To " << *(negotiate.targetPlayer);
}

//Setters and Getters
string Negotiate::getOrderType() const
{
    return orderType;
}
void Negotiate::setCallingPlayer(Player* cPlayer)
{
    callingPlayer = cPlayer;
}
void Negotiate::setTargetPlayer(Player* tPlayer)
{
    targetPlayer = tPlayer;
}
Player* Negotiate::getCallingPlayer() const
{
    return callingPlayer;
}
Player* Negotiate::getTargetPlayer() const
{
    return targetPlayer;
}
//Implementation of validate
bool Negotiate::validate()
{
    //Checks if the pointers point to an existing object. If it is not, then it is not valid
    if (callingPlayer == NULL || targetPlayer == NULL || callingPlayer == targetPlayer)
    {
        return false;
    }
    //Otherwise, it is valid
    return true;
}

//Implementation of execute
void Negotiate::execute()
{
    if (validate())
    {
        cout << "Negotiation between " << *(callingPlayer) << " and " << *(targetPlayer) << endl;
    }
    else
    {
        cout << "The order cannot be executed." << endl;
    }
}

//Territory Dummy class Implementation
//Default Constructor
Territory::Territory()
{
    amountOfArmies = 0;
}
//1 arg constructor
Territory::Territory(int nOfArmies, string name)
{
    amountOfArmies = nOfArmies;
    terrName = name;
}
//Destructor
Territory::~Territory()
{
    amountOfArmies = 0;
    adjacentList.clear();
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Territory &terr)
{
    return strm << "Territory " << terr.terrName << ": currently has " << terr.amountOfArmies << " armies. ";
}
//Returns true if the element
bool Territory::isAdjacent(Territory* adjTerr)
{
    //If the passed pointer points to the calling territory
    if(this == adjTerr)
    {
        return false;
    }

    for (int i = 0; adjacentList.size(); i++)
    {
        Territory* currentTerr = adjacentList.at(i);
        if(currentTerr == adjTerr)
        {
            return true;
        }
    }
    return false;
}
//Expands the adjacency list of a Territory
void Territory::addEdges(Territory* adjTerr)
{
    if (this != adjTerr)
    {
        adjacentList.push_back(adjTerr);
    }

}
//Getter
int Territory::getAmountOfArmies()
{
    return amountOfArmies;
}

string Territory::getName()
{
    return terrName;
}

vector<Territory*> Territory::getAdjacentList() const
{
    return adjacentList;
}


//Card Dummy class implementation
string types[] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

//Card functions
//initializes a card with a random type
Card::Card(){
    int randomType = rand()%5;
    type = types[randomType];
}
//initialize with a specific string
Card::Card(string s){
    type = s;
}

//Copy Constructor
Card::Card(const Card& c)
{
    type = c.type;
}

//Destructor
Card::~Card()
{
    type = "";
}

//Assignment operator overload.
Card& Card::operator = (const Card& c)
{
    this->type = c.type;
    return *this;
}

void Card::play(){

}
void Card::setType(string s){
    type = s;
}
string Card::getType() const{
    return type;
}
ostream & operator << (ostream &out, const Card &c){
    out << "Card with type " << c.type << endl;
    return out;
}

ostream & operator << (ostream &out, const Card *c){
    out << "Card with type " << c->type << endl;
    return out;
}

istream & operator >> (istream &in, Card &c){
    cout << "Enter the card type: ";
    in >> c.type;
    return in;
}


//Hand Dummy Class Implementation
Hand::Hand(){
    vector<Card*> v;
    cards = v;
}
Hand::Hand(vector<Card*> c){
    cards = c;
}
//Copy Constructor
Hand::Hand(const Hand& h)
{
    cards = h.cards;
}

Hand::~Hand(){
    cards.clear();
}

//Assignment operator overload.
Hand& Hand::operator = (const Hand& h)
{
    this->cards = h.cards;
    return *this;
}

vector<Card*> const &Hand::getCards() const{
    return cards;
}
ostream & operator << (ostream &out, const Hand &h){
    vector<Card*> v = h.cards;
    out << "Hand with cards: ";
    for(int i=0; i < v.size(); i++){
        out << v.at(i) << ' ';
    }
    out << endl;
    return out;
}

ostream & operator << (ostream &out, const Hand* h){
    out << "Hand: \n";
    for(vector<Card*>::const_iterator it = h->cards.begin(); it != h->cards.end();++it){
        out << (*it);
    }
    out << endl;
    return out;
}

//**Player Implementation**
//Default Constructor
Player::Player()
{
    name = "Player Default";
    playerCount++;
    OrdersList alist = OrdersList();
    ordersList = &alist;
}
//1 arg Constructor
Player::Player(string newName)
{
    name = newName;
    playerCount++;
    OrdersList alist = OrdersList();
    ordersList = &alist;
}
//2 arg Constructor
Player::Player(string newName, Hand* aHand)
{
    name = newName;
    playerCount++;
    hand = aHand;
    OrdersList alist = OrdersList();
    ordersList = &alist;
}

//2 arg Constructor
Player::Player(string newName, vector <Territory*> &terr)
{
    name = newName;
    playerCount++;
    territories = terr;
    OrdersList alist = OrdersList();
    ordersList = &alist;
}

//3 arg Constructor
Player::Player(string newName, vector <Territory*> &terr, Hand* aHand)
{
    name = newName;
    playerCount++;
    territories = terr;
    hand = aHand;
    OrdersList alist = OrdersList();
    ordersList = &alist;
}

//Copy Constructor
Player::Player(const Player& pl)
{
    name = pl.name;
    playerCount++;
    territories = pl.territories;
    hand = pl.hand;
    ordersList = pl.ordersList;
}

//Destructor
Player::~Player()
{
    playerCount--;
    territories.clear();
    delete hand;
    hand = NULL;
    delete ordersList;
    ordersList = NULL;
}

//Assignment operator overload
Player& Player :: operator = (const Player& pl)
{
    this->name = pl.name;
    this->territories = pl.territories;
    this->hand = pl.hand;
    this->ordersList = pl.ordersList;
    return *this;
}

//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Player &aPlayer)
{
    strm << "Player named \"" << aPlayer.name << "\" has the following:";

    if(!aPlayer.getTerritories().empty()){
        strm << "\nTerritories: ";

        for(auto x: aPlayer.getTerritories())
        {
            strm << x->getName() << " ";
        }
    }else{
        strm << "\nTerritories: No Territories";
    }

    if(aPlayer.getOrderList()->getOrdList().size() < 10000){
        strm << "\nOrders: " << aPlayer.getOrderList();
    }else{
        strm << "\nOrders: No Orders";
    }

    if(aPlayer.getHand()->getCards().size() < 10000){
        strm << aPlayer.getHand();
    }else{
        strm << "Hand: No nHand";
    }

    return strm << endl;
}

//Initializing the playerCount to 0
int Player::playerCount = 0;

//Accessors

vector <Territory*> Player::getTerritories() const
{
    return territories;
}

Hand* Player::getHand() const
{
    return this->hand;
}

OrdersList* Player::getOrderList() const
{
    return ordersList;
}

int Player::getPlayerCount()
{
    return playerCount;
}

//Mutators

void Player::setTerritories(vector <Territory*> &terr)
{
    territories = terr;
}

void Player::setOrderList(OrdersList* aOrdersList)
{
    ordersList = aOrdersList;
}

void Player::setHand(Hand* h)
{
    this->hand = h;
}

//Required Methods

//Returns Territories which are adjacent and not the current player's territory
vector <Territory*> Player::toAttack()
{
    set<Territory*> uniqueTerritoriesToAttack;
    string adjTerritoryName;
    bool attackTerr;

    for(int i = 0; i < territories.size(); i++){
        if(!territories[i]->getAdjacentList().empty()){
            for(int j = 0; j < territories[i]->getAdjacentList().size(); j++){
                attackTerr = true;
                adjTerritoryName = territories[i]->getAdjacentList()[j]->getName();

                for(int k = 0; k < territories.size(); k++){
                    if(adjTerritoryName == territories[k]->getName()){
                        attackTerr = false;
                        break;
                    }
                }

                if(attackTerr){
                    uniqueTerritoriesToAttack.insert(territories[i]->getAdjacentList()[j]);
                }
            }
        }
    }
    vector<Territory*> territoriesToAttack(uniqueTerritoriesToAttack.begin(), uniqueTerritoriesToAttack.end());
    return territoriesToAttack;
}

//Returns the territories owned by the player.
vector <Territory*> Player::toDefend()
{
    return this->getTerritories();
}

//Different implementations of issueOrder based on the parameters needed to create a specific order
//Creates an order and places it in the player's list of orders
void Player::issueOrder(string ordType, Territory* targetTerritory, int nOfArmies)
{
    Order* ord;

    if(ordType == "Deploy"){
        ord = new Deploy(targetTerritory, &territories, nOfArmies);
        ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
    }else{
        cout << "Invalid Order" << endl;
    }
}

void Player::issueOrder(string ordType, Territory* targetTerritory, int nOfArmies, Territory* sourceTerr)
{
    Order* ord;

    if(ordType == "Advance"){
        ord = new Advance(targetTerritory, &territories, nOfArmies, sourceTerr);
        ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
    }else if(ordType == "Airlift"){
        ord = new Airlift(targetTerritory, &territories, nOfArmies, sourceTerr);
        ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
    }else{
        cout << "Invalid Order" << endl;
    }
}

void Player::issueOrder(string ordType, Territory* targetTerritory)
{
    Order* ord;

    if(ordType == "Bomb"){
        ord = new Bomb(targetTerritory, &territories);
        ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
    }else if(ordType == "Blockade"){
        ord = new Blockade(targetTerritory, &territories);
        ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
    }else{
        cout << "Invalid Order" << endl;
    }
}

void Player::issueOrder(string ordType, Player* targetPlayer)
{
    Order* ord;

    if(ordType == "Negotiate"){
        ord = new Negotiate(this, targetPlayer);
        ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
    }else{
        cout << "Invalid Order" << endl;
    }
}

//Splits the list of all territories into almost equal or equal parts depending on the number of players.
void setPlayersTerritories(vector <Territory*> allTerritories, vector <Player*> allPlayers, int playerCount)
{

    int territoryCount = allTerritories.size();

    int subLength = territoryCount / playerCount;
    int remainder = territoryCount % playerCount;
    int limit = min(playerCount, territoryCount);

    int startIndex = 0;
    int endIndex = 0;

    for(int i = 0; i < limit; i++) {
        endIndex += (remainder > 0) ? (subLength + !!(remainder--)) : subLength;

        vector <Territory*> subTerritories(allTerritories.begin() + startIndex, allTerritories.begin() + endIndex);
        allPlayers.at(i)->setTerritories(subTerritories);

        startIndex = endIndex;
    }

}

