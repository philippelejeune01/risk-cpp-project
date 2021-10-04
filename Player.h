#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <list>

using namespace std;


class Territories
{
    public:
        Territories();
        Territories(int);
        int id;


    private:

};

class Hand
{
    public:
        Hand();
//        Hand(vector<Card*> cards);


    private:


};

class OrdersList
{
    public:
        OrdersList();
        list <string> orders;
        string type;


    private:

};


class Player
{
    public:
        Player();
        Player (Hand &aHand);
        Player(vector <Territories> &terr, Hand &aHand);
        ~Player();

        vector <Territories*> toDefend();
        vector <Territories*> toAttack();
        void issueOrder(OrdersList* ordersList, string orderType);

        vector <Territories*> getTerritories() const;
        void setTerritories(vector <Territories*> &terr);

        Hand* getHand() const;
//        void setHand(vector<Card*> cards);

        OrdersList* getOrderList() const;

        static int getPlayerCount();


    private:
        static int playerCount;
        vector <Territories*> territories;
        Hand* hand;
        OrdersList* ordersList;

};

void setPlayersTerritories(vector <Territories*> allTerritories, vector <Player*> allPlayers, int playerCount);
//vector<vector<Territories*>> splitTerritories(vector <Territories*> allTerritories, int playerCount);

#endif // PLAYER_H
