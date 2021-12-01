#include "Player.h"
#include "Card.h"
#include "Orders.h"
#include "Map.h"
#include "PlayerStrategies.h"
#include <time.h>
#include <iostream>
#include <set>
#include <vector>
#include <list>

using namespace std;

//**Player Implementation**
//Default Constructor
Player::Player()
{
    territories = new vector<Territory*>();
    name = "Player Default";
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
//1 arg Constructor
Player::Player(string newName)
{
    territories = new vector<Territory*>();
    name = newName;
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName,string strat)
{
    name = newName;
    territories = new vector<Territory*>();
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
    strategy = strat;
    if (strategy=="Human")      ps = new HumanPlayerStrategy(this);
    if (strategy=="Aggressive") ps = new AggressivePlayerStrategy(this);
    if (strategy=="Benevolent") ps = new BenevolentPlayerStrategy(this);
    if (strategy=="Neutral")    ps = new NeutralPlayerStrategy(this);
    if (strategy=="Cheater")    ps=  new CheaterPlayerStrategy(this);
}
//2 arg Constructors
string Player::getStrategy() const
{
    return strategy;
}
Player::Player(string newName, OrdersList* ordList)
{
    territories = new vector<Territory*>();
    name = newName;
    hand = new Hand();
    ordersList = ordList;
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, Hand* aHand)
{

    territories = new vector<Territory*>();
    name = newName;
    hand = aHand;
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, vector <Territory*>* terr)
{
    name = newName;
    territories = new vector<Territory*>();
    territories = terr;
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}

int Player::doesOwn(string name)
{
    int index = -1;
    for (int i = 0 ;i<territories->size();i++)
        if (territories->at(i)->getName()==name)
        {
            index = i;
            break;
        }
    return index;
}

//3 arg Constructors
Player::Player(string newName, Hand* aHand, OrdersList* ordList)
{
    name = newName;
    hand = aHand;
    ordersList = ordList;
    territories = new vector<Territory*>();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, vector <Territory*>* terr, OrdersList* ordList)
{
    name = newName;
    territories = terr;
    hand = new Hand();
    ordersList = ordList;
    territories = new vector<Territory*>();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, vector <Territory*> * terr, Hand* aHand)
{
    name = newName;
    territories = new vector<Territory*>();
    territories = terr;
    hand = aHand;
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}

//Copy Constructor
Player::Player(const Player& pl)
{
    this->name = pl.name;
    territories = new vector<Territory*>();
    this->strategy = pl.strategy;
    this->territories = pl.territories;
    this->hand =new Hand(*pl.hand);
    this->ordersList =new OrdersList(*pl.ordersList);
    this->flagConqTerr = pl.flagConqTerr;
    this->flagIssueOrder = pl.flagIssueOrder;
    if (strategy=="Human")      ps = new HumanPlayerStrategy(this);
    if (strategy=="Aggressive") ps = new AggressivePlayerStrategy(this);
    if (strategy=="Benevolent") ps = new BenevolentPlayerStrategy(this);
    if (strategy=="Neutral")    ps = new NeutralPlayerStrategy(this);
    if (strategy=="Cheater")    ps=  new CheaterPlayerStrategy(this);
}

//Destructor
Player::~Player()
{
    //This erases all the pointers stored in the vector
    territories->clear();

    delete hand;
    hand = NULL;
    delete ordersList;
    ordersList = NULL;
    delete flagConqTerr;
    flagConqTerr = NULL;
    delete flagIssueOrder;
    flagIssueOrder = NULL;
}

//Assignment operator overload
Player& Player :: operator = (const Player& pl)
{
    this->name = pl.name;
    territories = new vector<Territory*>();
    this->strategy = pl.strategy;
    this->territories = pl.territories;

    this->hand =new Hand(*pl.hand);
    this->ordersList =new OrdersList(*pl.ordersList);
    this->flagConqTerr = pl.flagConqTerr;
    this->flagIssueOrder = pl.flagIssueOrder;
    if (strategy=="Human")      ps = new HumanPlayerStrategy(this);
    if (strategy=="Aggressive") ps = new AggressivePlayerStrategy(this);
    if (strategy=="Benevolent") ps = new BenevolentPlayerStrategy(this);
    if (strategy=="Neutral")    ps = new NeutralPlayerStrategy(this);
    if (strategy=="Cheater")    ps=  new CheaterPlayerStrategy(this);
}

//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Player &aPlayer)
{
    strm << "Player named \"" << aPlayer.name << "\"";

    if(!aPlayer.getTerritories()->empty()){
        strm << "\nTerritories: ";

        for(auto x: *aPlayer.getTerritories())
        {
            strm << x->getName() << " ";
        }
    }else{
        strm << "\nTerritories: No Territories\n";
    }

    if(!aPlayer.getOrderList()->getOrdList().empty()){
        strm << "\nOrders: " << *aPlayer.getOrderList();
    }else{
        strm << "\nOrders: No Orders\n";
    }

    if(!aPlayer.getHand()->getCards()->empty()){
        strm << *aPlayer.getHand();
    }else{
        strm << "Hand: No Hand\n";
    }

    strm << "Player has " << aPlayer.getPool() << " armies in his reinforcement pool" <<endl;
    return strm;
}

//Accessors

vector <Territory*>* Player::getTerritories() const
{
    return territories;
}

Hand* Player::getHand() const
{
    return this->hand;
}
string Player::getName() const
{
    return name;
}
OrdersList* Player::getOrderList() const
{
    return ordersList;
}

int Player::getPool() const
{
    return rPool;
}

bool Player::getFlagConqTerr() const
{
    return *flagConqTerr;
}
bool Player::getFlagIssueOrder() const
{
    return *flagIssueOrder;
}
//This is a method for testing purposes.
vector<Territory*>* Player::getPointerToTerritories()
{
     return territories;
}

void Player::setPool(int numberOfArmies)
{
    rPool = numberOfArmies;
}

//Mutators

void Player::setTerritories(vector <Territory*>* terr)
{
    territories->clear();
    for (int i=0;i<terr->size();i++)
        territories->push_back(terr->at(i));
}

void Player::setOrderList(OrdersList* aOrdersList)
{
    ordersList = aOrdersList;
}

void Player::setHand(Hand* h)
{
    this->hand = h;
}

void Player::setFlagConqTerr(bool flag)
{
    *flagConqTerr = flag;
}

void Player::setFlagIssueOrder(bool flag)
{
    *flagIssueOrder = flag;
}

void Player::addToPool(int numberOfArmies)
{
    rPool += numberOfArmies;
}

bool Player::removeFromPool(int numberOfArmies)
{
    if((rPool - numberOfArmies) >= 0)
    {
        rPool -= numberOfArmies;
        return true; //Operation successful
    }
    else
    {
        return false; //Operation not successful
    }
}

//Creates Deploy orders on territories to defend as long as the reinforcement pool is not empty
void Player::createDeployOrders(vector <Territory*>* territoriesToDefend, Order* ord)
{
    int numberTerritoriesOwned = territoriesToDefend->size();
    //Number of armies to deploy for each territory
    int numberArmiesToDeploy = getPool() / numberTerritoriesOwned;
    int remainder = getPool() % numberTerritoriesOwned;
    //If there is a remainder, the last territory will be allocated more armies than others
    //to make sure the reinforcement pool is equal to 0 after everything has been deployed.
    int nArmiesToDeployLastTerritory = numberArmiesToDeploy + remainder;

    //Creating Deploy orders
    for(int i = 0; i < numberTerritoriesOwned; i++)
    {
        if(getPool() != 0)
        {
            if(getPool() == nArmiesToDeployLastTerritory)
            {
                removeFromPool(nArmiesToDeployLastTerritory);
                ord = new Deploy(territoriesToDefend->at(i), territories, nArmiesToDeployLastTerritory);
                ordersList->addOrder(ord);
                //ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
            }else
            {
                removeFromPool(numberArmiesToDeploy);
                ord = new Deploy(territoriesToDefend->at(i), territories, numberArmiesToDeploy);
                ordersList->addOrder(ord);
                //ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
            }
        }
    }
}

//Determines the number of armies to use in an attack/advance order.
//The number is a random number generated between 0 and the number of armies in a specific source territory
int Player::determineNArmiesForAttack(int randIndexSource)
{
    int randNOfArmies;
    //If deploy orders have not been executed yet, that means there are no armies in the territories right now.
    //To get the right number of armies we get it from the appropriate Deploy order if there is one.
    if(territories->at(randIndexSource)->getAmountOfArmies() == 0)
    {
        if(ordersList->getOrdList().size() > randIndexSource)
        {
            list<Order*>::iterator it = next(ordersList->getOrdList().begin(), randIndexSource);
            Deploy* deployOrder = dynamic_cast<Deploy*>((*it));
            if(deployOrder != NULL)
            {
                int nOfArmies = deployOrder->getNAddedArmies();
                //Generate random number between 1 and the number of armies from the source territory
                randNOfArmies = rand() % nOfArmies + 1;
            }
            else
            {
                randNOfArmies = 0;
            }
        }
        else
        {
            list<Order*>::iterator it = ordersList->getOrdList().begin();
            Deploy* deployOrder = dynamic_cast<Deploy*>((*it));
            if(deployOrder != NULL)
            {
                int nOfArmies = deployOrder->getNAddedArmies();
                //Generate random number between 1 and the number of armies from the source territory
                randNOfArmies = rand() % nOfArmies + 1;
            }
            else
            {
                randNOfArmies = 0;
            }
        }
    }
    else
    {
        randNOfArmies = rand() % territories->at(randIndexSource)->getAmountOfArmies() + 1;
    }
    return randNOfArmies;
}


//Required Methods

//Returns Territories which are adjacent and not the current player's territory
vector <Territory*>* Player::toAttack()
{
    return ps->toAttack();
}

//Returns territories owned by the player that are under attack.
//If no territories are under attack, return all territories owned by the player.
vector <Territory*>* Player::toDefend()
{
    return ps->toDefend();
}

//Creates an order based on the armies in the player's reinforcement pool and the player's hand. Then places the order in the player's list of orders
void Player::issueOrder()
{
    ps->issueOrder();
}


