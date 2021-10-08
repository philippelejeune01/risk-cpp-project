#include "Orders.h"
#include <iostream>
#include <list>
using namespace std;
int main(){
    //Creating test territories and test players
    Territory terr1(2,"Joe");
    Territory terr2(4,"Bojoe");
    Territory terr3(3,"Lorem");
    Territory terr4(5,"Ipsum");
    Player pl1("Elsam");
    Player pl2("Doug");
    //Creating adjacency lists
    terr1.addEdges(&terr2);
    terr1.addEdges(&terr3);
    terr2.addEdges(&terr1);
    terr2.addEdges(&terr4);
    terr3.addEdges(&terr1);
    terr3.addEdges(&terr4);
    terr4.addEdges(&terr2);
    terr4.addEdges(&terr3);
    //Creating a list of pointers to territories
    list<Territory*> p1;
    p1.push_front(&terr1);

    //Creating Deploy objects and testing the execute method
    //Valid deploy
    Deploy* depl1 = new Deploy(&terr1,&p1,3);
    cout << *depl1 << endl;
    depl1->execute();
    //Invalid deploy
    Deploy* depl2 = new Deploy(&terr2,&p1,3);
    cout << *depl2 << endl;
    depl2->execute();
    //Valid deploy created from copy constructor
    Deploy* depl3 = new Deploy(*depl1);
    cout << *depl3 << endl;
    depl3->execute();
    cout << "\n";
    delete depl1;
    delete depl2;
    delete depl3;
    depl1 = NULL;
    depl2 = NULL;
    depl3 = NULL;
    //Creating Advance objects and testing execute method
    //Valid advance
    Advance* adv1 = new Advance(&terr2, &p1,1, &terr1);
    cout << *adv1 << endl;
    adv1->execute();
    //Invalid advance. the source terr
    Advance* adv2 = new Advance(&terr1, &p1,1, &terr2);
    cout << *adv2 << endl;
    adv2->execute();
    //Copy Constructor Sowcase
    Advance* adv3 = new Advance(*adv1);
    cout << *adv3 << endl;
    adv3->execute();
    cout << "\n";
    delete adv1;
    delete adv2;
    delete adv3;
    adv1 = NULL;
    adv2 = NULL;
    adv3 = NULL;
    //Creating Bomb objects and testing execute method
    //Valid Bomb
    Bomb* bomb1 = new Bomb(&terr2, &p1);
    cout << *bomb1 << endl;
    bomb1->execute();
    //Unvalid Bomb: Cannot bomb your own territory
    Bomb* bomb2 = new Bomb(&terr1, &p1);
    cout << *bomb2 << endl;
    bomb2->execute();
    //Copy Constructor Showcase
    Bomb* bomb3 = new Bomb(*bomb1);
    cout << *bomb3 << endl;
    bomb3->execute();
    cout << "\n";
    delete bomb1;
    delete bomb2;
    delete bomb3;
    bomb1 = NULL;
    bomb2 = NULL;
    bomb3 = NULL;

    //Creating Blockade objects and testing the execute method
    //Valid Blockade
    Blockade* block1 = new Blockade(&terr1, &p1);
    cout << *block1 << endl;
    block1->execute();
    //Invald Blockade
    Blockade* block2 = new Blockade(&terr2, &p1);
    cout << *block2 << endl;
    block2->execute();
    //Copy Constructor showcase
    Blockade* block3 = new Blockade(*block1);
    cout << *block1 << endl;
    block1->execute();
    cout << "\n";
    delete block1;
    delete block2;
    delete block3;
    block1 = NULL;
    block2 = NULL;
    block3 = NULL;
    //Creating Airlift objects and testing the execute method
    //Valid Airlift
    Airlift* airLi1 = new Airlift(&terr2, &p1,1, &terr1);
    cout << *airLi1 << endl;
    airLi1->execute();
    //Invalid Airlift
    Airlift* airLi2 = new Airlift(&terr1, &p1,1, &terr2);
    cout << *airLi2 << endl;
    airLi2->execute();
    //Copy Constructor
    Airlift* airLi3 = new Airlift(*airLi1);
    cout << *airLi3 << endl;
    airLi3->execute();
    cout << "\n";
    delete airLi1;
    delete airLi2;
    delete airLi3;
    airLi1 = NULL;
    airLi2 = NULL;
    airLi3 = NULL;

    //Creating Negotiate objects and testing the execute method
    //Valid Negotiate
    Negotiate* negotiate1 = new Negotiate(&pl1,&pl2);
    cout << *negotiate1 << endl;
    negotiate1->execute();
    //Invalid Negotiate
    Negotiate* negotiate2 = new Negotiate(&pl1,&pl1);
    cout << *negotiate2 << endl;
    negotiate2->execute();
    //Copy Constructor Showcase
    Negotiate* negotiate3 = new Negotiate(*negotiate1);
    cout << *negotiate3 << endl;
    negotiate3->execute();
    cout << "\n";
    delete negotiate1;
    delete negotiate2;
    delete negotiate3;
    negotiate1 = NULL;
    negotiate2 = NULL;
    negotiate3 = NULL;

    //Creating test objects for OrdersList
    Deploy* depl = new Deploy(&terr1, &p1, 3);
    Advance* adv = new Advance(&terr2, &p1, 3, &terr1);
    Bomb* bomb = new Bomb(&terr2, &p1);
    Blockade* block = new Blockade(&terr3, &p1);
    Airlift* airLi = new Airlift(&terr4, &p1, 3, &terr3);
    Negotiate* negotiate = new Negotiate(&pl1,&pl2);

    //Testing OrdersList
    OrdersList oLs;
    //Valid move
    oLs.move(depl,0);
    oLs.move(adv,0);
    oLs.move(block,2);
    cout << oLs << endl;

    //Valid remove
    oLs.remove(1);
    cout << oLs << endl;

    //Valid move
    oLs.move(bomb,1);
    oLs.move(airLi,2);
    oLs.move(negotiate,1);

    //Invalid move and remove
    oLs.move(depl,9);
    oLs.remove(8);
    cout << oLs << endl;
    //Copy constructor showcase
    OrdersList oLs2(oLs);
    cout << "This is the copy constructor: " << oLs2 << endl;

    return 0;
}
