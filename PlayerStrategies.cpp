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
                Order* ord = new Bomb(GameEngine::_map->territories->at(index),player->getPointerToTerritories());
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
                Order* ord = new Airlift(player->getPointerToTerritories()->at(index2),player->getPointerToTerritories(),n,player->getPointerToTerritories()->at(index1));
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
                Order*  ord = new Deploy(player->getPointerToTerritories()->at(index), player->getPointerToTerritories(), n);
                player->ordersList->addOrder(ord);
            }
            if (card=="diplomacy")
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
                Order* ord = new Blockade(player->getPointerToTerritories()->at(index),player->getPointerToTerritories());
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

    for(int i = 0; i < player->getPointerToTerritories()->size(); i++)
    {
        if(!player->getPointerToTerritories()->at(i)->adjacentTerritories->empty())
        {
            for(int j = 0; j < player->getPointerToTerritories()->at(i)->adjacentTerritories->size(); j++)
            {
                attackTerr = true;
                adjTerritoryName = player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j)->getName();

                if (player->doesOwn(adjTerritoryName)!=-1)
                    attackTerr = false;

                if(attackTerr){
                        //Set the target territory to be attacked
                    player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j)->setAttackStatus(attackTerr);
                    uniqueTerritoriesToAttack.insert(player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j));
                }
            }
        }
    }
    vector<Territory*>* territoriesToAttack=new vector<Territory*>(uniqueTerritoriesToAttack.begin(), uniqueTerritoriesToAttack.end());
    return territoriesToAttack;
}

vector<Territory*>* HumanPlayerStrategy::toDefend()
{
    return player->getPointerToTerritories();
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
    //get strongest territory on border
    int maxAmountOfArmies = 0;
    Territory* strongestTerritory;
    for(int i=0; player->getTerritories()->size(); i++){

        string territoryName = player->getTerritories()->at(i)->getName();
        bool hasAnAdjacentNonOwned = false;
        //checks if the territory has a not owned adjacent territory
        for(int j =0;j<player->getTerritories()->at(i)->adjacentTerritories->size();j++){
            if(!player->doesOwn(player->getTerritories()->at(i)->adjacentTerritories->at(j)->getName())){
                hasAnAdjacentNonOwned = true;
            }
        }

        if(player->getTerritories()->at(i)->getAmountOfArmies() > maxAmountOfArmies && hasAnAdjacentNonOwned){
            maxAmountOfArmies = player->getTerritories()->at(i)->getAmountOfArmies();
            strongestTerritory = player->getTerritories()->at(i);
        }
    }
    //safeguard for null pointer
    if(strongestTerritory==NULL){
        strongestTerritory = player->getTerritories()->at(0);
    }

    //reinforce with all the pool there
    Order* deployOrder = new Deploy(strongestTerritory, player->getTerritories(), player->getPool());
    player->setPool(0);
    player->getOrderList()->addOrder(deployOrder);

    //advance all territory to strongest
    for(int i=0; player->getTerritories()->size(); i++){
        if(player->getTerritories()->at(i) != strongestTerritory){
            int armies = player->getTerritories()->at(i)->getAmountOfArmies();
            //only advance from armies for territories with more than 1 army
            if(armies>1){
                Order* advanceOrder = new Advance(strongestTerritory, player->getTerritories(), armies-1, player->getTerritories()->at(i));
                player->getOrderList()->addOrder(advanceOrder);
            }
        }
    }



}

vector<Territory*>* AggressivePlayerStrategy::toAttack()
{
    //get strongest territory
    int maxAmountOfArmies = 0;
    Territory* strongestTerritory;
    for(int i=0; player->getTerritories()->size(); i++){
        if(player->getTerritories()->at(i)->getAmountOfArmies() > maxAmountOfArmies){
            maxAmountOfArmies = player->getTerritories()->at(i)->getAmountOfArmies();
            strongestTerritory = player->getTerritories()->at(i);
        }
    }

    vector<Territory*>* territoriesToAttack = new vector<Territory*>;
    territoriesToAttack->push_back(strongestTerritory->adjacentTerritories->at(0));
    return territoriesToAttack;

}

vector<Territory*>* AggressivePlayerStrategy::toDefend()
{
    return NULL;
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
    srand (time(NULL));
    int numberPlayers = GameEngine::players->size();
    //Refers to the player having cards in their hand
    bool isHandEmpty = player->getHand()->getCards()->empty();
    vector <Territory*>* territoriesToDefend = toDefend();
    //Generate random number indicating the random index to choose in the list of territories to defend
    int randIndexDefend = rand() % territoriesToDefend->size();
    //Generate random number indicating the random index to choose in the player's territories
    int randIndexSource = rand() % player->getPointerToTerritories()->size();
    //Determine if player has more orders to issue.
    if(player->getPool() != 0 || !isHandEmpty)
    {
        player->setFlagIssueOrder(true);
    }
    else
    {
        player->setFlagIssueOrder(false);
    }

    //Create deploy orders if player has armies in its reinforcement pool
    if(player->getPool() != 0)
    {
        player->createDeployOrders(territoriesToDefend);
        cout << "Created Deploy Orders" << endl;
    }

    //Number of armies to use in an advance order
    int randNOfArmies = player->determineNArmiesForAttack(randIndexSource);

    //If player has cards in his hand, select the first card to create an order (non-attacking orders)
    if(!isHandEmpty)
    {
        if (player->getHand()->getCards()->front()->getType().compare("airlift") == 0)
        {
            Order* ord = new Airlift(territoriesToDefend->at(randIndexDefend),player->getPointerToTerritories(),randNOfArmies,player->getPointerToTerritories()->at(randIndexSource));
            player->ordersList->addOrder(ord);
            cout << "Created an " << ord->getOrderType() << " order and placed it in the player's OrderList" << endl;
        }
        if (player->getHand()->getCards()->front()->getType().compare("reinforcement") == 0)
        {
            int n = 5;
            Order* ord = new Deploy(territoriesToDefend->at(randIndexDefend), player->getPointerToTerritories(), n);
            player->ordersList->addOrder(ord);
            cout << "Created a " << ord->getOrderType() << " order and placed it in the player's OrderList" << endl;
        }
        if (player->getHand()->getCards()->front()->getType().compare("diplomacy") == 0)
        {
            //Generate random number indicating the random index to choose in the list of Players
            int randIndexPlayer = rand() % numberPlayers;

            Order* ord = new Negotiate(player , GameEngine::players->at(randIndexPlayer));
            player->ordersList->addOrder(ord);
            cout << "Created a " << ord->getOrderType() << " order and placed it in the player's OrderList" << endl;
        }
        if (player->getHand()->getCards()->front()->getType().compare("blockade") == 0)
        {
            Order* ord = new Blockade(territoriesToDefend->at(randIndexDefend),player->getPointerToTerritories());
            player->ordersList->addOrder(ord);
            cout << "Created a " << ord->getOrderType() << " order and placed it in the player's OrderList" << endl;
        }
        if (player->getHand()->getCards()->front()->getType().compare("bomb") == 0)
        {
            cout << "Cannot issue an attacking order when the player is a Benevolent Player" << endl;
        }
        //Remove first card in Hand
        player->getHand()->removeCard(0);


        /*====Creating Advance orders====*/

        //Find the index of one of the territories returned by toDefend() in the player's territories vector
        string terrDefendName = territoriesToDefend->at(0)->getName();
        for (vector<Territory*>::iterator it = player->getPointerToTerritories()->begin(); it != player->getPointerToTerritories()->end(); ++it)
        {
            if((*it)->getName() == terrDefendName)
            {
                auto index = distance(player->getPointerToTerritories()->begin(), it);
                randIndexSource = index;
            }
        }

        //Re-determine the number of armies to use in an advance order
        randNOfArmies = player->determineNArmiesForAttack(randIndexSource);

        if(randNOfArmies != 0)
        {
            /*Create advance order to defend*/
            //If the territory to defend and the source territory are the same, then generate another random index which is not the same as randIndexDefend
            if(territoriesToDefend->at(randIndexDefend)->getName() == player->getPointerToTerritories()->at(randIndexSource)->getName())
            {
                 int newRandIndex;

                do
                {
                    newRandIndex = rand() % territoriesToDefend->size();
                }
                while(randIndexDefend == newRandIndex);
                randIndexDefend = newRandIndex;
                Order* defendAdvanceOrd = new Advance(territoriesToDefend->at(randIndexDefend), player->getPointerToTerritories(), randNOfArmies, player->getPointerToTerritories()->at(randIndexSource));
                //Adding order to the end of the list
                player->ordersList->addOrder(defendAdvanceOrd);
                cout << "Created an " << defendAdvanceOrd->getOrderType() << " order (to defend) and placed it in the player's OrderList\n" << endl;
            }
            else
            {
                Order* defendAdvanceOrd = new Advance(territoriesToDefend->at(randIndexDefend), player->getPointerToTerritories(), randNOfArmies, player->getPointerToTerritories()->at(randIndexSource));
                //Adding order to the end of the list
                player->ordersList->addOrder(defendAdvanceOrd);
                cout << "Created an " << defendAdvanceOrd->getOrderType() << " order (to defend) and placed it in the player's OrderList\n" << endl;
            }
        }
        else
        {
            cout << "Cannot create advance order (to defend) - No armies in source territory " << player->getPointerToTerritories()->at(randIndexSource)->getName() << "\n" << endl;
        }

    }
    else
    {
        cout << "No more orders to issue\n" << endl;
    }
}

//Returns Territories which are adjacent and not the current player's territory
vector<Territory*>* BenevolentPlayerStrategy::toAttack()
{
    set<Territory*> uniqueTerritoriesToAttack;
    string adjTerritoryName;
    bool attackTerr;

    for(int i = 0; i < player->getPointerToTerritories()->size(); i++)
    {
        if(!player->getPointerToTerritories()->at(i)->adjacentTerritories->empty())
        {
            for(int j = 0; j < player->getPointerToTerritories()->at(i)->adjacentTerritories->size(); j++)
            {
                attackTerr = true;
                adjTerritoryName = player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j)->getName();

                if (player->doesOwn(adjTerritoryName)!=-1)
                    attackTerr = false;

                if(attackTerr){
                        //Set the target territory to be attacked
                    player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j)->setAttackStatus(attackTerr);
                    uniqueTerritoriesToAttack.insert(player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j));
                }
            }
        }
    }
    vector<Territory*>* territoriesToAttack=new vector<Territory*>(uniqueTerritoriesToAttack.begin(), uniqueTerritoriesToAttack.end());
    return territoriesToAttack;
}

//Returns territories owned by the player that are the top 3 weakest.
vector<Territory*>* BenevolentPlayerStrategy::toDefend()
{
    vector <Territory*>* weakestTerritories = new vector<Territory*>();
    //sort vector by the number of armies in a territory (ascending)
    sort(player->getPointerToTerritories()->begin(), player->getPointerToTerritories()->end(), [](Territory* a, Territory* b){ return a->getAmountOfArmies() < b->getAmountOfArmies(); });
    for(int i = 0; i < 3; i++)
    {
        if (player->getPointerToTerritories()->size()>=(i+1))
            weakestTerritories->push_back(player->getPointerToTerritories()->at(i));
    }
    return weakestTerritories;
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
        player->getPointerToTerritories()->push_back(terrToConquer);
    }
    cout<<"Issued Orders"<<endl;
    //Deallocates the memory taken by the vector
    territoriesToAssimilate->clear();
}

//To attack will get all the adjacent enemy territories
vector<Territory*>* CheaterPlayerStrategy::toAttack()
{
    string adjTerritoryName;
    bool attackTerr;
    for(int i = 0; i < player->getPointerToTerritories()->size(); i++)
    {
        if(!player->getPointerToTerritories()->at(i)->adjacentTerritories->empty())
        {
            for(int j = 0; j < player->getPointerToTerritories()->at(i)->adjacentTerritories->size(); j++)
            {
                attackTerr = true;
                adjTerritoryName = player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j)->getName();

                if (player->doesOwn(adjTerritoryName)!=-1)
                    attackTerr = false;

                if(attackTerr){
                        //Set the target territory to be attacked
                    player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j)->setAttackStatus(attackTerr);
                    uniqueTerritoriesToAttack.insert(player->getPointerToTerritories()->at(i)->adjacentTerritories->at(j));
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
