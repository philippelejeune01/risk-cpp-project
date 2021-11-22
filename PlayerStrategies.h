#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H
#include <vector>
#include "Map.h"
class Player;
class PlayerStrategy
{
    public:
        Player* ps;
        virtual void issueOrder()=0;
        virtual vector<Territory*> toAttack()=0;
        virtual vector<Territory*> toDefend()=0;
};

class HumanPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

class AggressivePlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

class BenevolentPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

class NeutralPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};
class CheaterPlayerStrategy:public PlayerStrategy
{
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};
#endif
