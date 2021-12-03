#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H
#include <vector>
#include <set>
#include "Map.h"
class Player;
class PlayerStrategy
{
    public:
        Player* player;
        virtual void issueOrder()=0;
        virtual vector<Territory*>* toAttack()=0;
        virtual vector<Territory*>* toDefend()=0;
        virtual ~PlayerStrategy();
        set<Territory*> uniqueTerritoriesToAttack;
        vector<Territory*>* territoriesToAttack;
};

class HumanPlayerStrategy: public PlayerStrategy
{
    public:
        HumanPlayerStrategy(Player *p);
        void issueOrder();
        vector<Territory*>* toAttack();
        vector<Territory*>* toDefend();
        ~HumanPlayerStrategy();
};

class AggressivePlayerStrategy:public PlayerStrategy
{
    public:
        Territory* strongestTerritory;
        void issueOrder();
        AggressivePlayerStrategy(Player* p);
        vector<Territory*>* toAttack();
        vector<Territory*>* toDefend();
        ~AggressivePlayerStrategy();
};

class BenevolentPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        BenevolentPlayerStrategy(Player* p);
        vector<Territory*>* toAttack();
        vector<Territory*>* toDefend();
        ~BenevolentPlayerStrategy();
};

class NeutralPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        NeutralPlayerStrategy(Player* p);
        vector<Territory*>* toAttack();
        vector<Territory*>* toDefend();
        ~NeutralPlayerStrategy();
};
class CheaterPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        CheaterPlayerStrategy(Player* p);
        vector<Territory*>* toAttack();
        vector<Territory*>* toDefend();
        ~CheaterPlayerStrategy();
        set<Territory*> uniqueTerritoriesToAttack;
        vector<Territory*>* territoriesToAttack;
};
#endif
