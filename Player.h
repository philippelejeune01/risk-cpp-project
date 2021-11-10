
#ifndef PLAYER_H
#define PLAYER_H
#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class Player
{
    public:
        Player();
        Player(string newName);
        Player(string newName, Hand* aHand);
        Player(string newName, vector <Territory*> &terr);
        Player(string newName, vector <Territory*> &terr, Hand* aHand);
        Player(const Player& pl);
        Player& operator = (const Player& pl);
        ~Player();
        friend ostream& operator <<(ostream &strm, const Player &aPlayer);
        //Required Methods
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder(string ordType, Territory* targetTerritory, int nOfArmies);
        void issueOrder(string ordType, Territory* targetTerritory, int nOfArmies, Territory* sourceTerr);
        void issueOrder(string ordType, Territory* targetTerritory);
        void issueOrder(string ordType, Player* targetPlayer);
        //Accesors and Mutators
        string getName();
        void setName(string newName);
        vector <Territory*> getTerritories() const;
        void setTerritories(vector <Territory*> &terr);
        Hand* getHand() const;
        void setHand(Hand* h);
        OrdersList* getOrderList() const;
        void setOrderList(OrdersList* aOrdersList);
        static int getPlayerCount();


    private:
        string name;
        static int playerCount;
        //The player's territories
        vector <Territory*> territories;
        Hand* hand;
        OrdersList* ordersList;

};
//Global function to assign territories to player's
void setPlayersTerritories(vector <Territory*> allTerritories, vector <Player*> allPlayers, int playerCount);


#endif // PLAYER_H
