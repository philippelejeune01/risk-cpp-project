#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <list>
using namespace std;

int main()
{
    Order::setUpPlayerCannotAttackList();
    Player* pl1 = new Player("Doug");
    Player* pl2 = new Player("Elsam");
    Player* pl3 = new Player("DougDoug");
    Territory* terr1 = new Territory(1,2,4,1,4, pl1, "Quebec");
    Territory* terr2 = new Territory(2,1,3,1,3, pl1, "Vancouver");
    Territory* terr3 = new Territory(3,3,4,1,2, pl2, "Ottawa");
    Territory* terr4 = new Territory(4,6,7,1,4, pl2, "Montreal");
    Territory* terr5 = new Territory(5,5,5,1,2, pl2, "Winnipeg");
    Territory* terr6 = new Territory(6,2,3,1,1, pl3, "Gatineau");

    terr1->adjacentTerritories.push_back(terr2);
    terr1->adjacentTerritories.push_back(terr3);
    terr1->adjacentTerritories.push_back(terr6);

    terr2->adjacentTerritories.push_back(terr1);
    terr2->adjacentTerritories.push_back(terr3);

    terr3->adjacentTerritories.push_back(terr1);
    terr3->adjacentTerritories.push_back(terr2);
    terr3->adjacentTerritories.push_back(terr4);

    terr4->adjacentTerritories.push_back(terr3);
    terr4->adjacentTerritories.push_back(terr5);

    terr5->adjacentTerritories.push_back(terr4);
    terr6->adjacentTerritories.push_back(terr1);

    vector<Territory*> pl1Territories;
    vector<Territory*> pl2Territories;
    vector<Territory*> pl3Territories;

    pl1Territories.push_back(terr1);
    pl1Territories.push_back(terr2);
    pl2Territories.push_back(terr4);
    pl2Territories.push_back(terr5);
    pl2Territories.push_back(terr3);
    pl3Territories.push_back(terr6);

    pl1->setTerritories(pl1Territories);
    pl2->setTerritories(pl2Territories);
    pl3->setTerritories(pl3Territories);

    //Deploy Order test
    cout << "Player 1 does the deploy order" << endl;
    cout << *terr1 << endl;
    Deploy* depl1 = new Deploy(terr1, &pl1Territories, 4);
    depl1->execute();
    cout << *terr1 << endl;

    //Advance order test 1
    cout << "Player 1 does the Advance order on an allied territory" << endl;
    cout << *terr2 << endl;
    Advance* adv1 = new Advance(terr1, &pl1Territories, 1, terr2,
                                 terr2->getPlayer()->getPointerToTerritories(), new bool(false));
    adv1->execute();
    cout << *terr2 << endl;
    cout << *terr1 << endl;

    //Advance order test 2
    cout << "Player 1 does the Advance order on an enemy territory" << endl;
    cout << "Player 1's territories:" << endl;
    for (vector<Territory*>::iterator it = pl1->getPointerToTerritories()->begin(); it != pl1->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ",";
    }
    cout << endl;
    cout << "Player 3's territories:" << endl;
    for (vector<Territory*>::iterator it = pl3->getPointerToTerritories()->begin(); it != pl3->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ",";
    }
    cout << endl;
    Advance* adv2 = new Advance(terr6, pl1->getPointerToTerritories(), 8,
                                terr1, terr6->getPlayer()->getPointerToTerritories(), new bool(false));
    adv2->execute();
    cout << *terr6 << endl;
    cout << *terr1 << endl;

        for (vector<Territory*>::iterator it = pl1->getPointerToTerritories()->begin(); it != pl1->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ",";
    }
    cout << endl;
    cout << "Player 3's territories:" << endl;
    for (vector<Territory*>::iterator it = pl3->getPointerToTerritories()->begin(); it != pl3->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ",";
    }
    cout << endl;
    //Bomb order test
    cout << *terr3 << endl;
    Bomb* bomb1 = new Bomb(terr3, pl1->getPointerToTerritories());
    bomb1->execute();
    cout << *terr3 << endl;

    //Blockade order test
    cout << "Player 2's territories: " << endl;
    for (vector<Territory*>:: iterator it = pl2->getPointerToTerritories()->begin(); it != pl2->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ", ";
    }
    cout << endl;

    Blockade* block1 = new Blockade(terr5, pl2->getPointerToTerritories(), new Player("NEUTRAL"));
    block1->execute();
    cout << *terr5 << endl;
    cout << "Player 2's territories: " << endl;
    for (vector<Territory*>:: iterator it = pl2->getPointerToTerritories()->begin(); it != pl2->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ", ";
    }
    cout << endl;

    //Testing AirLift order
    cout << *terr2 << endl;
    cout << *terr6 << endl;
    Airlift* airL1 = new Airlift(terr2, pl1->getPointerToTerritories(), 6, terr6);
    airL1->execute();
    cout << *terr2 << endl;
    cout << *terr6 << endl;

    //Testing Negotiate order
    Negotiate* negotiate1 = new Negotiate(pl1,pl2);
    negotiate1->execute();
    //Advance order test3
    Advance* adv3 = new Advance(terr3, pl1->getPointerToTerritories(), 1, terr2, terr3->getPlayer()->getPointerToTerritories(), new bool(false));
    adv3->execute();

    Order::clearPlayerCannotAttackList();
    adv3->execute();

    negotiate1->execute();
    adv3->execute();

    delete depl1;
    delete adv1;
    delete adv2;
    delete adv3;
    delete bomb1;
    delete block1;
    delete airL1;
    delete negotiate1;
    delete pl1;
    delete pl2;
    delete terr1;
    delete terr2;
    delete terr3;
    delete terr4;
    delete terr5;
    delete terr6;
}
