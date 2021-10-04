#include "Orders.h"
#include <iostream>
#include <list>
using std::string;
//For storing elements
using std::list;
using std::cin;
using std::cout;
using std::endl;

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
//Getter
list<Order*> OrdersList:: getOrdList() const
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
}
//Two arg constructor
Order::Order(Territory* targetTerr, list<Territory*>* ownedTerr)
{
    targetTerritory = targetTerr;
    ownedTerritories = ownedTerr;
}
//Copy Constructor
Order::Order(const Order& ord)
{
    targetTerritory = ord.getTargetTerritory();
    ownedTerritories = ord.getOwnedTerritories();
}
//Assignment operator overload.
Order& Order::operator = (const Order& ord)
{
    this->targetTerritory = ord.targetTerritory;
    this->ownedTerritories = ord.ownedTerritories;
    return *this;
}
//Destructor
Order:: ~Order()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Order &ord)
{
    return strm << "Targetted Territory: "<<*(ord.targetTerritory);
}
//Getters and Setters
Territory* Order::getTargetTerritory() const
{
    return targetTerritory;
}
list<Territory*>* Order::getOwnedTerritories() const
{
    return ownedTerritories;
}
void Order:: setTargetTerritory(Territory* newTarTerr)
{
    targetTerritory = newTarTerr;
}
void Order:: setOwnedTerritories(list<Territory*>* ownedTerr)
{
    ownedTerritories = ownedTerr;
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
}
//3-arg constructor
Deploy::Deploy(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies)
: Order(targetTerritory,ownedTerr)
{
    nAddedArmies = nOfArmies;
}
//Copy Constructor
Deploy::Deploy(const Deploy& depl): Order(depl.targetTerritory, depl.ownedTerritories)
{
    nAddedArmies = depl.nAddedArmies;
}
//Assignment operator overload
Deploy& Deploy:: operator = (const Deploy& depl)
{
    Order::operator=(depl);
    this->nAddedArmies = depl.nAddedArmies;
    return *this;
}
//Destructor
Deploy:: ~Deploy()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nAddedArmies = 0;
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Deploy &depl)
{
    return strm << "Deploy " << depl.nAddedArmies << " armies on " << *(depl.targetTerritory);
}
//Setter and Getter
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
    for(list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
    {
        //Getting the pointer
        Territory* currentTerr = *it;
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
}
//4 args constructor
Advance::Advance(Territory* targetTerritory, list<Territory*>* ownedTerr,
                  int nOfArmies, Territory* sourceTerr): Order(targetTerritory,ownedTerr)
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
}
//Copy Constructor
Advance::Advance(const Advance& adv):Order(adv.targetTerritory, adv.ownedTerritories)
{
    nMovedArmies = adv.nMovedArmies;
    sourceTerritory = adv.sourceTerritory;
}
//Assignment operator overload
Advance& Advance :: operator = (const Advance& adv)
{
    Order::operator=(adv);
    this->nMovedArmies = adv.nMovedArmies;
    this->sourceTerritory = adv.sourceTerritory;
    return *this;
}
//Destructor
Advance::~Advance()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nMovedArmies = 0;
    sourceTerritory = NULL;
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Advance &adv)
{
    return strm << "Advance " << adv.nMovedArmies << " armies : From "
    << *(adv.sourceTerritory) << " to " << *(adv.targetTerritory);
}

//setters and getters
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
    for (list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If the source territory is owned by the player, then it is valid and returns true
        if (sourceTerritory == *it)
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
        for (list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
        {
            //If the target territory is owned by the player, then it is an ally
            if (targetTerritory == *it)
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
}
//1 arg constructor
Bomb::Bomb(Territory* targetTerritory, list<Territory*>* ownedTerr): Order(targetTerritory,ownedTerr)
{
}
//Copy constructor
Bomb::Bomb(const Bomb& bomb): Order(bomb.targetTerritory, bomb.ownedTerritories)
{
}
//Overload assignment operator
Bomb& Bomb :: operator = (const Bomb& bomb)
{
    Order::operator=(bomb);
    return *this;
}
//Destructor
Bomb::~Bomb()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Bomb &bomb)
{
    return strm << "Bomb " << *(bomb.targetTerritory);
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
    for (list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If the target territory is owned by the player, then the order is not valid.
        if (targetTerritory == *it)
        {
            return false;
        }
    }
    //Checking if the targetted territory is adjacent to any
    for (list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
    {
        if (targetTerritory->isAdjacent(*it))
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
}
//2 arg Constructor
Blockade::Blockade(Territory* targetTerritory, list<Territory*>* ownedTerr):Order(targetTerritory, ownedTerr)
{
}
//Copy Constructor
Blockade::Blockade(const Blockade& block):Order(block.targetTerritory,block.ownedTerritories)
{

}
//Overload the assignment operator
Blockade& Blockade::operator = (const Blockade& block)
{
    Order::operator=(block);
    return *this;
}
//Destructor
Blockade::~Blockade()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
}
//Stream insertion operator
ostream& operator <<(ostream &strm, const Blockade &block)
{
    return strm << "Blockade " << *(block.targetTerritory);
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
    for (list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If it is, then the order is valid and the function returns true
        if (targetTerritory == *it)
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
}
//4 args constructor
Airlift::Airlift(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr):
    Order(targetTerritory, ownedTerr)
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
}
//Copy Constructor
Airlift::Airlift(const Airlift& airLi):Order(airLi.targetTerritory, airLi.ownedTerritories)
{
    nMovedArmies = airLi.nMovedArmies;
    sourceTerritory = airLi.sourceTerritory;
}
//Overload assignment Operator
Airlift& Airlift::operator = (const Airlift& airLi)
{
    Order::operator=(airLi);
    this->nMovedArmies = airLi.nMovedArmies;
    this->sourceTerritory = airLi.sourceTerritory;
    return *this;
}
//Destructor
Airlift::~Airlift()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nMovedArmies = 0;
    sourceTerritory = NULL;
}
//Stream insertion operator
ostream& operator <<(ostream &strm, const Airlift &airL)
{
    return strm << "Airlift: From " << *(airL.sourceTerritory) << " To " << *(airL.targetTerritory);
}

//Getters and Setters
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
    for(list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
    {
        //If the source territory is owned, then it is valid and returns true
        if(sourceTerritory == *it)
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
        for(list<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
        {
            if (targetTerritory == *it)
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
}
//2 args constructor
Negotiate::Negotiate(Player* cPlayer, Player* tPlayer):Order()
{
    callingPlayer = cPlayer;
    targetPlayer = tPlayer;
}
//Copy Constructor
Negotiate::Negotiate(const Negotiate& negotiate): Order()
{
    callingPlayer = negotiate.callingPlayer;
    targetPlayer = negotiate.targetPlayer;
}
//Assignment Operator overload
Negotiate& Negotiate::operator = (const Negotiate& negotiate)
{
    Order::operator=(negotiate);
    this->callingPlayer = negotiate.callingPlayer;
    this->targetPlayer = negotiate.targetPlayer;
    return *this;
}
//Destructor
Negotiate::~Negotiate()
{
    callingPlayer = NULL;
    targetPlayer = NULL;
}

//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Negotiate &negotiate)
{
    return strm << "Negotiate: From " << *(negotiate.callingPlayer) << " To " << *(negotiate.targetPlayer);
}

//Setters and Getters
void Negotiate::setCallingPlayer(Player* cPlayer)
{
    callingPlayer = cPlayer;
}
void Negotiate::setTargetPlayer(Player* tPlayer)
{
    targetPlayer = tPlayer;
}
Player* Negotiate::getCallingPlayer()
{
    return callingPlayer;
}
Player* Negotiate::getTargetPlayer()
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
    //
    for (list<Territory*>::iterator it = adjacentList.begin(); it != adjacentList.end();++it)
    {
        Territory* currentTerr = *it;
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

//Player Dummy Class implementation
//Default Constructor
Player::Player()
{
    name = "Player Lambda";
}
//1 arg constructor
Player::Player(string newName)
{
    name = newName;
}
//Destructor
Player::~Player()
{

}
//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Player &pl)
{
    return strm << "Player: " << pl.name;
}
//Setter and Getter
string Player::getName()
{
    return name;
}
void Player::setName(string newName)
{
    name = newName;
}
