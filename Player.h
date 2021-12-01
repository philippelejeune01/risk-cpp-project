#ifndef PLAYER_H
#define PLAYER_H
#include "Orders.h"
#include "PlayerStrategies.h"
#include "Card.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class Hand;
class Order;
class OrdersList;

class Player
{
    public:
        Player();
        Player(string newName);
        Player(string newName, string strategy);
        Player(string newName, OrdersList* ordList);
        Player(string newName, Hand* aHand);
        Player(string newName, vector <Territory*> *terr);

        Player(string newName, Hand* aHand, OrdersList* ordList);
        Player(string newName, vector <Territory*> *terr, OrdersList* ordList);
        Player(string newName, vector <Territory*> *terr, Hand* aHand);

        Player(const Player& pl);
        Player& operator = (const Player& pl);
        ~Player();
        friend ostream& operator <<(ostream &strm, const Player &aPlayer);
        //Required Methods
        vector <Territory*>* toDefend();
        vector <Territory*>* toAttack();
        void issueOrder();
        //Accesors and Mutators
        string getName() const;
        void setName(string newName);
        vector <Territory*>* getTerritories() const;
        void setTerritories(vector <Territory*> * terr);
        Hand* getHand() const;
        void setHand(Hand* h);
        OrdersList* getOrderList() const;
        void setOrderList(OrdersList* aOrdersList);
        bool getFlagConqTerr() const;
        void setFlagConqTerr(bool flag);
        bool getFlagIssueOrder() const;
        int doesOwn(string name);
        string getStrategy() const;
        void setFlagIssueOrder(bool flag);
        //This method is for testing purposes.
        vector<Territory*>* getPointerToTerritories();
        int getPool() const;
        void setPool(int numberOfArmies);
        void addToPool(int numberOfArmies);
        bool removeFromPool(int numberOfArmies);
        friend class HumanPlayerStrategy;
        friend class AggressivePlayerStrategy;
        friend class BenevolentPlayerStrategy;
        friend class CheaterPlayerStrategy;
        friend class NeutralPlayerStrategy;
        friend class PlayerStrategy;
    private:
        PlayerStrategy* ps;
        string name,strategy;
        //Determines if the player has more orders to issue
        bool* flagIssueOrder;
        //The player's reinforcement pool
        int rPool = 0;
        //The player's territories
        vector <Territory*>* territories;
        Hand* hand;
        OrdersList* ordersList;
        //bool pointer that determines if the player instance has conquered at least one territory
        bool* flagConqTerr;
        //Creates Deploy orders as long as the reinforcement pool is not empty
        void createDeployOrders(vector <Territory*>* territoriesToDefend);
        //Determines the number of armies to use in an attack order.
        int determineNArmiesForAttack(int randIndexSource);

};
//Global function to assign territories to player's

#endif // PLAYER_H
