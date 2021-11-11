#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

class Player;
class Territory
{
    public:
        Player* ownedplayer;
        string name;
        int xCoordinate,yCoordinate,continentNumber;
        int TerritoryNumber;
        bool isUnderAttack;
        vector<Territory*> adjacentTerritories;
        void setTerritoryNum(int t);
        int getTerritoryNum();
        bool isAdjacentTo(Territory &t2);
        Territory(int tnum,int x,int y,int c,int num,Player* ownedP, string n);
        Territory();
        ~Territory();
        friend ostream& operator <<(ostream &strm, const Territory &terr);
        string getName();
        void setName(string n);
        int getContinent();
        void setContinent(int c);
        void setCoordinates(int x,int y);
        void setPlayer(Player* p);
        Player* getPlayer();
        void setAmountOfArmies(int nOfArmies);
        int getAmountOfArmies();
        bool isTerritoryUnderAttack();
        void setAttackStatus(bool attack);

    private:
        int amountOfArmies;
};

class Map
{
    public:
        Map(vector<int>* adjacency,vector<Territory*> listOfTerritories,int nOfContinents,int nOfTerritories,int endOf[]);
        Map(const Map& m);
        Map();

        void setAdjacency(vector<int>* adjacency);
        void setTerritories(vector<Territory*> territories);
        bool doesPlayerOwnAllTerritories(int cnum,Player* player);
        vector <Territory*> getTerritories() const;
        void setNumberOfContinents(int n);
        void setNumberOfTerritories(int n);
        void setEndOfContinents(const int *arr);
        bool isAdjacentto(Territory t1, Territory t2);
        bool validate();
        int* getEndOfContinents();
        int getNumberOfContinents();
        Map& operator =(const Map& m);
        friend ostream& operator<<(ostream &strm, Map &m);
        ~Map();

    protected:
        int numOfTerritories, numOfContinents;
        vector<int>* adjacencyList;
        vector<Territory*> territories;
        int endofContinents[100];

};
class MapLoader
{
    public:
        MapLoader(string filepath);
        Map Load();
    private:
        string filepath;

};

#endif // MAP_H
