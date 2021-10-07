#include <iostream>
#include <vector>
#include <list>
#include "Player.h"


using namespace std;

int main()
{
    vector<Territory*> allTerritories;
    vector<Player*> allPlayers;
    vector<Card*> cards;

    //Creating test territories and test players
    Territory terr1(2,"Joe");
    allTerritories.push_back(&terr1);
    Territory terr2(4,"Bojoe");
    allTerritories.push_back(&terr2);
    Territory terr3(3,"Lorem");
    allTerritories.push_back(&terr3);
    Territory terr4(5,"Ipsum");
    allTerritories.push_back(&terr4);
    Territory terr5(7,"fifth");
    allTerritories.push_back(&terr5);

    Player pl1("Elsam");
    allPlayers.push_back(&pl1);
    Player pl2("Doug");
    allPlayers.push_back(&pl2);

    //Creating adjacency lists
    terr1.addEdges(&terr2);
    terr1.addEdges(&terr3);
    terr2.addEdges(&terr1);
    terr2.addEdges(&terr4);
    terr3.addEdges(&terr1);
    terr3.addEdges(&terr4);
    terr4.addEdges(&terr2);
    terr4.addEdges(&terr3);

    //Creating cards adding them to the player's hand
    Card card1;
    cards.push_back(&card1);
    Card card2;
    cards.push_back(&card2);
    Card card3;
    cards.push_back(&card3);
    Card card4;
    cards.push_back(&card4);

    Hand playerHand(cards);
    pl1.setHand(&playerHand);

    //Splitting all territories between players into almost equal parts depending on the number of players
    setPlayersTerritories(allTerritories, allPlayers, Player::getPlayerCount());

    vector<Territory*> pl1Territories = pl1.getTerritories();

    //Creating some orders and adding them to the players list of orders
    Order* depl = new Deploy(&terr1, &pl1Territories, 3);
    Order* adv = new Advance(&terr2, &pl1Territories, 3, &terr1);
    Order* block = new Blockade(&terr3, &pl1Territories);

    OrdersList oLs;
    oLs.move(depl,0);
    oLs.move(adv,0);
    oLs.move(block,2);

    pl1.setOrderList(&oLs);

    cout << endl;
    cout << pl1;

    //Testing toDefend() method
    cout << "Testing toDefend(): " << endl;
    for(auto x:pl1.toDefend()){
        cout << *x << endl;
    }

    //Testing toAttack() method
    cout << "\nTesting toAttack(): " << endl;
    for(auto x:pl1.toAttack()){
        cout << *x << endl;
    }

    //Testing issueOrder() method
    cout << "\nTesting issueOrder(): " << endl;
    pl1.issueOrder("Deploy", &terr1, 1);
    pl1.issueOrder("Advance", &terr2, 2, &terr1);
    pl1.issueOrder("Airlift", &terr2, 2, &terr1);
    pl1.issueOrder("Bomb", &terr3);
    pl1.issueOrder("Blockade", &terr3);
    pl1.issueOrder("Negotiate", &pl2);
    cout << pl1 << endl;

    delete depl;
    delete adv;
    delete block;
    depl = NULL;
    adv = NULL;
    block = NULL;

    return 0;

}
