#include "Player.h"
#include <iostream>
using namespace std;

// **Player Constructors**

Player::Player()
{
    playerCount++;
    OrdersList alist = OrdersList();
    this->ordersList = &alist;
}

//Player::Player(Hand &aHand)
//{
//    playerCount++;
//
//    this->hand = aHand;
//    OrdersList alist = OrdersList();
//    this->ordersList = &alist;
//}
//
//Player::Player(vector <Territories> &terr, Hand &aHand)
//{
//    playerCount++;
//    this->territories = terr;
//    this->hand = aHand;
//    OrdersList alist = OrdersList();
//    this->ordersList = &alist;
//}

// **Player Destructor**

Player::~Player()
{
    //TODO: Implement Destructor
}

//Initializing the playerCount to 0
int Player::playerCount = 0;

// **Player Accessors**

vector <Territories*> Player::getTerritories() const
{
    return territories;
}

Hand* Player::getHand() const
{
    return this->hand;
}

OrdersList* Player::getOrderList() const
{
    return this->ordersList;
}

int Player::getPlayerCount()
{
    return playerCount;
}

// **Player Mutators**

void Player::setTerritories(vector <Territories*> &terr)
{
    this->territories = terr;
}

//void Player::setHand(vector<Card*> cards)
//{
//    this->hand = Hand(cards);
//}


vector <Territories*> Player::toAttack()
{
    //TODO: Implement function
}

vector <Territories*> Player::toDefend()
{
    return this->getTerritories();
}

void Player::issueOrder(OrdersList* ordersList, string orderType)
{
    //TODO: Implement function
}

//This function splits the list of all territories into almost equal or equal parts depending on the number of players.
void setPlayersTerritories(vector <Territories*> allTerritories, vector <Player*> allPlayers, int playerCount)
{

    int territoryCount = allTerritories.size();
    cout << "territoryCount: " << territoryCount << endl;

    int subLength = territoryCount / playerCount;
    int remainder = territoryCount % playerCount;
    int limit = min(playerCount, territoryCount);

    int startIndex = 0;
    int endIndex = 0;

    for(int i = 0; i < limit; i++) {
        endIndex += (remainder > 0) ? (subLength + !!(remainder--)) : subLength;

        vector <Territories*> subTerritories(allTerritories.begin() + startIndex, allTerritories.begin() + endIndex);
        allPlayers.at(i)->setTerritories(subTerritories);

        startIndex = endIndex;
    }

}

//Splitting territories into almost equal parts depending on the number of players
//vector<vector<Territories*>> splitTerritories(vector <Territories*> allTerritories, int playerCount)
//{
//    vector<vector<Territories*>> listSplitTerritories;
//
//    int territoryCount = allTerritories.size();
//    cout << "territoryCount: " << territoryCount << endl;
//
//    int subLength = territoryCount / playerCount;
//    cout << "subLength: " << subLength << endl;
//    int remainder = territoryCount % playerCount;
//    cout << "remainder: " << remainder << endl;
//    int limit = min(playerCount, territoryCount);
//    cout << "limit: " << limit << endl;
//
//    int startIndex = 0;
//    int endIndex = 0;
//
//    for(int i = 0; i < limit; i++) {
//        endIndex += (remainder > 0) ? (subLength + !!(remainder--)) : subLength;
//        cout << "endIndex: " << endIndex << endl;
//
//        listSplitTerritories.push_back(vector <Territories*>(allTerritories.begin() + startIndex, allTerritories.begin() + endIndex));
//
//        startIndex = endIndex;
//    }
//    return listSplitTerritories;
//}

Territories::Territories(){}

Territories::Territories(int num)
{
    id = num;
}

OrdersList::OrdersList(){}

