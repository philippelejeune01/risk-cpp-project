#include "Orders.h"
#include <iostream>
#include <list>
using namespace std;
int main(){
    //Creating test territories
    Territory terr1(2);
    Territory terr2(4);
    Territory terr3(3);
    Territory terr4(5);

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

    //Creates Deploy objects
    Deploy* depl1 = new Deploy(&terr1,&p1,3);
    Deploy* depl2 = new Deploy(&terr2,&p1,3);

    //Test the move and remove functions
    OrdersList oList;
    oList.move(depl1,0);
    oList.move(depl2,0);
    oList.move(depl1,0);
    oList.remove(depl2);
    oList.move(depl2,0);

    //Test the execute method
    depl1-> execute();
    depl2-> execute();
return 0;
}
