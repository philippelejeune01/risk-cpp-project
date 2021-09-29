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
    ordList.clear();
}
//Assignment operator overload
OrdersList& OrdersList :: operator = (const OrdersList& ls)
{
    //This copy all the values stored in the list
    this->ordList = ls.ordList;
    return *this;
}
//Getter
list<Order*> OrdersList:: getOrdList() const
{
    return ordList;
}
//Moves an order in the list
void OrdersList::move(Order* order, int index)
{
    list<Order*>::iterator oldPos = ordList.begin();
    list<Order*>::iterator newPos = ordList.begin();

    //Determines the original position of the Order. If the order is not in the list, then it
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
        cout << "new order has been added in the list"<< endl;
    }
    //Otherwise, it moves the order from its old position to its new one.
    else
    {
        ordList.splice(oldPos, ordList, newPos);
        cout << "an order has shifted position in the list" << endl;
    }

}

void OrdersList::remove(Order* order)
{
    ordList.remove(order);
    cout << "order has been succesfully been removed" << endl;
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
    //If the amount of armies to be deployed is zero
    if(nAddedArmies == 0)
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

//Territory Implementation
//Default Constructor
Territory::Territory()
{
    amountOfArmies = 0;
}
//1 arg constructor
Territory::Territory(int nOfArmies)
{
    amountOfArmies = nOfArmies;
}
//Destructor
Territory::~Territory()
{
    amountOfArmies = 0;
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

