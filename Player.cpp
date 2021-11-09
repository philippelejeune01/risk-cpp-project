#include "Player.h"
#include "Card.h"
#include "Orders.h"
#include "Map.h"
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
    name = "Player Default";
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
}
//1 arg Constructor
Player::Player(string newName)
{
    name = newName;
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
}
//2 arg Constructors
Player::Player(string newName, OrdersList* ordList)
{
    name = newName;
    hand = new Hand();
    ordersList = ordList;
    flagConqTerr = new bool(false);
}
Player::Player(string newName, Hand* aHand)
{
    name = newName;
    hand = aHand;
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
}
Player::Player(string newName, vector <Territory*> &terr)
{
    name = newName;
    territories = terr;
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
}

//3 arg Constructors
Player::Player(string newName, Hand* aHand, OrdersList* ordList)
{
    name = newName;
    hand = aHand;
    ordersList = ordList;
    flagConqTerr = new bool(false);
}
Player::Player(string newName, vector <Territory*> &terr, OrdersList* ordList)
{
    name = newName;
    territories = terr;
    hand = new Hand();
    ordersList = ordList;
    flagConqTerr = new bool(false);
}
Player::Player(string newName, vector <Territory*> &terr, Hand* aHand)
{
    name = newName;
    territories = terr;
    hand = aHand;
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
}

//Copy Constructor
Player::Player(const Player& pl)
{
    name = pl.name;
    territories = pl.territories;
    hand = pl.hand;
    ordersList = pl.ordersList;
    flagConqTerr = pl.flagConqTerr;
}

//Destructor
Player::~Player()
{
    //This deletes all the Territory objects stored in the vector
    for(vector<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it)
    {
        delete *it;
    }
    //This erases all the pointers stored in the vector
    territories.clear();

    delete hand;
    hand = NULL;
    delete ordersList;
    ordersList = NULL;
    delete flagConqTerr;
    flagConqTerr = NULL;
}

//Assignment operator overload
Player& Player :: operator = (const Player& pl)
{
    this->name = pl.name;
    this->territories = pl.territories;
    this->hand = pl.hand;
    this->ordersList = pl.ordersList;
    this->flagConqTerr = pl.flagConqTerr;
    return *this;
}

//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Player &aPlayer)
{
    strm << "Player named \"" << aPlayer.name << "\"";

    if(!aPlayer.getTerritories().empty()){
        strm << "\nTerritories: ";

        for(auto x: aPlayer.getTerritories())
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

int Player::getPool() const
{
    return rPool;
}

bool Player::getFlagConqTerr()
{
    return *flagConqTerr;
}
//This is a method for testing purposes.
vector<Territory*>* Player::getPointerToTerritories()
{
     return &territories;
}

void Player::setPool(int numberOfArmies)
{
    rPool = numberOfArmies;
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

void Player::setFlagConqTerr(bool flag)
{
    *flagConqTerr = flag;
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


//Required Methods

//Returns Territories which are adjacent and not the current player's territory
vector <Territory*> Player::toAttack()
{
    set<Territory*> uniqueTerritoriesToAttack;
    string adjTerritoryName;
    bool attackTerr;

    for(int i = 0; i < territories.size(); i++){
        if(!territories[i]->adjacentTerritories.empty()){
            for(int j = 0; j < territories[i]->adjacentTerritories.size(); j++){
                attackTerr = true;
                adjTerritoryName = territories[i]->adjacentTerritories[j]->getName();

                for(int k = 0; k < territories.size(); k++){
                    if(adjTerritoryName == territories[k]->getName()){
                        attackTerr = false;
                        break;
                    }
                }

                if(attackTerr){
                    uniqueTerritoriesToAttack.insert(territories[i]->adjacentTerritories[j]);
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
void setPlayersTerritories(vector <Territory*> allTerritories, vector <Player*> allPlayers)
{

    int territoryCount = allTerritories.size();
    int playerCount = allPlayers.size();

    int subLength = territoryCount / playerCount;
    int remainder = territoryCount % playerCount;
    int limit = min(playerCount, territoryCount);

    int startIndex = 1; //Start index is one because the first element in allTerritories is always null
    int endIndex = 0;

    for(int i = 0; i < limit; ++i) {
        endIndex += (remainder > 0) ? (subLength + !!(remainder--)) : subLength;

        vector <Territory*> subTerritories(allTerritories.begin() + startIndex, allTerritories.begin() + endIndex);
        allPlayers.at(i)->setTerritories(subTerritories);

        startIndex = endIndex;
    }

}
