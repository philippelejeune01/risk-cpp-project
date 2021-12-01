#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "GameEngine.h"
#include "Map.h"
#include <set>
#include <vector>
PlayerStrategy::~PlayerStrategy()
{
    player = NULL;
}
HumanPlayerStrategy::HumanPlayerStrategy(Player* p)
{
    player = p;
}

void HumanPlayerStrategy::issueOrder()
{
    string order;
    char output;
    cout<<"would you like to see the info for this player? [y/n]\n";
    cin>>output;
    if (output=='y')
        cout<<*player;
    do
    {
        cout<<"Enter Player's Order: [reinforce,advance,card], enter stop to finish:\n";
        cin>>order;
        if (order == "reinforce")
        {
            int n,index;
            string name;
            cout<<"Which territory?\n";
            cin>>name;
            index = player->doesOwn(name);
            if (index == -1)
            {
                cout<<"Not owned territory,invalid order\n";
                continue;
            }
            cout<<"How many armies?\n";
            cin>>n;
            if (n<=player->getPool())
            {
                Order*  ord = new Deploy(player->getTerritories()->at(index), player->getTerritories(), n);
                player->getOrderList()->addOrder(ord);
                player->removeFromPool(n);
            }
            else
                cout<<"Invalid order\n";
        }

        if (order == "advance")
        {
            int n,index1,index2=-1;
            string name;
            cout<<"From Which territory?\n";
            cin>>name;
            index1 = player->doesOwn(name);
            cout<<"To?\n";
            cin>>name;
            for (int i = 0;i<GameEngine::_map->territories->size();i++)
                if (GameEngine::_map->territories->at(i)->getName()==name)
                {
                    index2 = i;
                    if (index2 == index1) index2 = -1;
                    break;
                }
            if (index1 == -1 || index2 == -1)
            {
                cout<<"invalid order\n";
                continue;
            }
            cout<<"How many armies?\n";
            cin>>n;
            Order* ord = new Advance(GameEngine::_map->territories->at(index2),player->getTerritories(),n,player->getTerritories()->at(index1));
            player->ordersList->addOrder(ord);
        }
        if (order == "card")
        {
            if (player->getHand()->getCards()->size()==0)
            {
                cout<<"This player has no card!\n";
                continue;
            }
            string card;
            cout<<"Which Card would you like to use?\n";
            cin>>card;
            int found = -1;
            for (int i = 0; i<player->getHand()->getCards()->size();i++)
                if (player->getHand()->getCards()->at(i)->getType()==card)
                {
                    found = i;
                    break;
                }
            if (found == -1)
            {
                cout<<"You do not own this card!\n";
                continue;
            }
            if (card=="bomb")
            {
                string name;
                int index;
                cout<<"Which territory?\n";
                cin>>name;
                for (int i = 0;i<GameEngine::_map->territories->size();i++)
                    if (GameEngine::_map->territories->at(i)->getName()==name)
                    {
                        index = i;
                        break;
                    }
                if (player->doesOwn(name)!=-1)
                {
                    cout<<"You cannot bomb your own territory\n";
                    continue;
                }
                Order* ord = new Bomb(GameEngine::_map->territories->at(index),player->territories);
                player->ordersList->addOrder(ord);
            }
            if (card=="airlift")
            {
                int n,index1,index2=-1;
                string name;
                cout<<"From Which territory?\n";
                cin>>name;
                index1 = player->doesOwn(name);
                cout<<"To?\n";
                cin>>name;
                index2 = player->doesOwn(name);
                if (index1 == -1 || index2 == -1)
                {
                    cout<<"invalid order\n";
                    continue;
                }
                cout<<"How many armies?\n";
                cin>>n;
                Order* ord = new Airlift(player->territories->at(index2),player->territories,n,player->territories->at(index1));
                player->ordersList->addOrder(ord);
            }
            if (card=="reinforcement")
            {
                int n = 5,index;
                string name;
                cout<<"On which territory?\n";
                cin>>name;
                index = player->doesOwn(name);
                if (index == -1)
                {
                    cout<<"invalid order\n";
                    continue;
                }
                Order*  ord = new Deploy(player->territories->at(index), player->territories, n);
                player->ordersList->addOrder(ord);
            }
            if (card=="deplomacy")
            {
                Player* target;
                string pname;
                cout<<"Enter the name of the player that you wanna enforce a truce with:\n";
                cin>>pname;
                for (int i=0;i<GameEngine::players->size();i++)
                    if (GameEngine::players->at(i)->getName() == pname)
                    {
                        target = GameEngine::players->at(i);
                        break;
                    }
                if (target == player)
                {
                    cout<<"invalid order\n";
                    continue;
                }
                Order* ord = new Negotiate(player , target);
                player->ordersList->addOrder(ord);
            }
            if (card=="blockade")
            {
                string name;
                int index;
                cout<<"Where would you like to Blockade?\n";
                cin>>name;
                index = player->doesOwn(name);
                if (index == -1)
                {
                    cout<<"Not owned territory,invalid order\n";
                    continue;
                }
                Order* ord = new Blockade(player->territories->at(index),player->territories);
                player->ordersList->addOrder(ord);
            }
            player->getHand()->removeCard(found);
        }
        if (order == "stop") break;
    }
    while (true);
}

vector<Territory*>* HumanPlayerStrategy::toAttack()
{
    set<Territory*> uniqueTerritoriesToAttack;
    string adjTerritoryName;
    bool attackTerr;

    for(int i = 0; i < player->territories->size(); i++)
    {
        if(!player->territories->at(i)->adjacentTerritories->empty())
        {
            for(int j = 0; j < player->territories->at(i)->adjacentTerritories->size(); j++)
            {
                attackTerr = true;
                adjTerritoryName = player->territories->at(i)->adjacentTerritories->at(j)->getName();

                if (player->doesOwn(adjTerritoryName)!=-1)
                    attackTerr = false;

                if(attackTerr){
                        //Set the target territory to be attacked
                    player->territories->at(i)->adjacentTerritories->at(j)->setAttackStatus(attackTerr);
                    uniqueTerritoriesToAttack.insert(player->territories->at(i)->adjacentTerritories->at(j));
                }
            }
        }
    }
    vector<Territory*>* territoriesToAttack=new vector<Territory*>(uniqueTerritoriesToAttack.begin(), uniqueTerritoriesToAttack.end());
    return territoriesToAttack;
}

vector<Territory*>* HumanPlayerStrategy::toDefend()
{
    return player->territories;
}

HumanPlayerStrategy::~HumanPlayerStrategy()
{
    player = NULL;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p)
{
    player = p;
}

void AggressivePlayerStrategy::issueOrder()
{

}

vector<Territory*>* AggressivePlayerStrategy::toAttack()
{

}

vector<Territory*>* AggressivePlayerStrategy::toDefend()
{

}

AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
    player = NULL;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p)
{
    player = p;
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
    player = NULL;
}

void BenevolentPlayerStrategy::issueOrder()
{

}

vector<Territory*>* BenevolentPlayerStrategy::toAttack()
{

}

vector<Territory*>* BenevolentPlayerStrategy::toDefend()
{

}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p)
{
    player = p;
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
    player = NULL;
}

void NeutralPlayerStrategy::issueOrder()
{
    cout << "I do nothing.\n";
    //Does Nothing
}

vector<Territory*>* NeutralPlayerStrategy::toAttack()
{
    return NULL;
}

vector<Territory*>* NeutralPlayerStrategy::toDefend()
{
    return NULL;
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p)
{
    player = p;
}

CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
    player = NULL;
}

void CheaterPlayerStrategy::issueOrder()
{
    //using the toAttack method, we get all the territories adjacent to the cheater player's territories
    vector<Territory*>* territoriesToAssimilate;
    territoriesToAssimilate = this->toAttack();
    //This loop iterates through the territoriesToAssimilate to add all the Territory objects
    for (int i = 0; i < territoriesToAssimilate->size(); i++)
    {
        //Gets a pointer to an adjacent enemy territory
        Territory* terrToConquer = territoriesToAssimilate->at(i);
        //Gets a pointer to the list of oldEnemyTerritory
        vector<Territory*>* oldEnemyTerritories;
        oldEnemyTerritories = terrToConquer->getPlayer()->getPointerToTerritories();
        //Removes the territory from its old owner
        if (oldEnemyTerritories != NULL && !oldEnemyTerritories->empty())
        {
            for (vector<Territory*>::iterator it = oldEnemyTerritories->begin();it != oldEnemyTerritories->end();++it)
            {
                if (*it == terrToConquer)
                {
                    oldEnemyTerritories->erase(it);
                    break;
                }
            }
        }
        //Adds the territory to the cheater player's territory.
        terrToConquer->setPlayer(this->player);
        player->territories->push_back(terrToConquer);
    }
    cout<<"Issued Orders"<<endl;
    //Deallocates the memory taken by the vector
    //territoriesToAssimilate->clear();
    //delete territoriesToAssimilate;
}

//To attack will get all the adjacent enemy territories
vector<Territory*>* CheaterPlayerStrategy::toAttack()
{
    string adjTerritoryName;
    bool attackTerr;
    for(int i = 0; i < player->territories->size(); i++)
    {
        if(!player->territories->at(i)->adjacentTerritories->empty())
        {
            for(int j = 0; j < player->territories->at(i)->adjacentTerritories->size(); j++)
            {
                attackTerr = true;
                adjTerritoryName = player->territories->at(i)->adjacentTerritories->at(j)->getName();

                if (player->doesOwn(adjTerritoryName)!=-1)
                    attackTerr = false;

                if(attackTerr){
                        //Set the target territory to be attacked
                    player->territories->at(i)->adjacentTerritories->at(j)->setAttackStatus(attackTerr);
                    uniqueTerritoriesToAttack.insert(player->territories->at(i)->adjacentTerritories->at(j));
                }
            }
        }
    }
    territoriesToAttack=new vector<Territory*>(uniqueTerritoriesToAttack.begin(), uniqueTerritoriesToAttack.end());
    return territoriesToAttack;
}

vector<Territory*>* CheaterPlayerStrategy::toDefend()
{
    return NULL;
}
