#include "Player.h"
#include "Card.h"
#include "Orders.h"
#include "Map.h"
#include <time.h>
#include <iostream>
#include <set>
#include <vector>
#include <list>

using namespace std;

//**Player Implementation**
//Default Constructor
Player::Player()
{
    name = "Player Default";
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
//1 arg Constructor
Player::Player(string newName)
{
    name = newName;
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
//2 arg Constructors
Player::Player(string newName, OrdersList* ordList)
{
    name = newName;
    hand = new Hand();
    ordersList = ordList;
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, Hand* aHand)
{
    name = newName;
    hand = aHand;
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, vector <Territory*> &terr)
{
    name = newName;
    territories = terr;
    hand = new Hand();
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}

//3 arg Constructors
Player::Player(string newName, Hand* aHand, OrdersList* ordList)
{
    name = newName;
    hand = aHand;
    ordersList = ordList;
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, vector <Territory*> &terr, OrdersList* ordList)
{
    name = newName;
    territories = terr;
    hand = new Hand();
    ordersList = ordList;
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}
Player::Player(string newName, vector <Territory*> &terr, Hand* aHand)
{
    name = newName;
    territories = terr;
    hand = aHand;
    ordersList = new OrdersList();
    flagConqTerr = new bool(false);
    flagIssueOrder = new bool(true);
}

//Copy Constructor
Player::Player(const Player& pl)
{
    this->name = pl.name;
    this->territories = pl.territories;
    this->hand = pl.hand;
    this->ordersList = pl.ordersList;
    this->flagConqTerr = pl.flagConqTerr;
    this->flagIssueOrder = pl.flagIssueOrder;
}

//Destructor
Player::~Player()
{
    //This erases all the pointers stored in the vector
    territories.clear();

    delete hand;
    hand = NULL;
    delete ordersList;
    ordersList = NULL;
    delete flagConqTerr;
    flagConqTerr = NULL;
    flagIssueOrder = NULL;
}

//Assignment operator overload
Player& Player :: operator = (const Player& pl)
{
    this->name = pl.name;
    this->territories = pl.territories;
    this->hand = pl.hand;
    this->ordersList = pl.ordersList;
    this->flagConqTerr = pl.flagConqTerr;
    this->flagIssueOrder = pl.flagIssueOrder;
    return *this;
}

//Stream Insertion Operator
ostream& operator <<(ostream &strm, const Player &aPlayer)
{
    strm << "Player named \"" << aPlayer.name << "\"";

    if(!aPlayer.getTerritories().empty()){
        strm << "\nTerritories: ";

        for(auto x: aPlayer.getTerritories())
        {
            strm << x->getName() << " ";
        }
    }else{
        strm << "\nTerritories: No Territories\n";
    }

    if(!aPlayer.getOrderList()->getOrdList().empty()){
        strm << "\nOrders: " << *aPlayer.getOrderList();
    }else{
        strm << "\nOrders: No Orders\n";
    }

    if(!aPlayer.getHand()->getCards()->empty()){
        strm << *aPlayer.getHand();
    }else{
        strm << "Hand: No Hand\n";
    }

    strm << "Player has " << aPlayer.getPool() << " armies in his reinforcement pool" <<endl;
    return strm;
}

//Accessors

vector <Territory*> Player::getTerritories() const
{
    return territories;
}

Hand* Player::getHand() const
{
    return this->hand;
}

OrdersList* Player::getOrderList() const
{
    return ordersList;
}

int Player::getPool() const
{
    return rPool;
}

bool Player::getFlagConqTerr() const
{
    return *flagConqTerr;
}
bool Player::getFlagIssueOrder() const
{
    return *flagIssueOrder;
}
//This is a method for testing purposes.
vector<Territory*>* Player::getPointerToTerritories()
{
     return &territories;
}

void Player::setPool(int numberOfArmies)
{
    rPool = numberOfArmies;
}

//Mutators

void Player::setTerritories(vector <Territory*> &terr)
{
    territories = terr;
}

void Player::setOrderList(OrdersList* aOrdersList)
{
    ordersList = aOrdersList;
}

void Player::setHand(Hand* h)
{
    this->hand = h;
}

void Player::setFlagConqTerr(bool flag)
{
    *flagConqTerr = flag;
}

void Player::setFlagIssueOrder(bool flag)
{
    *flagIssueOrder = flag;
}

void Player::addToPool(int numberOfArmies)
{
    rPool += numberOfArmies;
}

bool Player::removeFromPool(int numberOfArmies)
{
    if((rPool - numberOfArmies) >= 0)
    {
        rPool -= numberOfArmies;
        return true; //Operation successful
    }
    else
    {
        return false; //Operation not successful
    }
}

//Creates Deploy orders on territories to defend as long as the reinforcement pool is not empty
void Player::createDeployOrders(vector <Territory*>* territoriesToDefend, Order* ord)
{
    int numberTerritoriesOwned = territoriesToDefend->size();
    //Number of armies to deploy for each territory
    int numberArmiesToDeploy = getPool() / numberTerritoriesOwned;
    int remainder = getPool() % numberTerritoriesOwned;
    //If there is a remainder, the last territory will be allocated more armies than others
    //to make sure the reinforcement pool is equal to 0 after everything has been deployed.
    int nArmiesToDeployLastTerritory = numberArmiesToDeploy + remainder;

    //Creating Deploy orders
    for(int i = 0; i < numberTerritoriesOwned; i++)
    {
        if(getPool() != 0)
        {
            if(getPool() == nArmiesToDeployLastTerritory)
            {
                removeFromPool(nArmiesToDeployLastTerritory);
                ord = new Deploy(territoriesToDefend->at(i), &territories, nArmiesToDeployLastTerritory);
                ordersList->addOrder(ord);
                //ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
            }else
            {
                removeFromPool(numberArmiesToDeploy);
                ord = new Deploy(territoriesToDefend->at(i), &territories, numberArmiesToDeploy);
                ordersList->addOrder(ord);
                //ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
            }
        }
    }
}

//Determines the number of armies to use in an attack/advance order.
//The number is a random number generated between 0 and the number of armies in a specific source territory
int Player::determineNArmiesForAttack(int randIndexSource)
{
    int randNOfArmies;
    //If deploy orders have not been executed yet, that means there are no armies in the territories right now.
    //To get the right number of armies we get it from the appropriate Deploy order if there is one.
    if(territories.at(randIndexSource)->getAmountOfArmies() == 0)
    {
        if(ordersList->getOrdList().size() > randIndexSource)
        {
            list<Order*>::iterator it = next(ordersList->getOrdList().begin(), randIndexSource);
            Deploy* deployOrder = dynamic_cast<Deploy*>((*it));
            if(deployOrder != NULL)
            {
                int nOfArmies = deployOrder->getNAddedArmies();
                //Generate random number between 1 and the number of armies from the source territory
                randNOfArmies = rand() % nOfArmies + 1;
            }
            else
            {
                randNOfArmies = 0;
            }
        }
        else
        {
            list<Order*>::iterator it = ordersList->getOrdList().begin();
            Deploy* deployOrder = dynamic_cast<Deploy*>((*it));
            if(deployOrder != NULL)
            {
                int nOfArmies = deployOrder->getNAddedArmies();
                //Generate random number between 1 and the number of armies from the source territory
                randNOfArmies = rand() % nOfArmies + 1;
            }
            else
            {
                randNOfArmies = 0;
            }
        }
    }
    else
    {
        randNOfArmies = rand() % territories.at(randIndexSource)->getAmountOfArmies() + 1;
    }
    return randNOfArmies;
}


//Required Methods

//Returns Territories which are adjacent and not the current player's territory
vector <Territory*> Player::toAttack()
{
    set<Territory*> uniqueTerritoriesToAttack;
    string adjTerritoryName;
    bool attackTerr;

    for(int i = 0; i < territories.size(); i++){
        if(!territories[i]->adjacentTerritories.empty()){
            for(int j = 0; j < territories[i]->adjacentTerritories.size(); j++){
                attackTerr = true;
                adjTerritoryName = territories[i]->adjacentTerritories[j]->getName();

                for(int k = 0; k < territories.size(); k++){
                    if(adjTerritoryName == territories[k]->getName()){
                        attackTerr = false;
                        break;
                    }
                }

                if(attackTerr){
                    //Set the target territory to be attacked
                    territories[i]->adjacentTerritories[j]->setAttackStatus(attackTerr);
                    uniqueTerritoriesToAttack.insert(territories[i]->adjacentTerritories[j]);
                }
            }
        }
    }
    vector<Territory*> territoriesToAttack(uniqueTerritoriesToAttack.begin(), uniqueTerritoriesToAttack.end());
    return territoriesToAttack;
}

//Returns territories owned by the player that are under attack.
//If no territories are under attack, return all territories owned by the player.
vector <Territory*> Player::toDefend()
{
    bool noTerritoriesUnderAttack = true;
    vector <Territory*> territoriesToDefend;

    for(int i = 0; i < territories.size(); i++)
    {
        if(territories.at(i)->isTerritoryUnderAttack())
        {
            noTerritoriesUnderAttack = false;
            territoriesToDefend.push_back(territories.at(i));
        }
    }

    if(!noTerritoriesUnderAttack)
    {
        return territoriesToDefend;
    }else
    {
        return this->territories;
    }
}

//Creates an order based on the armies in the player's reinforcement pool and the player's hand. Then places the order in the player's list of orders
void Player::issueOrder(Deck* deck, Player* enemyPlayer)
{
    srand (time(NULL));
    //Refers to the player having cards in their hand
    bool isHandEmpty = getHand()->getCards()->empty();
    bool* flagOrder;
    vector <Territory*> territoriesToAttack = toAttack();
    vector <Territory*> territoriesToDefend = toDefend();
    Order* ord;
    Order* defendAdvanceOrd;
    Order* attackAdvanceOrd;
    Card* card;
    //Generate random number indicating the random index to choose in the list of territories to attack/defend
    int randIndexAttack = rand() % territoriesToAttack.size();
    int randIndexDefend = rand() % territoriesToDefend.size();
    //Generate random number indicating the random index to choose in the player's territories
    int randIndexSource = rand() % territories.size();

    //Determine if player has more orders to issue.
    if(getPool() != 0 || !isHandEmpty)
    {
        flagOrder = new bool(true);
        setFlagIssueOrder(flagOrder);
    }
    else
    {
        flagOrder = new bool(false);
        setFlagIssueOrder(flagOrder);
    }

    //Create deploy orders if player has armies in its reinforcement pool
    if(getPool() != 0)
    {
        createDeployOrders(&territoriesToDefend, ord);
        cout << "Created Deploy Orders" << endl;
    }

    //Number of armies to use in an attack/advance order
    int randNOfArmies = determineNArmiesForAttack(randIndexSource);

    //If player has cards in his hand, select the first card to create an order
    //Then create Advance orders
    if(!isHandEmpty)
    {
        //Get the first card in the player's hand
        card = getHand()->getCards()->front();
        //Using play() to create the appropriate order based on the card type
        ord = card->play(deck, getHand(), territoriesToAttack.at(randIndexAttack), territoriesToDefend.at(randIndexDefend), randIndexSource, randNOfArmies, this, enemyPlayer);

        if(ord != NULL)
        {
            ordersList->addOrder(ord);
            //ordersList->move(ord, ordersList->getOrdList().size()); //Adding order to the end of the list
            cout << "Created a " << ord->getOrderType() << " order and placed it in the player's OrderList" << endl;
        }
        else
            cout<<"Order is Null\n";
        /*====Creating Advance orders====*/

        //Find the index of one of the territories returned by toDefend() in the player's territories vector
        string terrDefendName = territoriesToDefend.at(0)->getName();
        for (vector<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it)
        {
            if((*it)->getName() == terrDefendName)
            {
                auto index = distance(territories.begin(), it);
                randIndexSource = index;
            }
        }

        //Re-determine the number of armies to use in an attack/advance order
        randNOfArmies = determineNArmiesForAttack(randIndexSource);

        if(randNOfArmies != 0)
        {
            /*Create advance order to defend*/
            //If the territory to defend and the source territory are the same, then generate another random index which is not the same as randIndexDefend
            if(territoriesToDefend.at(randIndexDefend)->getName() == territories.at(randIndexSource)->getName())
            {
                int newRandIndex;

                /*do
                {
                    newRandIndex = rand() % territoriesToDefend.size();
                }
                while(randIndexDefend == newRandIndex);

                randIndexDefend = newRandIndex;*/
                defendAdvanceOrd = new Advance(territoriesToDefend.at(randIndexDefend), &territories, randNOfArmies, territories.at(randIndexSource));
            }
            else
            {
                defendAdvanceOrd = new Advance(territoriesToDefend.at(randIndexDefend), &territories, randNOfArmies, territories.at(randIndexSource));
            }
            //Adding order to the end of the list
            ordersList->addOrder(defendAdvanceOrd);
            //ordersList->move(defendAdvanceOrd, ordersList->getOrdList().size());
            cout << "Created a " << defendAdvanceOrd->getOrderType() << " order (to defend) and placed it in the player's OrderList" << endl;
        }
        else
        {
            defendAdvanceOrd = NULL;
            cout << "Cannot create advance order (to defend) - No armies in source territory " << territories.at(randIndexSource)->getName() << "\n" << endl;
        }

        //Create a new random Index
        randIndexSource = rand() % territories.size();
        //Re-determine the number of armies to use in an attack/advance order
        randNOfArmies = determineNArmiesForAttack(randIndexSource);
        if(randNOfArmies != 0)
        {
            /*Create advance order to attack*/
            attackAdvanceOrd = new Advance(territoriesToAttack.at(randIndexAttack), &territories, randNOfArmies, territoriesToDefend.at(randIndexDefend), territoriesToAttack.at(randIndexAttack)->getPlayer()->getPointerToTerritories(), flagConqTerr);
            ordersList->addOrder(attackAdvanceOrd);
            //ordersList->move(attackAdvanceOrd, ordersList->getOrdList().size());
            //Set the attack status to false on the territory where an attack order has been created
            territoriesToAttack.at(randIndexAttack)->setAttackStatus(false);
            cout << "Created a " << attackAdvanceOrd->getOrderType() << " order (to attack) and placed it in the player's OrderList\n" << endl;

        }
        else
        {
            attackAdvanceOrd = NULL;
            cout << "Cannot create advance order (to attack) - No armies in source territory " << territories.at(randIndexSource)->getName() << "\n" << endl;
        }

    }
    else
    {
        cout << "No more orders to issue\n" << endl;
    }

    cout << *this << endl;
}


