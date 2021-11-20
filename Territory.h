#ifndef TERRITORY_H
#define TERRITORY_H
#include "Player.h"
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
        Territory(const Territory& t);
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

    protected:
        int amountOfArmies;
};

#endif // TERRITORY_H_INCLUDED
