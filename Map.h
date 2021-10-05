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
        void setNumberOfContinets(int n);
        void setNumberOfTerritories(int n);
        void setEndOfContinents(const int *arr);
        void Print();

        bool validate();
        void load(string filepath);

    //protected:
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
