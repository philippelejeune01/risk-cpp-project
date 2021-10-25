#include "Orders.h"
#include <iostream>
#include <list>
#include <vector>
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
OrdersList::OrdersList(list<Order*>* ls)
{
    //This copies all the pointers to Order stored in the passed list
    for (list<Order*>::iterator it = ls->begin(); it != ls->end(); ++it)
    {
        //Creates a new Order object from the object of the passed list
        //Maintains the passed list order
        ordList.push_back((*it)->duplicate());
    }
}
//Copy Constructor
OrdersList::OrdersList(const OrdersList& ordsL)
{
    //This copies all the pointers stored in the list
    for (list<Order*>::const_iterator it = ordsL.ordList.begin(); it != ordsL.ordList.end(); ++it)
    {
        //Creates a new Order object from the object of the passed list
        //Maintains the passed OrdersList
        ordList.push_back((*it)->duplicate());
    }
}
//Destructor
OrdersList::~OrdersList()
{
    //ordList.clear();

    //This deletes all the Order objects stored in the list
    for(list<Order*>::iterator it = ordList.begin(); it != ordList.end(); ++it)
    {
        delete *it;
    }
    //This erases all the pointers stored in the list
    ordList.clear();

}
//Assignment operator overload
OrdersList& OrdersList :: operator = (const OrdersList& ls)
{
    //This copy all the pointers stored in the list
    this->ordList = ls.ordList;
    for (list<Order*>::const_iterator it = ls.ordList.begin(); it != ls.ordList.end(); ++it)
    {
        //Creates a new Order object based on the passed pointer
        //Maintains the order of the passed OrdersList
        this->ordList.push_back((*it)->duplicate());
    }
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
//Moves an order in the list at the given index.
//If it's in the list already, then it inserts it at the given index
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

    //Determines the original position of the Order. If the order is not in the list, then the oldPos points to the endpoint.
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
//This removes an order at a particular index
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
//addOrder method for adding an order in the OrdersList
void OrdersList:: addOrder(Order* order)
{
    ordList.push_back(order);
}
//Order Implementation
//Default Constructor
Order::Order()
{
}
//Two arg constructor
Order::Order(Territory* targetTerr, vector<Territory*>* ownedTerr)
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
    return strm << ord.doPrint();
}
//doPrint method for the stream insertion operator of Order
string Order::doPrint() const
{
    return "Targetted Territory: " + targetTerritory->getName() + "(" + std::to_string(targetTerritory->getAmountOfArmies()) + " armies)";
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
/*
//Duplicate function
Order* Order::duplicate()
{
    //Creates a new object and returns its pointer
    return new Order(targetTerritory,ownedTerritories);
}
*/
/*
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
*/
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
Deploy::Deploy(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies)
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
    return strm << depl.doPrint();
}
//doPrint method for the stream insertion operator of Deploy
string Deploy::doPrint() const
{
    return "Deploy: " + std::to_string(nAddedArmies) + " armies on " + targetTerritory->getName()
    + "(" + std::to_string(targetTerritory->getAmountOfArmies()) + " armies)";
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
//Duplicate function
Order* Deploy::duplicate()
{
    //Creates a new object and returns its pointer
    return new Deploy(targetTerritory,ownedTerritories,nAddedArmies);
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
    for(vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
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
        //Actual execution of the method
        //targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()+nAddedArmies);

        cout << "Deploying " << nAddedArmies << " armies on the targetted territory." << endl;
    }
    //Warns the player the order could not be done
    else
    {
        cout << "This order cannot be executed." << endl;
    }

    //Notify(this);
}

//Advance Implementation
//Default Constructor
Advance::Advance():Order()
{
    nMovedArmies = 0;
    sourceTerritory = NULL;
}
//4 args constructor
Advance::Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr,
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
    return strm << adv.doPrint();
}
//doPrint method for the stream insertion operator of Advance
string Advance::doPrint() const
{
    return "Advance: " + std::to_string(nMovedArmies) + " armies: From "
    + sourceTerritory->getName() + "(" + std::to_string(sourceTerritory->getAmountOfArmies()) + " armies)"
    + " to " + targetTerritory->getName() + "(" + std::to_string(targetTerritory->getAmountOfArmies()) + " armies)";
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
//Duplicate function
Order* Advance::duplicate()
{
    //Creates a new object and returns its pointer
    return new Advance(targetTerritory,ownedTerritories,nMovedArmies,sourceTerritory);
}
//Implementation of validate function
bool Advance:: validate()
{
    //Checks if the pointers to an existing object, that the number of
    //of armies is not equal or below 0.
    //If the target territory is not adjacent to the source territory, then it is not valid
    //If the sourceTerritory does not have enough armies, then it is not valid
    if (sourceTerritory == NULL || targetTerritory == NULL || nMovedArmies <= 0 || ownedTerritories == NULL
         || sourceTerritory->getAmountOfArmies() < nMovedArmies)
    {
        return false;
    }

    //Checking if the source territory is owned by the player
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
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

        if (sourceTerritory.getPlayer() != targetTerritory.getPlayer())
        {
            /*
            int nDefArmies = targetTerritory->getAmountOfArmies();
            int nAttArmies = nMovedArmies;
            for (; nAttArmies  )
            {

            }
            */
            cout << "Initiating an attack! Advancing " << nMovedArmies << " armies to the targetted enemy territory." << endl;
        }
        else
        {
            //Transfer the selected armies from the source territory to the target territory
            /*
            targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()+nMovedArmies);
            sourceTerritory->setAmountOfArmies(sourceTerritoru->getAmountOfArmies()-nMovedArmies);
            */
            cout << "Initiating a reinforcement! Advancing " << nMovedArmies << " armies to the targetted ally territory." << endl;
        }
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
Bomb::Bomb(Territory* targetTerritory, vector<Territory*>* ownedTerr): Order(targetTerritory,ownedTerr)
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
    return strm << bomb.doPrint();
}
//doPrint method for the stream insertion operator of Bomb
string Bomb::doPrint() const
{
    return "Bomb: " + targetTerritory->getName()
    + "(" + std::to_string(targetTerritory->getAmountOfArmies()) + " armies)";
}
//Duplicate function
Order* Bomb::duplicate()
{
    //Creates a new object and returns its pointer
    return new Bomb(targetTerritory,ownedTerritories);
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
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If the target territory is owned by the player, then the order is not valid.
        if (targetTerritory == *it)
        {
            return false;
        }
    }
    //Checking if the targetted territory is adjacent to any of the player owned territories
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
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
        //targetTerritory->getAmountOfArmies(targetTerritory->getAmountOfArmies()/2);
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
Blockade::Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr):Order(targetTerritory, ownedTerr)
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
    return strm << block.doPrint();
}
//doPrint method for the stream insertion operator of Blockade
string Blockade::doPrint() const
{
    return "Blockade: " + targetTerritory->getName()
    + "(" + std::to_string(targetTerritory->getAmountOfArmies()) + " armies)";
}
//Duplicate function
Order* Blockade::duplicate()
{
    //Creates a new object and returns its pointer
    return new Blockade(targetTerritory,ownedTerritories);
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
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
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
        /*
        targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()*3);
        targetTerritory->setPlayer(new Player("NEUTRAL"));
        ownedTerritories->remove(targetTerritory);
        */
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
Airlift::Airlift(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr):
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
    return strm << airL.doPrint();
}
//doPrint method for the stream insertion operator of Airlift
string Airlift::doPrint() const
{
    return "Airlift " + std::to_string(nMovedArmies) + " armies: From "
    + sourceTerritory->getName() + "(" + std::to_string(sourceTerritory->getAmountOfArmies()) + " armies)"
    + " to " + targetTerritory->getName() + "(" + std::to_string(targetTerritory->getAmountOfArmies()) + " armies)";
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
//Duplicate function
Order* Airlift::duplicate()
{
    //Creates a new object and returns its pointer
    return new Airlift(targetTerritory,ownedTerritories,nMovedArmies,sourceTerritory);
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

    bool srcTerrIsOwned = false;
    bool tgtTerrIsOwned = false;
    //Checks if the source territory is owned by the player
    for(vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
    {
        //If the source territory is owned, then it is valid and returns true
        if(sourceTerritory == *it)
        {
            srcTerrIsOwned = true;
        }
        if(targetTerritory == *it)
        {
            tgtTerrIsOwned = true;
        }
    }

    return (srcTerrIsOwned && tgtTerrIsOwned);
}
//Implementation of execute
void Airlift::execute()
{
    if (validate())
    {
        /*
        targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()+nMovedArmies);
        sourceTerritory->setAmountOfArmies(sourceTerritoru->getAmountOfArmies()-nMovedArmies);
        */
        cout << "Airlift deployment! From " << *(sourceTerritory) << " To " << *(targetTerritory) << endl;

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
    return strm << negotiate.doPrint();
}
//DoPrint method for the stream insertion operator of Negotiate
string Negotiate::doPrint() const
{
    return "Negotiate: ";
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
//Duplicate function
Order* Negotiate::duplicate()
{
    //Creates a new object and returns its pointer
    return new Negotiate(callingPlayer,targetPlayer);
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
        cout << "Negotiation have been settled between the two players" << endl;
    }
    else
    {
        cout << "The order cannot be executed." << endl;
    }
}

