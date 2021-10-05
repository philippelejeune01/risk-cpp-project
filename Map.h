#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Player.h"

using namespace std;


class Territory
{
    public:
        Player* ownedplayer;
        string name;
        int xCoordinate,yCoordinate,continentNumber;
        Territory(int x,int y,int c ,Player* ownedP, string n);
        Territory();
        string getName();
        void setName(string n);
        int getContinent();
        void setContinent(int c);
        void setCoordinates(int x,int y);
        void setPlayer(Player* p);
        Player* getPlayer();
};

class Map
{
    public:
        Map(vector<int>* adjacency,vector<Territory> listOfTerritories,int nOfContinents,int nOfTerritories,int endOf[]);
        Map(const Map& m);
        Map();

        void setAdjacency(vector<int>* adjacency);
        void setTerritories(vector<Territory> territories);
        void setNumberOfContinents(int n);
        void setNumberOfTerritories(int n);
        void setEndOfContinents(const int *arr);

        bool validate();
        Map& operator =(const Map& m);
        friend ostream& operator<<(ostream &strm, const Map &m);
        ~Map();

    protected:
        int numOfTerritories, numOfContinents;
        vector<int>* adjacencyList;
        vector<Territory> territories;
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
