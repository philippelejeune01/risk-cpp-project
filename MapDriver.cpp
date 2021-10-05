#include "Map.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    MapLoader m("solar.map");
    Map* test = new Map(m.Load());
    cout<<*test;
    test->validate();

    cout<<endl;

    MapLoader m2("europe.map");
    Map* test2 = new Map(m2.Load());
    cout<<*test2;
    test2->validate();

    delete(test);
    delete(test2);

    return 0;
}
