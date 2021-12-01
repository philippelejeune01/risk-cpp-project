#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "GameEngine.h"
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

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p)
{
    player = p;
}

void BenevolentPlayerStrategy::issueOrder()
{
    srand (time(NULL));
    //Refers to the player having cards in their hand
    bool isHandEmpty = player->getHand()->getCards()->empty();
    bool* flagOrder;
    vector <Territory*>* territoriesToDefend = toDefend();
    Order* ord;
    Order* defendAdvanceOrd;
    Card* card;
    //Generate random number indicating the random index to choose in the list of territories to defend
    int randIndexDefend = rand() % territoriesToDefend->size();
    //Generate random number indicating the random index to choose in the player's territories
    int randIndexSource = rand() % player->territories->size();

    //Number of armies to use in an advance order
    int randNOfArmies = player->determineNArmiesForAttack(randIndexSource);

    //If player has cards in his hand, select the first card to create an order (non-attacking orders)
    if(!isHandEmpty)
    {
        flagOrder = new bool(true);
        player->setFlagIssueOrder(flagOrder);

        //Get the first card in the player's hand
        card = player->getHand()->getCards()->front();

        if (card->getType().compare("airlift") == 0)
        {
            Order* ord = new Airlift(territoriesToDefend->at(randIndexDefend),player->territories,randNOfArmies,player->territories->at(randIndexSource));
            player->ordersList->addOrder(ord);
        }
        if (card->getType().compare("reinforcement") == 0)
        {
            int n = 5;
            Order*  ord = new Deploy(territoriesToDefend->at(randIndexDefend), player->territories, n);
            player->ordersList->addOrder(ord);
        }
        if (card->getType().compare("diplomacy") == 0)
        {
            //Generate random number indicating the random index to choose in the list of Players
            int randIndexPlayer = rand() % GameEngine::players->size();

            Order* ord = new Negotiate(player , GameEngine::players->at(randIndexPlayer));
            player->ordersList->addOrder(ord);
        }
        if (card->getType().compare("blockade") == 0)
        {
            Order* ord = new Blockade(territoriesToDefend->at(randIndexDefend),player->territories);
            player->ordersList->addOrder(ord);
        }
        if (card->getType().compare("bomb") == 0)
        {
            cout << "Cannot an attacking order when the player is a Benevolent Player" << endl;
        }
        //Remove first card in Hand
        player->getHand()->removeCard(0);


        /*====Creating Advance orders====*/

        //Find the index of one of the territories returned by toDefend() in the player's territories vector
        string terrDefendName = territoriesToDefend->at(0)->getName();
        for (vector<Territory*>::iterator it = player->territories->begin(); it != player->territories->end(); ++it)
        {
            if((*it)->getName() == terrDefendName)
            {
                auto index = distance(player->territories->begin(), it);
                randIndexSource = index;
            }
        }

        //Re-determine the number of armies to use in an advance order
        randNOfArmies = player->determineNArmiesForAttack(randIndexSource);

        if(randNOfArmies != 0)
        {
            /*Create advance order to defend*/
            if(territoriesToDefend->at(randIndexDefend)->getName() == player->territories->at(randIndexSource)->getName())
            {
                defendAdvanceOrd = new Advance(territoriesToDefend->at(randIndexDefend), player->territories, randNOfArmies, player->territories->at(randIndexSource));
            }
            else
            {
                defendAdvanceOrd = new Advance(territoriesToDefend->at(randIndexDefend), player->territories, randNOfArmies, player->territories->at(randIndexSource));
            }
            //Adding order to the end of the list
            player->ordersList->addOrder(defendAdvanceOrd);
            //ordersList->move(defendAdvanceOrd, ordersList->getOrdList().size());
            cout << "Created a " << defendAdvanceOrd->getOrderType() << " order (to defend) and placed it in the player's OrderList" << endl;
        }
        else
        {
            defendAdvanceOrd = NULL;
            cout << "Cannot create advance order (to defend) - No armies in source territory " << player->territories->at(randIndexSource)->getName() << "\n" << endl;
        }

    }
    else
    {
        flagOrder = new bool(false);
        player->setFlagIssueOrder(flagOrder);
        cout << "No more orders to issue\n" << endl;
    }

    cout << this << endl;
}

//Returns Territories which are adjacent and not the current player's territory
vector<Territory*>* BenevolentPlayerStrategy::toAttack()
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

//Returns territories owned by the player that are the top 3 weakest.
vector<Territory*>* BenevolentPlayerStrategy::toDefend()
{
    vector <Territory*>* weakestTerritories;
    vector <Territory*>* territoriesToDefend(player->territories);

    //sort vector by the number of armies in a territory (ascending)
    sort(territoriesToDefend->begin(), territoriesToDefend->end(), [](Territory* a, Territory* b){ return a->getAmountOfArmies() < b->getAmountOfArmies(); });

    for(int i = 0; i < 3; i++)
    {
        weakestTerritories->push_back(territoriesToDefend->at(i));
    }

    return territoriesToDefend;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p)
{
    player = p;
}

void NeutralPlayerStrategy::issueOrder()
{

}

vector<Territory*>* NeutralPlayerStrategy::toAttack()
{

}

vector<Territory*>* NeutralPlayerStrategy::toDefend()
{

}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p)
{
    player = p;
}

void CheaterPlayerStrategy::issueOrder()
{

}

vector<Territory*>* CheaterPlayerStrategy::toAttack()
{

}

vector<Territory*>* CheaterPlayerStrategy::toDefend()
{

}
