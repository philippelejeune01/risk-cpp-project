#include "Orders.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Map.h"
#include "LoggingObserver.h"
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
    logO = new LogObserver();
    this->Attach(logO);
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
    logO = new LogObserver();
    this->Attach(logO);
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
    logO = new LogObserver();
    this->Attach(logO);
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
bool OrdersList::isEmpty()
{
    return ordList.empty();
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
    //If the order is a Deploy object, then it is pushed at the front of the list
    if (order->getOrderType() == "Deploy")
    {
        ordList.push_front(order);
        lastAddedWasDeployed = true;
    }
    //Otherwise, it is added at the back
    else
    {
        ordList.push_back(order);
        lastAddedWasDeployed = false;
    }
    Notify(this);
}
//This method executes the order at the front of OrdersList and pops it
void OrdersList:: executeFirstOrder()
{
    Order* firstOrder = *ordList.begin();
    firstOrder->execute();
    delete firstOrder;
    ordList.pop_front();
}
string OrdersList::stringToLog()
{
    Order* ord = (lastAddedWasDeployed) ? ordList.front(): ordList.back();
    return "Order Issued : " + ord->doPrint();
}
//Order Implementation
//Default Constructor
Order::Order()
{
    logO = new LogObserver();
    this->Attach(logO);
}
//Two arg constructor
Order::Order(Territory* targetTerr, vector<Territory*>* ownedTerr)
{
    targetTerritory = targetTerr;
    ownedTerritories = ownedTerr;
    logO = new LogObserver();
    this->Attach(logO);
}
//Copy Constructor
Order::Order(const Order& ord)
{
    targetTerritory = ord.getTargetTerritory();
    ownedTerritories = ord.getOwnedTerritories();
    logO = new LogObserver();
    this->Attach(logO);
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
Order::Order(Territory* targetTerr, vector<Territory*>* ownedTerr, string oType)
{
    targetTerritory = targetTerr;
    ownedTerritories = ownedTerr;
    orderType = oType;
    logO = new LogObserver();
    this->Attach(logO);
}
//doPrint method for the stream insertion operator of Order
string OrdersList::getFirstOrderType()
{
    return ordList.front()->getOrderType();
}
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
string Order::getOrderType() const
{
    return orderType;
}
void Order:: setTargetTerritory(Territory* newTarTerr)
{
    targetTerritory = newTarTerr;
}
void Order:: setOwnedTerritories(vector<Territory*>* ownedTerr)
{
    ownedTerritories = ownedTerr;
}

Player*** Order::playersCannotAttackList = NULL;
int Order::sizeOfPlCantAttList = 6;
int Order::indexOfEnd = 0;
//This method should be called at the start of the game. It sets up the multidimensional array
//playersCannotAttackList.
void Order::setUpPlayerCannotAttackList()
{
    playersCannotAttackList = new Player**[6];
    sizeOfPlCantAttList = 6;
    for (int i = 0; i < 6; i++)
    {
        playersCannotAttackList[i] = new Player*[2];
        playersCannotAttackList[i][0] = NULL;
        playersCannotAttackList[i][1] = NULL;
    }
}
//This method clears out the content of playersCannotAttackList. This should be called at the end of each round.
void Order::clearPlayerCannotAttackList()
{
    for(int i = 0; i < sizeOfPlCantAttList; i++)
    {
        playersCannotAttackList[i][0] = NULL;
        playersCannotAttackList[i][1] = NULL;
    }
    indexOfEnd = 0;
}
//This method deletes the playersCannotAttackList from the program.
void Order::deletePlayerCannotAttackList()
{
    for(int i = 0; i < sizeOfPlCantAttList; i++)
    {
        delete [] playersCannotAttackList[i];
    }
    indexOfEnd = 0;
    sizeOfPlCantAttList = 0;
    delete [] playersCannotAttackList;
    playersCannotAttackList = NULL;
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
/*
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
*/
//Deploy implementation
//Default constructor
Deploy::Deploy():Order(NULL, NULL, "Deploy")
{
    nAddedArmies = 0;
}
//3-arg constructor
Deploy::Deploy(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies)
: Order(targetTerritory,ownedTerr, "Deploy")
{
    nAddedArmies = nOfArmies;
}
//Copy Constructor
Deploy::Deploy(const Deploy& depl): Order(depl.targetTerritory, depl.ownedTerritories, "Deploy")
{
    nAddedArmies = depl.nAddedArmies;
}
//Assignment operator overload
Deploy& Deploy:: operator = (const Deploy& depl)
{
    Order::operator=(depl);
    this->nAddedArmies = depl.nAddedArmies;
    this->orderType = "Deploy";
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
//StringtoLog method from ILoggable
string Deploy::stringToLog()
{
    return "Deploy Order Executed: " + std::to_string(nAddedArmies) + " armies are added on the territory "
    + targetTerritory->getName();
}
//Implementation of validate
bool Deploy::validate()
{
    //If the pointers points to an existing object and the number of armies deployed is not equal or less than 0,
    //It returns false
    if(targetTerritory == NULL || ownedTerritories == NULL || nAddedArmies <= 0 || ownedTerritories->empty())
    {
        cout<<"Null values \n";
        return false;
    }
    //Checks if the targetTerritory belongs to the player.
    if (ownedTerritories->at(0)->getPlayer() == targetTerritory->getPlayer())
    {
        return true;
    }
    /*
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
    */
    //Otherwise, returns false
    cout<<"territory is not owned by you"<<endl;
    return false;

}
//Implementation of execute
void Deploy::execute()
{
    //If the order is valid, it describes the action
    if (validate())
    {
        //Actual execution of the method
        targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()+nAddedArmies);

        cout << "Deploying " << nAddedArmies << " armies on the targetted territory:" <<*targetTerritory<< endl;
    }
    //Warns the player the order could not be done
    else
    {
        cout << "This order cannot be executed." << endl;
    }

    Notify(this);
}

//Advance Implementation
//Default Constructor
Advance::Advance():Order(NULL, NULL, "Advance")
{
    nMovedArmies = 0;
    sourceTerritory = NULL;
}
//4 args constructor
Advance::Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr,
                  int nOfArmies, Territory* sourceTerr): Order(targetTerritory,ownedTerr, "Advance")
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
}
Advance::Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies,
         Territory* sourceTerr, vector<Territory*>* enemyTerrs, bool* flag):
             Order(targetTerritory, ownedTerr, "Advance")
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
    enemyTerritories = enemyTerrs;
    flagConq = flag;
}
//Copy Constructor
Advance::Advance(const Advance& adv):Order(adv.targetTerritory, adv.ownedTerritories, "Advance")
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
    this->orderType = "Advance";
    return *this;
}
//Destructor
Advance::~Advance()
{
    targetTerritory = NULL;
    ownedTerritories = NULL;
    nMovedArmies = 0;
    sourceTerritory = NULL;
    flagConq = NULL;
    enemyTerritories = NULL;
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
void Advance::setFlagConqTerr(bool* flag)
{
    flagConq = flag;
}
void Advance::setEnemyTerritories(vector<Territory*>* enmyTerrs)
{
    enemyTerritories = enmyTerrs;
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
string Advance::stringToLog()
{
    return "Advance Order executed: " + std::to_string(nMovedArmies) + " armies are moved from the territory " + sourceTerritory->getName()
    + " to the territory " + targetTerritory->getName();
}
//Implementation of validate function
bool Advance:: validate()
{
    //Checks if the pointers to an existing object, that the number of
    //of armies is not equal or below 0.
    //If the target territory is not adjacent to the source territory, then it is not valid
    //If the sourceTerritory does not have enough armies, then it is not valid
    cout<<"In Advance:\n";
    if (sourceTerritory == NULL || targetTerritory == NULL || nMovedArmies <= 0 || ownedTerritories == NULL ||
         sourceTerritory->getAmountOfArmies() < nMovedArmies || ownedTerritories->empty())
    {
        cout << "Some values are NULL" << endl;
        return false;
    }
    if (!sourceTerritory->isAdjacentTo(*targetTerritory))
    {
        cout << "Target territory and source territory are not adjacent."<< endl;
        return false;
    }
    //If the targetTerritory is an enemy territory, we need to check if the player owning that territory
    //is not under negotiation.
    if (sourceTerritory->getPlayer() != targetTerritory->getPlayer())
    {
        //Cycles through the playersCannotAttackList to see if the calling player and the enemy player
        //are under negotiations.
        for(int i = 0; i < indexOfEnd; i++)
            {
                //Creates variables
                Player* attPl = sourceTerritory->getPlayer();
                Player* defPl = targetTerritory->getPlayer();

                //If the pair of players is in the list, then the Advance order is invalid
                if ((attPl == playersCannotAttackList[i][0] || attPl == playersCannotAttackList[i][1])
                    && (defPl == playersCannotAttackList[i][0] || defPl == playersCannotAttackList[i][1]))
                {
                    attPl = NULL;
                    defPl = NULL;
                    cout << "These players are under negotiations" << endl;
                    return false;
                }
            }
    }
    //Checking if the source territory is owned by the player
    if (ownedTerritories->at(0)->getPlayer() == sourceTerritory->getPlayer())
    {
        return true;
    }
    /*
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If the source territory is owned by the player, then it is valid and returns true
        if (sourceTerritory == *it)
        {
            return true;
        }
    }
    */
    //Otherwise, returns false
    cout << "The source territory is not owned by the player" << endl;
    return false;
}
//Implementation of execute function
void Advance::execute()
{
    //Checks if the order is valid
    if(validate())
    {
        //If the targetTerritory is an enemy territory, then this Advance order initiates an attack
        if (sourceTerritory->getPlayer() != targetTerritory->getPlayer())
        {
            cout << "Initiating an attack! Advancing " << nMovedArmies << " armies to the targetted enemy territory." << endl;
            //Fields for the amount of attacking armies and of defending armies
            int nDefArmies = targetTerritory->getAmountOfArmies();
            int nAttArmies = nMovedArmies;
            //Records how many armies were killed.
            int nDeadAttArmies = 0;
            int nDeadDefArmies = 0;

            //Setting up the seed of the random number generator
            srand(time(NULL));
            int chance = 0;

            //Calculate how many defending armies are killed
            for (int i = 0; i < nAttArmies && nDeadDefArmies < nDefArmies; i++)
            {
                chance = rand() % 100;
                if (chance < 60)
                {
                    ++nDeadDefArmies;
                }
            }
            //Calculate how many attacking armies are killed
            for (int i = 0; i < nDefArmies && nDeadAttArmies < nAttArmies; i++)
            {
                chance = rand() % 100;
                if (chance < 70)
                {
                    ++nDeadAttArmies;
                }
            }

            //Substract the amount of armies killed
            nAttArmies -= nDeadAttArmies;
            nDefArmies -= nDeadDefArmies;

            //If there are remaining attacking armies and no more defending armies, then the territory is conquered
            if (nAttArmies > 0 && nDefArmies == 0)
            {
                //Switches ownership of the territory
                targetTerritory->setPlayer(sourceTerritory->getPlayer());
                targetTerritory->setAmountOfArmies(nAttArmies);
                if (enemyTerritories != NULL)
                {
                    for (vector<Territory*>::const_iterator it = enemyTerritories->begin(); it != enemyTerritories->end(); ++it)
                    {
                        if (targetTerritory == *it)
                        {
                            enemyTerritories->erase(it);
                            break;
                        }
                    }
                }

                ownedTerritories->push_back(targetTerritory);
                sourceTerritory->setAmountOfArmies(sourceTerritory->getAmountOfArmies()-nMovedArmies);
                *flagConq = true;
            }
            //Otherwise, the remaining respective armies returns back to their respective territory.
            else
            {
                //Sets the amount of armies
                targetTerritory->setAmountOfArmies(nDefArmies);
                sourceTerritory->setAmountOfArmies(sourceTerritory->getAmountOfArmies() -nMovedArmies + nAttArmies);
            }
        }
        //Otherwise, it simply transfers the armies from the sourceTerritory to the targetTerritory
        else
        {
            //Transfer the selected armies from the source territory to the target territory

            targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()+nMovedArmies);
            sourceTerritory->setAmountOfArmies(sourceTerritory->getAmountOfArmies()-nMovedArmies);

            cout << "Initiating a reinforcement! Advancing " << nMovedArmies << " armies to the targetted ally territory." << endl;
        }
    }
    //If the Advance is invalid
    else
    {
        cout << "This order cannot be executed" << endl;
    }
    Notify(this);
}
//Implementation of the subclass Bomb
//Default constructor
Bomb::Bomb():Order(NULL, NULL, "Bomb")
{
}
//2 arg constructor
Bomb::Bomb(Territory* targetTerritory, vector<Territory*>* ownedTerr): Order(targetTerritory,ownedTerr, "Bomb")
{
}
//Copy constructor
Bomb::Bomb(const Bomb& bomb): Order(bomb.targetTerritory, bomb.ownedTerritories, "Bomb")
{
}
//Overload assignment operator
Bomb& Bomb :: operator = (const Bomb& bomb)
{
    Order::operator=(bomb);
    this->orderType = "Bomb";
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
string Bomb::stringToLog()
{
    return "Bomb Order executed: the territory affected is " + targetTerritory->getName();
}
//Implementation of validate
bool Bomb::validate()
{
    //If the pointers point to an existing object
    cout<<"In Bomb:\n";
    if (targetTerritory == NULL || ownedTerritories == NULL || ownedTerritories->empty())
    {
        cout<<"Null values \n";
        return false;
    }
    //Checking if the target territory is owned by the player
    if (ownedTerritories->at(0)->getPlayer() == targetTerritory->getPlayer())
    {
        cout<<"territory is owned by this player,cannot be bombed!\n";
        return false;
    }
    /*
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If the target territory is owned by the player, then the order is not valid.
        if (targetTerritory == *it)
        {
            return false;
        }
    }
    */
    //Checking if the targetted territory is adjacent to any of the player owned territories
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end();++it)
    {
        if (targetTerritory->isAdjacentTo(**(it)))
        {
            return true;
        }
    }
    //Otherwise
    cout<<"Not Adjacent to this territory!\n";
    return false;
}
//Implementation of execute
void Bomb::execute()
{
    //If the order validates, it executes it
    if(validate())
    {
        cout << "Bomb the targetted Territory " << *targetTerritory << endl;
        targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()/2);
    }
    //Otherwise, it sends an error message
    else
    {
        cout << "This order cannot be executed." << endl;
    }
    Notify(this);
}

//Implementation of Blockade
//Default Constructor
Blockade::Blockade():Order(NULL, NULL, "Blockade")
{
    neutralPlayer = NULL;
}
//2 arg Constructor
Blockade::Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr):Order(targetTerritory, ownedTerr, "Blockade")
{
    neutralPlayer = NULL;
}
//3 arg Constructor
Blockade::Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr, Player* neutralPl):Order(targetTerritory, ownedTerr, "Blockade")
{
    neutralPlayer = neutralPl;
}
//Copy Constructor
Blockade::Blockade(const Blockade& block):Order(block.targetTerritory,block.ownedTerritories, "Blockade")
{
    neutralPlayer = block.neutralPlayer;
}
//Overload the assignment operator
Blockade& Blockade::operator = (const Blockade& block)
{
    Order::operator=(block);
    this->neutralPlayer = block.neutralPlayer;
    this->orderType = "Blockade";
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
//Setter and Getter
Player* Blockade::getNeutralPlayer()
{
    return neutralPlayer;
}
void Blockade::setNeutralPlayer(Player* nPl)
{
    neutralPlayer = nPl;
}
string Blockade::stringToLog()
{
    return "Blockade Order executed: the targetted territory is " + targetTerritory->getName();
}
//Implementation of validate
bool Blockade:: validate()
{
    //Checks if the pointers point to an existing object
    cout<<"In Blockade:\n";
    if (targetTerritory == NULL || ownedTerritories == NULL)
    {
        cout<<"Null values \n";
        return false;
    }
    //Checks if the targetted territory is owned by the player
    if (ownedTerritories->at(0)->getPlayer() == targetTerritory->getPlayer())
    {
        return true;
    }
    /*
    for (vector<Territory*>::iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
    {
        //If it is, then the order is valid and the function returns true
        if (targetTerritory == *it)
        {
            return true;
        }
    }
    */
    //Otherwise, returns false
    cout<<"Not owned by this player!\n";
    return false;
}
//Implementation of execute
void Blockade::execute()
{
    //Checks if the order is valid
    if (validate())
    {
        cout << "Blockade the targetted territory " << *(targetTerritory) << ". It has now 3 times the amount of armies and is neutral" << endl;
        //Executes the order
        targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()*3);
        targetTerritory->setPlayer(neutralPlayer);
        for (vector<Territory*>::const_iterator it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it)
        {
            if (targetTerritory == *it)
            {
                ownedTerritories->erase(it);
            }
        }
    }
    //Otherwise, sends an error message
    else
    {
        cout << "This order cannot be executed." << endl;
    }
    Notify(this);
}

//Implementation of Airlift
//Default Constructor
Airlift::Airlift():Order(NULL, NULL, "Airlift")
{
}
//4 args constructor
Airlift::Airlift(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr):
    Order(targetTerritory, ownedTerr, "Airlift")
{
    nMovedArmies = nOfArmies;
    sourceTerritory = sourceTerr;
}
//Copy Constructor
Airlift::Airlift(const Airlift& airLi):Order(airLi.targetTerritory, airLi.ownedTerritories, "Airlift")
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
    this->orderType = "Airlift";
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
string Airlift::stringToLog()
{
    return "Airlift Order executed: "+ std::to_string(nMovedArmies) + " armies are moved from the territory " + sourceTerritory->getName()
    + " to the territory " + targetTerritory->getName();;
}
//Implementation of validate
bool Airlift::validate()
{
    //If the pointers don't point to an existing object
    cout<<"In Airlift:\n";
    if(nMovedArmies == 0 || sourceTerritory == NULL || targetTerritory == NULL || ownedTerritories == NULL
       || sourceTerritory->getAmountOfArmies() < nMovedArmies || ownedTerritories->empty())
    {
        cout << "Wrong values" << endl;
        return false;
    }
    Player* pl = ownedTerritories->at(0)->getPlayer();

    if (pl == sourceTerritory->getPlayer() && pl == targetTerritory->getPlayer())
    {
        return true;
    }
    /*
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
    */
    //Otherwise return false
    cout<<"Neither territory is owned by player!";
    return false;
}
//Implementation of execute
void Airlift::execute()
{
    if (validate())
    {

        cout << "Airlift deployment of " << nMovedArmies << " armies! From " << *(sourceTerritory) << " To " << *(targetTerritory) << endl;
        targetTerritory->setAmountOfArmies(targetTerritory->getAmountOfArmies()+nMovedArmies);
        sourceTerritory->setAmountOfArmies(sourceTerritory->getAmountOfArmies()-nMovedArmies);
    }
    else
    {
        cout << "The order cannot be executed" << endl;
    }
    Notify(this);
}

//Negotiate Implementation
//Default Constructor
Negotiate::Negotiate():Order(NULL, NULL, "Negotiate")
{
}
//2 args constructor
Negotiate::Negotiate(Player* cPlayer, Player* tPlayer):Order(NULL, NULL, "Negotiate")
{
    callingPlayer = cPlayer;
    targetPlayer = tPlayer;
}

//Copy Constructor
Negotiate::Negotiate(const Negotiate& negotiate): Order(NULL, NULL, "Negotiate")
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
    this->orderType = "Negotiate";
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
    return "Negotiate: Between two players";
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
string Negotiate::stringToLog()
{
    return "Negotiate Order executed: the two players are now under a truce.";
}
//Implementation of validate
bool Negotiate::validate()
{
    //Checks if the pointers point to an existing object. If it is not, then it is not valid
    cout<<"In Negotiate:\n";
    if (callingPlayer == NULL || targetPlayer == NULL || callingPlayer == targetPlayer)
    {
        cout<<"Null values \n";
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
        //This expands the multidimensional array in order to add more entries
        if (indexOfEnd >= sizeOfPlCantAttList)
        {
            cout << "creating new list" << endl;
            //Creates a new multidimensional array
            Player*** newPlCantAttList;
            newPlCantAttList = new Player**[sizeOfPlCantAttList*2];
            for (int i = 0; i < sizeOfPlCantAttList * 2; i++)
            {
                newPlCantAttList[i] = new Player*[2];
                if (i < indexOfEnd)
                {
                    newPlCantAttList[i][0] = playersCannotAttackList[i][0];
                    newPlCantAttList[i][1] = playersCannotAttackList[i][1];
                }
                else
                {
                    newPlCantAttList[i][0] = NULL;
                    newPlCantAttList[i][1] = NULL;
                }
            }
            for (int i = 0; i < sizeOfPlCantAttList; i++)
            {
                delete [] playersCannotAttackList[i];
            }
            delete [] playersCannotAttackList;
            playersCannotAttackList = newPlCantAttList;
            sizeOfPlCantAttList *= 2;
        }
        playersCannotAttackList[indexOfEnd][0] = callingPlayer;
        playersCannotAttackList[indexOfEnd][1] = targetPlayer;
        indexOfEnd++;
        cout << "Negotiation have been settled between the two players" << endl;
        /*
        set<Player*> setPl{};
        setPl.insert(targetPlayer);
        setPl.insert(callingPlayer);
        plrsCantAttackList->insert(setPl);
        */
    }
    else
    {
        cout << "The order cannot be executed." << endl;
    }
    Notify(this);
}

