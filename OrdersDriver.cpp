#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <list>
#include "LoggingObserver.h"
using namespace std;

int main()
{
    //Sets up
    Order::setUpPlayerCannotAttackList();
    //Create test players
    Player* pl1 = new Player("Doug");
    Player* pl2 = new Player("Elsam");
    Player* pl3 = new Player("DougDoug");
    Player* neutralPlayer = new Player("NEUTRAL");
    //Create test territories
    Territory* terr1 = new Territory(1,2,4,1,4, pl1, "Quebec");
    Territory* terr2 = new Territory(2,1,3,1,3, pl1, "Vancouver");
    Territory* terr3 = new Territory(3,3,4,1,2, pl2, "Ottawa");
    Territory* terr4 = new Territory(4,6,7,1,4, pl2, "Montreal");
    Territory* terr5 = new Territory(5,5,5,1,2, pl2, "Winnipeg");
    Territory* terr6 = new Territory(6,2,3,1,1, pl3, "Gatineau");

    //Quebec is adjacent to Vancouver, Ottawa and Gatineau
    terr1->adjacentTerritories.push_back(terr2);
    terr1->adjacentTerritories.push_back(terr3);
    terr1->adjacentTerritories.push_back(terr6);

    //Vancouver is adjacent to Quebec and Ottawa
    terr2->adjacentTerritories.push_back(terr1);
    terr2->adjacentTerritories.push_back(terr3);

    //Ottawa is adjacent to Quebec, Vancouver and Montreal
    terr3->adjacentTerritories.push_back(terr1);
    terr3->adjacentTerritories.push_back(terr2);
    terr3->adjacentTerritories.push_back(terr4);

    //Montreal is adjacent to Vancouver and Winnipeg
    terr4->adjacentTerritories.push_back(terr3);
    terr4->adjacentTerritories.push_back(terr5);

    //Winnipeg is adjacent to Montreal
    terr5->adjacentTerritories.push_back(terr4);

    //Gatineau is adjacent to Quebec
    terr6->adjacentTerritories.push_back(terr1);

    //vectors of territories for each players
    vector<Territory*> pl1Territories;
    vector<Territory*> pl2Territories;
    vector<Territory*> pl3Territories;

    //Player Doug owns Quebec, Vancouver and Montreal
    pl1Territories.push_back(terr1);
    pl1Territories.push_back(terr2);
    pl2Territories.push_back(terr4);

    //Player Elsam owns Ottawa and Winnipeg
    pl2Territories.push_back(terr5);
    pl2Territories.push_back(terr3);

    //Player Dougdoug owns Gatineau
    pl3Territories.push_back(terr6);

    //Set the territories for pl1, pl2 and pl3
    pl1->setTerritories(pl1Territories);
    pl2->setTerritories(pl2Territories);
    pl3->setTerritories(pl3Territories);

    /*
    Deploy Order test
    Quebec will have 4 more armies
    */
    cout << "Player 1 does the deploy order" << endl;
    cout << *terr1 << endl;
    Deploy* depl1 = new Deploy(terr1, &pl1Territories, 4);
    depl1->execute();
    cout << *terr1 << endl;

    /*
    Advance order test 1
    This Advance moves 1 army to Quebec from Vancouver.
    Quebec has 1 more army and Vancouver has 1 less.
    */
    cout << "Player 1 does the Advance order on an allied territory" << endl;
    cout << *terr2 << endl;
    Advance* adv1 = new Advance(terr1, &pl1Territories, 1, terr2,
                                 terr2->getPlayer()->getPointerToTerritories(), new bool(false));
    adv1->execute();
    cout << *terr2 << endl;
    cout << *terr1 << endl;

    /*
    Advance order test 2
    This is an attack of 8 armies from Quebec to Gatineau.
    If there is a conquest, then Gatineau gets removed from the DougDoug list of territories and
    gets added to Doug's list of territories. Gatineau gets the remaining attacking armies and Quebec loses
    them.
    */
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
    /*
    Bomb order test
    This reduces by half the amount of armies in Ottawa.
    */
    cout << *terr3 << endl;
    Bomb* bomb1 = new Bomb(terr3, pl1->getPointerToTerritories());
    bomb1->execute();
    cout << *terr3 << endl;

    /*
    Blockade order test
    This triples the amount of armies in Winnipeg, but it is now owned by the neutral Player instead.
    */
    cout << "Player 2's territories: " << endl;
    for (vector<Territory*>:: iterator it = pl2->getPointerToTerritories()->begin(); it != pl2->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ", ";
    }
    cout << endl;

    Blockade* block1 = new Blockade(terr5, pl2->getPointerToTerritories(), neutralPlayer);
    block1->execute();
    cout << *terr5 <<  endl;
    cout << "Player 2's territories: " << endl;
    for (vector<Territory*>:: iterator it = pl2->getPointerToTerritories()->begin(); it != pl2->getPointerToTerritories()->end(); ++it)
    {
        cout << **it << ", ";
    }
    cout << endl;

    /*
    Testing AirLift order
    This moves 5 armies from Gatineau to Vancouver, 2 territories not adjacent to one and another
    and are owned by player Doug
    */
    cout << *terr2 << endl;
    cout << *terr6 << endl;
    Airlift* airL1 = new Airlift(terr2, pl1->getPointerToTerritories(), 5, terr6);
    airL1->execute();
    cout << *terr2 << endl;
    cout << *terr6 << endl;

    /*
    Testing Negotiate order
    Sets up a truce between player Doug and player Elsam.
    */
    Negotiate* negotiate1 = new Negotiate(pl1,pl2);
    negotiate1->execute();
    /*
    Advance order test3
    This attack will fail because player Doug is attacking a territory
    owned by Elsam while they are under negotiations
    */
    Advance* adv3 = new Advance(terr3, pl1->getPointerToTerritories(), 1, terr2, terr3->getPlayer()->getPointerToTerritories(), new bool(false));
    adv3->execute();

    /*
    After clearing the playersCannotAttackList, the player Doug will be able to attack player Elsam's territories
    */
    Order::clearPlayerCannotAttackList();
    adv3->execute();

    Order::deletePlayerCannotAttackList();

    delete depl1;
    delete adv1;
    delete adv2;
    delete adv3;
    delete bomb1;
    delete block1;
    delete airL1;
    delete negotiate1;

    delete terr1;
    delete terr2;
    delete terr3;
    delete terr4;
    delete terr5;
    delete terr6;
    delete pl1;
    delete pl2;
    delete pl3;
    delete neutralPlayer;
    LogObserver::output.close();
}
